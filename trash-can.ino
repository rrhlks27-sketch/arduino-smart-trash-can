#include <Servo.h>

#define SENSOR_PIN 4   // OUT proximity sensor
#define SERVO_PIN 9    // signal servo

Servo tutupServo;

int bukaSudut = 90;
int tutupSudut = 0;
int delayTutup = 3000; // waktu sebelum tutup otomatis (3 detik)

// State tracking
int lastSensorState = LOW; // simpan state sensor sebelumnya
unsigned long detectionTime = 0; // waktu saat sensor terdeteksi

void setup() {
  pinMode(SENSOR_PIN, INPUT);

  tutupServo.attach(SERVO_PIN);
  tutupServo.write(tutupSudut); // posisi awal tertutup
  delay(500);

  Serial.begin(9600);
  Serial.println("Smart Trash Can - Ready!");
}

void loop() {
  int currentSensorState = digitalRead(SENSOR_PIN);

  // Deteksi perubahan dari LOW ke HIGH (atau sebaliknya)
  if (currentSensorState != lastSensorState) {
    
    // Jika sensor baru saja aktif (deteksi objek)
    if (currentSensorState == HIGH) {
      Serial.println("Sensor mendeteksi! Membuka penutup...");
      tutupServo.write(bukaSudut);
      detectionTime = millis(); // catat waktu deteksi
    }
    
    lastSensorState = currentSensorState; // update state
  }

  // Jika sudah buka, tunggu delay untuk menutup
  if (lastSensorState == HIGH && (millis() - detectionTime) >= delayTutup) {
    Serial.println("Waktu habis. Menutup penutup...");
    tutupServo.write(tutupSudut);
    lastSensorState = LOW; // reset state
  }

  delay(50); // debounce sensor
}
