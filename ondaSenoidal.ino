#define pwm1 10
#define pwm2 11
#define pwm3 12
#define pwm4 13
#define iNormal 22
#define iFallaInterna 24
#define iFallaExterna 26

float sine;
int iAT1=0;
int iAT2=0;
int iBT1=0;
int iBT2=0;
int iN;
int iFI;
int iFE;

void setup() {
  // put your setup code here, to run once:
  pinMode(pwm1, OUTPUT);
  pinMode(pwm2, OUTPUT);
  pinMode(pwm3, OUTPUT);
  pinMode(pwm4, OUTPUT);
  pinMode(iNormal, INPUT);
  pinMode(iFallaInterna, INPUT);
  pinMode(iFallaExterna, INPUT);
  Serial.begin(9600);
}


void condicionNormal(){
    iAT1 = 1*int(sine*255.0/2);
    iAT2 = 1*int(sine*255.0/2);
    iBT1 = 5*int(sine*255.0/2);
    iBT2 = 5*int(sine*255.0/2);
   // Serial.print("condicion Normal  ");
}

void condicionFallaInterna(){
    iAT1 = 2*int(sine*255.0/2);
    iAT2 = 2*int(sine*255.0/2);
    iBT1 = 3*int(sine*255.0/2);
    iBT2 = 3*int(sine*255.0/2);
   // Serial.print("condicion Falla Interna  ");
}

void condicionFallaExterna(){
    iAT1 = 1*int(sine*255.0/2);
    iAT2 = 1*int(sine*255.0/2);
    iBT1 = 5*int(sine*255.0/2);
    iBT2 = 5*int(sine*255.0/2);
    //Serial.print("condicion Falla Externa  ");
}

void condicionCero(){
    iAT1 = 0;
    iAT2 = 0;
    iBT1 = 0;
    iBT2 = 0;
    //Serial.print("condicion Falla Externa  ");
}


void loop() {
  // put your main code here, to run repeatedly:
  for (int i=-180;i<180;i+=1){
    sine= sin(i*(3.1416/180.0));
    iN=digitalRead(iNormal);
    iFI=digitalRead(iFallaInterna);
    iFE=digitalRead(iFallaExterna);
    
    if (iN==LOW && iFI == HIGH && iFE == HIGH){
      condicionNormal();
    }
    if (iN==HIGH && iFI == LOW && iFE == HIGH){
      condicionFallaInterna();
    }
    if (iN==HIGH && iFI == HIGH && iFE == LOW){
      condicionFallaExterna();
    }

    if (iN==HIGH && iFI == HIGH && iFE == HIGH){
      condicionCero();
    }
    
    analogWrite(pwm1,iAT1);
    analogWrite(pwm2,iAT2);
    analogWrite(pwm3,iBT1);
    analogWrite(pwm4,iBT2);
    Serial.print(iAT1);
    Serial.print(" ");
    Serial.print(iAT2);
    Serial.print(" ");
    Serial.print(iBT1);
    Serial.print(" ");
    Serial.print(iBT2);
    Serial.println(" ");

    //delay(5);
  }

}
