//Function to measure battery voltage

void batteryMeasure(){
  
  batteryVoltage = batteryConstant * analogRead(BATTSENS) * (5.0 / 1023.0);
  batteryStateMsg.voltage = batteryVoltage;

  if(batteryVoltage <= minBatteryVoltage){
    lowBattery = true;
    digitalWrite(LEDPIN, HIGH);
  }
  else if(batteryVoltage > minBatteryVoltage){
    lowBattery = false;
    digitalWrite(LEDPIN, LOW);
  }
  
}
