#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Fonts/FreeSerif12pt7b.h>
Adafruit_SSD1306 display(-1);


class UniqueRandom{
  private:
    int _index;
    int _min;
    int _max;
    int _size;
    int* _list;
    void _init(int min, int max) {
      _list = 0; 
      if (min < max) { _min = min; _max = max; } else { _min = max; _max = min; }
      _size = _max - _min; 
      _index = 0;
    }    
  public:
    UniqueRandom(int max)           { _init(0,   max); randomize(); } //construtor com 1 parametro
    UniqueRandom(int min, int max)  { _init(min, max); randomize(); } //construtor com 2 parametros
    
    void randomize() {
      if (_list == 0) { _list = (int*) malloc(size() * sizeof(int)); }  
      for (int i=0; i<=size(); i++) {   _list[i] = _min+i;  }   //preenche a lista do menor ao maior valor
      
      //embaralha a lista
      for (int i=0; i<=size(); i++) {  
        int r = random(0, size());     //sorteia uma posição qualquer
        int aux = _list[i];               
        _list[i] = _list[r];
        _list[r] = aux;
      }
    }
  
    void resetWithNewParameters(int min, int max) { _init(min, max); randomize(); }
    
    int next() {                                  //retorna o proximo numero da lista
      if (_index > size() ) { _index = 0;}
      int n = _list[_index++];
       //após recuper o ultimo numero, recomeça na posicao 0
      return n;
    }
    
    int size() { return _size; }
  
    int index() { return _index; }
  
    int getAt(int index)
    {
      return _list[index];
    }
    
    ~UniqueRandom(){ free ( _list ); }  //destrutor
};


int LED_LARANJA = 13;
int LED_VERDE = 12;
int LED_AZUL = 11;
int LED_AMARELO = 10;

int BOTAO_AMARELO = 9;
int BOTAO_AZUL = 8;
int BOTAO_VERDE = 7;
int BOTAO_LARANJA = 6;
int BOTAO_MENOS = 5;
int BOTAO_MAIS = 4;
int BOTAO_START = 3;

int BUZZER = 2;
long buzzer_timer = 0;

int GAME_TIME = 0;
bool START = false;

UniqueRandom perguntas(0);
int quantidade_perguntas = 5;
int index_perguntas = 0;


//Configurações do Display
long timer_oled = 0;
bool inverted = true;

void setup()
{
  Serial.begin(9600);
  int seed = 0;
  seed = analogRead(A0);
  randomSeed(seed);
  
  
  pinMode(LED_LARANJA, OUTPUT);
  pinMode(LED_VERDE, OUTPUT);
  pinMode(LED_AZUL, OUTPUT);
  pinMode(LED_AMARELO, OUTPUT);
  
  digitalWrite(LED_LARANJA, LOW);
  digitalWrite(LED_VERDE, LOW);
  digitalWrite(LED_AZUL, LOW);
  digitalWrite(LED_AMARELO, LOW);
  
  pinMode(BOTAO_LARANJA,INPUT_PULLUP);
  pinMode(BOTAO_VERDE,INPUT_PULLUP);
  pinMode(BOTAO_AZUL,INPUT_PULLUP);
  pinMode(BOTAO_AMARELO,INPUT_PULLUP);
  
  pinMode(BOTAO_MAIS,INPUT_PULLUP);
  pinMode(BOTAO_MENOS,INPUT_PULLUP);
  pinMode(BOTAO_START,INPUT_PULLUP);
  
  pinMode(BUZZER,OUTPUT);
  perguntas.resetWithNewParameters(1,quantidade_perguntas);

  //Inicializar Display
  Wire.begin(); //INICIALIZA A BIBLIOTECA WIRE
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C); //INICIALIZA O DISPLAY COM ENDEREÇO I2C 0x3C
  display.setTextColor(WHITE); //DEFINE A COR DO TEXTO
  display.setTextSize(1); //DEFINE O TAMANHO DA FONTE DO TEXTO
  display.clearDisplay(); //LIMPA AS INFORMAÇÕES DO DISPLAY
}

void loop()
{
  if(GAME_TIME == 3)
  {
    
    if (!digitalRead(BOTAO_MAIS))
    {
      ledApagaTodos();
      index_perguntas++;
      if(quantidade_perguntas <= index_perguntas)
      {
        index_perguntas--;
        //fim do jogo
      }
      else
      {
        Serial.print("PERGUNTA: ");
        Serial.println(perguntas.getAt(index_perguntas));
      }
      delay(500);
    }
    if (!digitalRead(BOTAO_MENOS))
    {
      ledApagaTodos();
      index_perguntas--;
      if(index_perguntas < 0)
      {
        index_perguntas = 0;
      }
      Serial.print("PERGUNTA: ");
      Serial.println(perguntas.getAt(index_perguntas));
      delay(500);
    }
    if (!digitalRead(BOTAO_START)) {
      
      int tempo_init = random(3,8);
      piscaTodosLeds(tempo_init, 500, 500);
      START = true;
      buzzer_timer = millis();
      tone(BUZZER,500);
      
    }

    if (!digitalRead(BOTAO_LARANJA) && START) {
      digitalWrite(LED_LARANJA, HIGH);
      START = false;
    }
    if (!digitalRead(BOTAO_VERDE) && START) {
      digitalWrite(LED_VERDE, HIGH);
      START = false;
    }
    if (!digitalRead(BOTAO_AZUL) && START) {
      digitalWrite(LED_AZUL, HIGH);
      START = false;
    }
    if (!digitalRead(BOTAO_AMARELO) && START) {
      digitalWrite(LED_AMARELO, HIGH);
      START = false;
    }
    buzzer();
  }
  else
  {
    if(GAME_TIME == 0)
    {
      IniciaHardware();
      Serial.println("Selecione a quantidade de perguntas");
      Serial.print("Quantidade: ");
      Serial.println(quantidade_perguntas);
      SelecionaQuantidadePerguntas();
      
      GAME_TIME = 1;
    }
    else
    {
      if(GAME_TIME == 1)
      {
        if (!digitalRead(BOTAO_MAIS))
        {
          if(quantidade_perguntas<99)
          {
            quantidade_perguntas++;
          }
          Serial.print("Quantidade: ");
          Serial.println(quantidade_perguntas);
          SelecionaQuantidadePerguntas();
          delay(200);
        }
        if (!digitalRead(BOTAO_MENOS))
        {
          if(quantidade_perguntas>5)
          {
            quantidade_perguntas--;
          }
          Serial.print("Quantidade: ");
          Serial.println(quantidade_perguntas);
          SelecionaQuantidadePerguntas();
          delay(200);
        }
        if (!digitalRead(BOTAO_START)) 
        {
          Serial.println("Comecando Jogo!");
          ledStartGame();
          index_perguntas = 0;
          GAME_TIME = 3;
          perguntas.resetWithNewParameters(1,quantidade_perguntas);
          IniciaQuiz();
          delay(250);
          Serial.print("PERGUNTA: ");
          Serial.println(perguntas.getAt(index_perguntas));
          ExibePergunta(perguntas.getAt(index_perguntas));
        }
      }
      
    }
  }
}

void ledAcendeTodos(int time)
{
  digitalWrite(LED_LARANJA, HIGH);
  digitalWrite(LED_VERDE, HIGH);
  digitalWrite(LED_AZUL, HIGH);
  digitalWrite(LED_AMARELO, HIGH);
  delay(time);
  digitalWrite(LED_LARANJA, LOW);
  digitalWrite(LED_VERDE, LOW);
  digitalWrite(LED_AZUL, LOW);
  digitalWrite(LED_AMARELO, LOW);
}

void ledApagaTodos()
{
  digitalWrite(LED_LARANJA, LOW);
  digitalWrite(LED_VERDE, LOW);
  digitalWrite(LED_AZUL, LOW);
  digitalWrite(LED_AMARELO, LOW);
}

void piscaTodosLeds(int vezes, int aceso, int apagado)
{
  for(int i=0; i<vezes; i++)
  {
    ledAcendeTodos(aceso);
    delay(apagado);
  }
}
  

void ledStartGame()
{
  digitalWrite(LED_LARANJA, HIGH);
  delay(250);
  digitalWrite(LED_LARANJA, LOW);
  digitalWrite(LED_VERDE, HIGH);
  delay(250);
  digitalWrite(LED_VERDE, LOW);
  digitalWrite(LED_AZUL, HIGH);
  delay(250);
  digitalWrite(LED_AZUL, LOW);
  digitalWrite(LED_AMARELO, HIGH);
  delay(250);
  digitalWrite(LED_AMARELO, LOW);
  digitalWrite(LED_AZUL, HIGH);
  delay(250);
  digitalWrite(LED_AZUL, LOW);
  digitalWrite(LED_VERDE, HIGH);
  delay(250);
  digitalWrite(LED_VERDE, LOW);
  digitalWrite(LED_LARANJA, HIGH);
  delay(250);
  digitalWrite(LED_LARANJA, LOW);
  delay(500);
  
  digitalWrite(LED_LARANJA, HIGH);
  digitalWrite(LED_VERDE, HIGH);
  digitalWrite(LED_AZUL, HIGH);
  digitalWrite(LED_AMARELO, HIGH);
  delay(500);
  digitalWrite(LED_LARANJA, LOW);
  digitalWrite(LED_VERDE, LOW);
  digitalWrite(LED_AZUL, LOW);
  digitalWrite(LED_AMARELO, LOW);

}

void buzzer()
{
  if(buzzer_timer != 0)
  {
    int current_time = millis();
    int delay = current_time - buzzer_timer;
    if(delay > 500)
    {
      noTone(BUZZER);
      buzzer_timer = 0;
    }
      
  }
}

void IniciaHardware()
{
  
  timer_oled = 0;
// Movimenta o texto sobre a tela..
  display.clearDisplay();
  display.setTextSize(1); // Fonte do texto
  display.invertDisplay(false);
  display.setTextColor(WHITE); // Cor do texto
  display.setCursor(30,9); // fim da linha amarela
  display.setTextSize(3);
  display.println("QUIZ");
  display.display();
  delay(500);
  display.invertDisplay(true);
  delay(500);
  display.invertDisplay(false);
  delay(500);
  display.invertDisplay(true);
  delay(500);
  display.invertDisplay(false);
  delay(500);
  display.invertDisplay(true);
  delay(500);
  display.invertDisplay(false);
  delay(500);
  

}

void IniciaQuiz()
{
  timer_oled = 0;
// Movimenta o texto sobre a tela..
  display.clearDisplay();
  display.setTextSize(1); // Fonte do texto
  display.setTextColor(WHITE); // Cor do texto
  display.setCursor(0,0); // Posiciona o cursor
  display.println("Iniciando"); // Imprime mensagem
  display.display();
  
  display.setCursor(0,8); // fim da linha amarela
  display.setTextSize(3);
  display.println("QUIZ");
  display.display();
  display.startscrollright(1, 7); // Movimenta texto para a direita
  delay(2000);
  display.stopscroll();
  delay(500);
  display.startscrollleft(1, 7); // Movimenta texto para a esquerda
  delay(2000);
  display.stopscroll();
  delay(500);
}

void ExibePergunta(int numero)
{
  timer_oled = 0;
  display.clearDisplay();
  display.setTextSize(1); // Fonte do texto
  display.setTextColor(WHITE); // Cor do texto
  display.setCursor(0,0); // Posiciona o cursor
  display.println("Pergunta"); // Imprime mensagem
  display.display();
  display.setCursor(0,8); // fim da linha amarela
  display.setTextSize(3);
  display.println(numero);
  display.display();
}

void PrimeiraPergunta(int numero)
{
  timer_oled = 0;
  display.clearDisplay();
  display.setTextSize(1); // Fonte do texto
  display.setTextColor(WHITE); // Cor do texto
  display.setCursor(0,0); // Posiciona o cursor
  display.println("Primeira Pergunta"); // Imprime mensagem
  display.display();
  display.setCursor(0,8); // fim da linha amarela
  display.setTextSize(3);
  display.println(numero);
  display.display();
}

void UltimaPergunta(int numero)
{
  timer_oled = 0;
  display.clearDisplay();
  display.setTextSize(1); // Fonte do texto
  display.setTextColor(WHITE); // Cor do texto
  display.setCursor(0,0); // Posiciona o cursor
  display.println("Ultima Pergunta"); // Imprime mensagem
  display.display();
  display.setCursor(0,8); // fim da linha amarela
  display.setTextSize(3);
  display.println(numero);
  display.display();
}

void SelecionaQuantidadePerguntas()
{
  timer_oled = 0;
  display.clearDisplay();
  display.setTextSize(1); // Fonte do texto
  display.setTextColor(WHITE); // Cor do texto
  display.setCursor(0,0); // Posiciona o cursor
  display.println("Quantas Perguntas?"); // Imprime mensagem
  display.display();
  display.setCursor(0,8); // fim da linha amarela
  display.setTextSize(3);
  display.println(quantidade_perguntas);
  display.display();
}

void aguarde(int aguarde_fase)
{
  if(aguarde_fase == 0)
  {
    timer_oled = millis();
    display.clearDisplay();
  
    display.setTextSize(3);
    display.setTextColor(WHITE);
    display.setCursor(0,9);
    display.println("Aguarde");
    display.display();
    display.fillRect(0, 0, 16, 8, WHITE);
    display.display();
    
    display.startscrollright(0, 0);
  }
  
  if(aguarde_fase == 2)
  {
    display.stopscroll();
    display.clearDisplay();
  }
  
  
}

void aperte()
{
  
  if(timer_oled == 0)
  {
    timer_oled = millis();
  }

  long current_millis = millis();
  long passed = current_millis - timer_oled;
  if(passed>500)
  {
      display.clearDisplay();
      if(!inverted)
      {
        display.invertDisplay(false);
        inverted = true;
      }
      else
      {
        display.invertDisplay(true);
        inverted = false;
      }
      display.setTextColor(WHITE);
      display.setCursor(10,9); // fim da linha amarela
      display.setTextSize(3);
      display.println("APERTE");
      display.display();
      timer_oled = current_millis;
  }
}
