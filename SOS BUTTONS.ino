#include <TinyGPS++.h>

TinyGPSPlus gps;

#include <SoftwareSerial.h>
SoftwareSerial mySerial(3, 2);
SoftwareSerial mySerial1(4, 5);
char msg;
char call;

float Lat, Lon;
void setup()
{
  mySerial.begin(9600);
  mySerial1.begin(38400);
  Serial.begin(19200);
  pinMode(12, INPUT);
  pinMode(9, OUTPUT);
}
void loop()
{
  int key = digitalRead(12);

  while (mySerial1.available() > 0)
  {
    gps.encode(mySerial1.read());
    if (gps.location.isUpdated())
    {
      Lat = gps.location.lat();
      Lon = gps.location.lng();
    }
  }

  if (key == 0)
  {
    Serial.println("Setting the GSM in text mode");
    digitalWrite(9, HIGH);
    sendsms();
    digitalWrite(9, LOW);
  }
}
void sendsms()
{

  Serial.println("Setting the GSM in text mode");
  mySerial.println("AT+CMGF=1\r");
  delay(2000);
  Serial.println("Sending SMS to the desired phone number!");
  mySerial.println("AT+CMGS=\"+919999999999\"\r");
  // Replace x with mobile number
  delay(2000);
  // mySerial.println("Help me please");
  String msg = "I want Help !!!Location: Lat: " + String(Lat) + " Lon: " + String(Lon);
  mySerial.println(msg);
  delay(200);
  mySerial.println((char)26); // ASCII code of CTRL+Z
  delay(2000);
}
