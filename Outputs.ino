// --------------------------------------------------
// Apply State Outputs
// --------------------------------------------------
void applyStateOutputs(unsigned long currentTime) {
  switch (currentState) {

    case IDLE:
      digitalWrite(RELAY_PIN, RELAY_OFF);
      noTone(BUZZER_PIN);
      setRGB(false, false, true); // Blue
      break;

    case MONITORING:
      digitalWrite(RELAY_PIN, RELAY_OFF);
      noTone(BUZZER_PIN);
      setRGB(false, true, false); // Green
      break;

    case IRRIGATING:
      // Safety backup: pump cannot run if water is low/failsafe
      if (!waterLow && !waterFailsafe && sensorsValid) {
        digitalWrite(RELAY_PIN, RELAY_ON);
      } else {
        digitalWrite(RELAY_PIN, RELAY_OFF);
      }

      noTone(BUZZER_PIN);
      setRGB(false, true, true); // Cyan
      break;

    case WARNING:
      digitalWrite(RELAY_PIN, RELAY_OFF);
      setRGB(true, true, false); // Yellow

      if (warningAcknowledged) {
        noTone(BUZZER_PIN);
      } else {
        // Slow warning beep
        if ((currentTime / 500) % 2 == 0) {
          tone(BUZZER_PIN, 800);
        } else {
          noTone(BUZZER_PIN);
        }
      }
      break;

    case FAILSAFE:
      digitalWrite(RELAY_PIN, RELAY_OFF);
      setRGB(true, false, false); // Red

      // Fast critical beep
      if ((currentTime / 200) % 2 == 0) {
        tone(BUZZER_PIN, 1500);
      } else {
        noTone(BUZZER_PIN);
      }
      break;
  }
}

// --------------------------------------------------
// RGB Helper
// Common cathode RGB:
// HIGH = colour ON
// LOW  = colour OFF
// --------------------------------------------------
void setRGB(bool red, bool green, bool blue) {
  digitalWrite(RGB_RED_PIN, red ? HIGH : LOW);
  digitalWrite(RGB_GREEN_PIN, green ? HIGH : LOW);
  digitalWrite(RGB_BLUE_PIN, blue ? HIGH : LOW);
}
