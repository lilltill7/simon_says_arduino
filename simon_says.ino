// Simon Says - Arduino Uno
// 4 LEDs, 4 buttons, 1 buzzer
// Each LED lights up with a corresponding tone when shown or pressed

const int LED_PINS[]    = {2, 3, 4, 5};
const int BUTTON_PINS[] = {6, 7, 8, 9};
const int BUZZER_PIN    = 10;

// Each colour has its own tone (Hz)
const int TONES[] = {262, 330, 392, 523}; // C, E, G, C (one octave up)

const int MAX_ROUNDS = 20;
int sequence[MAX_ROUNDS];
int round_number = 0;

void setup() {
  for (int i = 0; i < 4; i++) {
    pinMode(LED_PINS[i], OUTPUT);
    pinMode(BUTTON_PINS[i], INPUT_PULLUP);
  }
  pinMode(BUZZER_PIN, OUTPUT);
  randomSeed(analogRead(A0));
  delay(1000);
  start_game();
}

void loop() {
  play_sequence();
  if (!get_player_input()) {
    game_over();
  } else {
    round_number++;
    if (round_number >= MAX_ROUNDS) {
      win_sequence();
      start_game();
    }
    delay(1000);
  }
}

void start_game() {
  round_number = 0;
  for (int i = 0; i < MAX_ROUNDS; i++) {
    sequence[i] = random(4);
  }
  flash_all(3);
  delay(500);
}

// Light up and play the full sequence up to the current round
void play_sequence() {
  for (int i = 0; i <= round_number; i++) {
    int idx = sequence[i];
    digitalWrite(LED_PINS[idx], HIGH);
    tone(BUZZER_PIN, TONES[idx], 400);
    delay(500);
    digitalWrite(LED_PINS[idx], LOW);
    noTone(BUZZER_PIN);
    delay(200);
  }
}

// Wait for the player to repeat the sequence
// Returns true if correct, false if wrong
bool get_player_input() {
  for (int i = 0; i <= round_number; i++) {
    int pressed = wait_for_press();
    if (pressed != sequence[i]) {
      return false;
    }
    digitalWrite(LED_PINS[pressed], HIGH);
    tone(BUZZER_PIN, TONES[pressed], 300);
    delay(400);
    digitalWrite(LED_PINS[pressed], LOW);
    noTone(BUZZER_PIN);
  }
  return true;
}

// Block until a button is pressed and return its index
int wait_for_press() {
  while (true) {
    for (int i = 0; i < 4; i++) {
      if (digitalRead(BUTTON_PINS[i]) == LOW) {
        delay(50); // debounce
        while (digitalRead(BUTTON_PINS[i]) == LOW); // wait for release
        return i;
      }
    }
  }
}

void game_over() {
  // Rapid flash all LEDs with a descending tone
  for (int i = 0; i < 3; i++) {
    flash_all(1);
    tone(BUZZER_PIN, 200 - (i * 50), 300);
    delay(400);
  }
  noTone(BUZZER_PIN);
  delay(1000);
  start_game();
}

void win_sequence() {
  // Cycle through all LEDs with ascending tones
  for (int r = 0; r < 2; r++) {
    for (int i = 0; i < 4; i++) {
      digitalWrite(LED_PINS[i], HIGH);
      tone(BUZZER_PIN, TONES[i], 200);
      delay(250);
      digitalWrite(LED_PINS[i], LOW);
    }
  }
  noTone(BUZZER_PIN);
}

void flash_all(int times) {
  for (int t = 0; t < times; t++) {
    for (int i = 0; i < 4; i++) digitalWrite(LED_PINS[i], HIGH);
    tone(BUZZER_PIN, 440, 200);
    delay(300);
    for (int i = 0; i < 4; i++) digitalWrite(LED_PINS[i], LOW);
    noTone(BUZZER_PIN);
    delay(200);
  }
}
