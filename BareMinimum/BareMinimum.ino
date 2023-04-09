const int Xpin = A1;
const int Ypin = A2;
const int Spin = 8;
int X;
int Y;
int S;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(10000);
  pinMode(Xpin, INPUT);
  pinMode(Ypin, INPUT);
  pinMode(Spin, INPUT);
  digitalWrite(Spin, HIGH);
}

void loop() {
  // put your main code here, to run repeatedly:
  X = analogRead(Xpin);
  Y = analogRead(Ypin);
  S = analogRead(Spin);
  delay(1);
  Serial.print("X value = ");
  Serial.print(X);
  Serial.print("Y value = ");
  Serial.print(Y);
  Serial.print("Switch State is ");
  Serial.println(S);
  
}
