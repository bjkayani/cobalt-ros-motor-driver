#!/usr/bin/env python

import rospy
from geometry_msgs.msg import Twist
from std_msgs.msg import String
import serial
import time
import tf
from geometry_msgs.msg import Vector3
from geometry_msgs.msg import Point
from nav_msgs.msg import Odometry

class driver:
    def __init__(self):
        rospy.init_node('cobalt_motor_driver', anonymous=True)

        self.param = {}	
        self.param["odom_topic"] = rospy.get_param("~odom_topic", 'odom')
        self.param["baseId"] = rospy.get_param('~base_id', 'base_link')
        self.param["odomId"] = rospy.get_param('~odom_id', 'odom')
        self.param["device_port"] = rospy.get_param('~port', '/dev/ttyAMA0')
        self.param["baudrate"] = int(rospy.get_param('~baudrate', '115200'))
        self.param["debug"] = bool(rospy.get_param('~debug', False))
        rospy.set_param("cobalt_motor_driver", self.param)
        
        rospy.loginfo("Cobalt motor driver starting...")
    
        rospy.Subscriber('/cmd_vel', Twist, self.send_cmd_vel)
        rospy.Subscriber('/camera_angle', String, self.send_camera_angle)
        
        self.odom_pub = rospy.Publisher("odom", Odometry, queue_size=10)
        self.rate = rospy.Rate(10)

        self.odom = Odometry()
        self.odom.header.seq = 0
        self.odom.header.frame_id = self.param["odomId"]
        self.odom.child_frame_id = self.param["baseId"]
        for i in range(36):
        	self.odom.pose.covariance[i] = 0
        	self.odom.twist.covariance[i] = 0
        self.odom.twist.covariance[0] = 1.0
        self.odom.twist.covariance[35] = 1.0

        try:
            rospy.loginfo("Opening serial port: "+self.param["device_port"])
            self.serial = serial.Serial(self.param["device_port"], self.param["baudrate"])
        except Exception:
            rospy.logerr("Failed to open serial port")
            raise
            return

        self.get_arduino_message()


    def send_camera_angle(self, data):
        angle = data.data
        angleMsg = str(angle)+"\n"
        self.serial.write(angleMsg)

    # send linear velocity and angular velocity to the motor controler 
    def send_cmd_vel(self, data):
        v = data.linear.x
        w = data.angular.z
        vMsg = "v"+str(v)+"\n"
        wMsg = "w"+str(w)+"\n"
        self.serial.write(vMsg)
        time.sleep(0.01)
        self.serial.write(wMsg)

    def get_arduino_message(self):
        while not rospy.is_shutdown():
            self.serial.write("o\n")
            self.publish_odom(self.serial.readline())
            self.rate.sleep()

    def publish_odom(self, odom_string):
        # extracting position data from string and converting to float
        seq = float(odom_string[odom_string.find("t")+1:odom_string.find("s")])
        time = float(odom_string[odom_string.find("s")+1:odom_string.find("x")])
        x = float(odom_string[odom_string.find("x")+1:odom_string.find("y")])
        y = float(odom_string[odom_string.find("y")+1:odom_string.find("th")])
        th = float(odom_string[odom_string.find("th")+2:odom_string.find("v")])
        v_x = float(odom_string[odom_string.find("v")+1:odom_string.find("w")])
        v_th = float(odom_string[odom_string.find("w")+1:])

        if(self.param["debug"]): 
            rospy.loginfo("Odometry: x"+str(x)+" y"+str(y)+" th"+str(th) +" v_x"+str(v_x)+" v_th"+str(v_th))
        
        # creating and populating Odometry message
        self.odom.header.seq = seq
        self.odom.header.stamp = time
        self.odom.pose.pose.position = Point(x, y, 0.0)
        quat = tf.transformations.quaternion_from_euler(0, 0, th)
        self.odom.pose.pose.orientation.x = quat[0]
        self.odom.pose.pose.orientation.y = quat[1]
        self.odom.pose.pose.orientation.z = quat[2]
        self.odom.pose.pose.orientation.w = quat[3]
        self.odom.twist.twist.linear = Vector3(v_x, 0.0, 0.0)
        self.odom.twist.twist.angular = Vector3(0.0, 0.0, v_th)
        
        # publishing odometry message
        self.odom_pub.publish(self.odom)

if __name__ == '__main__':
    try:
        d = driver()
    except rospy.ROSInterruptException: 
        pass