
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
#include <ESP32Servo.h>

//----------------------------------------------
// GLOBAL VARIABLES and CONSTANTS
// your code here
const int RED_PIN = 26;
const int GREEN_PIN = 27;
const int BLUE_PIN = 14;
const int YELLOW_PIN = 12;
const int Buzzer_PIN = 32;
const int BUTTON_PIN = 25;

const int SERVO_PIN = 5;

Servo myServo;
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
int buzzer_frequency = 1000;
bool buzzer_status = false;

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


BLYNK_WRITE(V7)
{   
  int value = param.asInt();
  buzzer_frequency = value; // Get value as integer
}

BLYNK_WRITE(V8)
{   
  int value = param.asInt();
  myServo.write(value);
  Serial.print("Servo Angle: ");
  Serial.println(value);
}

BLYNK_WRITE(V3)
{   
  int value = param.asInt();
  // if (value == 1){
  //   ledcWriteTone(0, buzzer_frequency); // Start buzzer at specified frequency
  //   buzzer_status  = true;
  //   Serial.println("Buzzer ON");
  //   Serial.print("Frequency: ");
  //   Serial.println(buzzer_frequency);
  // } else {
  //   ledcWriteTone(0, 0); // Stop buzzer
  //   buzzer_status  = false;
  //   Serial.println("Buzzer OFF");
  // }
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
    pinMode(Buzzer_PIN, OUTPUT);
    // ledcSetup(0, buzzer_frequency, 8);
    // ledcAttachPin(Buzzer_PIN, 0);

    pinMode(BUTTON_PIN, INPUT);

    myServo.attach(SERVO_PIN);

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

    // Detect button press and release - to send value to V4 - button is active HIGH
    static bool lastButtonState = LOW;
    bool currentButtonState = digitalRead(BUTTON_PIN);
    static uint32_t lastDebounceTime = 0;
    
    if (currentButtonState != lastButtonState && (millis() - lastDebounceTime) > 100) {
        if (currentButtonState == HIGH) {
            Blynk.virtualWrite(V4, 1); // Button pressed
            Serial.println("Button Pressed - V4 set to 1");
        } else {
            Blynk.virtualWrite(V4, 0); // Button released
            Serial.println("Button Released - V4 set to 0");
        }
        lastButtonState = currentButtonState;
        lastDebounceTime = millis();
    }
    

    static uint32_t startTime = millis();
    static bool lastBuzzerStatus = false;

    // if (buzzer_status == true && lastBuzzerStatus == false) {
    //     startTime = millis();
    //     lastBuzzerStatus = true;
    // } else if (buzzer_status == false) {
    //     lastBuzzerStatus = false;
    // }

    // if (millis() - startTime >= 2000 && buzzer_status == true) {
    //     // Stop the buzzer after 2 seconds
    //     ledcWriteTone(0, 0);
    //     buzzer_status = false;
    //     lastBuzzerStatus = false;
    // }
}