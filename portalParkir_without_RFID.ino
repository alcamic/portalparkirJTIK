// Define pins for UP and DOWN control
const int pinUP = 2;      // Pin to control UP (Raise the barrier)
const int pinDOWN = 3;    // Pin to control DOWN (Lower the barrier)
bool isBarrierUp = false; // Variable to track the barrier state (default: DOWN)

void setup() {
  // Set pins as output
  pinMode(pinUP, OUTPUT);
  pinMode(pinDOWN, OUTPUT);

  // Ensure all control pins are LOW initially
  digitalWrite(pinUP, LOW);
  digitalWrite(pinDOWN, LOW);

  // Default state: Ensure the barrier is DOWN
  closeBarrier();
}

void loop() {
  // Check if the barrier is in its default (DOWN) state
  if (!isBarrierUp) {
    // Step 1: Raise the barrier to the UP position
    openBarrier();

    // Step 2: Keep the barrier UP for 10 seconds
    delay(15000);

    // Step 3: Lower the barrier to the default DOWN position
    closeBarrier();

    // Step 4: Set the state back to default (DOWN)
    isBarrierUp = false;
  }

  // Wait indefinitely (or until another condition is met to raise the barrier again)
  while (true) {
    // The barrier remains DOWN forever (default state)
  }
}

// Function to raise the barrier (UP)
void openBarrier() {
  digitalWrite(pinUP, HIGH); // Activate UP signal
  delay(500);               // 500ms pulse duration
  digitalWrite(pinUP, LOW);  // Deactivate UP signal
  isBarrierUp = true;        // Mark barrier as UP
}

// Function to lower the barrier (DOWN)
void closeBarrier() {
  digitalWrite(pinDOWN, HIGH); // Activate DOWN signal
  delay(500);                 // 500ms pulse duration
  digitalWrite(pinDOWN, LOW);  // Deactivate DOWN signal
  isBarrierUp = false;         // Mark barrier as DOWN
}
