
#include <Thermocouple.h>
#include <MAX6675_Thermocouple.h>
#include <WiFi.h>
#include <PubSubClient.h>

// Add your MQTT Broker IP address, example:
//const char* mqtt_server = "192.168.1.144";
const char* mqtt_server = "192.168.0.215";




//WiFi 
const char* ssid = "SEE_Lab";
const char* password = "Monitor$2020";

//Port
#define LISTEN_PORT 80

//Create instance of server
WiFiServer server(LISTEN_PORT);


WiFiClient espClient;
PubSubClient client(espClient);
long lastMsg = 0;
char msg[50];
int value = 0;

//Pines del termopar 
#define SCK_PIN 14
#define CS_PIN 32
#define SO_PIN 15
Thermocouple* thermocouple;
//Pin dek rele
const int rele = 33 ;
int statuss = 1;




void setup()
{

  Serial.begin(9600);
  Serial.println("1");
  thermocouple = new MAX6675_Thermocouple(SCK_PIN, CS_PIN, SO_PIN);
  Serial.println("2");


  setup_wifi();  
  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);


 
 
 pinMode(rele,  OUTPUT) ;

}


void setup_wifi() {
  delay(10);
  // We start by connecting to a WiFi network
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}



void callback(char* topic, byte* message, unsigned int length) {
  Serial.print("Message arrived on topic: ");
  Serial.print(topic);
  Serial.print(". Message: ");
  String messageTemp;
  
  for (int i = 0; i < length; i++) {
    Serial.print((char)message[i]);
    messageTemp += (char)message[i];
  }
  Serial.println();

  // Feel free to add more if statements to control more GPIOs with MQTT

  // If a message is received on the topic esp32/output, you check if the message is either "on" or "off". 
  // Changes the output state according to the message
  if (String(topic) == "esp32/output") {
    Serial.print("Changing output to ");
    if(messageTemp == "on"){
      Serial.println("on");
      digitalWrite(rele, HIGH);
    }
    else if(messageTemp == "off"){
      Serial.println("off");
      digitalWrite(rele, LOW);
    }
  }
}

void reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    // Attempt to connect
    if (client.connect("ESP8266Client")) {
      Serial.println("connected");
      // Subscribe
      client.subscribe("esp32/output");
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 min (300,000s");
      // Wait 5 seconds before retrying
      delay(300000);
    }
  }
}




void loop()
{  

if (!client.connected()) {
    reconnect();
  }
  client.loop();

  long now = millis();
  if (now - lastMsg > 5000) {
    lastMsg = now;

  
  // Leer temperatura 
  const double celsius = thermocouple->readCelsius();

    char tempString[8];
    dtostrf(celsius, 1, 2, tempString);
 
  

if( celsius >= 120)
{
   digitalWrite (rele, LOW);
   statuss=0;
}
else
{
  if(celsius >= 118)
  {
    digitalWrite (rele, statuss);
  }
  else
  {
    digitalWrite (rele, HIGH);
    statuss=1;
  }
}
  Serial.print("  Temperatura:  ");  
  Serial.print(celsius);
  Serial.println("ºC");   
  Serial.print("  Estatus del rele:  ");
  if(  statuss == 0){
    Serial.println("Apagado");
    }
    else {
      Serial.println("Prendido");
    }
 
  Serial.println ("---");
  client.publish("esp32/temperature", tempString);
  Serial.println (tempString);




  

 }
}
