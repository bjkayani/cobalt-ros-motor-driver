//main loop function

void loop() {
  //get current time
  long currentTime = millis();

  //compute new PID values
  left_PID.Compute();
  right_PID.Compute();

  //ROS spin function
  nh.spinOnce();

  
  if ((currentTime - LastDebug) >= DEBUGOUTPUTRATE)
  {
    debugDump();
    batteryState.publish(&batteryStateMsg);
  }

  if ((currentTime - ControlLoopLastTime) >= CONTROLLOOPRATE)
  {
    controlLoop();
  }

  if ((currentTime - MotorCommandLastSent) >= MOTORCOMMANDLOOPRATE)
  {
    writeMotorCommands();
  } 
  
}
