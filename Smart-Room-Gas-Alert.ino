const int gasSensorPin = A0;
const int irSensorPin = 22;
const int buttonPin = 23;
const int buzzerPin = 24;
const int redLedPin = 25;
const int greenLedPin = 26;

const int gasThreshold = 400;
bool alarmActive = false;

void setup() {
  pinMode(gasSensorPin, INPUT);
  pinMode(irSensorPin, INPUT);
  pinMode(buttonPin, INPUT);

  pinMode(buzzerPin, OUTPUT);
  pinMode(redLedPin, OUTPUT);
  pinMode(greenLedPin, OUTPUT);

  digitalWrite(buzzerPin, HIGH);
  digitalWrite(redLedPin, LOW);
  digitalWrite(greenLedPin, HIGH);

  Serial.begin(9600);
  Serial.println("System Ready");
}

void loop() {
  int gasValue = analogRead(gasSensorPin);
  int irValue = digitalRead(irSensorPin);
  int buttonState = digitalRead(buttonPin);

  // Print values
  Serial.print("Gas: ");
  Serial.print(gasValue);
  Serial.print(" | IR: ");
  Serial.print(irValue);
  Serial.print(" | Button: ");
  Serial.print(buttonState);
  Serial.print(" | Alarm: ");
  Serial.println(alarmActive ? "ON" : "OFF");

  if (!alarmActive) {
    if (gasValue > gasThreshold && irValue == HIGH) {
      alarmActive = true;
      digitalWrite(buzzerPin, LOW);
      digitalWrite(redLedPin, HIGH);
      digitalWrite(greenLedPin, LOW);
      Serial.println("!!! ALARM TRIGGERED !!!");
    } else {
      digitalWrite(buzzerPin, HIGH);
      digitalWrite(redLedPin, LOW);
      digitalWrite(greenLedPin, HIGH);
    }
  }

  if (alarmActive && buttonState == HIGH) {
    alarmActive = false;
    digitalWrite(buzzerPin, HIGH);
    digitalWrite(redLedPin, LOW);
    digitalWrite(greenLedPin, HIGH);
    Serial.println(">>> Alarm RESET <<<");
  }

  delay(300);
}
