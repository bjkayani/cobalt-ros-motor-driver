//debugging function

void debugDump(){
  LastDebug = millis();

  if(debug){
    Serial.println("-------------------------------------------");
    Serial.println("EncoderCount is:   Left: "+String(leftEncoderPos)+     "   Right: "+String(rightEncoderPos));
    Serial.println("ActualSpeed is:    Left: "+String(obsLeftMotorSpeed)+  "   Right: "+String(obsRightMotorSpeed));
    Serial.println("IK is:             Left: "+String(desLeftMotorSpeed)+  "   Right: "+String(desRightMotorSpeed));
    Serial.println("ActualCommand is:  Left: "+String(cmdLeftMotorSpeed)+  "   Right: "+String(cmdRightMotorSpeed));
    Serial.println("PWM Command is:    Left: "+String(pwmLeftMotorSpeed)+  "   Right: "+String(pwmRightMotorSpeed));
    Serial.println("Motor Directions:  Left: "+String(leftMotorDirection)+  "   Right: "+String(rightMotorDirection));
    Serial.println("Battery Voltage:   "+String(batteryVoltage));
  }
}
