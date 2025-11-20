
#include <Arduino.h>


/* Fill-in information from Blynk Device Info here */
#define BLYNK_TEMPLATE_ID "TMPL6RMFIQUqi"
#define BLYNK_TEMPLATE_NAME "Polito"
#define BLYNK_AUTH_TOKEN "zXcUh_D9FicRvXG_CQuEb2QlAmopJlIg"

/* Comment this out to disable prints and save space */
#define BLYNK_PRINT Serial

#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>
// #include <BlynkSimpleEsp32_SSL.h>

#include <Wire.h>
#include <hd44780.h>
#include <hd44780ioClass/hd44780_I2Cexp.h>


//----------------------------------------------
// GLOBAL VARIABLES and CONSTANTS
// your code here
const int RED_PIN = 26;
const int GREEN_PIN = 27;
const int BLUE_PIN = 14;
const int YELLOW_PIN = 12;

// LCD Configuration
hd44780_I2Cexp lcd;  // Auto-detect I2C address
const int LCD_COLS = 16;
const int LCD_ROWS = 2;

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "Wokwi-GUEST";
char pass[] = "";
// char ssid[] = "MaxPC";
// char pass[] = "polito2025";

//----------------------------------------------
// FUNCTIONS
BLYNK_WRITE(V1)
{   
  int value = param.asInt(); // Get value as integer
  digitalWrite(RED_PIN, value);
}
BLYNK_WRITE(V2)
{   
  int value = param.asInt(); // Get value as integer
  digitalWrite(GREEN_PIN, value);
}
BLYNK_WRITE(V5)
{   
  int value = param.asInt(); // Get value as integer
  digitalWrite(BLUE_PIN, value);
}

BLYNK_WRITE(V6)
{   
  int value = param.asInt(); // Get value as integer
  digitalWrite(YELLOW_PIN, value);
}
//----------------------------------------------
// SETUP FUNCTION
void setup(void) 
{
    // Serial setup
    Serial.begin(115200);
    delay(1000);
    Serial.println("Starting setup...");

    // led setup
    pinMode(RED_PIN, OUTPUT);
    pinMode(GREEN_PIN, OUTPUT);
    pinMode(BLUE_PIN, OUTPUT);
    pinMode(YELLOW_PIN, OUTPUT);

    // Initialize LCD
    int status = lcd.begin(LCD_COLS, LCD_ROWS);
    if (status) {
        Serial.println("LCD initialization failed!");
        Serial.print("Status code: ");
        Serial.println(status);
        hd44780::fatalError(status);
    }
  
    Serial.println("LCD initialized successfully!");

    // Clear LCD and display initial message
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Initializing...");
    delay(1000);

    Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);  
    // Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass, "ny3.blynk.cloud", 80);
}


//----------------------------------------------
// LOOP FUNCTION
void loop(void) 
{
    Blynk.run();
}