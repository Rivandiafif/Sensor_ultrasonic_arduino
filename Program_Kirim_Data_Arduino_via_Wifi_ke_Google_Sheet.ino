#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <WiFiClientSecure.h>



#ifndef STASSID
#define STASSID "network name"
#define STAPSK  "network password"
#endif

const char* ssid     = STASSID;
const char* password = STAPSK;
const char* host = "script.google.com";
const int httpsPort = 443;

int avg = 0, nilai1 = 0, nilai2 = 0, nilai3 = 0, nilai4 = 0, nilai5 = 0, nilai6 = 0, nilai7 = 0, nilai8 = 0, nilai9 = 0, nilai10 = 0, nilai11 = 0, nilai12 = 0, nilai13 = 0, nilai14 = 0, nilai15 = 0, nilai16 = 0, nilai17 = 0, nilai18 = 0, nilai19 = 0, nilai20 = 0;
      
unsigned long currentMillis = 0, prevMillis = 0, intervalMillis = 5000;

WiFiClientSecure client;

String GSheet_ID = "AKfycbwiShWrpZ0myX1hFUWRExy7iK9asdfjsdhr7f2dAlVI7BoCz5hUouc6YX_";


void setup() {
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  Serial.println("");
  Serial.println("Connecting");
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }

  Serial.println("");
  Serial.print("Successfully connected to : ");
  Serial.println(ssid);
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  client.setInsecure();
}

String splitString(String data, char separator, int index) {
  int found = 0;
  int strIndex[] = {0, -1};
  int maxIndex = data.length() - 1;

  for (int i = 0; i <= maxIndex && found <= index; i++) {
    if (data.charAt(i) == separator || i == maxIndex) {
      found++;
      strIndex[0] = strIndex[1] + 1;
      strIndex[1] = (i == maxIndex) ? i + 1 : i;
    }
  }
  return found > index ? data.substring(strIndex[0], strIndex[1]) : "";
}

void loop() {
  if(Serial.available()){
    String msg = "";
    while(Serial.available()){
      msg += char (Serial.read());
      delay(50);
   }
   //======================= Pemisahan tipe data String ========================
   avg = splitString(msg, ';', 0).toFloat();
   nilai1 = splitString(msg, ';', 1).toFloat();
   nilai2 = splitString(msg, ';', 2).toFloat();
   nilai3 = splitString(msg, ';', 3).toFloat();
   nilai4 = splitString(msg, ';', 4).toFloat();
   nilai5 = splitString(msg, ';', 5).toFloat();
   nilai6 = splitString(msg, ';', 6).toFloat();
   nilai7 = splitString(msg, ';', 7).toFloat();
   nilai8 = splitString(msg, ';', 8).toFloat();
   nilai9 = splitString(msg, ';', 9).toFloat();
   nilai10 = splitString(msg, ';', 10).toFloat();
   nilai11 = splitString(msg, ';', 11).toFloat();
   nilai12 = splitString(msg, ';', 12).toFloat();
   nilai13 = splitString(msg, ';', 13).toFloat();
   nilai14 = splitString(msg, ';', 14).toFloat();
   nilai15 = splitString(msg, ';', 15).toFloat();
   nilai16 = splitString(msg, ';', 16).toFloat();
   nilai17 = splitString(msg, ';', 17).toFloat();
   nilai18 = splitString(msg, ';', 18).toFloat();
   nilai19 = splitString(msg, ';', 19).toFloat();
   nilai20 = splitString(msg, ';', 20).toFloat();
  }

  currentMillis = millis();
  if((currentMillis - prevMillis) >= intervalMillis){
    sendData(avg, nilai1, nilai2, nilai3, nilai4, nilai5, nilai6, nilai7, nilai8, nilai9, nilai10, nilai11, nilai12, nilai13, nilai14, nilai15, nilai16, nilai17, nilai18, nilai19, nilai20);
    delay(60000); //jeda pengiriman data
  }
}

//========================== Sending data to Google Sheets ========================
void sendData(int avg, int nilai1, int nilai2, int nilai3, int nilai4, int nilai5, int nilai6, int nilai7, int nilai8, int nilai9, int nilai10, int nilai11, int nilai12, int nilai13, int nilai14, int nilai15, int nilai16, int nilai17, int nilai18, int nilai19, int nilai20) {  

  if (!client.connect(host, httpsPort)) {
      Serial.println("connection failed");
      return;
  }
    int water_lvl = int(avg);
    int data1 = int(nilai1);
    int data2 = int(nilai2);
    int data3 = int(nilai3);
    int data4 = int(nilai4);
    int data5 = int(nilai5);
    int data6 = int(nilai6);
    int data7 = int(nilai7);
    int data8 = int(nilai8);
    int data9 = int(nilai9);
    int data10 = int(nilai10);
    int data11 = int(nilai11);
    int data12 = int(nilai12);
    int data13 = int(nilai13);
    int data14 = int(nilai14);
    int data15 = int(nilai15);
    int data16 = int(nilai16);
    int data17 = int(nilai17);
    int data18 = int(nilai18);
    int data19 = int(nilai19);
    int data20 = int(nilai20);
    //===================================Processing data and sending data===================================
    String url = "/macros/s/" + GSheet_ID + "/exec?water_level=" + water_lvl + 
                                                   "&data1=" + data1 + 
                                                   "&data2=" + data2 + 
                                                   "&data3=" + data3 + 
                                                   "&data4=" + data4 + 
                                                   "&data5=" + data5 +
                                                   "&data6=" + data6 +
                                                   "&data7=" + data7 + 
                                                   "&data8=" + data8 + 
                                                   "&data9=" + data9 + 
                                                   "&data10=" + data10 +
                                                   "&data11=" + data11 + 
                                                   "&data12=" + data12 + 
                                                   "&data13=" + data13 + 
                                                   "&data14=" + data14 + 
                                                   "&data15=" + data15 +
                                                   "&data16=" + data16 + 
                                                   "&data17=" + data17 + 
                                                   "&data18=" + data18 + 
                                                   "&data19=" + data19 + 
                                                   "&data20=" + data20;
                                               
  Serial.print("requesting URL: ");
  Serial.println(url);

  client.print(String("GET ") + url + " HTTP/1.1\r\n" +
         "Host: " + host + "\r\n" +
         "User-Agent: BuildFailureDetectorESP8266\r\n" +
         "Connection: close\r\n\r\n");
}
