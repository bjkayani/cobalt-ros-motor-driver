//main loop function

void loop() {
  //get current time
  long currentTime = millis();

  //compute new PID values
  left_PID.Compute();
  right_PID.Compute();

  serialHandler();
  
  if ((currentTime - LastDebug) >= DEBUGOUTPUTRATE)
  {
    debugDump();
  }

  if ((currentTime - ControlLoopLastTime) >= CONTROLLOOPRATE)
  {
    controlLoop();
  }

  if ((currentTime - MotorCommandLastSent) >= MOTORCOMMANDLOOPRATE)
  {
    writeMotorCommands();
  } 

  if ((currentTime - LedRefreshLastTime) >= LEDREFRESHRATE)
  {
    ledRefresh();
  }
}
