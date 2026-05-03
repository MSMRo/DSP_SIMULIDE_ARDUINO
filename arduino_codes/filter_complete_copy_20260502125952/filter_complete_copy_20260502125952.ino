#include <IIRFilter.h>

// PEriodo de muestreo
const unsigned long Ts_us = 1000; // 1 ms = 1 kHz
unsigned long t_next = 0;

// Pines MEga
const int pines_dac[10] = {31,33,35,37,39,41,43,45,47,49};

// Filter coefficients for a simple lowpass IIR
const double b[] = {6.10727147e-06, -2.86515817e-04,  6.60008999e-03, -9.95006101e-02,
        1.10397223e+00, -9.61165000e+00,  6.83735683e+01, -4.08572693e+02,
        2.09263106e+03, -9.32790684e+03,  3.66196794e+04, -1.27823908e+05,
        3.99789628e+05, -1.12754931e+06,  2.88285117e+06, -6.71145353e+06,
        1.42803223e+07, -2.78580474e+07,  4.99576366e+07, -8.25375306e+07,
        1.25861946e+08, -1.77410156e+08,  2.31428779e+08, -2.79641157e+08,
        3.13186655e+08, -3.25226594e+08,  3.13186655e+08, -2.79641157e+08,
        2.31428779e+08, -1.77410156e+08,  1.25861946e+08, -8.25375306e+07,
        4.99576366e+07, -2.78580474e+07,  1.42803223e+07, -6.71145353e+06,
        2.88285117e+06, -1.12754931e+06,  3.99789628e+05, -1.27823908e+05,
        3.66196794e+04, -9.32790684e+03,  2.09263106e+03, -4.08572693e+02,
        6.83735683e+01, -9.61165000e+00,  1.10397223e+00, -9.95006101e-02,
        6.60008999e-03, -2.86515817e-04,  6.10727147e-06}; // Numerator coefficients
const double a[] = {1.00000000e+00, -4.84987682e+01,  1.15392162e+03, -1.79511729e+04,
        2.05325333e+05, -1.84100888e+06,  1.34727050e+07, -8.27289979e+07,
        4.34904447e+08, -1.98731280e+09,  7.98771289e+09, -2.85080634e+10,
        9.10402769e+10, -2.61794086e+11,  6.81431383e+11, -1.61258909e+12,
        3.48227502e+12, -6.88310794e+12,  1.24858211e+13, -2.08306862e+13,
        3.20201859e+13, -4.54163706e+13,  5.95075433e+13, -7.20914646e+13,
        8.08006982e+13, -8.38154592e+13,  8.04754267e+13, -7.15121842e+13,
        5.87916875e+13, -4.46893025e+13,  3.13806278e+13, -2.03323326e+13,
        1.21379588e+13, -6.66433717e+12,  3.35797944e+12, -1.54874479e+12,
        6.51805296e+11, -2.49398288e+11,  8.63780106e+10, -2.69383678e+10,
        7.51722794e+09, -1.86264814e+09,  4.05961827e+08, -7.69082866e+07,
        1.24735848e+07, -1.69750237e+06,  1.88543601e+05, -1.64162286e+04,
        1.05090760e+03, -4.39868399e+01,  9.03216493e-01};  // Denominator coefficients

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


void dac10bits(int value){
  if(value < 0) value = 0;
  if(value > 1023) value = 1023;

  for(int i = 0; i < 10; i++){ 
    digitalWrite(pines_dac[i], (value >> i) & 1);
  }
}
