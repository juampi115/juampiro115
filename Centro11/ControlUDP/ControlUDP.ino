
#include <ESP8266WiFi.h>
#include <WiFiUdp.h>

//#ifndef STASSID
//#define STASSID "Fibertel WiFi333 2.4GHz"
//#define STAPSK  "0043801931"
//#endif

unsigned int localPort = 8888;                  // local port to listen on
char  ReplyBuffer[] = "";          // a string to send back
const char ssid[] = "NodeMCU-ESP8266";    //Definimos la SSDI de nuestro servidor WiFi -nombre de red- 
const char password[] = "CENTRO1120";     //Definimos la contraseña de nuestro servidor
int incomingByte = 5; // for incoming serial data

WiFiUDP Udp;

void setup() {
  Serial.begin(115200);
 // WiFi.mode(WIFI_STA);
  WiFi.mode(WIFI_AP);                     //crea el Access Poin
  WiFi.softAP(ssid, password,8888);       //Red con clave, en el canal 1 y visible
  WiFi.begin();
  Serial.println("Direccion IP Access Point - por defecto: ");
  Serial.println(WiFi.softAPIP()); 
  Serial.print("Direccion MAC Access Point: ");
  Serial.println(WiFi.softAPmacAddress()); 
//  Server.begin(8888);                     //inicializamos el servidor
  Serial.println("Server Started..");
  Serial.println();
  Serial.print("Connected! IP address: ");
  Serial.println(WiFi.localIP());
  Serial.printf("UDP server on port %d\n", 8888);
  Udp.begin(8888);
}

void loop() {

    // send data only when you receive data:
    if (Serial.available() > 0) {
      // read the incoming byte:
      incomingByte = Serial.read();
  
      // say what you got:
      //Serial.println(),
      Serial.println("mandee: ");
      //Serial.println(incomingByte, DEC);
  }

 //   Udp.beginPacket(Udp.remoteIP(), 8888);
 Udp.beginPacket("192.168.4.2", 8888);
    char aChar = incomingByte;
    Serial.print(aChar);
        Serial.println();
    ReplyBuffer[0]= aChar;
    Udp.write(ReplyBuffer);               //manda
    Udp.endPacket();



    delay(100);

    
} //end loop
