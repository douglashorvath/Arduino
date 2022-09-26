#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Fonts/FreeSerif12pt7b.h>
Adafruit_SSD1306 display(-1);

int quantidade_perguntas = 5;
long timer_oled = 0;
bool inverted = true;


void setup()   
{                
  Wire.begin(); //INICIALIZA A BIBLIOTECA WIRE
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C); //INICIALIZA O DISPLAY COM ENDEREÇO I2C 0x3C
  display.setTextColor(WHITE); //DEFINE A COR DO TEXTO
  display.setTextSize(1); //DEFINE O TAMANHO DA FONTE DO TEXTO
  display.clearDisplay(); //LIMPA AS INFORMAÇÕES DO DISPLAY

  display.clearDisplay();
  
}
void loop() {

  IniciaQuiz();
  ExibePergunta(54);
  delay(6000);
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
