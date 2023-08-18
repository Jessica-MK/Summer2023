# Safe box project
Development (MBSE) and Proof of concept.

## Simulink MBSE development

## Keys elements
4X4 keyboard, RFID card verification, servo motor control using Arduino.

### RFID card access control
The radio frequency identification (RFID) is a form of wireless communication that allows to identify an object. In this case, a card that unlock a mechanism (example door) represented by the movement of the servo motor.  
The RFID controller is connected to the Arduino, and the authorized cards are configured in its code. When the authorized card is detected, a led turns green and the servo motor moves to the position “open” for 2 seconds. If the card scanned is not authorized, the led turns red and the servo motor does not move. 

### Keyboard password lock 
A 4x4 matrix keypad connected to Arduino allows to input numbers and letters. If the combination entered corresponds to the password set then the system “unlocks”, if not it remains locked. The “unlocked” setting is represented by the movement of the servo motor. 
