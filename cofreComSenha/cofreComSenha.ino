#include <Servo.h>

Servo servoTrancaCofre;
const int buzzer = 3;

// Teclado matricial
const int linha1 = 4, linha2 = 5, linha3 = 6, linha4 = 7;
const int coluna1 = 8, coluna2 = 9, coluna3 = 10, coluna4 = 11;

// Senha de 4 dígitos
const char senha[5] = "1234";
char entrada[5];
int idx = 0;

// Estados
bool modoDigitacao = false;
bool cofreAberto   = false;
int tentativas     = 0;

// Debounce por liberação
bool teclaAindaPressionada() {
  int l, c;
  return leTecla(l, c);
}

// Lê uma tecla (se houver), retornando true
bool leTecla(int &l, int &c) {
  digitalWrite(linha1, LOW);
  digitalWrite(linha2, LOW);
  digitalWrite(linha3, LOW);
  digitalWrite(linha4, LOW);
  for (int i = 0; i < 4; i++) {
    int pinL = linha1 + i;
    digitalWrite(pinL, HIGH);
    if (digitalRead(coluna1) == HIGH) { l = i; c = 0; digitalWrite(pinL, LOW); return true; }
    if (digitalRead(coluna2) == HIGH) { l = i; c = 1; digitalWrite(pinL, LOW); return true; }
    if (digitalRead(coluna3) == HIGH) { l = i; c = 2; digitalWrite(pinL, LOW); return true; }
    if (digitalRead(coluna4) == HIGH) { l = i; c = 3; digitalWrite(pinL, LOW); return true; }
    digitalWrite(pinL, LOW);
  }
  return false;
}

char mapaTeclas(int l, int c) {
  const char M[4][4] = {
    {'1','2','3','A'},
    {'4','5','6','B'},
    {'7','8','9','C'},
    {'*','0','#','D'}
  };
  return M[l][c];
}

void limpaConsole() {
  // Envia várias linhas em branco (Serial Monitor mostra no topo)
  for (int i = 0; i < 50; i++) {
    Serial.println();
  }
}

void alarme() {
  for (int k = 0; k < 15; k++) {
    for (int f = 500; f < 2000; f += 20) {
      tone(buzzer, f);
      delayMicroseconds(600);
    }
  }
  noTone(buzzer);
}

void destranca() {
  for (int a = 90; a >= 0; a--) {
    servoTrancaCofre.write(a);
    delay(10);
  }
}

void tranca() {
  for (int a = 0; a <= 90; a++) {
    servoTrancaCofre.write(a);
    delay(10);
  }
}

void setup() {
  Serial.begin(9600);
  // Configura linhas como saída e colunas como entrada
  pinMode(linha1, OUTPUT); pinMode(linha2, OUTPUT);
  pinMode(linha3, OUTPUT); pinMode(linha4, OUTPUT);
  pinMode(coluna1, INPUT); pinMode(coluna2, INPUT);
  pinMode(coluna3, INPUT); pinMode(coluna4, INPUT);

  pinMode(buzzer, OUTPUT);
  servoTrancaCofre.attach(12);
  tranca();  // inicia fechado
}

void loop() {
  int l, c;
  if (!leTecla(l, c)) return;

  char tecla = mapaTeclas(l, c);
  delay(50);  // debounce inicial

  // PROCESSA '#'
  if (tecla == '#') {
    // Se o cofre estiver aberto, fecha e limpa console
    if (cofreAberto) {
      limpaConsole();
      Serial.println("Fechando cofre...");
      tranca();
      cofreAberto = false;
      modoDigitacao = false;
      idx = 0;
    }
    // Se não está em modo digitação, inicia entrada
    else if (!modoDigitacao) {
      limpaConsole();
      modoDigitacao = true;
      idx = 0;
      Serial.println("Modo senha: digite 4 dígitos");
    }
    // Caso esteja no meio da digitação, valida e limpa console
    else {
      entrada[idx] = '\0';
      limpaConsole();
      if (idx == 4 && strcmp(entrada, senha) == 0) {
        Serial.println("Senha correta! Abrindo cofre...");
        destranca();
        cofreAberto = true;
        tentativas = 0;
      } else {
        tentativas++;
        Serial.print("Senha incorreta! Tentativas: ");
        Serial.println(tentativas);
        if (tentativas >= 3) {
          Serial.println("Alarme ativado!");
          alarme();
        }
      }
      modoDigitacao = false;
      idx = 0;
    }

    // espera até soltar
    while (teclaAindaPressionada()) delay(10);
    return;
  }

  // PROCESSA dígitos se estiver no modo de digitação
  if (modoDigitacao) {
    if (idx < 4) {
      entrada[idx++] = tecla;
      entrada[idx] = '\0';
      Serial.print("Senha até agora: ");
      Serial.println(entrada);
    } else {
      // ultrapassou 4 dígitos → invalida e limpa
      limpaConsole();
      Serial.println("Máximo de 4 dígitos excedido! Tentativa inválida.");
      tentativas++;
      Serial.print("Tentativas: "); Serial.println(tentativas);
      if (tentativas >= 3) {
        Serial.println("Alarme ativado!");
        alarme();
      }
      modoDigitacao = false;
      idx = 0;
    }
  }

  // debounce por liberação
  while (teclaAindaPressionada()) delay(10);
}
