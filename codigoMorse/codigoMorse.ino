const unsigned int MAX_MESSAGE_LENGTH = 12;


const int LED_PONTO = 5;  // LED para ponto
const int LED_TRACO = 6;  // LED para traço

void setup() {
  pinMode(LED_PONTO, OUTPUT);
  pinMode(LED_TRACO, OUTPUT);
  Serial.begin(9600);
}

String morseChar(char c) {
  switch (toupper(c)) {
    case 'A': return ".-";
    case 'B': return "-...";
    case 'C': return "-.-.";
    case 'D': return "-..";
    case 'E': return ".";
    case 'F': return "..-.";
    case 'G': return "--.";
    case 'H': return "....";
    case 'I': return "..";
    case 'J': return ".---";
    case 'K': return "-.-";
    case 'L': return ".-..";
    case 'M': return "--";
    case 'N': return "-.";
    case 'O': return "---";
    case 'P': return ".--.";
    case 'Q': return "--.-";
    case 'R': return ".-.";
    case 'S': return "...";
    case 'T': return "-";
    case 'U': return "..-";
    case 'V': return "...-";
    case 'W': return ".--";
    case 'X': return "-..-";
    case 'Y': return "-.--";
    case 'Z': return "--..";
    case '0': return "-----";
    case '1': return ".----";
    case '2': return "..---";
    case '3': return "...--";
    case '4': return "....-";
    case '5': return ".....";
    case '6': return "-....";
    case '7': return "--...";
    case '8': return "---..";
    case '9': return "----.";
    case ' ': return "/"; 
    default: return "";   
  }
}

void blinkMorse(String morseCode) {
  for (int i = 0; i < morseCode.length(); i++) {
    char symbol = morseCode[i];

    if (symbol == '.') {
      digitalWrite(LED_PONTO, HIGH);
      delay(500); // ponto
      digitalWrite(LED_PONTO, LOW);
    } else if (symbol == '-') {
      digitalWrite(LED_TRACO, HIGH);
      delay(1000); // traço
      digitalWrite(LED_TRACO, LOW);
    } else if (symbol == '/') {
      delay(1500); // pausa
      continue;
    }

    delay(250); // pausa os sinais que sao da mesma letra
  }
}

void loop() {
  static char message[MAX_MESSAGE_LENGTH];
  static unsigned int message_pos = 0;

  while (Serial.available() > 0) {
    char inByte = Serial.read();

    if ((inByte != '\n') && (message_pos < MAX_MESSAGE_LENGTH - 1)) {
      message[message_pos++] = inByte;
    } else {
      message[message_pos] = '\0';

      Serial.println("Mensagem recebida:");
      Serial.println(message);

      for (int i = 0; i < message_pos; i++) {
        String morse = morseChar(message[i]);
        blinkMorse(morse);
        delay(750); // pausa entra as letras 
      }

      message_pos = 0;
    }
  }
}
