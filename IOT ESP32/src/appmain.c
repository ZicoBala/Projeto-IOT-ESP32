#include <DHT.h> //importa a biblioteca para conversar com o sensor

#define DHTPIN 4     // define que o pino de dados está na GPIO 4 da ESP32
#define DHTTYPE DHT22 // especifica que estamos usando o modelo DHT22

DHT sensor(DHTPIN, DHTTYPE); // inicia o objeto do sensor dht

void setup() {

  Serial.begin(115200); // inicia a comunicação serial em alta velocidade para a ESP32
  Serial.println("Iniciando o sensor DHT22...");
  sensor.begin(); // inicia o sensor físico
}

void loop() {
  
delay(2000); 
  // le a umidade (%) e a temperatura (°C) em valores decimais (float)
  float temperatura = sensor.readTemperature();
  float umidade = sensor.readHumidity();
  
  // testa se a leitura falhou (isnan significa "não é um numero")
  if (isnan(umidade) || isnan(temperatura)) {
    Serial.println("Falha ao ler dados do sensor DHT22!");
    return; // reinicia o loop para tentar ler novamente
  }else{
  Serial.print("Umidade: ");// mostra as leituras em tempo real no monitor do seu computador
  Serial.print(umidade);
  Serial.print("%\t");
  Serial.print("Temperatura: ");
  Serial.print(temperatura);
  Serial.println("°C");
  }
}