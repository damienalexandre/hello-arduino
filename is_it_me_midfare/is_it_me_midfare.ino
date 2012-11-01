/*
Base code from Adafruit:
 @author   Adafruit Industries
 @license  BSD (see license.txt)

 @author   Damien Alexandre
 
 This is for the Adafruit PN532 NFC/RFID breakout boards
 This library works with the Adafruit NFC breakout 
 ----> https://www.adafruit.com/products/364
 
 Check out the links above for our tutorials and wiring diagrams 
 These chips use I2C to communicate

 Todo:
 - Use an RVB LED instead of multiple colors
 - Play a sound
 - Make it reconize my Galaxy S3
 - Use Authentification, store the played sound on the card
*/
#include <Wire.h>
#include <Adafruit_NFCShield_I2C.h>

#define IRQ     (2)
#define RESET   (3)  // Not connected by default on the NFC Shield
#define OK_PIN  (11)
#define NOK_PIN (10)

Adafruit_NFCShield_I2C nfc(IRQ, RESET);

void setup(void) {
  Serial.begin(9600);
  Serial.println("Hello you!");

  // Setup shield and pins
  nfc.begin();
  pinMode(OK_PIN, OUTPUT);    
  pinMode(NOK_PIN, OUTPUT);   

  // Auto-test LED's :)
  Serial.println("Testing LEDs");
  digitalWrite(OK_PIN, HIGH);
  digitalWrite(NOK_PIN, HIGH);
  delay(1000);
  digitalWrite(OK_PIN, LOW); 
  digitalWrite(NOK_PIN, LOW);

  // configure board to read RFID tags
  nfc.SAMConfig();

  Serial.println("Waiting for an ISO14443A Card ...");
}

void loop(void) {
  uint8_t success;
  // This is the ID of one of my Mifare cards
  uint8_t me[] = { 0x6A, 0x95, 0x0A, 0xD6 };
  // Buffer to store the returned UID
  uint8_t uid[] = { 0, 0, 0, 0, 0, 0, 0 };
  // Length of the UID (4 or 7 bytes depending on ISO14443A card type)  
  uint8_t uidLength; 

  // Wait for an ISO14443A type cards (Mifare, etc.).  When one is found
  // 'uid' will be populated with the UID, and uidLength will indicate
  // if the uid is 4 bytes (Mifare Classic) or 7 bytes (Mifare Ultralight)
  success = nfc.readPassiveTargetID(PN532_MIFARE_ISO14443A, uid, &uidLength);

  if (success) {
    // Display some basic information about the card
    Serial.println("Found an ISO14443A card");
    Serial.print("  UID Length: ");
    Serial.print(uidLength, DEC);
    Serial.println(" bytes");
    Serial.print("  UID Value: ");
    nfc.PrintHex(uid, uidLength);
    Serial.println("");

    if (uidLength == 4 && me[0] == uid[0] && me[1] == uid[1] && me[2] == uid[2] && me[3] == uid[3])
    {
      itsme();
    } 
    else 
    {
      itsnotme();
    }
  }
}

void itsme() {
  digitalWrite(OK_PIN, HIGH);
  digitalWrite(NOK_PIN, LOW);
  delay(1000);
  digitalWrite(OK_PIN, LOW);
}

void itsnotme() {
  digitalWrite(NOK_PIN, HIGH);
  digitalWrite(OK_PIN, LOW);
  delay(1000);
  digitalWrite(NOK_PIN, LOW);
}
