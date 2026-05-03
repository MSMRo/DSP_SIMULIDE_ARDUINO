#include <IIRFilter.h>

// Filter coefficients for a simple lowpass IIR
const double b[] = {0.05, 0.05}; // Numerator coefficients
const double a[] = {1.0, -0.9};  // Denominator coefficients

// Create the IIR Filter object
IIRFilter lp(b, a);

void setup() {
  Serial.begin(9600);
}

void loop() {
  float input = analogRead(A0);
  float filtered = lp.filter(input); // Apply the IIR filter
  Serial.println(filtered);
}
