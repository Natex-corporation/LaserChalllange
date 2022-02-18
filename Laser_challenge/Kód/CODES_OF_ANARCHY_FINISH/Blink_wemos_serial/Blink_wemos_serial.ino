void setup() {
  
  pinMode(LED_BUILTIN, OUTPUT);
  Serial.begin(115200);
  digitalWrite(LED_BUILTIN, HIGH);
      delay(1000);
  digitalWrite(LED_BUILTIN, LOW);
}

void loop(){
      
  if(Serial.available()){
    char msg = Serial.read();
    Serial.print(msg);
    
    if(msg == 'K'){
      digitalWrite(LED_BUILTIN, HIGH);
      delay(10000);
      digitalWrite(LED_BUILTIN, LOW);
    }

    if(msg == 'B'){ 
     digitalWrite(LED_BUILTIN, HIGH);
     delay(1000);
     digitalWrite(LED_BUILTIN, LOW);
    }
  }
}
