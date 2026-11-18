#include <WiFi.h>

// Konfigurasi WiFi
const char* ssid = "iPhone";       
const char* password = "mnijungkook";   

// Definisi Pin Sensor
const int mqPin = 34;       
const int trigPin = 23;     
const int echoPin = 22;     

// Variabel untuk menyimpan data sensor
int gasValue = 0;
long duration;
float distance = 0;

void setup() {
  Serial.begin(115200);
  delay(1000);

  pinMode(mqPin, INPUT);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  Serial.println();
  Serial.print("Menghubungkan ke WiFi: ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi berhasil terhubung!");
  Serial.print("Alamat IP ESP32: ");
  Serial.println(WiFi.localIP());
}

void loop() {
  // 1. Membaca data dari Sensor Gas MQ (Analog)
  gasValue = analogRead(mqPin);

  // 2. Membaca data dari Sensor Ultrasonik (Jarak)
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH);
  distance = duration * 0.034 / 2;

  // 3. Tampilkan hasil pembacaan ke Serial Monitor
  Serial.println("========================================");
  Serial.print("Status WiFi : Terhubung (IP: ");
  Serial.print(WiFi.localIP());
  Serial.println(")");
  Serial.print("Nilai Sensor Gas (MQ)  : ");
  Serial.println(gasValue);
  Serial.print("Jarak Objek (Ultrasonic): ");
  Serial.print(distance);
  Serial.println(" cm");
  Serial.println("========================================");

  delay(2000);
}