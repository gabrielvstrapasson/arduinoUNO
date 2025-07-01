const int ledVerdeCarro = 4;
const int ledAmareloCarro = 3;
const int ledVermelhoCarro = 2;

const int ledVerdePedestre = 6;
const int ledVermelhoPedestre = 5;

const int botao = 7;

void setup() {
  pinMode(ledVerdeCarro, OUTPUT);
  pinMode(ledAmareloCarro, OUTPUT);
  pinMode(ledVermelhoCarro, OUTPUT);
  pinMode(ledVerdePedestre, OUTPUT);
  pinMode(ledVermelhoPedestre, OUTPUT);
  pinMode(botao, INPUT_PULLUP);
  }

void loop() {
  if (digitalRead(botao) == LOW) {

    digitalWrite(ledVerdeCarro, LOW);
    digitalWrite(ledAmareloCarro, LOW);
    digitalWrite(ledVermelhoCarro, HIGH);

    digitalWrite(ledVermelhoPedestre, LOW);
    digitalWrite(ledVerdePedestre, HIGH);
  } else {

    digitalWrite(ledVerdePedestre, LOW);
    digitalWrite(ledVermelhoPedestre, HIGH);

    digitalWrite(ledVermelhoCarro, LOW);
    digitalWrite(ledVerdeCarro, HIGH);
    delay(4000);

    digitalWrite(ledVerdeCarro, LOW);
    digitalWrite(ledAmareloCarro, HIGH);
    delay(1000);

    digitalWrite(ledAmareloCarro, LOW);
    digitalWrite(ledVermelhoCarro, HIGH);
    delay(3000);
  }
}
