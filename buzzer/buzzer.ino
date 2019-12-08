#define BUZZER_PIN  6

void setup() {
  pinMode(BUZZER_PIN, OUTPUT);
}

void loop() {
  // pulse the buzzer on for a short time
  digitalWrite(BUZZER_PIN, HIGH);
  delay(100);
  digitalWrite(BUZZER_PIN, LOW);
  delay(2000);
}
