//actual speed calculation based on encoder values

void actualObsSpeed(){

    //current encoder tick values
    long currentLeftPos = leftEncoderPos;
    long currentRightPos = rightEncoderPos;

    //current time
    long currentTime =  millis();

    //speed calculation using encoder ticks, robot parameters and time
    //speed = distance / time
    float addedLeftDist = ((currentLeftPos-lastLeftPos)*WheelCirumference/(EncoderTicksPerRev*MotorRevsPerWheelRev));
    float addedRightDist = ((currentRightPos-lastRightPos)*WheelCirumference/(EncoderTicksPerRev*MotorRevsPerWheelRev));
    obsLeftMotorSpeed = addedLeftDist * 1000.0/(currentTime-lastEncoderTime);
    obsRightMotorSpeed = addedRightDist * 1000.0/(currentTime-lastEncoderTime);

    float dist = (addedLeftDist + addedRightDist) / 2.0;
    float d_theta;
     
    if(abs(obsLeftMotorSpeed - obsRightMotorSpeed) < 0.001){
      d_theta = 0.0;
      x += dist * cos(theta);
      y += dist * sin(theta);
    }
    else{
      d_theta = (addedRightDist - addedLeftDist) / WheelSpacing;
      float r = dist / d_theta;
      x += r * (sin(d_theta + theta) - sin(theta));
      y -= r * (cos(d_theta + theta) - cos(theta));
      theta = theta + d_theta;
    }

    mesLinearVelocity = dist * 1000/ (currentTime-lastEncoderTime);
    mesAngularVelocity = d_theta * 1000/ (currentTime-lastEncoderTime);
    
    leftDist += addedLeftDist;
    rightDist += addedRightDist;

    //storing encoder states and time for next calculation
    lastLeftPos = currentLeftPos;
    lastRightPos = currentRightPos;
    lastEncoderTime = currentTime;

    //determining motor directions
    leftMotorDirection = (cmdLeftMotorSpeed >= 0) ? 1 : 0;
    rightMotorDirection = (cmdRightMotorSpeed >= 0) ? 1 : 0;
     
}
