        
        /******************************************************\
                           SCIENCE CHALLENGE
        
          //////////////////CODE OF ANARCHY//////////////////
                  ***kod pouze pro pohyby motoru***
            ***je nutne spustit prilozeny python soubor***

                           ---v. 1.0.0---
        \******************************************************/
        
#include "DEFINES.hpp"

void setup() {

    Serial.begin(115200);
    vertical.enable(ENABLE);      //zvoleni pinu pro zapnuti motoru          
    delay(1000);
    calibration(150, LEN / 2);    //kalibrace sestavy
}

void loop() { 

  if(Serial.available()) {       //nacteme si data ze seriove linky
    char msg = Serial.read();

    switch (msg)                 //na zaklade dat ze seriove linky davame pokyny pro laser
    {
      case 'a':
        horizontal.move(left, STEPS);
        break;

      case 'd':
        horizontal.move(right, STEPS);
        break;

      case 'w':
        vertical.move(up, STEPS);
        break;

      case 's':
        vertical.move(down, STEPS);
        break;

      case 'k':                     //hlavni poloha ze ktere probiha mereni                 
        scan(0.75, 1);
        break;

      case 'c':                     //porvedeni kalibrace
        calibration(150, LEN / 2);
        break;      
    }                 
  }
}
