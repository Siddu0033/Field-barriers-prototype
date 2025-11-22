#define BLYNK_TEMPLATE_ID "TMPL3yfgoQzsc"
#define BLYNK_TEMPLATE_NAME "Fieldbarrier"
#define BLYNK_AUTH_TOKEN "feu3jdCOVOm2NWJ_a1DKsFKNsOWrJGnL"

#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>

char ssid[] = "Hotspot";
char pass[] = "30405060";

#define TRIG 5
#define ECHO 18
#define BUZZER 2

long duration;
int distance;

void setup() {
  Serial.begin(115200);

  pinMode(TRIG, OUTPUT);
  pinMode(ECHO, INPUT);
  pinMode(BUZZER, OUTPUT);

  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);
}

void loop() {
  Blynk.run();

  // Ultrasonic Trigger
  digitalWrite(TRIG, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG, LOW);

  duration = pulseIn(ECHO, HIGH);
  distance = duration * 0.034 / 2;

  Serial.print("Distance: ");
  Serial.println(distance);

  Blynk.virtualWrite(V1, distance);  // send distance to app

  if (distance <= 50 && distance > 0) {
    // Object Detected
    Blynk.virtualWrite(V0, "Object Detected");
    Blynk.logEvent("alert", "Object Detected");

    digitalWrite(BUZZER, HIGH);
    delay(4000);
    digitalWrite(BUZZER, LOW);

  } else {
    // No Object
    Blynk.virtualWrite(V0, "No Object");
    digitalWrite(BUZZER, LOW);
  }

  delay(100);
}