//encoder interrupt service routines

void leftEncoder(){
  //checking values of both inputs
  leftAset = digitalRead(LEFTENCODER_A)== HIGH;
  leftBset = digitalRead(LEFTENCODER_B)== HIGH;
  
  //incremending or decrementing based on leading or lagging
  leftEncoderPos += (leftAset != leftBset) ? -1 : +1;
}

void rightEncoder(){
  //checking values of both inputs
  rightAset = digitalRead(RIGHTENCODER_A)== HIGH;
  rightBset = digitalRead(RIGHTENCODER_B)== LOW;

  //incremending or decrementing based on leading or lagging
  rightEncoderPos += (rightAset != rightBset) ? -1 : +1;
}
