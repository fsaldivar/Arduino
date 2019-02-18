
 
 #define outputA 7
 #define outputB 8
 int counter = 0; 
 int counter2 = 0;
 int aState;
 int bState;
 int aLastState;  
 int led=11;
 
 void setup() { 
   pinMode (outputA,INPUT);
   pinMode (outputB,INPUT);
   pinMode(led,OUTPUT);
   
   Serial.begin (9600);
   // Reads the initial state of the outputA
   aLastState = digitalRead(outputA);   
 } 
 void loop() { 
   aState = digitalRead(outputA); // Reads the "current" state of the outputA
   bState = digitalRead(outputB);
   //Serial.print("State A: ");
   //Serial.println(aState);
   //Serial.print("State B: ");
   //Serial.println(bState);
   //Serial.print("Ultimo Estado: ");
   //Serial.println(aLastState);
   
   //Serial.println("---------------");
   //delay(100);
   // If the previous and the current state of the outputA are different, that means a Pulse has occured
   if (aState != aLastState){     
     // If the outputB state is different to the outputA state, that means the encoder is rotating clockwise

     if (digitalRead(outputB) != aState) { 
       counter ++;
     } else {
       counter --;
     }
   Serial.print("State A: ");
   Serial.println(aState);
   if (counter < 0){counter2=0;} else if (counter > 255){counter2=255;} else {counter2=counter;}
    
   analogWrite(led,counter2);
   
   Serial.print("State B: ");
   Serial.println(bState);
   Serial.print("Ultimo Estado: ");
   Serial.println(aLastState);
  
   
     Serial.print("Position: ");
     Serial.println(counter);
     Serial.print("Intensidad Led: ");
     Serial.println(counter2);
  
   Serial.println("---------------");
   
   } 
   aLastState = aState; // Updates the previous state of the outputA with the current state
 }
