const int parlante = 3;
const int pulsador = 2;
int pul=0;

void setup() {
  pinMode(pulsador,INPUT);
  
  Serial.begin(9600);
 
}

void loop() {
  pul= digitalRead(pulsador);
   Serial.println(pul);
 if (pul == LOW){
    tone(3,200);
    delay(500);
    noTone(3);
    delay(500);
 }
 else{
    tone(3,500);
    delay(200);
    noTone(3);
    delay(200);
 }
}
