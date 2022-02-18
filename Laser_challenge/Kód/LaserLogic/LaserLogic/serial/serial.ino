

void setup(){
    Serial.begin(115200);

}

void loop(){
  for(int i = 0; i < 300; i++){
      Serial.println(i);
      }
  for(int i = 300; i > 300; i--){
      Serial.println(i);
      }
}
