#include <Arduino.h>
#include <WiFi.h>

int ledPin;
int botaoPin;
bool estadoBotao;

void setup()
{
ledPin = 2;
botaoPin = 4;
pinMode(botaoPin, INPUT);
}

void loop()
{
estadoBotao = digitalRead(botaoPin);
if (estadoBotao == 1)
{
digitalWrite(ledPin, HIGH);
}
else
{
digitalWrite(ledPin, LOW);
}
delay(1000);
}
