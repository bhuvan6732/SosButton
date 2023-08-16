#include <SoftwareSerial.h>
SoftwareSerial mySerial(3, 2);
char msg;
char call;

void setup()
{
  mySerial.begin(9600);
  mySerial.println("AT+COPS?"); // Setting the baud rate of GSM Module
  mySerial.println("AT+CSQ");
  Serial.begin(9600); // Setting the baud rate of Serial Monitor (Arduino)
  Serial.println("GSM SIMS00A BEGIN");
  Serial.println("Enter character for control option:");
  Serial.println("h : to disconnect a call");
  Serial.println("i : to receive a call");
  Serial.println("s : to send message");
  Serial.println("r : to receive message");
  Serial.println("c : to make a call");
  Serial.println("e : to redial");
  Serial.println();
  delay(1000);
}
void loop()
{
  if (Serial.available() > 0)
    switch (Serial.read())
    {
    case 's':
      SendMessage();
      break;
    case 'r':
      ReceiveMessage();
      break;
    case 'c':
      MakeCall();
      break;
    case 'i':
      ReceiveCall();
      break;
    }
  if (mySerial.available() > 0)
    Serial.write(mySerial.read());
}

void SendMessage()

{

  Serial.println("Setting the GSM in text mode");
  mySerial.println("AT+CMGF=1\r");
  delay(2000);
  Serial.println("Sending SMS to the desired phone number!");
  mySerial.println("AT+CMGS=\"+919999999999\"\r");
  // Replace x with mobile number
  delay(2000);

  mySerial.println("Hello from SIM900"); // SMS Text
  delay(200);
  mySerial.println((char)26); // ASCII code of CTRL+Z
  delay(2000);
}

void ReceiveMessage()
{
  mySerial.println("AT+CNMI=2,2,0,0,0"); // AT Command to recieve a live SMS
  delay(1000);
  if (mySerial.available() > 0)
  {
    msg = mySerial.read();
    Serial.print(msg);
  }
}

void MakeCall()

{
  mySerial.println("atd9999999999;"); // watch out here for semicolon at the end!!
  Serial.println("Calling ");         // print response over serial port
  delay(1000);
}

void ReceiveCall()
{
  mySerial.println("ATA");
  delay(1000);
  {
    call = mySerial.read();
    Serial.print(call);
  }
}

void RedialCall()

{
  mySerial.println("ATDL");
  Serial.println("Redialing");
  delay(1000);
}
