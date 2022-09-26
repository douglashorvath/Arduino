// C++ code
//
int BOTAO = 2;
int LED_VERDE = 8;
int LED_AMARELO = 9;
int LED_LARANJA = 10;
int LED_AZUL = 11;
int LED_VERMELHO = 12;
int LED_BRANCO = 13;




void setup()
{
  Serial.begin(9600);
  pinMode(LED_VERDE,OUTPUT);
  pinMode(LED_AMARELO,OUTPUT);
  pinMode(LED_LARANJA,OUTPUT);
  pinMode(LED_AZUL,OUTPUT);
  pinMode(LED_VERMELHO,OUTPUT);
  pinMode(LED_BRANCO,OUTPUT);
  
  pinMode(BOTAO,INPUT_PULLUP);
  
  digitalWrite(LED_VERDE,LOW);
  digitalWrite(LED_AMARELO,LOW);
  digitalWrite(LED_LARANJA,LOW);
  digitalWrite(LED_AZUL,LOW);
  digitalWrite(LED_VERMELHO,LOW);
  digitalWrite(LED_BRANCO,LOW);
}

void loop()
{

  if(!digitalRead(BOTAO))
  {
    digitalWrite(LED_VERDE,LOW);
    digitalWrite(LED_AMARELO,LOW);
    digitalWrite(LED_LARANJA,LOW);
    digitalWrite(LED_AZUL,LOW);
    digitalWrite(LED_VERMELHO,LOW);
    digitalWrite(LED_BRANCO,LOW);
    delay(500);
    
    
    int sorteio = random(1,7);

    digitalWrite(LED_VERDE,HIGH);
    
    if(sorteio>1)
    {
      digitalWrite(LED_AMARELO,HIGH);
      if(sorteio>2)
      {
        digitalWrite(LED_LARANJA,HIGH);
        if(sorteio>3)
        {
          digitalWrite(LED_AZUL,HIGH);
          if(sorteio>4)
          {
            digitalWrite(LED_VERMELHO,HIGH);
            if(sorteio>5)
            {
              digitalWrite(LED_BRANCO,HIGH);
            }
          }
        }
      }
      delay(100);
    }
    
    delay(10);
  }
  
}
