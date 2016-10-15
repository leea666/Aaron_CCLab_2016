import processing.serial.*;
import cc.arduino.*;

Arduino arduino ;

boolean withinBounds = false ;

void setup() {
   size(500, 500) ; 
   background(255) ;
   
   println(Arduino.list());
   arduino = new Arduino(this, Arduino.list()[3], 57600);
   
   arduino.pinMode(9, Arduino.OUTPUT) ;
}

void draw() {
  float x = mouseX ;
  float y = mouseY ;
  
  rectMode(CORNERS) ;
  rect(width/2 - 150, height/2 - 150, width/2+150, height/2+150) ;
  if (withinBounds == false) {
    fill(255,125,125) ;
     arduino.digitalWrite(9, Arduino.LOW) ;
  }
  if((x>=100 && y>=100) && (x>=100 && y<=400) && (x<=400 && y>=100) && (x<=400 && y<=400)) {
    fill(125,255,125) ;
    arduino.digitalWrite(9, Arduino.HIGH) ;
    withinBounds = true ;
  } else {
    withinBounds = false ;
  }
}