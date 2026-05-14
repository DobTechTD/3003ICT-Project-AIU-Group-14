#ifndef CONFIG_H
#define CONFIG_H

#include <DHT.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// --------------------------------------------------
// Pin Definitions
// --------------------------------------------------
#define DHT_PIN 2
#define DHT_TYPE DHT22

const int BUTTON_PIN = 3;
const int RELAY_PIN  = 4;
const int BUZZER_PIN = 5;

const int RGB_RED_PIN   = 9;
const int RGB_GREEN_PIN = 10;
const int RGB_BLUE_PIN  = 11;

const int SOIL_PIN  = A0;
const int WATER_PIN = A1;
const int LIGHT_PIN = A2;

// --------------------------------------------------
// Objects
// --------------------------------------------------
DHT dht(DHT_PIN, DHT_TYPE);
LiquidCrystal_I2C lcd(0x27, 20, 4);

// --------------------------------------------------
// FSM States
// --------------------------------------------------
enum SystemState {
  IDLE,
  MONITORING,
  IRRIGATING,
  WARNING,
  FAILSAFE
};

SystemState currentState = IDLE;

// --------------------------------------------------
// Relay Logic
// If your relay works backwards, swap HIGH and LOW.
// --------------------------------------------------
const int RELAY_ON = HIGH;
const int RELAY_OFF = LOW;

// --------------------------------------------------
// Hysteresis Thresholds
// --------------------------------------------------

// Soil moisture:
// Lower percentage = drier soil
const int SOIL_DRY_ON  = 40;
const int SOIL_DRY_OFF = 50;

const int SOIL_SEVERE_DRY_ON  = 20;
const int SOIL_SEVERE_DRY_OFF = 30;

// Water level
const int WATER_LOW_ON  = 25;
const int WATER_LOW_OFF = 35;

const int WATER_FAILSAFE_ON  = 10;
const int WATER_FAILSAFE_OFF = 15;

// Light level
const int DAY_ON_THRESHOLD = 50;
const int NIGHT_ON_THRESHOLD = 35;

// Day temperature thresholds
const float DAY_TEMP_HIGH_ON  = 30.0;
const float DAY_TEMP_HIGH_OFF = 28.0;

const float DAY_TEMP_WARNING_ON  = 35.0;
const float DAY_TEMP_WARNING_OFF = 33.0;

// Night temperature thresholds
const float NIGHT_TEMP_HIGH_ON  = 28.0;
const float NIGHT_TEMP_HIGH_OFF = 26.0;

const float NIGHT_TEMP_WARNING_ON  = 32.0;
const float NIGHT_TEMP_WARNING_OFF = 30.0;

// Sensor validity range
const float MIN_VALID_TEMP = -10.0;
const float MAX_VALID_TEMP = 60.0;

// --------------------------------------------------
// Timing
// --------------------------------------------------
unsigned long lastSensorRead = 0;
unsigned long lastLcdUpdate = 0;
unsigned long stateStartTime = 0;
unsigned long lastIrrigationEndTime = 0;

const unsigned long LCD_INTERVAL = 1000;

const unsigned long IRRIGATION_TIMEOUT = 8000;
const unsigned long IRRIGATION_COOLDOWN = 5000;

// --------------------------------------------------
// Sensor Variables
// --------------------------------------------------
float temperatureC = 0.0;

int soilRaw = 0;
int waterRaw = 0;
int lightRaw = 0;

int soilPercent = 0;
int waterPercent = 0;
int lightPercent = 0;

bool sensorsValid = false;

// --------------------------------------------------
// Hysteresis / Latched Condition Flags
// --------------------------------------------------
bool isDay = true;

bool soilDry = false;
bool soilSeverelyDry = false;

bool waterLow = false;
bool waterFailsafe = false;

bool tempHigh = false;
bool tempWarning = false;

// --------------------------------------------------
// Warning / Reset Flags
// --------------------------------------------------
bool warningAcknowledged = false;
bool irrigationTimedOut = false;

// --------------------------------------------------
// Button Debounce Variables
// --------------------------------------------------
bool lastButtonReading = HIGH;
bool stableButtonState = HIGH;
unsigned long lastDebounceTime = 0;
const unsigned long DEBOUNCE_DELAY = 50;

#endif
