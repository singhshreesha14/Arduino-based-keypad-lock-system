**Arduino-Based Key Lock System**

This project implements a secure electronic key lock system using an Arduino Uno, a keypad, and a servo motor. The system verifies a predefined password entered via the keypad. If the password matches, the servo motor rotates to unlock; otherwise, access is denied. An LCD display provides real-time feedback, showing messages like “Enter Password,” “Door Opened,” or “Wrong Password.”

The system offers a simple, reliable, and low-cost security solution suitable for homes, lockers, and offices.

**Key Features**

Password-protected door lock system

LCD display for user interaction

Servo motor-based locking mechanism

Option to reset or change password

Compact, efficient, and cost-effective

**Components Used**

Arduino Uno

4x4 Keypad

16x2 I2C LCD Display

Servo Motor

Jumper Wires and Breadboard

**Working**

The user enters a password using the keypad.

The Arduino compares the entered password with the stored one.

If correct, the servo rotates to unlock; otherwise, an error message is displayed.

The door can be locked or unlocked using the keypad commands.

**Future Enhancements**

Add fingerprint or RFID authentication

Integrate IoT for remote control

Enable dynamic password updates
