#define BUZZER_PIN 25

// Frequencies of Sa Re Ga Ma Pa Dha Ni Sa (Middle Octave)
int notes[] = {
  262,  // Sa (C4)
  294,  // Re (D4)
  330,  // Ga (E4)
  349,  // Ma (F4)
  392,  // Pa (G4)
  440,  // Dha (A4)
  494,  // Ni (B4)
  523   // Sa (C5)
};

void setup() {
  // Configure PWM channel
  ledcAttach(BUZZER_PIN, 2000, 8);
}

void loop() {

  for (int i = 0; i < 8; i++) {

    ledcWriteTone(BUZZER_PIN, notes[i]);
    delay(500);

    ledcWriteTone(BUZZER_PIN, 0);
    delay(100);
  }

  delay(2000);
}