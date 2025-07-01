void setup() {
  pinMode(13, OUTPUT);
  pinMode(12, OUTPUT);
}


void loop() {


        for (int aux = 0; aux <= 5000; aux+=200)
        {
        digitalWrite(13, HIGH);
        digitalWrite(12, HIGH);
        delay(aux);
        digitalWrite(13, LOW);
        digitalWrite(12, LOW);
        delay(aux);
        }
  }

