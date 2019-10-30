//////sensor variables//////////////////////////////////////////
const int pinecho = 11;
const int pintrigger = 12;
const int pinled = 9;
unsigned int tiempo,distancia;
 
//////display pins and variables///////////////////////////////
int shiftClock = 5;  //module pin label SCLK
int latchClock = 6;  //module pin label RCLK
int displayOut = 7;  //module pin label DIO
const byte numDigits = 4; //cant digits display
byte testDigits[numDigits] = {0};
byte* displayLocation = testDigits;
int showText = 6;
int charCount = -1150;

//////////////////////////////////////////////////////////////
void setup (){
 Serial.begin(9600);
   
 pinMode(pinecho, INPUT);
 pinMode(pintrigger, OUTPUT);
 pinMode(9, OUTPUT);
 
 pinMode(shiftClock, OUTPUT);
 pinMode(latchClock, OUTPUT);
 pinMode(displayOut, OUTPUT);

////////////////timer code/////////////////////////////////////////

  // Timer 2 - gives us the display segment refresh interval
  TCCR2A = 0;  // reset Timer 2
  TCCR2B = 0;
  TCCR2A = bit (WGM21) ;   // configure as CTC mode
  // 16 MHz clock (62.5 nS per tick) - prescaled by 256
  // counter increments every 16 µS.
  // There are 8 segments and 4 digits to scan every 1/60th of a second
  // so we count 32 of them at 60Hz, giving a display refresh interval of 512 µS.
  #define scanRateHz 60  // tested, maximum that works is 88 using Wire library and Serial
  #define displayScanCount 1000000L / numDigits / 8 / scanRateHz / 16
  OCR2A  = displayScanCount;            // count up to 32 @ 60Hz
  // Timer 2 - interrupt on match (ie. every segment refresh interval)
  TIMSK2 = bit (OCIE2A);   // enable Timer2 Interrupt
  TCNT2 = 0;  // counter to zero
  // Reset prescalers
  GTCCR = bit (PSRASY);        // reset prescaler now
  // start Timer 2
  TCCR2B =  bit (CS21) | bit (CS22) ;  // prescaler of 256
  
} // end of setup()


///////////////////////////////////////////////////////////////
void loop(){
 unsigned long currentMillis = millis();
 long start = millis();

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
  distancia = tiempo / 29;

  LED4_Print (distancia);

  
    if ((distancia >= 100)&&(distancia <200)) {
      pitido2();
  }
    if ((distancia >= 50)&&(distancia <100)){
      pitido1();
  }
    if ((distancia >= 2)&&(distancia <50)) {
      pitido05();
  }

}// end loop
////////////////////////////////////////////////////////////////////////

void pitido2() {

  Serial.print(distancia);
  Serial.println(" cm");
  
    analogWrite(9, 120);
    delay(200);
    analogWrite(9, 0);
}

void pitido1() {

  Serial.print(distancia);
  Serial.println(" cm");

    analogWrite(9, 160);
    delay(300);
    analogWrite(9, 0);
    /*delay(100);
    digitalWrite(13, HIGH);
    delay(100);
    digitalWrite(13, LOW);*/
}

void pitido05() {
  
  Serial.print(distancia);
  Serial.println(" cm");
  
    analogWrite(9, 220);
    delay(500);
    analogWrite(9, 0);
    /*delay(100);
    digitalWrite(13, HIGH);
    delay(200);
    digitalWrite(13, LOW);
    delay(100);
    digitalWrite(13, HIGH);
    delay(200);
    digitalWrite(13, LOW);*/
}


///////////////////////////////////////////////////////////
void pip(int pin,int repeat, int duration){
  for (int i = 0 ; i < repeat ; i++) {
    digitalWrite(pin,HIGH);
    delay(duration);
    digitalWrite(pin,LOW); 
    delay(duration);
  }
}

///////////////////////////////////////////////////////////
void LED4_Print (int num){
  byte LED2[4];
    if ((num < 9999)&&(num >= 0)){
      for(int i = 3; i >= 0; i--){
        LED2[i] = num % 10;  // digits to print
        num /= 10;
      }   
    }
 displayLocation = LED2;
 delay(1500);
}

///////////////////////////////////////////////////////////////////
ISR (TIMER2_COMPA_vect){
 const byte NUM_PLUS_SYMBOL_FONT[] = {
   0b00111111, // 0
   0b00000110, // 1
   0b01011011, // 2
   0b01001111, // 3
   0b01100110, // 4
   0b01101101, // 5
   0b01111101, // 6
   0b00000111, // 7
   0b01111111, // 8
   0b01101111, // 9
   0b01110111, // A
   0b01111100, // b
   0b00111001, // C
   0b01011110, // d
   0b01111001, // E
   0b01110001, // F
   0b00111101, // (71)  G
   0b01110110, // (72) H
   0b00011110, // (74) J
   0b00111000, // (76) L
   0b01110011, // (80) P
   0b00111110, // (85) U
   0b00000000, // (32)  <space>
   0b01000000, // (45) -
   0b10000000  //  .   float point
  };
  
  static byte digit = 0;
  static byte segment = 0x80;
  byte tempDigit = displayLocation[digit];
  shiftOut(displayOut, shiftClock, MSBFIRST,  // send segment data
    ~(segment & ((NUM_PLUS_SYMBOL_FONT[tempDigit & 0x7f]) | (tempDigit & 0x80))) );   
  shiftOut(displayOut, shiftClock, MSBFIRST, 8 >> digit);  // send digit select data
  // data is now in the display shift register, so latch to LEDs
  digitalWrite(latchClock, LOW);
  digitalWrite(latchClock, HIGH);
  
  // increment variables to select the next segment and possibly the next digit:
  segment = segment >> 1;
  if (segment == 0){
    segment = 0x80;
    digit++;
    if (digit >= numDigits)
      digit = 0;
  }
  
}
