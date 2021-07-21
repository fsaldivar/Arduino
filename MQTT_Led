#include <ArduinoMqttClient.h>
#include<WiFiClientSecure.h>
#include<ArduinoJson.h>


char ssid[] = "";
char password[] = "";
int status = WL_IDLE_STATUS;


DynamicJsonDocument doc(200);
String json ="";

WiFiClient wifiClient;
MqttClient mqttClient(wifiClient);

const char broker[] = "test.mosquitto.org";
int        port = 1883;
const char topic[] = "fermax/hola";
const char topic1[] = "fermax/temp";
const char topic2[] = "fermax/hum";
const char topic3[] = "fermax/escribe";


#define LED 2



void setup() {
  // put your setup code here, to run once:

  Serial.begin(9600);
  pinMode(LED,OUTPUT);
  digitalWrite(LED,LOW);

  //while (!Serial){
      //;
    //}

  Serial.print("Conectandome a : ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  printWifiStatus();
  while (WiFi.status() != WL_CONNECTED){
      Serial.print(".");
      delay(500);
    }

  Serial.println("Ya estas conectado a la red WiFi");
  Serial.println();

  Serial.print("Conectandome a este broker MQTT: ");
  Serial.println(broker);
  Serial.print("Conectandome al puerto: ");
  Serial.println(port);

  if (!mqttClient.connect(broker, port)){
      Serial.print("Fallo la conexion MQTT COdigo de error = ");
      Serial.println(mqttClient.connectError());

      while(1);
    }

  Serial.println("Tu estas conectado al broker");
  Serial.println();

  Serial.print("Estas inscrito en el topico: ");
  Serial.println(topic3);
  
  mqttClient.subscribe(topic3);
  Serial.print("Esperando mensajes del topico: ");
  Serial.println(topic3);
  Serial.println();


    
}

void loop() {
  // put your main code here, to run repeatedly:
lectura();



  }

void printWifiStatus(){
  Serial.println(WiFi.SSID());
  }




 void lectura(){
  int messageSize =mqttClient.parseMessage();
  if(messageSize){
    Serial.print("Recibiendo un mensaje ");
    Serial.print(mqttClient.messageTopic());
    Serial.print("', longitud ");
    Serial.print(messageSize);
    Serial.println(" bytes:");

    while (mqttClient.available()) {
      json = mqttClient.readString();
      }
      Serial.println(json);
      Serial.println();

      demoParse();

      Serial.println();
    }
  }

 void demoParse(){
  Serial.println("parse");
  Serial.println("=====");

  DeserializationError error = deserializeJson(doc,json);

  if(error) {
    Serial.print(F("deserializeJsen() failed: "));
    Serial.println(error.c_str());
    return;
   }

  String led = doc["led"];
  Serial.println(led);

  if(led == "ON"){
    digitalWrite(LED,HIGH);
    Serial.println("encendido");
    }

    else{
      digitalWrite(LED,LOW);
      Serial.println("Apagado");
      }

  
  }
