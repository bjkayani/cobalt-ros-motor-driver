//Function to change position of the servo angle 

void cameraServoSet(int servoAngle){

  servoAngle = map(servoAngle, 0, 180, 1000, 2000);
  cameraServo.write(servoAngle);
  cameraServoPosition = servoAngle;

}
