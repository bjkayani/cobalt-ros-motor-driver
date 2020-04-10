//actual speed calculation based on encoder values

void actualObsSpeed(){

    //current encoder tick values
    long currentLeftPos = leftEncoderPos;
    long currentRightPos = rightEncoderPos;

    //current time
    long currentTime =  millis();

    //speed calculation using encoder ticks, robot parameters and time
    //speed = distance / time
    obsLeftMotorSpeed = ((currentLeftPos-lastLeftPos)*1000.0/(EncoderTicksPerRev*MotorRevsPerWheelRev*WheelCirumference))/(currentTime-lastEncoderTime);
    obsRightMotorSpeed = ((currentRightPos-lastRightPos)*1000.0/(EncoderTicksPerRev*MotorRevsPerWheelRev*WheelCirumference))/(currentTime-lastEncoderTime);

    //storing encoder states and time for next calculation
    lastLeftPos = currentLeftPos;
    lastRightPos = currentRightPos;
    lastEncoderTime = currentTime;

    //determining motor directions
    leftMotorDirection = (cmdLeftMotorSpeed >= 0) ? 1 : 0;
    rightMotorDirection = (cmdRightMotorSpeed >= 0) ? 1 : 0;
}
