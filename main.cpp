// C++ code
//

volatile int light1 = 0;
volatile int light2 = 0;

bool phase1 = false;
bool phase2 = false;
bool inClearance = false;

unsigned long start1 = millis();
unsigned long start2 = millis();
unsigned long clearanceStart = 0;

void setup() {
  pinMode(2, INPUT);
  pinMode(3, INPUT);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);
  
  attachInterrupt(digitalPinToInterrupt(3), detectTop, RISING);
  attachInterrupt(digitalPinToInterrupt(2), detectBottom, RISING);
  allRed();
}
void allRed() {
  digitalWrite(4, HIGH);
  digitalWrite(7, HIGH);
  digitalWrite(5, LOW);
  digitalWrite(6, LOW);
}
// TOP
void detectTop() {
  light1 = 1;
  if(phase1)
  	start1 = millis();
}
// BOTTOM
void detectBottom() {
  light2 = 1;
  if(phase2)
  	start2 = millis();
}
void loop() {
  	if (inClearance) {
    	if (millis() - clearanceStart >= 2000)
      		inClearance = false; 
  	}
	if(light1 == 1 && !phase2 && !inClearance) {
      	digitalWrite(4, LOW);
    	digitalWrite(5, HIGH);
      	start1 = millis();
      	phase1 = true;
    	light1 = 0;
	}
    if(light2 == 1 && !phase1 && !inClearance) {
      	digitalWrite(7, LOW);
    	digitalWrite(6, HIGH);
      	start2 = millis();
      	phase2 = true;
		light2 = 0;
	}
  	if(phase1 && (millis() - start1 >= 5000)) {
    	allRed();
      	phase1 = false;
      	inClearance = true;
    	clearanceStart = millis();
	}
  	if(phase2 && (millis() - start2 >= 5000)) {
    	allRed();
      	phase2 = false;
      	inClearance = true;
    	clearanceStart = millis();
	}
}
