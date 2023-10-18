// C++ code
//
#define led 7

void setup()
{
  Serial.begin(115200);
  pinMode(led,OUTPUT);
  digitalWrite(led,LOW);

}

void loop()
{
  if(Serial.available()>0){
  	char c = Serial.read();
    if(c=='A'){
    	digitalWrite(led,HIGH);
    }
   if(c=='B'){
    	digitalWrite(led,LOW);
    }
   
  }
 
}