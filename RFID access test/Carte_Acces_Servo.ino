#include "SPI.h"
#include "MFRC522.h"
#include "Servo.h"

Servo servo; // création de l'objet "servo"

#define RST_PIN  9 // RES pin
#define SS_PIN  10 // SDA (SS) pin

byte readCard[4];
String cardIDb = " 83FD75DD"; // remplacer par l'ID de votre tag
String cardIDc = "F3842FFB"; // remplacer par l'ID de votre tag
String tagID = "";

const int PIN_RED   = 7;
const int PIN_GREEN = 6;
const int PIN_BLUE  = 5;

////variables to hold our color intensities and direction
////and define some initial "random" values to seed it
//int red             = 254;
//int green           = 1;
//int blue            = 127;
//int red_direction   = -1;
//int green_direction = 1;
//int blue_direction  = -1;

MFRC522 mfrc522(SS_PIN, RST_PIN);

void setup() {
   Serial.begin(9600);
   SPI.begin();
   mfrc522.PCD_Init();
   pinMode(PIN_RED,   OUTPUT);
   pinMode(PIN_GREEN, OUTPUT);
   pinMode(PIN_BLUE,  OUTPUT);
   servo.attach(8); // attache le servo au pin spécifié
}

void loop() {
    setColor(0, 0, 255);
    servo.write(180); // demande au servo de se déplacer à cette position
    while (getID()) {
    if (tagID == cardIDb || tagID == cardIDc) {
      Serial.println("Access Granted!");
      setColor(0, 255, 0);
      servo.write(90);
      delay(1000);
    }
    else {
      Serial.println("Access Denied!");
      setColor(255, 0, 0);
      delay(1000);
    }
    Serial.print("ID: ");
    Serial.println(tagID);
    delay(1000);
    setColor(0, 0, 255);
    servo.write(180);
  }
}

boolean getID() {
  if (! mfrc522.PICC_IsNewCardPresent()) {
    return false;
  }

  if (! mfrc522.PICC_ReadCardSerial()) {
    return false;
  }

  tagID = "";
  
  for (uint8_t i = 0; i < 4; i++) {
    tagID.concat(String(mfrc522.uid.uidByte[i], HEX));
  }

  tagID.toUpperCase();
  mfrc522.PICC_HaltA();
  return true;
}

void setColor(int R, int G, int B) {
  analogWrite(PIN_RED,   R);
  analogWrite(PIN_GREEN, G);
  analogWrite(PIN_BLUE,  B);
}
