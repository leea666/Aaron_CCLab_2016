//Aaron Lee
//HW 1: Your assignment is make a button that will change between two LED states on a single button press. However, both of your LED states must be different blinking patterns. 

int ledPin = 9 ;
int buttonPin = 8 ;
unsigned long lastBlinkTime = 0 ;
int waitTimeMode1 = 1000 ;
int waitTimeMode2 = 100 ;
bool ledState = false ;
bool buttonPush = true ;
int buttonStart = 0 ;
int holder = 0 ;

void setup() {

  Serial.begin(9600) ;
  pinMode(ledPin, OUTPUT) ;
  pinMode(buttonPin, INPUT_PULLUP) ;
  
}

void loop() {
  if(buttonStart == 0) {
    if(digitalRead(buttonPin) == 0) {
      buttonStart = 1 ;
    }
  }
  if(buttonStart == 1) {
    if (digitalRead(buttonPin) == HIGH) {
        holder = 1 ;
        unsigned long currentTime = millis() ;
        if (buttonPush == true) {
          if(currentTime - lastBlinkTime > waitTimeMode1) {
            ledState = !ledState ;
            lastBlinkTime = millis() ;
          }
        } else if(buttonPush == false) {

          if(currentTime - lastBlinkTime > waitTimeMode2) {
            ledState = !ledState ;
            lastBlinkTime = millis() ;
          }
        }
    } else if (digitalRead(buttonPin) == LOW) {
        if(holder == 1) {
          buttonPush = !buttonPush ;
          holder = 0 ;
        }
    }
  }
  
  if(ledState) {
    digitalWrite(ledPin, HIGH) ;
  }
  else {
     digitalWrite(ledPin, LOW) ;
  }

}
