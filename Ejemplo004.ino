int pot01 = A5;
int pot02 = A2;
int ledVerde = 2;
int ledBlanco = 6;
int entradaDigital;
int entradaAnaloga;
int salidaDigital;
int salidaAnaloga;

void setup() {
  // put your setup code here, to run once:

pinMode(pot01,INPUT);
pinMode(pot02,INPUT);
pinMode(ledVerde,OUTPUT);
pinMode(ledBlanco,OUTPUT);
Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:

  entradaDigital = digitalRead(pot01);
  Serial.println(entradaDigital);
  digitalWrite(ledVerde,entradaDigital);
  
  
  delay(1000);

  
  entradaAnaloga = analogRead(pot02);
  analogWrite(ledBlanco,entradaAnaloga);
  Serial.println(entradaAnaloga);
  
  delay(1000);

  Serial.println("------------------");
  delay(1000);

}
