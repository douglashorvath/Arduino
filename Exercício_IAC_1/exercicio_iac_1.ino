// Douglas Horvath
//

// declaração dos pinos
int LED_VERDE = 7;
int LED_AMARELO = 6;
int LED_VERMELHO = 8;
int BUZZER = 10;

void setup()
{
    // preparação dos modos dos pinos
    pinMode(LED_VERDE, OUTPUT);
    pinMode(LED_AMARELO, OUTPUT);
    pinMode(LED_VERMELHO, OUTPUT);
    pinMode(BUZZER, OUTPUT);

    // inicialização dos pinos desligados
    digitalWrite(LED_VERDE, LOW);
    digitalWrite(LED_AMARELO, LOW);
    digitalWrite(LED_VERMELHO, LOW);
}

void loop()
{
    // acende o verde
    digitalWrite(LED_VERDE, HIGH);
    delay(10000);
    // apaga o verde e acente o amarelho
    digitalWrite(LED_VERDE, LOW);
    digitalWrite(LED_AMARELO, HIGH);
    // tom em 440hz
    tone(BUZZER, 440);
    delay(2000);
    // desliga o tom
    noTone(BUZZER);
    // apaga o amarelho e acende o vermelho
    digitalWrite(LED_AMARELO, LOW);
    digitalWrite(LED_VERMELHO, HIGH);
    delay(5000);
    // apaga o vermelho
    digitalWrite(LED_VERMELHO, LOW);
}