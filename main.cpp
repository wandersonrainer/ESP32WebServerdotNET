#include  <Arduino.h>
#include  <WiFi.h>
#include  <WebServer.h>

const char* ssid = "NOME_DA_REDE";
const char* pswd = "SENHA_DA_REDE";

WebServer servidor(80);

#define POT 33
#define BOT 14
#define POW 26
#define LED 2

void  funcaoLED();
void  funcaoPOT();
void  funcaoBOT();

void  setup(){
  //GPIO
  pinMode(BOT,INPUT_PULLUP);
  pinMode(LED,OUTPUT);
  pinMode(POW,OUTPUT);
  digitalWrite(POW,1);

  Serial.begin(9600);
  WiFi.begin(ssid,pswd);

  while(WiFi.status() != WL_CONNECTED){
    Serial.print(".");
    delay(500);
  }

  Serial.println("");
  Serial.println("WiFi conectado");
  Serial.print("Endereco IP: ");
  Serial.println(WiFi.localIP());

  servidor.on("/led/on",funcaoLED);
  servidor.on("/led/off",funcaoLED);
  servidor.on("/potenciometro",funcaoPOT);
  servidor.on("/botao",funcaoBOT);

  servidor.begin();
}

void  loop(){
  servidor.handleClient();
}

void  funcaoLED(){
  String dado = servidor.uri();
  if(dado=="/led/on")
    digitalWrite(LED,1);
  else if(dado=="/led/off")
    digitalWrite(LED,0);
  servidor.send(200,"text/plain","ok");
}

void  funcaoBOT(){
  int leituraBOT = digitalRead(BOT);
  servidor.send(200,"text/plain",String(leituraBOT));
}

void  funcaoPOT(){
  int leituraPOT = analogRead(POT);
  servidor.send(200,"text/plain",String(leituraPOT));
}