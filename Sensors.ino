// --------------------------------------------------
// Adaptive Polling Rate
// --------------------------------------------------
unsigned long getSensorInterval() {
  switch (currentState) {
    case IDLE:
      return 2000;   // Slow checks while idle

    case MONITORING:
      return 1000;   // Normal checking

    case IRRIGATING:
      return 500;    // Faster checking while pump is active

    case WARNING:
      return 300;    // Fast checks during warning

    case FAILSAFE:
      return 250;    // Fast safety checks

    default:
      return 1000;
  }
}

// --------------------------------------------------
// Read Sensors
// --------------------------------------------------
void readSensors() {
  float tempReading = dht.readTemperature();

  if (isnan(tempReading) || tempReading < MIN_VALID_TEMP || tempReading > MAX_VALID_TEMP) {
    sensorsValid = false;
  } else {
    sensorsValid = true;
    temperatureC = tempReading;
  }

  soilRaw = analogRead(SOIL_PIN);
  waterRaw = analogRead(WATER_PIN);
  lightRaw = analogRead(LIGHT_PIN);

  soilPercent = map(soilRaw, 0, 1023, 0, 100);
  waterPercent = map(waterRaw, 0, 1023, 0, 100);
  lightPercent = map(lightRaw, 0, 1023, 0, 100);

  soilPercent = constrain(soilPercent, 0, 100);
  waterPercent = constrain(waterPercent, 0, 100);
  lightPercent = constrain(lightPercent, 0, 100);
}

// --------------------------------------------------
// Hysteresis Logic
// --------------------------------------------------
void updateHysteresisFlags() {

  // Day/night hysteresis
  if (!isDay && lightPercent > DAY_ON_THRESHOLD) {
    isDay = true;
  } 
  else if (isDay && lightPercent < NIGHT_ON_THRESHOLD) {
    isDay = false;
  }

  // Soil dry hysteresis
  if (!soilDry && soilPercent < SOIL_DRY_ON) {
    soilDry = true;
  } 
  else if (soilDry && soilPercent > SOIL_DRY_OFF) {
    soilDry = false;
  }

  // Severe dryness hysteresis
  if (!soilSeverelyDry && soilPercent < SOIL_SEVERE_DRY_ON) {
    soilSeverelyDry = true;
  } 
  else if (soilSeverelyDry && soilPercent > SOIL_SEVERE_DRY_OFF) {
    soilSeverelyDry = false;
  }

  // Water low hysteresis
  if (!waterLow && waterPercent < WATER_LOW_ON) {
    waterLow = true;
  } 
  else if (waterLow && waterPercent > WATER_LOW_OFF) {
    waterLow = false;
  }

  // Water failsafe hysteresis
  if (!waterFailsafe && waterPercent < WATER_FAILSAFE_ON) {
    waterFailsafe = true;
  } 
  else if (waterFailsafe && waterPercent >= WATER_FAILSAFE_OFF) {
    waterFailsafe = false;
  }

  // Temperature thresholds depend on day/night
  float highOn;
  float highOff;
  float warnOn;
  float warnOff;

  if (isDay) {
    highOn = DAY_TEMP_HIGH_ON;
    highOff = DAY_TEMP_HIGH_OFF;
    warnOn = DAY_TEMP_WARNING_ON;
    warnOff = DAY_TEMP_WARNING_OFF;
  } else {
    highOn = NIGHT_TEMP_HIGH_ON;
    highOff = NIGHT_TEMP_HIGH_OFF;
    warnOn = NIGHT_TEMP_WARNING_ON;
    warnOff = NIGHT_TEMP_WARNING_OFF;
  }

  if (!tempHigh && temperatureC >= highOn) {
    tempHigh = true;
  } 
  else if (tempHigh && temperatureC <= highOff) {
    tempHigh = false;
  }

  if (!tempWarning && temperatureC >= warnOn) {
    tempWarning = true;
  } 
  else if (tempWarning && temperatureC <= warnOff) {
    tempWarning = false;
  }
}
