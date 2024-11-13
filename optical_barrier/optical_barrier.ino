// (c) Michael Schoeffler 2014, http://www.mschoeffler.de


const int pinReceiver = 3; // input signal pin of receiver/detector (the used module does only return a digital state)

void setup() {
  
  pinMode(pinReceiver, INPUT); // set the laser pin to output mode
  
  Serial.begin(9600); // Setup serial connection for print out to console
}

void loop() {
  int value = digitalRead(pinReceiver); // receiver/detector send either LOW or HIGH (no analog values!)
  
  Serial.println(value); // send value to console
  delay(1000); // wait for 1000ms
}