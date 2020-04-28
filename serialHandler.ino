
void serialHandler(){
  
  while(Serial.available()){
        message = Serial.readString();
        cmd = message.substring(0,1);
        value =  message.substring(1,message.length()).toFloat();
    }
    
  if(cmd == "v"){
    if(abs(value)<=maxLinearVelocity)
      autoLinearVelocity = value;
  }
  else if(cmd == "w"){
    if(abs(value)<=maxAngularVelocity)
      autoAngularVelocity = value;
  }
  else if(cmd == "c"){
    if(0 <= value <= 180)
      cameraServoPosition = value;
      cameraServoSet(cameraServoPosition);
  }
  else if(cmd == "s"){
    autoLinearVelocity = 0;
    autoAngularVelocity = 0;
  }
  else if(cmd == "p"){
    Serial.println("x"+String(x)+"y"+String(y)+"t"+String(theta));
  }
  else if(cmd == "t"){
    Serial.println("v"+String(mesLinearVelocity)+"w"+String(mesAngularVelocity));
  }
  cmd = "";

}
