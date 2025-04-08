#define BLYNK_TEMPLATE_ID "TMPL31wbL7NtG"
#define BLYNK_TEMPLATE_NAME "MPMC Project"
// #define BLYNK_AUTH_TOKEN "Rnr4nCkFdarkEAMh6LnejS0TXUvqHC0D"

#include <Wire.h>
#include "MAX30100_PulseOximeter.h"
#define BLYNK_PRINT Serial
#include <Blynk.h>
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
 
#include "Wire.h"
#include "Adafruit_GFX.h"
#include "OakOLED.h"
 
#define REPORTING_PERIOD_MS 1000
OakOLED oled;

#define AD8232_PIN A0
 
char auth[] = "Rnr4nCkFdarkEAMh6LnejS0TXUvqHC0D";             // You should get Auth Token in the Blynk App.
char ssid[] = "E";                                     // Your WiFi credentials.
char pass[] = "11235813";

PulseOximeter pox;
 
float BPM, SpO2, sensorValue;
uint32_t tsLastReport = 0;
 
void setup()
{
  Blynk.begin(auth, ssid, pass);
    Serial.begin(115200);
    oled.begin();
    oled.clearDisplay();
    oled.setTextSize(1);
    oled.setTextColor(1);
    oled.setCursor(0, 0);
 
    oled.println("Initializing pulse oximeter..");
    oled.display();
    delay(1000);
    
    pinMode(16, OUTPUT);
    pinMode(AD8232_PIN, INPUT);
    
 
    Serial.print("Initializing Pulse Oximeter..");
 
    if (!pox.begin())
    {
         Serial.println("FAILED");
         oled.clearDisplay();
         oled.setTextSize(1);
         oled.setTextColor(1);
         oled.setCursor(0, 0);
         oled.println("FAILED");
         oled.display();
         for(;;);
    }
    else
    {
         oled.clearDisplay();
         oled.setTextSize(1);
         oled.setTextColor(1);
         oled.setCursor(0, 0);
         oled.println("SUCCESS");
         oled.display();
         Serial.println("SUCCESS");
}
     pox.setIRLedCurrent(MAX30100_LED_CURR_7_6MA);
 
}
 
void loop()
{
    pox.update();
    Blynk.run();
 
    BPM = pox.getHeartRate();
    SpO2 = pox.getSpO2();
    sensorValue = analogRead(AD8232_PIN);
    
    Serial.print("ECG Value "); 
    Serial.println(sensorValue);
    delay(40);
    

    if (millis() - tsLastReport > REPORTING_PERIOD_MS)
    {
        Serial.print("Heart rate:");
        Serial.print(BPM);
        Serial.print(" bpm / SpO2:");
        Serial.print(SpO2);
        Serial.println(" %");
 
        oled.clearDisplay();
        oled.setTextSize(2);
        oled.setTextColor(1);
        oled.setCursor(40,0);
        oled.println(pox.getHeartRate());
 
        oled.setTextSize(2);
        oled.setTextColor(1);
        oled.setCursor(0, 0);
        oled.println("HR");

        oled.setTextSize(1);
        oled.setCursor(100, 0);
        oled.println("bpm");
 
        oled.setTextSize(2);
        oled.setTextColor(1);
        oled.setCursor(0, 45);
        oled.println("Spo2");
 
        oled.setTextSize(2);
        oled.setTextColor(1);
        oled.setCursor(60,45);
        oled.println(pox.getSpO2());
        oled.display();

        oled.setTextSize(1);
        oled.setCursor(100, 30);
        oled.println("%");
 
        tsLastReport = millis();
        Blynk.virtualWrite(V0, BPM);
        Blynk.virtualWrite(V1, SpO2);
        //Blynk.virtualWrite(V2, sensorValue);
    }
}
