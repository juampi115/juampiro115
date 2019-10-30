

const int pinecho = 11;
const int pintrigger = 12;
const int pinled = 13;
unsigned int tiempo, distancia;

void setup() {

  Serial.begin(9600);
  pinMode(pinecho, INPUT);
  pinMode(pintrigger, OUTPUT);
  pinMode(13, OUTPUT);
}

void loop() {
  // ENVIAR PULSO DE DISPARO EN EL PIN "TRIGGER"
  digitalWrite(pintrigger, LOW);
  delayMicroseconds(2);
  digitalWrite(pintrigger, HIGH);
  // EL PULSO DURA AL MENOS 10 uS EN ESTADO ALTO
  delayMicroseconds(10);
  digitalWrite(pintrigger, LOW);

  // MEDIR EL TIEMPO EN ESTADO ALTO DEL PIN "ECHO" EL PULSO ES PROPORCIONAL A LA DISTANCIA MEDIDA
  tiempo = pulseIn(pinecho, HIGH);

  // LA VELOCIDAD DEL SONIDO ES DE 340 M/S O 29 MICROSEGUNDOS POR CENTIMETRO
  // DIVIDIMOS EL TIEMPO DEL PULSO ENTRE 58, TIEMPO QUE TARDA RECORRER IDA Y VUELTA UN CENTIMETRO LA ONDA SONORA
  distancia = tiempo / 58;




    if ((distancia >= 100)&&(distancia <200)) {
      pitido2();
  }
    if ((distancia >= 50)&&(distancia <100)){
      pitido1();
  }
    if ((distancia >= 15)&&(distancia <50)) {
      pitido05();
  }
    if (distancia < 15) {
      pitido15();
  }


}


void pitido2() {

  Serial.print(distancia);
  Serial.println(" cm");
  
    digitalWrite(13, HIGH);
    delay(500);
    digitalWrite(13, LOW);
}

void pitido1() {

  Serial.print(distancia);
  Serial.println(" cm");

    digitalWrite(13, HIGH);
    delay(500);
    digitalWrite(13, LOW);
    delay(100);
    digitalWrite(13, HIGH);
    delay(500);
    digitalWrite(13, LOW);
}

void pitido05() {
  
  Serial.print(distancia);
  Serial.println(" cm");
  
    digitalWrite(13, HIGH);
    delay(200);
    digitalWrite(13, LOW);
    delay(100);
    digitalWrite(13, HIGH);
    delay(200);
    digitalWrite(13, LOW);
    delay(100);
    digitalWrite(13, HIGH);
    delay(200);
    digitalWrite(13, LOW);
}
void pitido15() {

  Serial.print(distancia);
  Serial.println(" cm");
  
    digitalWrite(13, HIGH);
    delay(50);
    digitalWrite(13, LOW);
    delay(50);
    digitalWrite(13, HIGH);
    delay(50);
    digitalWrite(13, LOW);
    delay(50);
    digitalWrite(13, HIGH);
    delay(50);
    digitalWrite(13, LOW);
}
