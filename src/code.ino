#define BLYNK_TEMPLATE_ID ""               // Enter Blynk Template ID
#define BLYNK_TEMPLATE_NAME ""             // Enter Blynk Template Name

#include <Wire.h>                         // Include required libraries for I2C communication
#include "MAX30100_PulseOximeter.h"       // Library for MAX30100 pulse oximeter
#define BLYNK_PRINT Serial                // Enable debug prints for Blynk
#include <Blynk.h>                        // Blynk IoT library
#include <ESP8266WiFi.h>                  // ESP8266 WiFi library
#include <BlynkSimpleEsp8266.h>           // Blynk ESP8266 support library

#include "Wire.h"                         // Library for I2C communication
#include "Adafruit_GFX.h"                 // Graphics library for OLED
#include "OakOLED.h"                      // OLED display library

#define REPORTING_PERIOD_MS 1000          // Reporting period for sensor data in milliseconds
OakOLED oled;                             // Initialize the OLED object

#define AD8232_PIN A0                     // Define the analog pin for ECG sensor

// Blynk credentials
char auth[] = "";                         // Blynk Auth Token
char ssid[] = "";                         // WiFi SSID
char pass[] = "";                         // WiFi Password

PulseOximeter pox;                        // Initialize PulseOximeter object

// Variables for storing sensor data
float BPM, SpO2, sensorValue;            
uint32_t tsLastReport = 0;                // Timestamp for last report

void setup()
{
    Blynk.begin(auth, ssid, pass);        // Initialize Blynk connection
    Serial.begin(115200);                // Start serial communication
    oled.begin();                        // Initialize the OLED display
    oled.clearDisplay();                 // Clear the OLED display
    oled.setTextSize(1);
    oled.setTextColor(1);
    oled.setCursor(0, 0);
    oled.println("Initializing pulse oximeter..");
    oled.display();
    delay(1000);
    
    pinMode(16, OUTPUT);                 // Set pin 16 as output (optional, replace with your logic)
    pinMode(AD8232_PIN, INPUT);          // Set ECG pin as input
    
    Serial.print("Initializing Pulse Oximeter..");
    if (!pox.begin())                    // Initialize the pulse oximeter
    {
        Serial.println("FAILED");
        oled.clearDisplay();
        oled.setTextSize(1);
        oled.setTextColor(1);
        oled.setCursor(0, 0);
        oled.println("FAILED");
        oled.display();
        for(;;);                         // Halt if initialization fails
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
    pox.setIRLedCurrent(MAX30100_LED_CURR_7_6MA); // Set LED current for pulse oximeter
}

void loop()
{
    pox.update();                        // Update pulse oximeter readings
    Blynk.run();                         // Run Blynk process

    BPM = pox.getHeartRate();            // Get heart rate
    SpO2 = pox.getSpO2();                // Get SpO2 level
    sensorValue = analogRead(AD8232_PIN);// Read ECG sensor value
    
    Serial.print("ECG Value: "); 
    Serial.println(sensorValue);
    delay(40);                           // Delay for stable readings

    if (millis() - tsLastReport > REPORTING_PERIOD_MS) // Check if reporting period has elapsed
    {
        // Print heart rate and SpO2 to Serial Monitor
        Serial.print("Heart rate: ");
        Serial.print(BPM);
        Serial.print(" bpm / SpO2: ");
        Serial.print(SpO2);
        Serial.println(" %");
 
        // Update OLED display with sensor values
        oled.clearDisplay();
        oled.setTextSize(2);
        oled.setTextColor(1);
        oled.setCursor(40, 0);
        oled.println(pox.getHeartRate());
 
        oled.setTextSize(2);
        oled.setCursor(0, 0);
        oled.println("HR");

        oled.setTextSize(1);
        oled.setCursor(100, 0);
        oled.println("bpm");
 
        oled.setTextSize(2);
        oled.setCursor(0, 45);
        oled.println("Spo2");
 
        oled.setTextSize(2);
        oled.setCursor(60, 45);
        oled.println(pox.getSpO2());
        oled.display();

        oled.setTextSize(1);
        oled.setCursor(100, 30);
        oled.println("%");
 
        // Send data to Blynk Virtual Pins
        Blynk.virtualWrite(V0, BPM);
        Blynk.virtualWrite(V1, SpO2)

        tsLastReport = millis();         // Update the timestamp
    }
}
