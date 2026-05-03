#include <IIRFilter.h>

// PEriodo de muestreo
const unsigned long Ts_us = 1000; // 1 ms = 1 kHz
unsigned long t_next = 0;

// Pines MEga
const int pines_dac[10] = {31,33,35,37,39,41,43,45,47,49};

// Filter coefficients for a simple lowpass IIR
const double b[] = {0.05, 0.05}; // Numerator coefficients
const double a[] = {1.0, -0.9};  // Denominator coefficients

// Create the IIR Filter object
IIRFilter lp(b, a);

// Funciones
void dac10bits(int value);

void setup() {
  Serial.begin(9600);

  for(int i = 0; i < 10; i++){ 
    pinMode(pines_dac[i], OUTPUT);
  }

  t_next = micros(); 
}

void loop() {
  unsigned long now = micros();

  // Ejecuta exactamente cada Ts_us
  if ((long)(now - t_next) >= 0) {
    t_next += Ts_us;  // mantiene periodo constante (clave)
    float input = analogRead(A0);
    float filtered = lp.filter(input); // Apply the IIR filter

    dac10bits((int)filtered&1023); //truncamiento a 10bits entero
    Serial.println(filtered);
  
  }
}