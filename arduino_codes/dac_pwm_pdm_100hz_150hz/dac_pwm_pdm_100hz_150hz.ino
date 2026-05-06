#define OUT_PIN 9

volatile int32_t integrator = 0;
volatile uint8_t pdmOut = 0;

const float sampleRate = 62500.0;

const float f1 = 100.0;
const float f2 = 150.0;

volatile uint32_t sampleIndex = 0;

void setup() {
  pinMode(OUT_PIN, OUTPUT);

  cli();

  TCCR1A = 0;
  TCCR1B = 0;
  // CTC mode
  TCCR1B |= (1 << WGM12);
  // prescaler = 1
  TCCR1B |= (1 << CS10);
  // 62.5 kHz
  OCR1A = 255;
  TIMSK1 |= (1 << OCIE1A);

  sei();
}

ISR(TIMER1_COMPA_vect) {
  float t = sampleIndex / sampleRate;
  // Señal compuesta
  float s =
      0.5 * sin(2.0 * PI * f1 * t) +
      0.5 * sin(2.0 * PI * f2 * t);

  // Escalar a 0-255
  int16_t target = (int16_t)((s + 1.0) * 127.5);

  // Sigma-Delta
  integrator += target - pdmOut;

  if (integrator >= 0) {

    pdmOut = 255;

    PORTB |= (1 << 1); // Pin 9 HIGH

  } else {

    pdmOut = 0;

    PORTB &= ~(1 << 1); // Pin 9 LOW
  }

  sampleIndex++;
}

void loop() {
}