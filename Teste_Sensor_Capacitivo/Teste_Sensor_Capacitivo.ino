#include <CapacitiveSensor.h>

int BOTAO_MENOS_PIN = 16;
int BOTAO_MAIS_PIN = 15;
int CAPACITIVE_SENSOR_OUT = 8;
CapacitiveSensor BOTAO_MAIS = CapacitiveSensor(CAPACITIVE_SENSOR_OUT,BOTAO_MAIS_PIN);
CapacitiveSensor BOTAO_MENOS = CapacitiveSensor(CAPACITIVE_SENSOR_OUT,BOTAO_MENOS_PIN);
long press_botao_mais;
long press_botao_menos;

void setup() {
    Serial.begin(9600);

}

void loop() {
  press_botao_mais = BOTAO_MAIS.capacitiveSensor(30);

  if(press_botao_mais>500)
  {
    Serial.println("Botao MAIS Pressionado");
  }
  //Serial.println(press_botao_mais);

  press_botao_menos = BOTAO_MENOS.capacitiveSensor(30);

  if(press_botao_menos>500)
  {
    Serial.println("Botao MENOS Pressionado");
  }
  //Serial.println(press_botao_menos);
  delay(50);

  
}
