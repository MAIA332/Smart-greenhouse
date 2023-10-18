#include <WiFi.h>
#include <ESPAsyncWebSrv.h>
#include <HTTPClient.h>
 
const char* ssid = "NOTE 50";
const char* password = "39866418820";
const char* htmlContent = "<html><body><h1>Hello!, Esp32</h1><p>Projeto: IOT API para integrações em arduino ESP32</p><p>Documentação:https://github.com/MAIA332/IOTAPI</p>"
                          "</body></html>";

const char* htmlContentOn = "<html><body><h1>ON</h1>"
                          "</body></html>";

const char* htmlContentOff = "<html><body><h1>OFF</h1>"
                          "</body></html>";

int LED = 7;

AsyncWebServer server(80);
 
void setup() {
  Serial.begin(115200);
 
  Serial.println();
  Serial.print("Conectando-se a ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
 
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print("Conectando-se ao wifi \n");
  }
 
  Serial.println("");
  Serial.println("WiFi conectada.");
  Serial.println("Endereço de IP: ");
  Serial.println(WiFi.localIP());


  // Cria a rota principal  na raiz / pelo metodo GET e mostra o conteúdo principal
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(200, "text/html", htmlContent);
  });

  // Cria a rotas secundárias pelos metodos POST/GET
  /* server.on("/status", HTTP_GET, [](AsyncWebServerRequest *request){
    Serial.println("Acesso ao status");
    
    char* LEDState = digitalRead(LED);

    request->send(200, "text", LEDState);
  }); */

  server.on("/ligar-lamp", HTTP_GET, [](AsyncWebServerRequest *request){    
   
    Serial.println("Ligado lamp");
    Serial.write('A');
  
    request->send(200, "text/html", htmlContentOn);
  });

  server.on("/desligar-lamp", HTTP_GET, [](AsyncWebServerRequest *request){
   
    Serial.println("Desligou! lamp");
    Serial.write('B');
    
    request->send(200, "text/html", htmlContentOff);
  });

  server.on("/ligar-fan", HTTP_GET, [](AsyncWebServerRequest *request){
    digitalWrite(LED,HIGH);
    
    if(digitalRead(LED) == HIGH){
      Serial.println("Ligado fan");
    }
    request->send(200, "text/html", htmlContentOn);
  });

  server.on("/desligar-fan", HTTP_GET, [](AsyncWebServerRequest *request){
    digitalWrite(LED,LOW);

    if(digitalRead(LED) == LOW){
      Serial.println("Desligou fan!");
    }
    request->send(200, "text/html", htmlContentOff);
  });

  // Inicia o servidor
  server.begin();


}

void loop() {

}


