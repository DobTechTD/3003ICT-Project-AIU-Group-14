// --------------------------------------------------
// Helper Logic Functions
// --------------------------------------------------
bool irrigationDemandActive() {
  return soilDry && tempHigh && !waterLow && !waterFailsafe && sensorsValid;
}

bool severeHeatDryWarningActive() {
  return tempWarning && soilSeverelyDry;
}

// --------------------------------------------------
// FSM Update Logic
// --------------------------------------------------
void updateFSM(unsigned long currentTime, bool buttonPressedEvent) {

  // Start system from IDLE
  if (currentState == IDLE) {
    if (buttonPressedEvent) {
      warningAcknowledged = false;
      irrigationTimedOut = false;
      changeState(MONITORING);
    }
    return;
  }

  // Manual reset from FAILSAFE only when water is safely recovered
  if (currentState == FAILSAFE) {
    if (buttonPressedEvent && sensorsValid && waterPercent >= WATER_FAILSAFE_OFF) {
      waterFailsafe = false;
      warningAcknowledged = false;
      irrigationTimedOut = false;
      changeState(IDLE);
    }
    return;
  }

  // Universal failsafe rule
  if (!sensorsValid || waterFailsafe) {
    if (currentState != FAILSAFE) {
      changeState(FAILSAFE);
    }
    return;
  }

  switch (currentState) {

    case MONITORING:
      warningAcknowledged = false;

      if (waterLow) {
        changeState(WARNING);
      }
      else if (severeHeatDryWarningActive()) {
        changeState(WARNING);
      }
      else if (irrigationDemandActive() && irrigationCooldownFinished(currentTime)) {
        changeState(IRRIGATING);
      }
      break;

    case IRRIGATING:
      // Low-water pump lockout
      if (waterLow) {
        changeState(WARNING);
      }
      else if (severeHeatDryWarningActive()) {
        changeState(WARNING);
      }
      else if (currentTime - stateStartTime >= IRRIGATION_TIMEOUT) {
        irrigationTimedOut = true;
        lastIrrigationEndTime = currentTime;
        changeState(WARNING);
      }
      else if (!soilDry) {
        lastIrrigationEndTime = currentTime;
        changeState(MONITORING);
      }
      break;

    case WARNING:
      // Manual warning acknowledge: mutes buzzer but stays in WARNING if the risk is still active
      if (buttonPressedEvent) {
        warningAcknowledged = true;

        // Timeout can only be cleared if irrigation demand is no longer active
        if (irrigationTimedOut &&
            !waterLow &&
            !severeHeatDryWarningActive() &&
            !irrigationDemandActive()) {
          irrigationTimedOut = false;
          changeState(MONITORING);
          return;
        }
      }

      // Auto-clear warning only for non-timeout warnings when conditions become safe
      if (!waterLow && !severeHeatDryWarningActive() && !irrigationTimedOut) {
        warningAcknowledged = false;
        changeState(MONITORING);
      }
      break;

    case FAILSAFE:
      // Handled above
      break;

    case IDLE:
      // Handled above
      break;
  }
}

// --------------------------------------------------
// Cooldown Helper
// --------------------------------------------------
bool irrigationCooldownFinished(unsigned long currentTime) {
  return currentTime - lastIrrigationEndTime >= IRRIGATION_COOLDOWN;
}

// --------------------------------------------------
// Change State Helper
// --------------------------------------------------
void changeState(SystemState newState) {
  if (currentState != newState) {
    currentState = newState;
    stateStartTime = millis();

    if (newState == WARNING) {
      warningAcknowledged = false;
    }

    Serial.print("State changed to: ");
    Serial.println(getStateName(currentState));
  }
}

// --------------------------------------------------
// State Name Helper
// --------------------------------------------------
const char* getStateName(SystemState state) {
  switch (state) {
    case IDLE:
      return "IDLE";

    case MONITORING:
      return "MONITOR";

    case IRRIGATING:
      return "IRRIGATE";

    case WARNING:
      return "WARNING";

    case FAILSAFE:
      return "FAILSAFE";

    default:
      return "UNKNOWN";
  }
}
