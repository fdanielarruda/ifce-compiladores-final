#include <Arduino.h>
#include <WiFi.h>

int sensor;
int sensorValor;
String url;
String payload;
String ssid;
String senha;
String senha;

void setup()
{
Serial.begin(115200);
url = "http://example.com";
payload = "dados=123";
ssid = "MinhaRedeWiFi";
senha = "MinhaSenhaWiFi";
sensor = 36;
pinMode(sensor, INPUT);
WiFi.begin(ssid.c_str(), senha.c_str());
while (WiFi.status() != WL_CONNECTED)
{
    delay(500);
    Serial.println("Conectando ao WiFi...");
}
Serial.println("Conectado ao WiFi!");
}

void loop()
{
sensorValor = analogRead(sensor);
Serial.println("Valor do sensor: ");
Serial.println(sensorValor);
if (WiFi.status() == WL_CONNECTED)
{
    http.begin(url);
    int httpResponseCode = http.GET();
    if (httpResponseCode > 0) {
        Serial.print("Resposta HTTP: ");
        Serial.println(httpResponseCode);
    } else {
        Serial.print("Erro na requisição: ");
        Serial.println(httpResponseCode);
    }
    http.end();
} else {
    Serial.println("WiFi desconectado, tentando reconectar...");
    WiFi.begin(url, payload);
}
delay(2000);
}
