#define BLYNK_PRINT Serial
#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>
BlynkTimer timer;
char auth[] = "Z35wFDPMmUsXGZUi4MbVsMYtA940sLLL"; // Auth Token in Blynk Application or by email.
char ssid[] = "debarghya"; //wifi name
char pass[] = "debarghya2006"; //wifi password

int Raw= 0;
double Volt = 0;
double Celcius = 0;
const int ledPin = 2; // Led di pin 22
const int lmPin = 35; // LM35 di pin 35
void setup()
{
Serial.begin(115200);
// Blynk configuration system
Blynk.begin(auth, ssid, pass);
pinMode (lmPin, INPUT); // LM35 as input
pinMode (ledPin, OUTPUT); // LED as output
timer.setInterval(1000L, sendUptime); // Data will be send to Blynk for every 1 second
}
void sendUptime()
{
Blynk.virtualWrite(V1, Celcius); // Virtual Pin
}
void loop()
{
Blynk.run();
timer.run();
Raw = analogRead(lmPin); // Original data reading from LM35 sensor
Volt = (Raw / 1024.0) * 5000; // Convert original data according to the voltage used (3.3v)
Celcius = Volt * 0.019; // Find the temperature value in Celsius // location, device and set up @ debargha's home 
Serial.println(Celcius);
if (Celcius >= 35){
digitalWrite (ledPin, HIGH); // The LED will turn on if the temperature is more than 35 Celcius
}
else{
digitalWrite (ledPin, LOW); // The LED will turn off if the temperature is less than 35 Celcius
}
delay(2000); // Slow down the reading of the data for 2 seconds
}
