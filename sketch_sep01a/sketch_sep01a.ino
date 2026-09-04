

void setup() {
  // put your setup code here, to run once:
    Serial.begin(9600);
    pinMode(11, OUTPUT);
    pinMode(10, OUTPUT);
    pinMode(9, OUTPUT);
    //inputs
    pinMode(8, INPUT);
    pinMode(7, INPUT);
    pinMode(A0, INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  int brightness = analogRead(A0)/1023*255; 
  
  int pin8 = digitalRead(8);
  int pin7 = digitalRead(7);
  
  if (pin8 == HIGH){
    for (int i = 0; i<5, i++){
        analogWrite(11, brightness);
        delay(500);
        digitalWrite(11, LOW);
        delay(500);
      }
   }
  else{
    digitalWrite(11, LOW);
    }

   
  if (pin7 == HIGH) {
        for (int i = 0; i<5, i++){
        analogWrite(9, brightness);
        delay(500);
        digitalWrite(9, LOW);
        delay(500);
      }
   }
   else{
    digitalWrite(9, LOW);
    }

}
