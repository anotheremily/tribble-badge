int lastVal = 0;
int pin = 0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.write("hello");
}

void loop() {
  // put your main code here, to run repeatedly:
  int val = analogRead(pin);
  if (val != lastVal) {
    Serial.println("Val change");
    Serial.println(val);
    lastVal = val;  
  }
}
