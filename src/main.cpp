#include <Arduino.h>
#include <FlexiTimer2.h>

#define PRESSURE_SENSOR A0
#define LED 2

int v = 0;
int t = 0;

void flash() {
    if(t > 800) return;

    analogWrite(LED, 255);
    delay(t);
    analogWrite(LED, 0);
    delay(t);
}

void setup() {
    Serial.begin(9600);
    
    FlexiTimer2::set(100, flash); // 500ms period
    FlexiTimer2::start();
}

void loop() {
    v = analogRead(PRESSURE_SENSOR);
    //Serial.print("v: "); Serial.println(v);
    t = map(v, 0, 1023, 4000, 0);
    Serial.print("t: "); Serial.println(t);
}