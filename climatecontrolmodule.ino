const int tempPin = A0;
const int motorPin = 9;

void setup() {
  Serial.begin(9600);
  pinMode(motorPin, OUTPUT);
}

void loop() {

  // Read TMP36 sensor
  int sensorValue = analogRead(tempPin);

  // Convert ADC value to voltage
  float voltage = sensorValue * (5.0 / 1023.0);

  // TMP36 temperature calculation
  float temperature = (voltage - 0.5) * 100.0;

  int pwmValue;

  // Fan OFF below 27°C
  if (temperature < 27.0) {
    pwmValue = 0;
  }

  // Fan FULL speed at or above 40°C
  else if (temperature >= 40.0) {
    pwmValue = 255;
  }

  // Increase speed gradually between 27°C and 40°C
  else {
    pwmValue = map((int)temperature, 27, 40, 0, 255);
  }

  analogWrite(motorPin, pwmValue);

  Serial.print("Temp: ");
  Serial.print(temperature, 1);
  Serial.print(" C, PWM: ");
  Serial.println(pwmValue);

  delay(500);
}