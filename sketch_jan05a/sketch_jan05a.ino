int led = 3;
int i = 3;
void setup() {
  for(i=3; i<=5; i++){
    int led = 3;
    pinMode(led,OUTPUT);
  }

}

void loop() {
  digitalWrite(led, HIGH);
  delay(1000);
  digitalWrite(led,LOW);
  led = led + 1;
  if (led == 6){
    led = 3;
  }
}
