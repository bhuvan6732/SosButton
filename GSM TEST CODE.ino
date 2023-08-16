

void setup()
{
    // initialize serial communications at 9600 bps:
    Serial.begin(9600);

    delay(10000);
    // print the serial data to GSM
    Serial.print("ATD9999999999;"); // change here to call a number using SIM800
    // wait 10 seconds before the next loop
    delay(10000);
    Serial.print("ATH"); // hold the call
}

void loop()
{
}
