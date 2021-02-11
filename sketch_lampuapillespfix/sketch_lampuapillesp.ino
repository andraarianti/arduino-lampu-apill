#define BLYNK_PRINT Serial
#include <ESP8266_Lib.h>
#include <BlynkSimpleShieldEsp8266.h>

#include <SimpleTimer.h>
SimpleTimer timer;

//esp
char auth[] = "JWjGg49pS0r7RwOa44cr1ELQX2soywWR";
char ssid[] = "Galaxy A519989";
char pass[] = "andraaaa";

#include <SoftwareSerial.h>
SoftwareSerial EspSerial(2, 3); // RX, TX

#define ESP8266_BAUD 9600
ESP8266 wifi(&EspSerial);

//lampu
int ledR1 = 4;
int ledG1 = 5;
int ledR2 = 6;
int ledG2 = 7;
int ledR3 = 8;
int ledG3 = 9;

int otomatis = 0;
int dataserial;
int bangjo = 0;

void bangjoMerah1() { //utara
  digitalWrite(ledR1, HIGH); //pin 5
  digitalWrite(ledG1, LOW); //pin 4
}
void bangjoMerah2() { //selatan
  digitalWrite(ledR2, HIGH); //pin 7
  digitalWrite(ledG2, LOW);//pin 6
}
void bangjoMerah3() { //barat
  digitalWrite(ledR3, HIGH);//pin 9
  digitalWrite(ledG3, LOW);//pin 8
}

void bangjoHijau1() {
  digitalWrite(ledR1, LOW);
  digitalWrite(ledG1, HIGH);
}
void bangjoHijau2() {
  digitalWrite(ledR2, LOW);
  digitalWrite(ledG2, HIGH);
}
void bangjoHijau3() {
  digitalWrite(ledR3, LOW);
  digitalWrite(ledG3, HIGH);
}

BLYNK_WRITE(V1) {
  bangjo = param.asInt();
  switch (bangjo) {
    case 1: //J1 Hijau + J2 Merah + J3 Merah
      Serial.println("Manual hijau 1");
      bangjoHijau1();
      bangjoMerah2();
      bangjoMerah3();
      otomatis = 0;
      break;
    case 2: //J1 Merah + J2 Hijau + J3 Merah
      Serial.println("Manual hijau 2");
      bangjoHijau2();
      bangjoMerah1();
      bangjoMerah3();
      otomatis = 0;
      break;
    case 3: //J1 Merah + J2 Merah + J3 Hijau
      Serial.println("Manual hijau 3");
      bangjoHijau3();
      bangjoMerah2();
      bangjoMerah1();
      otomatis = 0;
      break;
    default: //Otomatis
      Serial.print("Otomatis");
      otomatis = 1;
      break;
  }
}

void setup()
{
  Serial.begin(9600);
  delay(10);
  EspSerial.begin(ESP8266_BAUD);
  delay(10);
  Blynk.begin(auth, wifi, ssid, pass, "blynk-cloud.com", 8080);

  pinMode(ledR1, OUTPUT);
  pinMode(ledG1, OUTPUT);
  pinMode(ledR2, OUTPUT);
  pinMode(ledG2, OUTPUT);
  pinMode(ledR3, OUTPUT);
  pinMode(ledG3, OUTPUT);
}

void loop()
{
  Blynk.run();
  if (otomatis == 1) {
    Serial.println("hijau 1");
    bangjoHijau1();
    bangjoMerah2();
    bangjoMerah3();
    delay(3000);
    Serial.println("hijau 2");
    bangjoHijau2();
    bangjoMerah1();
    bangjoMerah3();
    delay(3000);
    Serial.println("hijau 3");
    bangjoHijau3();
    bangjoMerah2();
    bangjoMerah1();
    delay(3000);

  }
  timer.run();
}
