
void colorWipe(uint32_t color) {
  for(int i=0; i<strip.numPixels(); i++) {
    strip.setPixelColor(i, color);
    strip.show();
  }
}

void ledRefresh(){
  cameraServo.detach();
  if(lowBattery){
    colorWipe(strip.Color(255, 0, 0));
  }
  else{
    colorWipe(strip.Color(255, 255, 255));
  }
  cameraServo.attach(CAMERA_SERVO);
  LedRefreshLastTime = millis();
}
