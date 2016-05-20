// Initializeren van den pinnen en waarmee ze verbonden zijn
int enable1Pin = 2; // pin 1 on L293D IC
int motor1Pin1 = 3; // pin 2 on L293D IC
int motor1Pin2 = 4; // pin 7 on L293D IC

int enable2Pin = 5; // pin 9 on L293D IC
int motor2Pin1 = 6; // pin 10 on L293D IC
int motor2Pin2 = 7; // pin 15 on L293D IC

int state;      // kiest uit vooruit / achteruit / links / rechts (bluetooth)
int flag=0;        //zorgt ervoor dat de status maar 1x geprint wordt
 
bool Automatic = false;
bool Tekenen = false;
bool Manueel = true;
bool scherpebocht = false;

  boolean start = true;
   boolean  Links = false;
#define trigPin 9    //sensor vooraan   //SENSOR PINNEN
#define echoPin 8    //sensor vooraan

#define trigPinLinks 11 //sensor rechts
#define echoPinLinks 10 //sensor rechts

#define trigPinRechts 13  //sensor links
#define echoPinRechts 12  //sensor links  
unsigned long previousMillis = 0;
const long interval = 1000;
  boolean voor = true;
  boolean lnks = false;
  boolean rchts = false;
  int tellerke = 1;

void setup() {
    pinMode(motor1Pin1, OUTPUT);
    pinMode(motor1Pin2, OUTPUT);
    pinMode(enable1Pin, OUTPUT);
    pinMode(motor2Pin1, OUTPUT);
    pinMode(motor2Pin2, OUTPUT);
    pinMode(enable2Pin, OUTPUT);
    pinMode(trigPin, OUTPUT);
    pinMode(echoPin, INPUT);
    digitalWrite(enable1Pin, HIGH);
    digitalWrite(enable2Pin, HIGH);
    Serial.begin(9600);
}

void loop() {
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////BLUETOOTH//////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
 //Als er data is zal deze uitgelezen worden 
    if(Serial.available() > 0){     
      state = Serial.read();   
      flag=0;
    } 
 
//Mode meegeven
if(state == '6'){ Automatic = true; Tekenen = false; Manueel = false; STOP();}
else if(state == '7'){Manueel = true; Automatic = false; Tekenen = false; STOP(); }
else if(state == '8'){Tekenen = true; Automatic = false; Manueel = false; }
else if(state == '9') {Tekenen = false; STOP(); voor = false; rchts = false; lnks = false; tellerke = 1;}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////AUTOMATICH RIJDEN//////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*
  if(Automatic == true){
   Serial.println("Automatisch aan het rijden");
   
   //Wat als sensor vanvoor iets detecteert
   if (distance < 10) {
   if(distancerechts > distancelinks){RECHTS();}  
   else if(distancelinks > distancerechts){LINKS();}
   else if(distancelinks == distancelinks){RECHTS();}
    
  } else { VOORUIT(); }
  
  //Print status vooraan
  if (distance >= 200 || distance <= 0){
    Serial.println("Out of range");
  }
  else {
    Serial.print(distance);
    Serial.println(" cm");
  }

  //Wat als sensor links iets detecteert
  if (distancelinks < 5) {  
  RECHTSRONDAS();
  }
  
  //Print status links
  if (distancelinks >= 200 || distancelinks <= 0){
    Serial.println("Out of range");
  }
  else {
    Serial.print(distancelinks);
    Serial.println(" cm links");
  }

  //Wat als sensor rechts iets detecteert
  if (distancerechts < 5) {  
    LINKSRONDAS();
  } 
  
  //Print status rechts
  if (distancerechts >= 200 || distancerechts <= 0){
    Serial.println("Out of range");
  }
  else {
    Serial.print(distancerechts);
    Serial.println(" cm rechts");
  }
}

*/

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////TEKENEN////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
if(Tekenen == true){
  unsigned long currentMillis = millis();
    if(voor)
    VOORUIT();
   if (voor&&(unsigned long)(currentMillis - previousMillis) >= interval) {
      voor = false;
      if(tellerke == 4)
      tellerke = 0;
      if(tellerke < 2){
      lnks = true;}
      else if(lnks == false&&tellerke <4){
        rchts = true;
        }
      previousMillis = currentMillis;
   }
   if(lnks)
    LINKS();
  if (lnks&&(unsigned long)(currentMillis - previousMillis) >= interval) {
      lnks= false;
      voor=true;
      tellerke++;
      previousMillis = currentMillis;
  }
  if(rchts)
  RECHTS();
  if (rchts&&(unsigned long)(currentMillis - previousMillis) >= interval) {
      rchts= false;
      voor=true;
      tellerke++;
      previousMillis = currentMillis;
  }
     
}

  
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////MANUEEL RIJDEN//////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//if (Manueel == true) {
    // Als de status 1 is zal het autotje achteruit rijden
    if (state == '1') {
       ACHTERUIT();
    } 
    // Als de status 2 is zal het autotje Rechts draaien
    else if (state == '2') {
       RECHTSRONDAS();
    }
    // Als de status 3 is zal het autotje stoppen. 
    else if (state == '3') {
       STOP();
    }
    // Als de status 2 is zal het autotje links draaien
    else if (state == '4') {
       LINKSRONDAS();
    }
    // Als de status 5 is zal het autotje vooruit rijden
    else if (state == '5') {
       VOORUIT();
    }
  //}
  //Einde van de loop
}


//Methodes
void LINKS(){
        digitalWrite(motor1Pin1, LOW); 
        digitalWrite(motor1Pin2, LOW); 
        digitalWrite(motor2Pin1, HIGH);
        digitalWrite(motor2Pin2, LOW); 
        if(flag == 0){
          Serial.println("Links");
          flag=1;
        }
  }

void RECHTS(){
        digitalWrite(motor1Pin1, LOW); 
        digitalWrite(motor1Pin2, HIGH); 
        digitalWrite(motor2Pin1, LOW);
        digitalWrite(motor2Pin2, LOW);
        if(flag == 0){
          Serial.println("Rechts");
          flag=1;
        }
  }

void ACHTERUIT(){
        digitalWrite(motor1Pin1, HIGH);
        digitalWrite(motor1Pin2, LOW); 
        digitalWrite(motor2Pin1, LOW);
        digitalWrite(motor2Pin2, HIGH);
        if(flag == 0){
          Serial.println("Achteruit!");
          flag=1;
        }
  }

void VOORUIT(){
        digitalWrite(motor1Pin1, LOW); 
        digitalWrite(motor1Pin2, HIGH);
        digitalWrite(motor2Pin1, HIGH);
        digitalWrite(motor2Pin2, LOW);
         if(flag == 0){
          Serial.println("Vooruit!");
          flag=1;
        }
  }

void STOP(){
        digitalWrite(motor1Pin1, LOW); 
        digitalWrite(motor1Pin2, LOW); 
        digitalWrite(motor2Pin1, LOW);
        digitalWrite(motor2Pin2, LOW);
        if(flag == 0){
          Serial.println("STOP!");
          flag=1;
        }
  }
void RECHTSRONDAS(){
        digitalWrite(motor1Pin1, LOW); 
        digitalWrite(motor1Pin2, HIGH); 
        digitalWrite(motor2Pin1, LOW);
        digitalWrite(motor2Pin2, HIGH);
         if(flag == 0){
          Serial.println("Rechts aan het draaien!");
          flag=1;
        }
  }
void LINKSRONDAS(){
        digitalWrite(motor1Pin1, HIGH); 
        digitalWrite(motor1Pin2, LOW); 
        digitalWrite(motor2Pin1, HIGH);
        digitalWrite(motor2Pin2, LOW);
         if(flag == 0){
          Serial.println("Links aan het draaien!");
          flag=1;
        }
  }
  
