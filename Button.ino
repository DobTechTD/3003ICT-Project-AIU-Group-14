bool readButtonPressedEvent() {
  bool reading = digitalRead(BUTTON_PIN);

  if (reading != lastButtonReading) {
    lastDebounceTime = millis();
  }

  bool pressedEvent = false;

  if ((millis() - lastDebounceTime) > DEBOUNCE_DELAY) {
    if (reading != stableButtonState) {
      stableButtonState = reading;

      if (stableButtonState == LOW) {
        pressedEvent = true;
      }
    }
  }

  lastButtonReading = reading;
  return pressedEvent;
}
