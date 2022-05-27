// Ultrasonic Sensor HC-SR04

// Define pins numbers
const int trigPin1 = 9;
const int echoPin1 = 10;

const int trigPin2 = 5;
const int echoPin2 = 6;

const int OutPin = 4; // Input for ESP

// Define variables
long duration1, duration2;
int distance1, distance2;

int cnt1 = 0, cnt2 = 0;
int lim_cnt = 3;

void setup() {
  pinMode(trigPin1, OUTPUT); // Sets the trigPin1 as an Output
  pinMode(echoPin1, INPUT); // Sets the echoPin1 as an Input

  pinMode(trigPin2, OUTPUT); // Sets the trigPin1 as an Output
  pinMode(echoPin2, INPUT); // Sets the echoPin1 as an Input

  pinMode(OutPin, OUTPUT); // Sets the trigPin1 as an Output
  digitalWrite(OutPin, LOW);
  
  Serial.begin(115200); // Starts the serial communication
}

void loop() {
  
  Serial.println();
  
  // Clears the trigPin1
  digitalWrite(trigPin1, LOW);
  delayMicroseconds(2);
  
  // Sets the trigPin1 on HIGH state for 10 microseconds
  digitalWrite(trigPin1, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin1, LOW);
  
  // Reads the echoPin1, returns the sound wave travel time in microseconds
  duration1 = pulseIn(echoPin1, HIGH, 500000);

  // Calculating the distance2
  distance1 = duration1 * 0.034 / 2;

  // If the object is not too close or too far
  if (distance1 != 0 and distance1 > 3 and distance1 < 16) {
    // Prints the distance1 on the Serial Monitor
    Serial.print("distance1: ");
    Serial.println(distance1);

    // Increment contor when the sensor detects something
    if (cnt1 < lim_cnt) cnt1++;
  } else {
    // Decrement contor when the sensor is free
    if (cnt1 > -1 * lim_cnt) cnt1--;
  }
  delay(500);
  
  // Clears the trigPin2
  digitalWrite(trigPin2, LOW);
  delayMicroseconds(2);
  
  // Sets the trigPin2 on HIGH state for 10 micro seconds
  digitalWrite(trigPin2, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin2, LOW);
  
  // Reads the echoPin2, returns the sound wave travel time in microseconds
  duration2 = pulseIn(echoPin2, HIGH, 500000);//[us]

  // Calculating the distance2
  distance2 = duration2 * 0.034 / 2;

  // If the object is not too close or too far
  if (distance2 != 0 and distance2 > 3 and distance2 < 16) {

    // Prints the distance2 on the Serial Monitor
    Serial.print("distance2: ");
    Serial.println(distance2);

    // Increment contor when the sensor detects something
    if (cnt2 < lim_cnt) cnt2++;
  } else {
    // Decrement contor when the sensor is free
    if (cnt2 > -1 * lim_cnt) cnt2--;
  }
  delay(500);

  Serial.print("cnt1: ");
  Serial.print(cnt1);
  Serial.print(" ");
  Serial.print("cnt2: ");
  Serial.print(cnt2);
  Serial.print(" ");

  // If one or both sensors detect something in the interested area => locked garage
  if (cnt1 == lim_cnt or cnt2 == lim_cnt) {
    // Send signal to ESP
    digitalWrite(OutPin, HIGH);
    Serial.println("GARAJ BLOCAT");
  } // If both sesnors are free => free garage
  else if (cnt1 == -1 * lim_cnt and cnt2 == -1 * lim_cnt) {
    // Send signal to ESP
    digitalWrite(OutPin, LOW);
    Serial.println("GARAJ LIBER");
  }
 
}
