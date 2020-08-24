//L298 motor driver commands 

void writeMotorCommands(){

  MotorCommandLastSent = millis();

  //convert speed in m/s to estimated PWM value
  pwmLeftMotorSpeed = min(((cmdLeftMotorSpeed/maxMotorSpeed) * 255), 255);
  pwmRightMotorSpeed = min(((cmdRightMotorSpeed/maxMotorSpeed) * 255), 255);

  //move motors if battery if good
  if(!lowBattery){
    //left motor speed set based on direction
    if(leftMotorDirection == 1){//forward
      analogWrite(LEFTMOTOR_A, pwmLeftMotorSpeed);
      digitalWrite(LEFTMOTOR_B, LOW);
    }
    else if(leftMotorDirection == 0){//reverse
      analogWrite(LEFTMOTOR_B, abs(pwmLeftMotorSpeed));
      digitalWrite(LEFTMOTOR_A, LOW);
    }
  
    //right motor speed set based on direction
    if(rightMotorDirection == 1){//forward
      analogWrite(RIGHTMOTOR_A, pwmRightMotorSpeed);
      digitalWrite(RIGHTMOTOR_B, LOW);
    }
    else if(rightMotorDirection == 0){//reverse
      analogWrite(RIGHTMOTOR_B, abs(pwmRightMotorSpeed));
      digitalWrite(RIGHTMOTOR_A, LOW);
    } 
  }
  else{
    //stop motors if battery is low
    analogWrite(LEFTMOTOR_B, 0);
    digitalWrite(LEFTMOTOR_A, LOW);
    analogWrite(RIGHTMOTOR_B, 0);
    digitalWrite(RIGHTMOTOR_A, LOW);
  }
}
