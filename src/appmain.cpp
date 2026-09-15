#include <DHT.h>
#include <stdio.h>

#define DHTPIN 4
#define DHTTYPE DHT11
#define LIMITE_TEMPERATURA 28.0

DHT sensor(DHTPIN, DHTTYPE);

float temperaturaMinima = 999;
float temperaturaMaxima = -999;
bool ALERTA_TEMPERATURA = false;
float historicoTemperatura[5] = {0.0, 0.0, 0.0, 0.0, 0.0};

void setup() {
  Serial.begin(115200);
  sensor.begin();
}

void addHistorico(float novaTemp) {
  for (int i = 0; i < 4; i++) {
    historicoTemperatura[i] = historicoTemperatura[i + 1]; 
    }
    historicoTemperatura[4] = novaTemp;
    }

void mostrarTemperaturas() {
   Serial.println("Últimas 5 temperaturas registradas:");
    for (int i = 0; i < 5; i++) {
      Serial.print(historicoTemperatura[i]);
      Serial.print(" °C | "); 
      } 
      Serial.println();
    }

void loop() {
  float temperatura = sensor.readTemperature();
  float umidade = sensor.readHumidity();

  
  if (isnan(umidade) || isnan(temperatura) || (temperatura == 0) & (umidade == 0)) {
    Serial.println("Falha ao ler dados do sensor DHT11!");
    return;
  } else {
    Serial.println("Temperatura: ");
    Serial.println(temperatura);
    Serial.println(" C");
    Serial.println("Umidade:");
    Serial.println(umidade);
    Serial.println(" %");
    Serial.println(" --- ");
  }

  addHistorico(temperatura);
  mostrarTemperaturas();

  // dentro do loop, depois de validar que a leitura não é nan:
  if (temperatura < temperaturaMinima) {
  temperaturaMinima = temperatura;
  }

  if (temperatura > temperaturaMaxima) {
  temperaturaMaxima = temperatura;
  }
    
    Serial.print("Minima: ");
    Serial.print(temperaturaMinima);
    Serial.print(" | Maxima: ");
    Serial.println(temperaturaMaxima);
    Serial.println("------");

  if (temperatura > LIMITE_TEMPERATURA) {
     ALERTA_TEMPERATURA = true;
     Serial.println("ALERTA: TEMPERATURA ACIMA DO PERMITIDO!!");
     Serial.println(temperatura);
     Serial.println("------");
  } else {
    ALERTA_TEMPERATURA = false;
  }


char jsonBuffer[100];
 
Serial.print(jsonBuffer, "{\"temperatura\":%.2f,\"umidade\":%.2f,\"temperaturaMaxima\":%.2f,\"ALERTA_TEMPERATURA\":true}", temperatura, umidade, temperaturaMaxima, ALERTA_TEMPERATURA);
 
Serial.println(temperatura);
Serial.println(umidade);
Serial.println(temperaturaMaxima);
Serial.println(LIMITE_TEMPERATURA);

Serial.printf("A temperatura, a umidade, a temperatura máxima e o alerta são: %.2f°C, %.2f%%, %.2f°C, %.2f\\n", temperatura, umidade, temperaturaMaxima, ALERTA_TEMPERATURA);
Serial.print("JSON Gerado: ");
Serial.println(jsonBuffer);
Serial.println("---");

delay(5000);
}