//Used the function Termister to get the temperature from this website: https://computers.tutsplus.com/tutorials/how-to-read-temperatures-with-arduino--mac-53714


#include <math.h>
bool holder = true ;
int counter = 0 ;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200) ;
  pinMode(7, OUTPUT) ;
  pinMode(4, OUTPUT) ;
  pinMode(3, OUTPUT) ;
}

double Thermister(int RawADC) {
  double temp ;
  temp = log(((10240000/RawADC) - 10000)) ;
  temp = 1 / (0.001129148 + (0.000234125 + (0.0000000876741 * temp * temp)) * temp) ;
  temp = temp - 273.15 ;
  temp = (temp * 9.0) / 5.0 + 32.0 ;
  return temp ;
}

void loop() {
  // put your main code here, to run repeatedly:
  while (counter < 10) {
    int val ;
    double temperature ;
    val = analogRead(0) ;
    temperature = Thermister(val) ;
    Serial.println(temperature) ;
    if(temperature < 85) {
      digitalWrite(7, HIGH) ;
    } else {
      digitalWrite(7, LOW) ;
    }
    if (85 <= temperature && temperature <= 87) {
      digitalWrite(4, HIGH) ;
    }  else {
      digitalWrite(4, LOW) ;
    }
    if(temperature > 87) {
        digitalWrite(3, HIGH) ;
        holder = false ;
        counter++ ;
    } else {
      digitalWrite(3, LOW) ;
      counter = 0 ;
    }
    delay(1000) ;
  }

  if(counter == 10) {
    digitalWrite(3, LOW) ;
    Serial.println("You died!!!") ;
  }
}
