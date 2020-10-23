////////////////////////////// Control Basquet Centro 11  ///////////////////////////////////////////////////////
/////////////////////////////    Librerias     /////////////////////////////////////////////////////////////////
#include <ESP8266WiFi.h>
#include <WiFiUdp.h>

unsigned int localPort = 8888;                           // puerto local para escuchar
char  ReplyBuffer[] = "";                               // a string to send back
const char ssid[] = "NodeMCU-ESP8266";                 // Definimos la SSDI de nuestro servidor WiFi -nombre de red-
const char password[] = "CENTRO1120";                 // Definimos la contraseña de nuestro servidor
int incomingByte = 0;                                // para datos en serie entrantes

#define pulsadorLV 5
#define plsadorTanto 6
int Pulsador1 = 0;
int Pulsador2 = 0;
WiFiUDP Udp;

void setup() {
  Serial.begin(115200);

  WiFi.mode(WIFI_AP);                     //crea el Access Poin
  WiFi.softAP(ssid, password, 8888);      //Red con clave, en el canal 1 y visible
  WiFi.begin();
  Serial.println("Direccion IP Access Point - por defecto: ");
  Serial.println(WiFi.softAPIP());
  Serial.print("Direccion MAC Access Point: ");
  Serial.println(WiFi.softAPmacAddress());
  Serial.println("Server Started..");
  Serial.println();
  Serial.print("Connected! IP address: ");
  Serial.println(WiFi.localIP());
  Serial.printf("UDP server on port %d\n", 8888);
  Udp.begin(8888);
  pinMode(pulsadorLV, INPUT_PULLUP);
  pinMode(pulsadorTanto, INPUT_PULLUP);
}

void loop() {
  ///////////////// Lectura de estados  ///////////////////////////////////////////////////
  Pulsador1 = digitalRead(pulsadorLV);
  Pulsador2 = digitalRead(PulsadorTanto);
  /////////////////////////////////////////////////////////////////////////////////////////
  ////////////////  Acción  ///////////////////////////////////////////////////////////////
  if (Pulsador1 == HIGH) {
    //////////////  Enviar suena Local  /////////////////////////////////////////////////
    Udp.beginPacket(Udp.remoteIP(), 8888);
    char aChar = incomingByte;
    Serial.print(aChar);
    Serial.println();
    ReplyBuffer[0] = aChar;
    Udp.write(ReplyBuffer);
    Udp.endPacket();
    delay(100);

    if (Pulsador2 == LOW) {
      /////////////  Enviar info Local anoto  //////////////////////////////////////////////
      Udp.beginPacket(Udp.remoteIP(), 8888);
      char aChar = incomingByte;
      Serial.print(aChar);
      Serial.println();
      ReplyBuffer[0] = aChar;
      Udp.write(ReplyBuffer);
      Udp.endPacket();
      delay(100);

    }
  }
  else {
    ///////////////  Enviar Suena Visitante  ///////////////////////////////////////////////
    Udp.beginPacket(Udp.remoteIP(), 8888);
    char aChar = incomingByte;
    Serial.print(aChar);
    Serial.println();
    ReplyBuffer[0] = aChar;
    Udp.write(ReplyBuffer);
    Udp.endPacket();
    delay(100);

    if (Pulsador2 == LOW) {
      /////////////  Enviar info Visitante anoto  /////////////////////////////////////////
      Udp.beginPacket(Udp.remoteIP(), 8888);
      char aChar = incomingByte;
      Serial.print(aChar);
      Serial.println();
      ReplyBuffer[0] = aChar;
      Udp.write(ReplyBuffer);
      Udp.endPacket();
      delay(100);

    }
  }
  /*
  ///////////////// enviar datos solo cuando reciba datos: ////////////////////////////////
  if (Serial.available() > 0) {
    // leer el byte entrante:
    incomingByte = Serial.read();

    // dice lo que tienes:
    Serial.println(),
    Serial.print("mande: ");
    Serial.println(incomingByte, DEC);
  }
  //   Udp.beginPacket(Udp.remoteIP(), 8888);
  Udp.beginPacket("192.168.4.2", 8888);
  char aChar = incomingByte;
  Serial.print(aChar);
  Serial.println();
  ReplyBuffer[0] = aChar;
  Udp.write(ReplyBuffer);               //  manda datos
  Udp.endPacket();

  delay(100);  
  */

}
