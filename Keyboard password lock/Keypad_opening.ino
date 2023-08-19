#include <Keypad.h>
#include "Servo.h"

Servo servo; // création de l'objet "servo"

const int ROW_NUM = 4; //four rows
const int COLUMN_NUM = 4; //four columns

char keys[ROW_NUM][COLUMN_NUM] = {
  {'1','4','7', '*'},
  {'2','5','8', '0'},
  {'3','6','9', '#'},
  {'A','B','C', 'D'}
};

byte pin_rows[ROW_NUM] = {9, 8, 7, 6}; //connect to the row pinouts of the keypad
byte pin_column[COLUMN_NUM] = {5, 4, 3, 2}; //connect to the column pinouts of the keypad

Keypad keypad = Keypad( makeKeymap(keys), pin_rows, pin_column, ROW_NUM, COLUMN_NUM );

const String password = "123A"; // change your password here
String input_password;

void setup(){
  Serial.begin(9600);
  input_password.reserve(32); // maximum input characters is 33, change if needed
  servo.attach(10); // attache le servo au pin spécifié
}

void loop(){
  char key = keypad.getKey();
     servo.write(180); // demande au servo de se déplacer à cette position

  if (key){
    Serial.print(key);
    if(key == '*') {
      input_password = ""; // clear input password
    } else if(key == '#') {
      if(password == input_password) {
        Serial.println("password is correct");
        // DO YOUR WORK HERE
        servo.write(90); // demande au servo de se déplacer à cette position
        delay(1000); // attend 1000 ms entre changement de position
      } else {
        Serial.println("password is incorrect, try again");
      }

      input_password = ""; // clear input password
    } else {
      input_password += key; // append new character to input password string
    }
  }
  servo.write(180);
}
