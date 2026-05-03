// PEriodo de muestreo
const unsigned long Ts_us = 1000; // 1 ms = 1 kHz
unsigned long t_next = 0;

// Pines MEga
const int pines_dac[10] = {2,3,4,5,6,7,8,9,10,11};

// Filter coefficients for a simple lowpass IIR
const double b[] = {0.0031638 , -0.00295323, -0.00295323,  0.0031638}; // Numerator coefficients
const double a[] = {-2.90118004,  2.81353648, -0.91193529};  // Denominator coefficients

// Create the IIR Filter object
//IIRFilter lp(b, a);

// Funciones
void dac10bits(int value);


void setup() {
  Serial.begin(9600);

  for(int i = 0; i < 10; i++){ 
    pinMode(pines_dac[i], OUTPUT);
  }

  t_next = micros(); 

}

float x=0, x_1=0, x_2=0, x_3=0, x_4=0, y=0, y_1=0, y_2=0, y_3=0;

void loop() {
 unsigned long now = micros();

  // Ejecuta exactamente cada Ts_us
  if ((long)(now - t_next) >= 0) {
    t_next += Ts_us;  // mantiene periodo constante (clave)

    x = analogRead(A0);
	
	y = b[0]*x + b[1]*x_1 + b[2]*x_2 + b[3]*x_3 + b[4]*x_4 - a[0]*y_1 - a[1]*y_2 - a[2]*y_3;
	
	x_4 = x_3;
	x_3 = x_2;
	x_2 = x_1;
	x_1 = x;
	
	y_3 = y_2;
	y_2 = y_1;
	y_1 = y; 
	
	
    dac10bits((int)y); 
  
  }

}

void dac10bits(int value){
  if(value < 0) value = 0;
  if(value > 1023) value = 1023;

  for(int i = 0; i < 10; i++){ 
    digitalWrite(pines_dac[i], (value >> i) & 1);
  }
}