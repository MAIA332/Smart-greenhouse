# Projeto estufa:

Biblioteca de scripts de automação e integração, utilizando Arduino ESP32 como comunicador com interface API e um arduino UNO como controlador de componentes. Este repositório tem como objetivo fornecer os scripts dos microcontroladores utilizado no projeto de uma estufa inteligente, para o controle e monitoramento no cultivo de plantas no geral.

No projeto da estufa inteligente, a biblioteca proporciona um conjunto de scripts elaborados para realizar tarefas específicas, como o controle de temperatura, umidade, iluminação e irrigação. A utilização do Arduino ESP32 como comunicador é estratégica, pois permite a integração fácil com outros dispositivos conectados à rede, ampliando as possibilidades de monitoramento remoto e ajuste de parâmetros em tempo real. Essa abordagem contribui significativamente para a eficiência do cultivo de plantas, garantindo condições ideais para o seu crescimento

# Utiliziação:

1. Certifique-se de que o software do Arduino está instalado corretamente, disponível em https://www.arduino.cc/en/software

2. Clone o repositório deste projeto:

```git clone git@github.com:MAIA332/ESP32.git```

3. Conecte o arduino em questão ao computador e selecione dentro do software a board e a porta corretamente

4. Modifique o código de acordo com suas necessidades e preferências

5. Faça o upload do script em seu arduino, certifique-se de fazer o upload do arquivo corresponde ao modelo do arduino trabalhado.

6. Clone o repositório do app de integração:

```git clone git@github.com:MAIA332/IOTAPI.git```

7. Altere o código do app de integração de acordo com suas necessidades e preferências, mais informações em https://github.com/MAIA332/IOTAPI

# Bibliotecas:

Para garantir o funcionamento do software de ambas aas micro controladoras, será necessário instalar algumas dependências, sendo elas:

## Arduino UNO:

### DHT.h

Biblioteca para o sensor de temperatura

```
#include <DHT.h>

```

## ESP32:

### WIFI:

Biblioteca para acionamento da conexão wireless no ESP32

```
#include <WiFi.h>
```

### Async Web Service:

Biblioteca para disponibilização de um "servidor web" dentro do ESP32, trabalhando de maneira assincrona

```
#include <ESPAsyncWebSrv.h>
```

### HTTP:

Biblioteca para comunicação web via protocolo HHTP

```
#include <HTTPClient.h>
```

# Informações a serem alteradas

## Modulo de comunicação (ESP32):

### Informações de conexão wireless:

```
5 const char* ssid = "SSID";
6 const char* password = "PASSWORD";
```

### Porta do serviço web:

```
18 AsyncWebServer server(80);
```

## Modulo de controle (UNO):

### Pinagem:

### Descrição:

**LAMPADA UV**: PORTA 2

**LAMPADA TERMICA**: PORTA 4

**FAN1** (exaustor) : PORTA 13

**FAN2:** (ventilador) PORTA 12

**SENSOR DE UM SOLO**: A0 e 10

**TEMPERATURA**: PORTA 6

**BOMBA**: PORTA 8

### Código: 

```
1 #define pinSensorA A02
2 #define pinSensorD 10
3 #define fan1 12
4 #define fan2 13
5 #define bomba 8
6 #define lampadaT 4
7 #define lampadaUV 2
8 #define DHTPIN  6   

```

## Mapeamento de comandos serial para controle manual:

### Verificação serial arduino UNO

**A**: Ligação dos dois fans

**B**: Desligamento dos dois fans 

**AA**: Ligação do fan frontal

**AB**: Ligação do fan traseiro

**C**: Ligação da lampada termica

**D**: Desligamento da lampada termica

**E**: Ligação da lampada UV

**F**: Desligamento da lampadava UV

**G**: Ligação da bomba de água

**H**: Desligamento da bomba de água

**S**: Comando para checagem de portas e estados

### Verificação serial arduino ESP32

**O**: feedback positivo para requisição do estado das portas

# Estufa montada:

![image](github/estufa.gif)

# Modelagem eletrônica de modulos, individualmente:

## Comunicação serial entre arduinos simulada utilizando TinkerCad:

![image](github/serialcom.png)

_projeto:_ https://www.tinkercad.com/things/icfZtYEGbAL

# Sensor de umidade do solo simulada utilizando TinkerCad:

![image](github/humidty.png)


_projeto:_ https://www.tinkercad.com/things/1rRbdnhr1l9

# Controle de compente com fonte de alimentação externa utilizando um transistor:

![image](github/externalfont.png)

_projeto:_ https://www.tinkercad.com/things/dB4gOPpdXq7
