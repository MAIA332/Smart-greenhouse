#include <WiFi.h>
#include <ESPAsyncWebSrv.h>
#include <HTTPClient.h>
 
const char* ssid = "N Multifibra Turbo";
const char* password = "nm12345678";
const char* htmlContent = "<html><body><h1>Hello, ESP32!</h1>"
                          "<form action='/execute' method='post'>"
                          "<input type='submit' value='Execute Action'>"
                          "</form></body></html>";

const char* htmlContentOn = "<html><body><h1>ON</h1>"
                          "</body></html>";

const char* htmlContentOff = "<html><body><h1>OFF</h1>"
                          "</body></html>";

int LED = 25;

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
  server.on("/execute", HTTP_POST, [](AsyncWebServerRequest *request){
    digitalWrite(LED,HIGH);
    
    if(digitalRead(LED) == HIGH){
      Serial.println("Ligado");
    }
    request->send(200, "text/html", htmlContentOn);
  });

  server.on("/off", HTTP_GET, [](AsyncWebServerRequest *request){
    digitalWrite(LED,LOW);

    if(digitalRead(LED) == LOW){
      Serial.println("Desligou!");
    }
    request->send(200, "text/html", htmlContentOff);
  });

  // Inicia o servidor
  server.begin();

  pinMode(LED,OUTPUT);

}

void loop() {
  /* WiFiClient client = server.available();
  if (client) {
    Serial.println("Novo Cliente.");
    Serial.println("Cliente aqui");
    } */
   /*  client.stop();
    Serial.println("Client Disconnected."); */
}


