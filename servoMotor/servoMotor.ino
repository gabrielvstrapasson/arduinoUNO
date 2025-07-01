
#include <Servo.h>
#define SERVO 9

Servo s;
int pos;
const int botaoHorario = 7; 
const int botaoAntHorario = 6;
int posicaoHorario = 0;
int posicaoAntHorario = 180;

void setup() {
  pinMode (botaoHorario, INPUT_PULLUP);
  pinMode (botaoAntHorario, INPUT_PULLUP);
  s.attach(SERVO);
  Serial.begin(9600);
  s.write(0);


}

void loop() {
  if (digitalRead(botaoHorario) == LOW){
    posicaoHorario = pos;
    for (pos = posicaoHorario; (digitalRead(botaoHorario) == LOW); pos++){
      s.write(pos);
      delay(10);
    
    } 
  }
  else if (digitalRead(botaoAntHorario) == LOW){
    posicaoAntHorario = pos;
      for(pos = posicaoAntHorario; (digitalRead(botaoAntHorario) == LOW); pos--){
        s.write(pos);
        delay(10);
        
    }
  }
  }

