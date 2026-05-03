const int pines_dac[10] = {31,33,35,37,39,41,43,45,47,49};

// Coeficientes del filtro
float b0 = 0.00362168;
float b1 = 0.00724336;
float b2 = 0.00362168;
float a1 = -1.82269493;
float a2 = 0.83718165;

// Estados (Direct Form II Transposed)
float w1 = 0, w2 = 0;

const unsigned long Ts_us = 1000; // 1 ms = 1 kHz
unsigned long t_next = 0;

void dac10bits(int value);

void setup() {
  for(int i = 0; i < 10; i++){ 
    pinMode(pines_dac[i], OUTPUT);
  }
  pinMode(13, OUTPUT);

  t_next = micros(); // inicialización
}

int bit_count = 0;

void loop() {

  unsigned long now = micros();

  // Ejecuta exactamente cada Ts_us
  if ((long)(now - t_next) >= 0) {

    t_next += Ts_us;  // mantiene periodo constante (clave)

    digitalWrite(13, bit_count);

    int raw_adc = analogRead(A0);
    float x0 = (float)raw_adc;

    // --- FILTRO IIR ---
    float w0 = x0 - a1*w1 - a2*w2;
    float y0 = b0*w0 + b1*w1 + b2*w2;

    w2 = w1;
    w1 = w0;

    dac10bits((int)y0);

    bit_count ^= 1;
  }
}

void dac10bits(int value){
  if(value < 0) value = 0;
  if(value > 1023) value = 1023;

  for(int i = 0; i < 10; i++){ 
    digitalWrite(pines_dac[i], (value >> i) & 1);
  }
}