int electro = 13;

void setup() {
  // put your setup code here, to run once:
  pinMode(electro, OUTPUT);
  Serial.begin(9600);
  digitalWrite(electro, HIGH);
  delay(10000);
  digitalWrite(electro, LOW);
}

void loop() {
  // put your main code here, to run repeatedly:

}
