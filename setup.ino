
void setPinConfiguration()
{
    pinMode(RELAY_FAN_PIN, OUTPUT);
    pinMode(RELAY_CIRCULATION_PIN, OUTPUT);
    pinMode(RELAY_HEATER_PIN, OUTPUT);
    pinMode(RELAY_LIGHT_PIN, OUTPUT);
    pinMode(RELAY_OZONE, OUTPUT);

    pinMode(NIGHT_LIGHT_PIN, OUTPUT);

    pinMode(BUTTON_ERASE_PIN, INPUT_PULLUP);
    pinMode(BUTTON_FEED_PIN, INPUT_PULLUP);
}

void setInititalCondition()
{
    digitalWrite(RELAY_FAN_PIN, LOW);
    digitalWrite(RELAY_CIRCULATION_PIN, LOW);
    digitalWrite(RELAY_HEATER_PIN, LOW);
    digitalWrite(RELAY_OZONE, LOW);
    digitalWrite(RELAY_LIGHT_PIN, LOW);
    digitalWrite(NIGHT_LIGHT_PIN, 0);
}

