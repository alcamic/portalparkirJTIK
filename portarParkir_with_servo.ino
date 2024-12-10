#include <Servo.h>

Servo myServo; // Membuat objek servo
int servoPin = 6; // Pin servo
int angle = 0; // Posisi awal servo
bool isUp = false; // Status servo (down/up)
unsigned long previousMillis = 0; // Waktu sebelumnya
const long interval = 10000; // Interval 10 detik

void setup() {
  myServo.attach(servoPin); // Menghubungkan servo ke pin
  myServo.write(angle); // Memulai di posisi awal (0 derajat)
}

void loop() {
  unsigned long currentMillis = millis();

  // Periksa apakah sudah 10 detik berlalu
  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis; // Reset waktu sebelumnya

    // Ubah posisi servo
    if (!isUp) { // Jika saat ini "down", naikkan ke "up" (180 derajat)
      angle = 90;
      isUp = true;
    } else { // Jika saat ini "up", turunkan ke "down" (0 derajat)
      angle = 0;
      isUp = false;
    }

    myServo.write(angle); // Gerakkan servo ke posisi baru
  }
}
