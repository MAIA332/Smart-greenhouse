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

  // Cria a rota de visualização de status pelos metodos POST/GET
  server.on("/status", HTTP_GET, [](AsyncWebServerRequest *request){
    Serial.println("Acesso ao status");
    Serial.write("S");

    request->send(200, "text", "Requisicao de dados em andamento...");
  });

  // Rota para controlar a lampada termica:

  server.on("/ligar-lamp-t", HTTP_GET, [](AsyncWebServerRequest *request){    
   
    Serial.println("Ligando lampada termica...");
    Serial.write('C');
  
    request->send(200, "text/html", htmlContentOn);
  });

  server.on("/desligar-lamp-t", HTTP_GET, [](AsyncWebServerRequest *request){
   
    Serial.println("Desligando lampada termica...");
    Serial.write('D');
    
    request->send(200, "text/html", htmlContentOff);
  });

  // Rota para controlar os fans

  server.on("/ligar-fan", HTTP_GET, [](AsyncWebServerRequest *request){
    
    Serial.println("Ligando fans...");
    Serial.write('A');
    
    request->send(200, "text/html", htmlContentOn);
  });

  server.on("/desligar-fan", HTTP_GET, [](AsyncWebServerRequest *request){
    
    Serial.println("Desliando fans...");
    Serial.write('B');

    request->send(200, "text/html", htmlContentOff);
  });

  // Rota para controlar a lampada UV:

  server.on("/ligar-lamp-uv", HTTP_GET, [](AsyncWebServerRequest *request){    
   
    Serial.println("Ligando lampada uv...");
    Serial.write('E');
  
    request->send(200, "text/html", htmlContentOn);
  });

  server.on("/desligar-lamp-uv", HTTP_GET, [](AsyncWebServerRequest *request){
   
    Serial.println("Desligando lampada uv...");
    Serial.write('F');
    
    request->send(200, "text/html", htmlContentOff);
  });

  // Rota para controlar a bomba de irrigação:
  server.on("/ligar-bomba", HTTP_GET, [](AsyncWebServerRequest *request){    
   
    Serial.println("Ligando lampada uv...");
    Serial.write('G');
  
    request->send(200, "text/html", htmlContentOn);
  });

  server.on("/desligar-bomba", HTTP_GET, [](AsyncWebServerRequest *request){
   
    Serial.println("Desligando lampada uv...");
    Serial.write('H');
    
    request->send(200, "text/html", htmlContentOff);
  });

  // Inicia o servidor
  server.begin();


}

void loop() {

  if(Serial.available()>0){
  	char c = Serial.read();

    if(c=='O'){
    	Serial.println("Resposta da requisicao, status: OK");
    }

  }

}


