
void controlLoop(){
    ControlLoopLastTime = millis();
    
    actualObsSpeed();
    inverseKinematics(autoLinearVelocity, autoAngularVelocity);
    batteryMeasure();
}
