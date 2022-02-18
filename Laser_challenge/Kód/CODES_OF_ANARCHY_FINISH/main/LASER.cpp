/*
#include "LASER.h"
#include <arduino.h>

laser::laser(int LASER_PWR){
    pinMode(LASER_PWR, INPUT);
    this -> LASER_PWR = LASER_PWR;
}

int laser::read(){
    return analogRead(LASER_PWR);
}

void laser::printValue(int pocet){
    for(int j = 0; j < pocet; j++){
        
         an_pwr = laser::read();
        double pwr = an_pwr / 1023.0 * 30.0;
        Serial.print(pwr);
        if (pocet > 1) Serial.print(",");
    }
    Serial.println();
}

                              
step::step(int DIR, int STEP){
    pinMode(DIR, OUTPUT);
    pinMode(STEP, OUTPUT);
    this -> DIR = DIR;
    this -> STEP = STEP;
}

void step::enable(int enable_pin){                   // povoleni rizeni pro vsechny drivery
    pinMode(enable_pin, OUTPUT);                       
    digitalWrite(enable_pin, LOW);
}

void step::move(dir smer, int steps){
    digitalWrite (DIR, smer);               // zapis smeru na prislusny pin DIR (true/false)
    delay(50);
                                            // smycka pro provedeni predaneho mnozstvi kroku
    for (int i = 0; i < steps; i++) {
        digitalWrite(STEP, HIGH);
        delayMicroseconds (800);
        digitalWrite(STEP, LOW);
        delayMicroseconds (800);
    }
}*/
