void inverseKinematics(float linearVelocity,float angularVelocity){

  //calculating desired motor speeds from linear and angular velocity
  desLeftMotorSpeed = linearVelocity - angularVelocity * WheelSpacing / 2.0;
  desRightMotorSpeed = linearVelocity + angularVelocity * WheelSpacing / 2.0;
  
}
