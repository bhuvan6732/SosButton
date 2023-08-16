#include <SoftwareSerial.h>

SoftwareSerial gsmSerial(3, 2); // RX, TX

void setup()
{
   gsmSerial.begin(9600); // Setting the baud rate of GSM Module
   Serial.begin(9600);    // Setting the baud rate of Serial Monitor (Arduino)
   delay(1000);
   Serial.println("Preparing to send SMS");
   SendMessage();
}

void loop()
{
}
void SendMessage()
{
   Serial.println("Setting the GSM in text mode");
   gsmSerial.println("AT+CMGF=1\r");
   delay(2000);
   Serial.println("Sending SMS to the desired phone number!");
   gsmSerial.println("AT+CMGS=\"+919999999999\"\r");
   // Replace x with mobile number
   delay(2000);

   gsmSerial.println("Hello from SIM900"); // SMS Text
   delay(200);
   gsmSerial.println((char)26); // ASCII code of CTRL+Z
   delay(2000);
}
