# SmartCutStepper

SmartCutStepper is an Arduino-based stepper motor controller that uses a keypad and LCD display to cut material to specified lengths. It features configurable cutting length and motor speed, and allows real-time interruption using the keypad.

## 🚀 Features

- Stepper motor control via keypad
- LCD display interface
- Enter desired cutting length
- Set motor speed in mm/sec
- Interrupt cutting mid-operation with `#` key
- Displays how far the motor moved if interrupted

## 🧰 Hardware Requirements

- Arduino Uno (or compatible board)
- 28BYJ-48 Stepper Motor + ULN2003 driver board
- 4x4 or 3x4 Keypad
- 16x2 LCD (HD44780 compatible)
- Potentiometer for LCD contrast (optional)
- Jumper wires & breadboard

## 🔌 Wiring Overview

| Component     | Arduino Pin |
|---------------|-------------|
| LCD RS        | A4          |
| LCD E         | A5          |
| LCD D4-D7     | A3, A2, A1, A0 |
| Keypad Rows   | 0, 1, 2, 3  |
| Keypad Cols   | 4, 5, 6     |
| Stepper IN1-4 | 8, 9, 10, 11 |

> Adjust the pin numbers in the code if your setup differs.

> Circuit
![circuit]([https://github.com/ArdeshirV/sample/blob/master/gplv3.svg](https://github.com/Natnael1alem/smartcut-arduino/blob/main/sensor.svg))

## 📦 Libraries Used

- [Keypad](https://www.arduino.cc/reference/en/libraries/keypad/)
- [LiquidCrystal](https://www.arduino.cc/en/Reference/LiquidCrystal)
- [Stepper](https://www.arduino.cc/en/Reference/Stepper)

Install these via the Arduino Library Manager.

## 📄 How to Use

1. Upload the code to your Arduino.
2. On boot, choose an option:
   - `1`: Enter cutting length (in meters)
   - `2`: Set stepper motor speed
3. Press `#` during a cut to stop the motor and see how far it moved.
4. Press `*` to clear input or return to main menu.

## 📷 Preview

*(Add photo or wiring diagram here if you have one)*

## 📜 License

MIT License

---

Built with 🛠️ and a bit of patience!
