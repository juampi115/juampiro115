////////////////////////////////// ESP8266 Parlante 1 ////////////////////////////////////
/////////////////////////////////  Librerias  ////////////////////////////////////////////
#include <ESP8266WiFi.h>
#include <WiFiUdp.h>

#ifndef STASSID
#define STASSID "NodeMCU-ESP826"
#define STAPSK  "CENTRO1120"


unsigned int localPort = 8888;       // puerto local para escuchar
char  ReplyBuffer[] = "";            // a string to send back
int incomingByte = 0;                // para datos en serie entrantes

WiFiUDP Udp;

void setup() {
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);
  WiFi.begin(STASSID, STAPSK);
  while (WiFi.status() != WL_CONNECTED) {
    Serial.println("Conectando");
    delay(50);
  }
  Serial.println();
  Serial.print("Connected! IP address: ");
  Serial.println(WiFi.localIP());
  Serial.printf("UDP server on port %d\n", localPort);
  Udp.begin(localPort);
}

void loop() {
  if (Serial.available() > 0) {
    // leer el byte entrante:
    incomingByte = Serial.read();
    // dice lo que tienes:
    Serial.println(),
    Serial.print("Reciví: ");
    Serial.println(incomingByte, DEC);
  }

  Serial.write(incomingByte);

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
