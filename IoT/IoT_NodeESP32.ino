//2019 Curso IoT de Platzi

//Lib
#include <WiFi.h>
#include <aREST.h>
#include <DHT.h>
#include <DHT_U.h>
#include <Adafruit_Sensor.h>

//Def
#define DHTPIN 15
#define DHTTYPE DHT11
#define MQ A0

//Init
DHT dht(DHTPIN, DHTTYPE);

//aREST
aREST rest = aREST();

//WiFi 
const char* ssid = "AXTEL XTREMO-EF67";
const char* password = "036AEF67";

//Port
#define LISTEN_PORT 80

//Create instance of server
WiFiServer server(LISTEN_PORT);

//Variables API
float mq, humidity, temperature;

void setup(){
  Serial.begin(9600);
  dht.begin();
  pinMode(DHTPIN,INPUT);  
//Init Variables API
  rest.variable("temperature",&temperature);
  rest.variable("humidity",&humidity);
  //rest.variable("contaminacion",&mq);

//Name ID
  rest.set_id("0");
  rest.set_name("sensor_esp32_node");

//Connect to WiFi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
    }
  Serial.println("");
  Serial.println("WiFi connected!");

//Start Server
  server.begin();
  Serial.println("Server started!");

//IP
  Serial.println(WiFi.localIP());
}

void loop() {
  //Wait 1s
  delay(1000);
 // mq = analogRead(MQ); //MQ135
  humidity = dht.readHumidity(); //RH %0 - 100 (Punto rocio)
  temperature = dht.readTemperature(); //0 - 100 *C
  Serial.println(temperature);
  Serial.println(humidity);

  //REST Calls
  WiFiClient client = server.available();
  if (!client) {
    return;
    }
  while(!client.available()){
    delay(1);
    }
  rest.handle(client);  
}
