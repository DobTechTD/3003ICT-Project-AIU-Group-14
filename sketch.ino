#include "Config.h"

// --------------------------------------------------
// Setup
// --------------------------------------------------
void setup() {
  Serial.begin(9600);

  dht.begin();

  lcd.init();
  lcd.backlight();

  pinMode(BUTTON_PIN, INPUT_PULLUP);

  pinMode(RELAY_PIN, OUTPUT);
  pinMode(BUZZER_PIN, OUTPUT);

  pinMode(RGB_RED_PIN, OUTPUT);
  pinMode(RGB_GREEN_PIN, OUTPUT);
  pinMode(RGB_BLUE_PIN, OUTPUT);

  digitalWrite(RELAY_PIN, RELAY_OFF);
  noTone(BUZZER_PIN);
  setRGB(false, false, true);

  lcd.setCursor(0, 0);
  lcd.print("A.I.U ADV FSM");
  lcd.setCursor(0, 1);
  lcd.print("Checkpoint 3/4");
  lcd.setCursor(0, 2);
  lcd.print("Press button");
  lcd.setCursor(0, 3);
  lcd.print("to start");

  Serial.println("A.I.U Advanced FSM Started");
  Serial.println("Initial State: IDLE");
}

// --------------------------------------------------
// Main Loop
// --------------------------------------------------
void loop() {
  unsigned long currentTime = millis();

  bool buttonPressedEvent = readButtonPressedEvent();

  // Adaptive polling rate based on state
  if (currentTime - lastSensorRead >= getSensorInterval()) {
    lastSensorRead = currentTime;
    readSensors();
    updateHysteresisFlags();
  }

  updateFSM(currentTime, buttonPressedEvent);
  applyStateOutputs(currentTime);

  if (currentTime - lastLcdUpdate >= LCD_INTERVAL) {
    lastLcdUpdate = currentTime;
    updateLCD();
    printSerialData();
  }
}
