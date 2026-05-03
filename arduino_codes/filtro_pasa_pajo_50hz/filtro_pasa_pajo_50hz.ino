const int pines_dac[10]={31,33,35,37,39,41,43,45,47,49};
float alpha = 0.98;
float y=0;

void dac10bits(int value);

void setup() {
  for(int i=0;i<12;i++){ 
		pinMode(pines_dac[i], OUTPUT);
	}
	pinMode(13, OUTPUT);
}

int raw_adc;
int bit_count=0;

void loop() {
	digitalWrite(13, bit_count);	
	
	raw_adc = analogRead(A0);
	
	y = alpha*y + (float)(1-alpha)*raw_adc;
	dac10bits(y);
  

	
	bit_count ^= 1;
	delayMicroseconds(795);
}

void dac10bits(int value){
  for(int i=0;i<10;i++){ 
		digitalWrite(pines_dac[i], (value>>i)&1);
	}
}
