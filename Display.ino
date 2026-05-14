// --------------------------------------------------
// LCD Display
// --------------------------------------------------
void updateLCD() {
  lcd.clear();

  lcd.setCursor(0, 0);
  lcd.print("State:");
  lcd.print(getStateName(currentState));

  lcd.setCursor(0, 1);
  lcd.print("T:");
  if (!sensorsValid) {
    lcd.print("ERR");
  } else {
    lcd.print(temperatureC, 1);
    lcd.print("C");
  }

  lcd.setCursor(10, 1);
  lcd.print(isDay ? "DAY" : "NIGHT");

  lcd.setCursor(0, 2);
  lcd.print("Soil:");
  lcd.print(soilPercent);
  lcd.print("%");

  lcd.setCursor(10, 2);
  lcd.print("W:");
  lcd.print(waterPercent);
  lcd.print("%");

  lcd.setCursor(0, 3);
  lcd.print("L:");
  lcd.print(lightPercent);
  lcd.print("% ");

  if (currentState == WARNING) {
    if (irrigationTimedOut) {
      lcd.print("TIMEOUT");
    } else if (waterLow) {
      lcd.print("LOW WTR");
    } else {
      lcd.print("HEAT/DRY");
    }
  } 
  else if (currentState == FAILSAFE) {
    lcd.print("LOCKOUT");
  } 
  else {
    lcd.print("Pump:");
    lcd.print(currentState == IRRIGATING ? "ON" : "OFF");
  }
}

// --------------------------------------------------
// Serial Monitor Output
// --------------------------------------------------
void printSerialData() {
  Serial.println("----------------------------");

  Serial.print("State: ");
  Serial.println(getStateName(currentState));

  Serial.print("Temperature: ");
  if (!sensorsValid) {
    Serial.println("ERROR");
  } else {
    Serial.print(temperatureC);
    Serial.println(" C");
  }

  Serial.print("Light: ");
  Serial.print(lightPercent);
  Serial.print("% | ");
  Serial.println(isDay ? "DAY" : "NIGHT");

  Serial.print("Soil: ");
  Serial.print(soilPercent);
  Serial.print("% | Dry: ");
  Serial.print(soilDry ? "YES" : "NO");
  Serial.print(" | Severe Dry: ");
  Serial.println(soilSeverelyDry ? "YES" : "NO");

  Serial.print("Water: ");
  Serial.print(waterPercent);
  Serial.print("% | Low: ");
  Serial.print(waterLow ? "YES" : "NO");
  Serial.print(" | Failsafe: ");
  Serial.println(waterFailsafe ? "YES" : "NO");

  Serial.print("Temp High: ");
  Serial.print(tempHigh ? "YES" : "NO");
  Serial.print(" | Temp Warning: ");
  Serial.println(tempWarning ? "YES" : "NO");

  Serial.print("Warning Acknowledged: ");
  Serial.println(warningAcknowledged ? "YES" : "NO");

  Serial.print("Irrigation Timed Out: ");
  Serial.println(irrigationTimedOut ? "YES" : "NO");

  Serial.print("Sensor Interval: ");
  Serial.print(getSensorInterval());
  Serial.println(" ms");
}
