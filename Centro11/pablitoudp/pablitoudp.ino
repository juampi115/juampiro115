
#include <ESP8266WiFi.h>
#include <WiFiUdp.h>

#ifndef STASSID
#define STASSID "NodeMCU-ESP8266"
#define STAPSK  "CENTRO1120"
#endif

unsigned int localPort = 8888;       // local port to listen on
char  ReplyBuffer[] = "";            // a string to send back
int incomingByte = 0;                // for incoming serial data

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

    // send data only when you receive data:
    if (Serial.available() > 0) {
      // read the incoming byte:
      incomingByte = Serial.read();
  
      // say what you got:
      Serial.println(),
      Serial.print("mandee: ");
      Serial.println(incomingByte, DEC);
  }

    Udp.beginPacket(Udp.remoteIP(), 8888);
    char aChar = incomingByte;
    Serial.print(aChar);
        Serial.println();
    ReplyBuffer[0]= aChar;
    Udp.write(ReplyBuffer);
    Udp.endPacket();



    delay(100);

    
} //end loop
