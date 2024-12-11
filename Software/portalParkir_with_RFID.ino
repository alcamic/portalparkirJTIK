#include <SPI.h>
#include <MFRC522.h>

// RFID pins
#define RST_PIN 9          // Configurable, see typical pin layout above
#define SS_PIN 10          // Configurable, see typical pin layout above

// Barrier control pins
const int pinUP = 2;      // Pin to control UP (Raise the barrier)
const int pinDOWN = 3;    // Pin to control DOWN (Lower the barrier)

// Create MFRC522 instance
MFRC522 mfrc522(SS_PIN, RST_PIN);

// Barrier state
bool barrierIsUp = false; // Tracks whether the barrier is UP or DOWN

void setup() {
  // Initialize serial communication
  Serial.begin(9600);
  while (!Serial); // Wait for serial port to open (for ATMEGA32U4-based boards)

  // Initialize SPI bus and RFID module
  SPI.begin();
  mfrc522.PCD_Init();
  delay(4); // Optional delay for some boards
  mfrc522.PCD_DumpVersionToSerial(); // Show RFID reader details
  Serial.println(F("Scan an RFID card to control the barrier gate..."));

  // Set up barrier control pins
  pinMode(pinUP, OUTPUT);
  pinMode(pinDOWN, OUTPUT);

  // Ensure barrier control pins are LOW initially
  digitalWrite(pinUP, LOW);
  digitalWrite(pinDOWN, LOW);
}

void loop() {
  // Check if a new RFID card is present
  if (!mfrc522.PICC_IsNewCardPresent()) {
    return; // Exit loop if no card is present
  }

  // Attempt to read the RFID card
  if (!mfrc522.PICC_ReadCardSerial()) {
    return; // Exit loop if card reading fails
  }

  // Display UID of the RFID card
  Serial.print(F("Card UID: "));
  String cardID = "";
  for (byte i = 0; i < mfrc522.uid.size; i++) {
    cardID += String(mfrc522.uid.uidByte[i], HEX); // Convert UID to HEX string
  }
  Serial.println(cardID);

  // Run the barrier logic
  handleBarrier();

  // Reset the RFID reader
  mfrc522.PICC_HaltA();        // Halt the current card
  mfrc522.PCD_StopCrypto1();   // Stop encryption

  // Small delay to prevent continuous triggering
  delay(1000); // Wait for 1 second before allowing the next scan
}

// Function to handle barrier logic
void handleBarrier() {
  if (!barrierIsUp) {
    // If the barrier is down, raise it
    Serial.println(F("Raising the barrier..."));
    openBarrier();
    barrierIsUp = true;

    // Keep the barrier UP for 20 seconds
    delay(20000);

    // Lower the barrier
    Serial.println(F("Lowering the barrier..."));
    closeBarrier();
    barrierIsUp = false;

    // Reset RFID reader after lowering the barrier
    Serial.println(F("Resetting RFID reader..."));
    mfrc522.PCD_Init();
  } else {
    // If the barrier is already UP, ignore further card scans
    Serial.println(F("Barrier is already UP, ignoring card scan."));
  }
}

// Function to raise the barrier (UP)
void openBarrier() {
  digitalWrite(pinUP, HIGH); // Activate UP signal
  delay(100);               // Short pulse (100ms)
  digitalWrite(pinUP, LOW);  // Deactivate UP signal
}

// Function to lower the barrier (DOWN)
void closeBarrier() {
  digitalWrite(pinDOWN, HIGH); // Activate DOWN signal
  delay(100);                 // Short pulse (100ms)
  digitalWrite(pinDOWN, LOW);  // Deactivate DOWN signal
}
