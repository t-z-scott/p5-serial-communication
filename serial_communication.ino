#include "PDMSerial.h"
PDMSerial pdm;

const int analogPin = A0;
const int ledPin = 13;
const int digitalInPin = 7;
int pressureValue = 0;
int outPWMPin = 10;
int mouseState = LOW;

void setup() {
  pinMode(analogPin, INPUT);
  pinMode(digitalInPin, INPUT_PULLUP);
  pinMode(ledPin, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  pressureValue = analogRead(analogPin);
  
  mouseState = digitalRead(digitalInPin);
  
  pdm.transmitSensor("pressure", pressureValue);
  pdm.transmitSensor("end");
  
  boolean newData = pdm.checkSerial();
  if(newData) {
    if( pdm.getName().equals(String("led")) ) {
      digitalWrite(ledPin, pdm.getValue());
    } else if( pdm.getName().equals(String("pressure")) ) {
      analogWrite(outPWMPin, pdm.getValue());
    }
  }
  
}