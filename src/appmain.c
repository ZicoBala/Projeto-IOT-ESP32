#include <DHT.h>
#include <math.h>

#define DHTPIN 4
#define DHTTYPE DHT22

DHT sensor(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(115200);
  Serial.println("Iniciando o sensor DHT22...");
  sensor.begin();
}

void loop() {
  delay(2000);

  float temperatura = sensor.readTemperature();
  float umidade = sensor.readHumidity();

  if (isnan(umidade) || isnan(temperatura)) {
    Serial.println("Falha ao ler dados do sensor DHT22!");
    return;
  }

  Serial.print("Umidade: ");
  Serial.print(umidade);
  Serial.print("%\t");
  Serial.print("Temperatura: ");
  Serial.print(temperatura);
  Serial.println(" C");
}