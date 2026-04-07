# Simon Says - Arduino Uno

A hardware implementation of the classic Simon Says memory game. The Arduino lights up a random sequence of LEDs, each paired with a unique tone from a buzzer. The player repeats the sequence using four buttons — get it wrong and the game resets, get through all 20 rounds and you win.

---

## Components

| Part | Quantity |
|------|----------|
| Arduino Uno | 1 |
| LEDs (different colours) | 4 |
| Push buttons | 4 |
| Passive buzzer | 1 |
| 220Ω resistors (for LEDs) | 4 |
| Breadboard + jumper wires | — |

---

## Wiring

| Component | Arduino Pin |
|-----------|-------------|
| LED 1 | D2 |
| LED 2 | D3 |
| LED 3 | D4 |
| LED 4 | D5 |
| Button 1 | D6 |
| Button 2 | D7 |
| Button 3 | D8 |
| Button 4 | D9 |
| Buzzer | D10 |

Each LED is wired in series with a 220Ω resistor to ground. Buttons use Arduino's internal pull-up resistors (INPUT_PULLUP), so one leg connects to the pin and the other to ground.

---

## How it Works

1. On startup all LEDs flash three times to signal the game is starting
2. The Arduino plays a sequence — each LED lights up alongside a unique tone
3. The player repeats the sequence by pressing the matching buttons in order
4. A correct round adds one more step to the sequence
5. A wrong press triggers a game over animation and the game restarts
6. Completing all 20 rounds triggers a win sequence and restarts

---

## How to Upload

1. Open the Arduino IDE
2. Connect your Uno via USB
3. Open `simon_says.ino`
4. Select your board: Tools → Board → Arduino Uno
5. Select your port: Tools → Port → (your COM port)
6. Click Upload

---

## Notes

- The random sequence is seeded from an unconnected analog pin (A0), giving a different game each time
- Button debouncing is handled in software with a short delay
- Tones used: C4, E4, G4, C5 — a simple major chord spread across the four buttons

---

## Demo

![Watch the demo](demo/demo.mp4)
