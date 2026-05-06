#include <TimerOne.h>

#define OUT_PIN 9

volatile int32_t integrator = 0;
volatile uint8_t pdmOut = 0;

const float sampleRate = 62500.0;

const float f1 = 80.0;
const float f2 = 80.0;

volatile uint32_t sampleIndex = 0;

void setup() {

  pinMode(OUT_PIN, OUTPUT);

  // periodo en microsegundos
  Timer1.initialize(16); // ~62.5kHz

  Timer1.attachInterrupt(pdmISR);
}

void pdmISR() {

  float t = sampleIndex / sampleRate;

  float s =
      0.5 * sin(2.0 * PI * f1 * t) +
      0.5 * sin(2.0 * PI * f2 * t);

  int16_t target = (int16_t)((s + 1.0) * 127.5);

  integrator += target - pdmOut;

  if (integrator >= 0) {

    pdmOut = 255;
    digitalWrite(OUT_PIN, HIGH);

  } else {

    pdmOut = 0;
    digitalWrite(OUT_PIN, LOW);
  }

  sampleIndex++;
}

void loop() {
}