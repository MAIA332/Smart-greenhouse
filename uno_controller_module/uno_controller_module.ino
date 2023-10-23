// C++ code
//
// Definição dos pinos dos componentes conectados
#define pinSensorA A0 // Analogico do sensor de umidade do solo
#define pinSensorD 8 // Digital do sensor de umidade do solo
#define fan 7 // Fan frontal

void setup()
{
  Serial.begin(115200);
  pinMode(pinSensorD, INPUT);
  pinMode(fan,OUTPUT);
  digitalWrite(fan,LOW);

}

void loop()
{
  // Comunicação do sensor de umidade do solo e exibição dos valores variáveis de umidade
  Serial.print("Digital:");
  
  if (digitalRead(pinSensorD)) {
     Serial.print("SEM UMIDADE ");
  } else {
     Serial.print("COM UMIDADE ");
  }

  Serial.print("  Analogico:"); //Exibe os valores flutantes da umidade do solo
  Serial.print(analogRead(pinSensorA)); 
  Serial.print("  ");
  //======================================================================
  // controle do fan de acordo com o sensor de umidade do solo á alterar para a bomba de água
  Serial.print("  Atuador:");
  if (analogRead(pinSensorA) > 700) {
     Serial.println("Desligando modulo...");
     digitalWrite(fan, LOW);
  } else {
    Serial.println("Ligando modulo...");
    digitalWrite(fan, HIGH);
  }
  //======================================================================
  //Detecção dos comandos manuais e informações transmitidas via comunicador (ESP32)


  if(Serial.available()>0){
  	char c = Serial.read();
    if(c=='A'){
    	digitalWrite(fan,HIGH);
    }
   if(c=='B'){
    	digitalWrite(fan,LOW);
    }
   
  }
  //======================================================================
 
}