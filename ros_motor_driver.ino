#include <PID.h>
#include <ServoTimer2.h> 
#include <ros.h>
#include <geometry_msgs/Twist.h>
#include <sensor_msgs/BatteryState.h>
#include <std_msgs/UInt16.h>

//====================LED Indicator====================

#define LEDPIN 13

//====================Camera Servo====================

ServoTimer2 cameraServo; 
#define CAMERA_SERVO 11
int cameraServoPosition;
int cameraServoRest = 120;

//====================Battery Voltage====================

float batteryVoltage;
//float batteryConstant = 2.0;
float minBatteryVoltage = 6.0;
bool lowBattery = false;
#define BATTSENS 5

//====================Debug====================

bool debug = true;

//====================Pin Definitions====================

#define LEFTMOTOR_A 10
#define LEFTMOTOR_B 9
#define RIGHTMOTOR_A 6
#define RIGHTMOTOR_B 5

#define LEFTENCODER_A 3
#define LEFTENCODER_B 7
#define RIGHTENCODER_A 2
#define RIGHTENCODER_B 4

//====================Inverse Kinematics====================

float WheelSpacing = 0.125; //wheel spacing in meters
float WheelDiameter = 0.0795; //wheel diameter in meters
float wheelCircMult = 0.81;
float WheelCirumference = WheelDiameter * 3.1416 * wheelCircMult; //wheel circumference

//====================Encoder====================

int EncoderTicksPerRev = 16;
int MotorRevsPerWheelRev = 120;

volatile long leftEncoderPos = 0;
volatile long rightEncoderPos = 0;

volatile boolean leftAset = false;
volatile boolean leftBset = false;
volatile boolean rightAset = false;
volatile boolean rightBset = false;

long lastLeftPos = 0;
long lastRightPos = 0;
long lastEncoderTime = 0;

float leftDist = 0.0;
float rightDist = 0.0;

//====================Global Velocity====================

//desired motor speed in m/s
double desLeftMotorSpeed;
double desRightMotorSpeed;

//commanded motor speed in m/s
double cmdLeftMotorSpeed;
double cmdRightMotorSpeed;

//robot velocity from ROS
double autoLinearVelocity; //in m/s
double autoAngularVelocity; //in rad/s

double mesLinearVelocity; //in m/s
double mesAngularVelocity; //in rad/s

//motor directions (1 - forward) (0 - reverse)
int leftMotorDirection; 
int rightMotorDirection;

//motor pwm speed values
//float pwmLeftMotorSpeed;
//float pwmRightMotorSpeed;

//measured motor speeds
double obsLeftMotorSpeed;
double obsRightMotorSpeed;

//maximum motor speed
float maxMotorSpeed = 0.5;

float x = 0.0;
float y = 0.0;
float theta = 0.0;

//====================Loop Timing====================

long LastDebug = 0;
long ControlLoopLastTime = 0;
long MotorCommandLastSent = 0;

#define DEBUGOUTPUTRATE 500
#define CONTROLLOOPRATE 20
#define MOTORCOMMANDLOOPRATE 20

//====================PID Stuff====================

float Kp = 3.0; //proportional
float Ki = 0.0; //integral
float Kd = 0.0; //derivative 

PID left_PID(&obsLeftMotorSpeed, &cmdLeftMotorSpeed, &desLeftMotorSpeed, Kp, Ki, Kd, DIRECT);
PID right_PID(&obsRightMotorSpeed, &cmdRightMotorSpeed, &desRightMotorSpeed, Kp, Ki, Kd, DIRECT);

//====================ROS Stuff====================

ros::NodeHandle nh;
sensor_msgs::BatteryState batteryStateMsg;

void autoPopulateSpeed(const geometry_msgs::Twist & msg){
    autoLinearVelocity = msg.linear.x;
    autoAngularVelocity = msg.angular.z;
}

void cameraServoCallback(const std_msgs::UInt16 & msg){
   cameraServoSet(msg.data);
}

ros::Subscriber<geometry_msgs::Twist> velSubscriber("cmd_vel",&autoPopulateSpeed);
ros::Subscriber<std_msgs::UInt16> cameraServoSubscriber("camera_servo", &cameraServoCallback);
ros::Publisher batteryState("battery_state", &batteryStateMsg);
