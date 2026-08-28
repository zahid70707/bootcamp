void setup() {
  Serial.begin(9600);
  pinMode(A1,INPUT_PULLUP);
 pinMode(3,OUTPUT);
}

void loop() {
 int x = analogRead(A1);
Serial.println(x);
if (x<=20){
Serial.println(x);
  digitalWrite(3,HIGH);
}
else {
Serial.println(x);
  digitalWrite(3,LOW);
}
delay(100);
}
