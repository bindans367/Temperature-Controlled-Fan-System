//Temperature control fan code

int tempPin = A0;
int fanPin  = 9;

int redLED    = 2;
int yellowLED = 3;
int greenLED  = 4;

const int samples = 10;   // averaging samples

void setup() {
  Serial.begin(9600);

  pinMode(fanPin, OUTPUT);
  pinMode(redLED, OUTPUT);
  pinMode(yellowLED, OUTPUT);
  pinMode(greenLED, OUTPUT);
}

void loop() {

  float tempSum = 0;

  // AVERAGING 
  for (int i = 0; i < samples; i++) {
    int tempValue = analogRead(tempPin);

    float temperature = (tempValue * 5.0 * 100.0) / 1023.0;

    tempSum += temperature;
    delay(200);
  }
  
  float realtem = tempSum / samples;
  float realtemp=realtem/10;
  float realTemp = realtemp-10;


  Serial.print("Temperature: ");
  Serial.print(realTemp);
  Serial.println(" C");

  // CONTROL LOGIC
  if (realTemp < 20.0) {
    analogWrite(fanPin, 0);          // OFF
    digitalWrite(redLED, LOW);
    digitalWrite(yellowLED, LOW);
    digitalWrite(greenLED, HIGH);
  }
  else if (realTemp >= 20.0 && realTemp < 25.0) {
    analogWrite(fanPin, 120);        // SLOW
    digitalWrite(redLED, LOW);
    digitalWrite(yellowLED, HIGH);
    digitalWrite(greenLED, LOW);
  }
  else {
    analogWrite(fanPin, 255);        // FAST
    digitalWrite(redLED, HIGH);
    digitalWrite(yellowLED, LOW);
    digitalWrite(greenLED, LOW);
  }

  delay(5000);   // update every 5 seconds
}