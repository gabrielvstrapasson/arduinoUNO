#include <HCSR04.h>
#include <Servo.h>
#define SERVO 11
#define TRIGGER 9
#define ECHO 8
UltraSonicDistanceSensor distanceSensor(TRIGGER,ECHO);
Servo s;


void setup() {

  s.attach(SERVO);
  Serial.begin(9600);
  s.write(0);
}

void loop() {
  int distancia = distanceSensor.measureDistanceCm();
  Serial.println("Distancia: " + distancia);

  if (distancia < 20 && distancia > 0){
    Serial.println("Esta perto..");
    s.write (180);
  }
  else if (distancia > 50 ){
    Serial.println("Esta longe..");
    s.write(0);
  }
  else {
    Serial.println("Distancia moderada..");
    s.write(90);
  }

  delay (500);

}
