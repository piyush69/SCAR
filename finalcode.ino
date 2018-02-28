//As on 19.4.17

// motor one : Wheels
int enA = 5;
int in1 = 7;
int in2 = 6;

// motor two : shaft 1
int enB = 10;
int in3 = 9;
int in4 = 8;

//motor three : shaft 2
int enC = 11;
int in5 = 12;
int in6 = 13;

const int trigPin = 3;
const int fanPin = 2;
const int echoPin = 4;

void setup()
{
  Serial.begin(9600);
  // set all the motor control pins to outputs
  pinMode(enA, OUTPUT);
  pinMode(enB, OUTPUT);
  pinMode(enC, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
  pinMode(in5, OUTPUT);
  pinMode(in6, OUTPUT);
  
  pinMode(trigPin, OUTPUT);
}

void m1clkwise()
{
  analogWrite(enA, 90);
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
}
void m1anticlkwise()
{
  analogWrite(enA, 100);
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
}
void m1stop()
{
  digitalWrite(enA, LOW);
}

void m2clkwise()
{
  analogWrite(enB, 62);
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
}
void m2anticlkwise()
{
  analogWrite(enB, 62);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
}
void m2stop()
{
  digitalWrite(enB, LOW);
}

void m3clkwise()
{
  analogWrite(enC, 47);
  digitalWrite(in5, LOW);
  digitalWrite(in6, HIGH);
}
void m3anticlkwise()
{
  analogWrite(enC, 47);
  digitalWrite(in5, HIGH);
  digitalWrite(in6, LOW);
}
void m3stop()
{
  digitalWrite(enC, LOW);
}

long getdistance()
{
  long duration, inches, cm;

  // The sensor is triggered by a HIGH pulse of 10 or more microseconds.
  // Give a short LOW pulse beforehand to ensure a clean HIGH pulse:
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // Read the signal from the sensor: a HIGH pulse whose
  // duration is the time (in microseconds) from the sending
  // of the ping to the reception of its echo off of an object.
  pinMode(echoPin, INPUT);
  duration = pulseIn(echoPin, HIGH);

  // convert the time into a distance
  inches = duration / 74 / 2;
  cm = duration / 29 / 2;
  /*
  Serial.print(inches);
  Serial.print("in, ");
  Serial.print(cm);
  Serial.print("cm");
  Serial.println();
  */
  delay(100);
  return cm;
}

void clean()
{
  digitalWrite(fanPin, HIGH);
  delay(3000);
  digitalWrite(fanPin, LOW);
  delay(2000);
}

void climb()
{
  int steps = 0;
  while( getdistance() < 4.00 )
  {
    m2clkwise();
    m3clkwise();
    steps = steps + 1;
  }
  m2stop();
  m3stop();
  while( getdistance() > 10.00 )
  {
    m1clkwise();
  }
  m1stop();
  while( steps > 0)
  {
    m2anticlkwise();
    m3anticlkwise();
    steps = steps - 1;
  }
  m2stop();
  m3stop();
}

void loop()
{
  //m1clkwise();
  m2anticlkwise();
  m3anticlkwise();
  delay(2000);
  //m2stop();
  //m3stop();
  //Serial.println(getdistance());
  //delay(500);
  //clean();
  //while( getdistance() > 4.00 ) //move forward
  //{
  //  m1clkwise();
  //}
  //m1stop();
  //climb();
}
