/*
                   SCIENCE CHALLENGE

  //////////////////CODE OF ANARCHY///////////////////////
*/

// oba motory maji stejne parametry, maji 800 kroku na otacku, a jedna otacka pohne s britvou o 1,6 cm.
// pro ovladani krokovych motoru je vyuzito driveru A4988

#define ENABLE 8
#define X_STEP 2
#define Y_STEP 3
#define X_DIR  5
#define Y_DIR  6
#define STEPP  250
#define LEN 600          // puvodni hodnota byla 900
                            // pin na ktery je privedena analogova hodnota z mereni vykonu laseru
#define LASER_PWR A3

int an_pwr;
double avrg_pwr;

void setup() {
  pinMode(X_STEP, OUTPUT);  //nastaveni vystupnich pinu 
  pinMode(Y_STEP, OUTPUT);
  pinMode(X_DIR,  OUTPUT);
  pinMode(Y_DIR,  OUTPUT);

  pinMode(ENABLE, OUTPUT);                        // povoleni rizeni pro vsechny drivery
  digitalWrite(ENABLE, LOW);
                            // Zahajime komunikaci s pocitacem na prenosove rychlost 115200 baudu, toto cislo je nutne take zvolit kdyz otevirame seriovy monitor.
  Serial.begin(115200);
                            //  pockame a nasledne zahajime kalibraci cele sestavy
  delay(5000);
  calibration(150, LEN / 2);
}

//maximalni hodnota laseru je 22.36
void loop() { 

  if(Serial.available()) {       //nacteme si data ze seriove linky
    char msg = Serial.read();
    change(msg);                 //na základě přijaté hodnoty spustíme danou funkci
  }
}

void printPower(int pocet){   //meri pocet krat energii, a vypisuje ji
  for(int j = 0; j < pocet; j++){
    an_pwr = analogRead(LASER_PWR);
    //Serial.print(an_pwr);
    double pwr = an_pwr / 1023.0 * 30.0;
    //Serial.print("\t Pwr (uW) = ");
    Serial.print(pwr);
    //Serial.print(",");
  }
  Serial.println();
}

void calibration(int value, int reverse){

 an_pwr = analogRead(LASER_PWR);
 
  if(an_pwr < 300){        //kdyz laser nesviti na detektor tak posune britvu dolu, dokud neprestane blokovat laser, nebo neujde 300 kroku
    int i =0;
    an_pwr = analogRead(LASER_PWR);
        while(an_pwr < 550 && i < 350){
          an_pwr = analogRead(LASER_PWR);
          pohybOsy(true,  X_DIR, X_STEP, 2);
          pohybOsy(true,  Y_DIR, Y_STEP, 2);
          i++;
        }
    }
  an_pwr = analogRead(LASER_PWR);

  while (an_pwr > value){                   // jede nahoru, dokud nedojede k laseru
    an_pwr = analogRead(LASER_PWR);
    pohybOsy(false,  Y_DIR, Y_STEP, 2);
  }

  pohybOsy(true,  Y_DIR, Y_STEP, reverse);  // poskoci o reverse zpet (dolů), aby nebranil laseru

  an_pwr = analogRead(LASER_PWR);
    
  while (an_pwr > value){                   // jede doprava, dokud nedojede k laseru
    an_pwr = analogRead(LASER_PWR);
    pohybOsy(false,  X_DIR, X_STEP, 2);
  }

  pohybOsy(true,  X_DIR, X_STEP, reverse);  // poskoci o reverse zpet (doleva), aby nebranil laseru

  delay(250);
}


void pohybOsy(boolean smer, byte dirPin, byte stepPin, int kroky) {                                 
                                            // zapis smeru na prislusny pin DIR
  digitalWrite (dirPin, smer);
  delay(50);
                                            // smycka pro provedeni predaneho mnozstvi kroku
  for (int i = 0; i < kroky; i++) {
    digitalWrite(stepPin, HIGH);
    delayMicroseconds (800);
    digitalWrite(stepPin, LOW);
    delayMicroseconds (800);
  }
}

int average(){
  int sum_pwr = 0;
  for (int fu_analogu = 0; fu_analogu < 4; fu_analogu++){
    an_pwr = analogRead(LASER_PWR);
    sum_pwr = an_pwr + sum_pwr;
  }
  double avrg = sum_pwr/4;
  //Serial.println(avrg - an_pwr);
  return avrg;
}

void K(){
  double scale = 0.75;    // upravuje pomer odskoceni v kalibraci a kam az jede brit pri mereni
      /*     DULEZITE             scale nesmi byt mensi nez 0.5, pak by nefungovalo mereni                     DULEZITE           */
      int pocet_vysledku = 1;   //pocet mereni v jednom bode
      for(int i = 0; i<LEN*scale;i++){
        printPower(pocet_vysledku);
        pohybOsy(false,  Y_DIR, Y_STEP, 1); //projede pres laser smerem nahoru
      }
      for(int i = 0; i<LEN*scale;i++){
        printPower(pocet_vysledku);
        pohybOsy(true,  Y_DIR, Y_STEP, 1);//projede zpatky dolu
      }
      for(int i = 0; i<LEN*scale;i++){
        printPower(pocet_vysledku);
        pohybOsy(false,  X_DIR, X_STEP,1);//projede pres laser doprava
      }
      for(int i = 0; i<LEN*scale;i++){
        printPower(pocet_vysledku);
        pohybOsy(true,  X_DIR, X_STEP, 1 );//projede zpatky doleva
      }
}

void up_mereni(){
  double data[10];
  for(int fu_analogu = 0; fu_analogu < 10; fu_analogu++){
    an_pwr = analogRead(LASER_PWR);
    data[fu_analogu] = an_pwr / 1023.0 * 30.0;
  }
  for(int i = 0; i<LEN;i++){
        for(int fu_analogu = 0; fu_analogu < 10; fu_analogu++){
         an_pwr = analogRead(LASER_PWR);
          data[fu_analogu] = an_pwr / 1023.0 * 30.0;
          double lul = 0;
           for( int t = 0; t< 10; t++){
           lul = lul +data[t];
         }
          avrg_pwr = lul/10;
          Serial.println(avrg_pwr);
        }
        pohybOsy(false,  Y_DIR, Y_STEP, 1); //projede to cele smerem nahoru
  }
}
void change(char msg){

  switch (msg)
  {
  case 'a':
    Serial.println("Left 200");
    pohybOsy(true,  X_DIR, X_STEP, STEPP); 
    break;

  case 'd':
    Serial.println("Right 200");
    pohybOsy(false,  X_DIR, X_STEP, STEPP); 
    break;

  case 'w':
    Serial.println("Up 200");
    pohybOsy(false,  Y_DIR, Y_STEP, STEPP); 
    break;

  case 's':
    Serial.println("Down 200");
    pohybOsy(true,  Y_DIR, Y_STEP, STEPP); 
    break;

  case 'k':
    double scale = 0.75;    // upravuje pomer odskoceni v kalibraci a kam az jede brit pri mereni
    /*     DULEZITE             scale nesmi byt mensi nez 0.5, pak by nefungovalo mereni                     DULEZITE           */
    int pocet_vysledku = 1;   //pocet mereni v jednom bode
    for(int i = 0; i<LEN*scale;i++){
      printPower(pocet_vysledku);
      pohybOsy(false,  Y_DIR, Y_STEP, 1); //projede pres laser smerem nahoru
    }
    for(int i = 0; i<LEN*scale;i++){
      printPower(pocet_vysledku);
      pohybOsy(true,  Y_DIR, Y_STEP, 1);//projede zpatky dolu
    }
    for(int i = 0; i<LEN*scale;i++){
      printPower(pocet_vysledku);
      pohybOsy(false,  X_DIR, X_STEP,1);//projede pres laser doprava
    }
    for(int i = 0; i<LEN*scale;i++){
      printPower(pocet_vysledku);
      pohybOsy(true,  X_DIR, X_STEP, 1 );//projede zpatky doleva
    }
    break;

  case 'j':
    float avrg = average();
    int number = 0;
    while (true){
      number++;
      int last_avrg = avrg;
      pohybOsy(false,  Y_DIR, Y_STEP, 1);
      avrg = average();
      Serial.print(",");
      Serial.print(last_avrg);
      Serial.print(",");
      Serial.print(avrg);
      // Serial.print(last_avrg - avrg);
      Serial.println();
      if(avrg > 200){
        ;
      }
      else if(avrg - last_avrg< 100){
        Serial.println("LUL koncim");
        break;
      }
    }
    Serial.println("aaaaaaaaaaaaa");
    Serial.print(number); 
    break;

  case 'c':
    calibration(150, LEN / 2);
    break;
  
  case 'o':
    int pocet = 0;
    while(average()> 800){
      pohybOsy(false,  Y_DIR, Y_STEP, 1);
    }
    delay(2000);
    Serial.println("jsem na zacatku");
    while(average()> 85){
      pohybOsy(false,  Y_DIR, Y_STEP, 1);
      pocet++;
    }
    Serial.println(pocet);
    break;

  default:
    break;
  }
}
