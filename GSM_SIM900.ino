#include <SoftwareSerial.h>

SoftwareSerial myGsm(7,8);
float temp;
int tempPin = 0;

void setup()
{
 myGsm.begin(9600);  
 Serial.begin(9600);  
 delay(500);
}

void loop()
{

myGsm.println("AT+CIPSHUT");
 delay(1000);
 printSerialData();

 myGsm.println("AT+CIPMUX=0");
 delay(1000);
 printSerialData();
 
 myGsm.println("AT+CGATT=1");
 delay(1000);
 printSerialData();
 
  
 myGsm.println("AT+CSTT=\"internet.itelcel.com\",\"webgprs\",\"webgprs2003\"");//setting the APN,2nd parameter empty works for all networks 
 delay(1000);
 printSerialData();
 
 myGsm.println();
 myGsm.println("AT+CIICR");
 delay(1000);
 printSerialData();
 
 myGsm.println("AT+CIFSR"); //init the HTTP request
 delay(1000); 
 printSerialData();
 
 myGsm.println("AT+CIPSTART=\"TCP\",\"201.156.91.13\",\"2900\"");
 delay(1000);
 printSerialData();
 delay(1000);
 
 myGsm.println("AT+CIPSEND");
 delay(1000);
 printSerialData();
 
sendtemp();
delay(1000);
myGsm.println("AT+CIPCLOSE");
printSerialData();

myGsm.println("AT+CIPSHUT");
delay(1000);
printSerialData();
}





void printSerialData()
{
 while(myGsm.available()!=0)
 Serial.write(myGsm.read());
}

void sendtemp()
{
  temp = analogRead(tempPin);
  temp = temp * 0.48828125;
  Serial.print("TEMPERATURE = ");
  Serial.print(temp);
  Serial.print("*C");
  Serial.println();
  delay(1000);
 myGsm.println(temp);
 delay(1000);
 printSerialData();
 myGsm.write(0x1A);
 delay(1000);
   printSerialData();
   
   
}



