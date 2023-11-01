#define pinSensorA A0
#define pinSensorD 10
#define fan1 12
#define fan2 13
#define bomba 8
#define lampadaT 4
#define lampadaUV 2
#include <DHT.h>
#define DHTPIN  6 
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

void setup()
{
  // ===============================
  pinMode(pinSensorD, INPUT);
  pinMode(fan1,OUTPUT);
  pinMode(fan2,OUTPUT);
  pinMode(bomba,OUTPUT);
  pinMode(lampadaT,OUTPUT);
  pinMode(lampadaUV,OUTPUT);
  //================================
  Serial.begin(9600);
  dht.begin();
  //================================
  digitalWrite(fan1,LOW);
  digitalWrite(fan2,LOW);
  digitalWrite(bomba,LOW);
  digitalWrite(lampadaT,LOW);
  digitalWrite(lampadaUV,LOW);

}

void loop()
{
  delay(1000);  //aguarda por 1s para a próxima leitura de temperatura.
  
  // Defina as variáveis de umidade e temperatura
  float humidity = dht.readHumidity();
  float temperature = dht.readTemperature();

  // Exibe os dados dígitais da umidade do solo
  Serial.print("Digital:");
  
  if (digitalRead(pinSensorD)) {
     Serial.print("SEM UMIDADE ");
  } else {
     Serial.print("COM UMIDADE ");
  }

  // Exibe os dados analógicos da umidade do solo
  Serial.print("  Analogico:");
  Serial.print(analogRead(pinSensorA)); 
  Serial.print("  ");
  //======================================================================
  // controle dos componentes de acordo com os sensores
  if (isnan(humidity) || isnan(temperature)) { // Verificação em cima da temperatura
    Serial.println("Failed to read from DHT sensor!");
  } else {
    if(temperature >= 25.00){ 
      Serial.println("Temperatura acima de 25°C, desligando sistema termico...."); // Verifica se a temperatura está acimad e 25 graus, desliga a lampada termica e liga os fans caso estejas desligados
      digitalWrite(lampadaT,LOW);
      digitalWrite(fan1,HIGH);
      digitalWrite(fan2,HIGH);
    }
    else if(temperature <= 19.00){
      Serial.println("Temperatura a baixo de 19°C religando sistema de aquecimenti...");
      digitalWrite(lampadaT,HIGH);
      digitalWrite(fan1,LOW);
      digitalWrite(fan2,LOW);
    }

    // Exibe os valores de umidade e temperatura
    Serial.print("Humidity: ");
    Serial.print(humidity);
    Serial.print("%\t");
    Serial.print("Temperature: ");
    Serial.print(temperature);
    Serial.println("°C");
  }

  //==============================================

  Serial.print("  Atuador:"); // Verificação em cima dos dados anlógicos do sensor de temperatura
  if (analogRead(pinSensorA) > 700) {
    
    Serial.println("Umidade abaixo do nível mínimo"); // Desliga os dois fans, desliga a lampada termica se estiver ligada e irriga com a bomba
    digitalWrite(fan1,LOW);
    digitalWrite(fan2,LOW);
    digitalWrite(bomba,HIGH); 
    digitalWrite(lampadaT,LOW);
     
  } else {
    Serial.println("Umidade acima do nível mínimo"); // Desliga a irrigação caso esteja ligada e religa os fans caso estejam desligados
      
    digitalWrite(fan1,HIGH);
    digitalWrite(fan2,HIGH);
    digitalWrite(bomba,LOW);
  }
  //======================================================================
  //Detecção dos comandos manuais e informações transmitidas via comunicador (ESP32)


  if(Serial.available()>0){
  	char c = Serial.read();
    if(c=='A'){
    	digitalWrite(fan1,HIGH);
      digitalWrite(fan2,HIGH);
    }
    else if(c=='B'){
    	digitalWrite(fan1,LOW);
    	digitalWrite(fan2,LOW);
    }
    else if(c=="AA"){
      digitalWrite(fan1,HIGH);
    }
    else if(c=="AB"){
      digitalWrite(fan2,HIGH);
    }
    else if(c=="C"){
      digitalWrite(lampadaT,HIGH);
    }
    else if(c=="D"){
      digitalWrite(lampadaT,LOW);
    }
    else if(c=="E"){
      digitalWrite(lampadaUV,HIGH);
    }

    else if(c=="F"){
      digitalWrite(lampadaUV,LOW);
    }
    else if(c=="G"){
      digitalWrite(bomba,HIGH);
    }
    else if(c=="H"){
      digitalWrite(bomba,LOW);
    }
    else if(c=="S"){
      //digitalWrite(bomba,LOW);
    }
   
  }
  //======================================================================
 
}