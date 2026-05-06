#define OUT_PIN 9

volatile uint8_t pdmOut = 0;
volatile int32_t integrator = 0;

const float signalFreq = 10.0;      // 10 Hz
const float sampleRate = 62500.0;   // PDM clock

volatile uint16_t phase = 0;

void setup() {

  pinMode(OUT_PIN, OUTPUT);

  cli();

  // Timer1 CTC mode
  TCCR1A = 0;
  TCCR1B = 0;

  TCCR1B |= (1 << WGM12);
  TCCR1B |= (1 << CS10);

  OCR1A = 255;

  TIMSK1 |= (1 << OCIE1A);

  sei();
}

ISR(TIMER1_COMPA_vect) {

  // DDS phase increment
  phase++;

  float t = phase / sampleRate;

  // Generate sine wave
  float s = sin(2.0 * PI * signalFreq * t);

  // Normalize to 0-255
  int16_t target = (int16_t)((s + 1.0) * 127.5);

  // Sigma-delta modulator
  integrator += target - pdmOut;

  if (integrator >= 0) {
    pdmOut = 255;
    PORTB |= (1 << 1);   // Pin 9 HIGH
  }
  else {
    pdmOut = 0;
    PORTB &= ~(1 << 1);  // Pin 9 LOW
  }
}

void loop() {
}