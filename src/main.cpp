#include <Arduino.h>
#include <FlexiTimer2.h>

#define PRESSURE_SENSOR A0
#define LED 2

int v = 0;
int t = 0;
double fg = 0;
double R1 = 10.0;

void flash() {
    if(fg < 100) return;
    analogWrite(LED, 255);
    delay(fg);
    analogWrite(LED, 0);
    delay(fg);
}

void setup() {
    Serial.begin(9600);
    
    FlexiTimer2::set(100, flash); // 500ms period
    FlexiTimer2::start();
}

void loop() {
    //曲げセンサー
    //v = analogRead(PRESSURE_SENSOR);
    ////Serial.print("v: "); Serial.println(v);
    //t = map(v, 0, 1023, 4000, 0);
    //Serial.print("t: "); Serial.println(t);

    //圧力センサー
    double Vo, Rf;
    int ain = analogRead(PRESSURE_SENSOR);
    // アナログ入力値から出力電圧を計算
    Vo = ain * 5.0 / 1024;
    // 出力電圧からFRSの抵抗値を計算
    Rf = R1*Vo / (5.0 - Vo);
    // FRSの抵抗値から圧力センサの荷重を計算
    // fgは100程度である程度おされている状態。
    fg = 880.79/Rf + 47.96;
    Serial.println(fg);
}