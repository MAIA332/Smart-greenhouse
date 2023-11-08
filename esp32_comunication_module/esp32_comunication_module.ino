#include <WiFi.h>
#include <ESPAsyncWebSrv.h>
#include <HTTPClient.h>
 
const char* ssid = "Escritorio Mesh";
const char* password = "nm12345678";
const char* htmlContent = "<html><body><h1>Hello!, Esp32</h1><p>Projeto: IOT API para integrações em arduino ESP32</p><p>Documentação:https://github.com/MAIA332/IOTAPI</p>"
                          "</body></html>";

const char* htmlContentOn = "<html><body><h1>ON</h1>"
                          "</body></html>";

const char* htmlContentOff = "<html><body><h1>OFF</h1>"
                          "</body></html>";
                          
AsyncWebServer server(80);
 
void setup() {
  Serial.begin(9600);
 
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

  //Rota para inicialização dos componentes
  server.on("/test", HTTP_POST, [](AsyncWebServerRequest *request){
    String postBody = request->arg("params");
    Serial.println("Rota para inicialização dos componentes");
    Serial.println(postBody);
    request->send(200, "text/plain", postBody);
  });

  server.on("/ligar-lamp-termica", HTTP_GET, [](AsyncWebServerRequest *request){
    Serial.println("Rota para inicialização da lampada termica");
    Serial.write("C");
    request->send(200, "text/plain", "Rota para inicialização da lampada termica");
  });
  
  server.on("/desligar-lamp-termica", HTTP_GET, [](AsyncWebServerRequest *request){
    Serial.println("Rota para desligamento da lampada termica");
    Serial.write("D");
    request->send(200, "text/plain", "Rota para desligamento da lampada termica");
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

