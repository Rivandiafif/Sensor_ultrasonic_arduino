#include <SoftwareSerial.h>
#include <Wire.h>

#define TRIGGER 12
#define ECHO 11

long durasi, cm;
int nilai1, nilai2, nilai3, nilai4, nilai5, nilai6, nilai7, nilai8, nilai9, nilai10, nilai11, nilai12, nilai13, nilai14, nilai15, nilai16, nilai17, nilai18, nilai19, nilai20, nilai_min, nilai_max, total, temp, jarak[20];
int avg, avgbefore;

SoftwareSerial ss (2,3);

void(*start_reset) (void) = 0;  //untuk reset arduino

void setup() {
    Serial.begin(9600);
    ss.begin(115200);
    pinMode(TRIGGER,OUTPUT);
    pinMode(ECHO,INPUT);
    pinMode(LED_BUILTIN,OUTPUT);
}

void loop(){
    total = 0;
    for ( int x=0; x<20; x++ ) {
       digitalWrite(TRIGGER, LOW);
       delayMicroseconds(2);
       digitalWrite(TRIGGER, HIGH);
       delayMicroseconds(20);
       digitalWrite(TRIGGER, LOW);
        
       durasi = pulseIn(ECHO,HIGH);
       digitalWrite(LED_BUILTIN,HIGH);
       delay(500);
       cm = (durasi/2) /29.1;
//       cm = ((durasi*0.343)/2)/10;
       jarak[x] = cm;
       Serial.println("Total = " + String(cm));
       digitalWrite(LED_BUILTIN,LOW);
       if( cm == 0 ){
        digitalWrite(LED_BUILTIN,HIGH);
       }
       delay(1000);
    }
    //========================= URUTKAN NILAI TERKECIL KE TERBESAR ===========
    for ( int i = 0; i < 20; i++ ) {
      for (int j = 0; j < 20; j++) {
       if (jarak[i] < jarak[j]) {
        temp = jarak[i];
        jarak[i] = jarak[j];
        jarak[j] = temp;
       }
      }
    }
    //=======================================================================
    for ( int a = 0 ; a < 20; a++ ) {
    total += jarak[a];
    nilai_min = jarak[0];
    nilai_max = jarak[19];
    Serial.print("[" + String(jarak[a]) + "]");
    //============================= PERIKSA KONDISI DATA ===================
     if ( nilai_min == jarak[1]){
        nilai_min = jarak[0]+jarak[1];
        avgbefore = (total-(nilai_min + nilai_max))/17;
        avg = avgbefore;
      }
      else if (nilai_max == jarak[18]){
        nilai_max = jarak[18]+jarak[19];
        avgbefore  = (total-(nilai_min + nilai_max))/17;
        avg = avgbefore;
      }  
      else if ( nilai_min == jarak[1] && nilai_max == jarak[18]){
        nilai_min = jarak[0]+jarak[1];
        nilai_max = jarak[18]+jarak[19];
        avgbefore  = (total-(nilai_min + nilai_max))/16;
        avg = avgbefore;
      }  
      else {
        avgbefore  = (total-(nilai_min + nilai_max))/18;
        avg = avgbefore;
      }
     }
      Serial.println();
      Serial.println("Total = " + String(total));
      Serial.println("Minimum = " + String(jarak[0]));
      Serial.println("Maksimum = " + String(jarak[19]));
      Serial.println("Rata-rata = " + String(avg));
      nilai1 = jarak[0];
      nilai2 = jarak[1];
      nilai3 = jarak[2];
      nilai4 = jarak[3];
      nilai5 = jarak[4];
      nilai6 = jarak[5];
      nilai7 = jarak[6];
      nilai8 = jarak[7];
      nilai9 = jarak[8];
      nilai10 = jarak[9];
      nilai11 = jarak[10];
      nilai12 = jarak[11];
      nilai13 = jarak[12];
      nilai14 = jarak[13];
      nilai15 = jarak[14];
      nilai16 = jarak[15];
      nilai17 = jarak[16];
      nilai18 = jarak[17];
      nilai19 = jarak[18];
      nilai20 = jarak[19];
      //============================ SEND TO ESP =====================
      String sendToESP = "";
      sendToESP += avg;
      sendToESP += ";";
      sendToESP += nilai1;
      sendToESP += ";";
      sendToESP += nilai2;
      sendToESP += ";";
      sendToESP += nilai3;
      sendToESP += ";";
      sendToESP += nilai4;
      sendToESP += ";";
      sendToESP += nilai5;
      sendToESP += ";";
      sendToESP += nilai6;
      sendToESP += ";";
      sendToESP += nilai7;
      sendToESP += ";";
      sendToESP += nilai8;
      sendToESP += ";";
      sendToESP += nilai9;
      sendToESP += ";";
      sendToESP += nilai10;
      sendToESP += ";";
      sendToESP += nilai11;
      sendToESP += ";";
      sendToESP += nilai12;
      sendToESP += ";";
      sendToESP += nilai13;
      sendToESP += ";";
      sendToESP += nilai14;
      sendToESP += ";";
      sendToESP += nilai15;
      sendToESP += ";";
      sendToESP += nilai16;
      sendToESP += ";";
      sendToESP += nilai17;
      sendToESP += ";";
      sendToESP += nilai18;
      sendToESP += ";";
      sendToESP += nilai19;
      sendToESP += ";";
      sendToESP += nilai20;           
      ss.print(sendToESP);
      delay(500);
      start_reset(); //untuk reset arduino
}
