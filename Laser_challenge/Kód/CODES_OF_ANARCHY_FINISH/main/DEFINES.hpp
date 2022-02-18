#include "LASER.h"

#define ENABLE 8
#define X_STEP 2
#define Y_STEP 3
#define X_DIR  5
#define Y_DIR  6
#define STEPP  250
#define LEN 600          // puvodni hodnota byla 900
#define STEPS 50
                            // pin na ktery je privedena analogova hodnota z mereni vykonu laseru
#define LASER_PWR 12

laser lsr(LASER_PWR);       //initializace motoru a vstupu laseru

step horizontal(X_DIR, X_STEP);        
step vertical(Y_DIR, Y_STEP);

double avrg_pwr;

void calibration(int value, int reverse){           //definice kalibrace

        int an_pwr = lsr.read();

        if (an_pwr < 300)
        {
            int i = 0;
            do
            {
              
          an_pwr = lsr.read();
                vertical.move(down, 2);
                horizontal.move(left, 2);
                i++;
            } while (an_pwr < 550 && i < 350);  
        }

        do
        {
            an_pwr = lsr.read();
            vertical.move(up, 2);
        } while (an_pwr > value);
        
        vertical.move(down, reverse);

        do
        {
            an_pwr = lsr.read();
            horizontal.move(right, 2);
        } while (an_pwr > value);
        
        horizontal.move(left, reverse);
        
        delay(250);
}
void scan(double scale, int results){           //scanovani laseru a posilani hodnot po seriove lince

     for(int i = 0; i<LEN*scale;i++){
        lsr.printValue(results);
        vertical.move(up, 1); //projede pres laser smerem nahoru
      }
      for(int i = 0; i<LEN*scale;i++){
        lsr.printValue(results);
        vertical.move(down, 1);//projede zpatky dolu
      }
      for(int i = 0; i<LEN*scale;i++){
        lsr.printValue(results);
        horizontal.move(right, 1);//projede pres laser doprava
      }
      for(int i = 0; i<LEN*scale;i++){
        lsr.printValue(results);
        horizontal.move(left, 1);//projede zpatky doleva
      }
    
}
