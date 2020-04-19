//Function to measure battery voltage

void batteryMeasure(){
  
  batteryConstant = 2.0;
  batteryVoltage = batteryConstant * analogRead(BATTSENS) * (5.0 / 1023.0);

  if(batteryVoltage <= minBatteryVoltage){
    lowBattery = true;
    digitalWrite(LEDPIN, HIGH);
  }
  else if(batteryVoltage > minBatteryVoltage){
    lowBattery = false;
    digitalWrite(LEDPIN, LOW);
  }
  
}
