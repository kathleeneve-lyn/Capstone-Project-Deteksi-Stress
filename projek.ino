#include <Wire.h> 
#include "MAX30105.h" 
#include "model.h"

#define BLYNK_PRINT Serial
#define BLYNK_TEMPLATE_ID "TMPL6OZQUp0SH"
#define BLYNK_TEMPLATE_NAME "Deteksi Stress"
#define BLYNK_AUTH_TOKEN "iWFnbLlR8yQGQqomovFTAWhiTQcq_Whg"

#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>
char ssid[] = "ROBOTIIK";
char pass[] = "81895656";

Eloquent::ML::Port::RandomForest clf;
MAX30105 particleSensor; 

const int bufferSize = 4; 
long buffer[bufferSize]; 
int bufferIndex = 0; 
long previousValue = 0; 
long peakThreshold = 20000; 
unsigned long lastPeakTime = 0; 
unsigned long minPeakInterval = 600; 

const int nnBufferSize = 100; 
unsigned long nnIntervals[nnBufferSize]; 
int nnIndex = 0; 
const int buzzerPin = 7;
float calculateAVNN(); 
float calculateSDNN(float avnn); 

void setup() { 
  Serial.begin(115200); 
  Serial.println("Initializing..."); 
  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);
  
  if (!particleSensor.begin(Wire, I2C_SPEED_FAST)) { 
    Serial.println("MAX30105 was not found. Please check wiring/power."); 
    while (1); 
  } 

  byte ledBrightness = 0x1F; 
  byte sampleAverage = 8; 
  byte ledMode = 3; 
  int sampleRate = 100; 
  int pulseWidth = 411; 
  int adcRange = 4096; 

  particleSensor.setup(ledBrightness, sampleAverage, ledMode, 
  sampleRate, pulseWidth, adcRange); 

  for (int i = 0; i < bufferSize; i++) buffer[i] = 0; 
  for (int i = 0; i < nnBufferSize; i++) nnIntervals[i] = 0; 
} 

void loop() { 
  Blynk.run();

  long currentValue = particleSensor.getIR(); 
  unsigned long currentTime = millis(); 

  buffer[bufferIndex] = currentValue; 
  bufferIndex = (bufferIndex + 1) % bufferSize; 

  long avgValue = 0; 
  for (int i = 0; i < bufferSize; i++) avgValue += buffer[i]; 
  avgValue /= bufferSize; 

  if (currentValue > peakThreshold && currentValue > previousValue 
  && (currentTime - lastPeakTime) > minPeakInterval) { 
    if (lastPeakTime > 0) { 
      unsigned long peakInterval = currentTime - lastPeakTime; 

      if (peakInterval > 300 && peakInterval < 2000) { 
        nnIntervals[nnIndex] = peakInterval; 
        nnIndex = (nnIndex + 1) % nnBufferSize; 

        float avnn = calculateAVNN(); 
        float sdnn = calculateSDNN(avnn); 

        Serial.print("AVNN: "); 
        Serial.print(avnn); 
        Serial.print(" ms | SDNN: "); 
        Serial.print(sdnn); 
        Serial.println(" ms"); 
        float input_baru[2] = {avnn, sdnn};
        float  result = clf.predict(input_baru);
        Blynk.virtualWrite(V0, avnn);
        Blynk.virtualWrite(V1, sdnn);
        // Tentukan string berdasarkan nilai result
        String statusStress = (result == 1) ? "tidak stress" : "stress";

        // Kirim string ke Blynk (V2)
        Blynk.virtualWrite(V2, statusStress);

        if(result == 0){
          tone(buzzerPin, 1000);
        }else{
          noTone(buzzerPin);
        }
        Serial.print("Prediksi: ");
        Serial.println(result == 1 ? "tidak stress" : "stress");
      } else { 
        Serial.println("Artefak terdeteksi, interval diabaikan."); 
      } 
    } 
    lastPeakTime = currentTime; 
  } 
  previousValue = avgValue; 
  delay(10); 
} 

float calculateAVNN() { 
  unsigned long total = 0; 
  int count = 0; 
  for (int i = 0; i < nnBufferSize; i++) { 
    if (nnIntervals[i] > 0) { 
      total += nnIntervals[i]; 
      count++; 
    } 
  } 
  if (count == 0) return 0; 
  return (float)total / count; 
} 

float calculateSDNN(float avnn) { 
  float variance = 0; 
  int count = 0; 
  for (int i = 0; i < nnBufferSize; i++) { 
    if (nnIntervals[i] > 0) { 
      variance += pow(nnIntervals[i] - avnn, 2); 
      count++; 
    } 
  } 
  if (count == 0) return 0; 
  return sqrt(variance / count); 
}
