#include <LiquidCrystal.h>

// Pinos 
int ultrassonicoPin = 3;
int vermelhoPin = 4;
int verdePin = 5;

// Configuração da distância limite para estar ocupado
int DISTANCIA_MINIMA = 150;

// Define os pinos do LCD
LiquidCrystal lcd(12, 11, 10, 9, 8, 7);

void setup() {
  // Define os leds como portas de saída
  pinMode(vermelhoPin, OUTPUT);
  pinMode(verdePin, OUTPUT);
 
  // Desliga todos os leds a piori
  digitalWrite(vermelhoPin, LOW);
  digitalWrite(verdePin, LOW);
  
  // Confifura o LCD
  lcd.begin(16, 2);
  
  // Inicializa o serial
  Serial.begin(9600);
}

void loop() {
  // Pega a distancia do sensor
  long distancia = getDistanceCm();
  
  // Mostra a distancia no serial
  Serial.println(distancia);
  
  // Lima a tela do LCD
  lcd.clear();
  
  if(distancia < DISTANCIA_MINIMA) {
    // Escreve na primeira linha do LCD "Vaga ocupada"
    lcd.setCursor(0, 0);
    lcd.print("Vaga ocupada");

    // Liga o led vermelho
  	digitalWrite(vermelhoPin, HIGH);
    
    // Desliga o led verde
    digitalWrite(verdePin, LOW);
  }
  else {
    // Escreve na primeira linha do LCD "Vaga disponivel"
    lcd.setCursor(0, 0);
    lcd.print("Vaga disponivel");

    // Desliga o led vermelho
  	digitalWrite(vermelhoPin, LOW);
    
    // Liga o led verde
    digitalWrite(verdePin, HIGH);
  }
  
  // Escreve a distância na segunda linha do LCD
  lcd.setCursor(0, 1);
  lcd.print(String(distancia) + " cm");
  
  // Espera 0.5 segundo
  delay(500);
}

long getDistanceCm() {
  // Manda um pulso
  pinMode(ultrassonicoPin, OUTPUT);
  digitalWrite(ultrassonicoPin, LOW);
  delayMicroseconds(2);
  digitalWrite(ultrassonicoPin, HIGH);
  delayMicroseconds(5);
  digitalWrite(ultrassonicoPin, LOW);
  
  // Mede o tempo de retorno do pulso
  pinMode(ultrassonicoPin, INPUT);
  long tempoTotal = pulseIn(ultrassonicoPin, HIGH);

  // Converte tempo do pulso em distância
  return 0.0343 * (tempoTotal / 2);
}