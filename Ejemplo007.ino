int ledVerde1 = 5;
int ledVerde2 = 6;
int pot01 = A5;
int entrada;

void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);
pinMode(ledVerde1,OUTPUT);
pinMode(ledVerde2,OUTPUT);

}

void loop() {
  // put your main code here, to run repeatedly:

entrada = analogRead(pot01);
analogWrite(ledVerde1,entrada);
analogWrite(ledVerde2,entrada/4);
Serial.println(entrada);
Serial.println(entrada/4);
Serial.println();
delay(1000);


}
