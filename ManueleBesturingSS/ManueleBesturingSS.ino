// Initializeren van den pinnen en waarmee ze verbonden zijn
int enable1Pin = 2; // pin 1 on L293D IC
int motor1Pin1 = 3; // pin 2 on L293D IC
int motor1Pin2 = 4; // pin 7 on L293D IC

int enable2Pin = 5; // pin 9 on L293D IC
int motor2Pin1 = 6; // pin 10 on L293D IC
int motor2Pin2 = 7; // pin 15 on L293D IC

int state;         // kiest uit vooruit / achteruit / links / rechts (bluetooth)
int flag=0;        //zorgt ervoor dat de status maar 1x geprint wordt
 
bool Automatic = false;         //Bluetooth inputs
bool Tekenen = false;           //
bool Manueel = true;            //

unsigned long previousMillis = 0;  //Timers voor tekenen
const long interval = 1800;        // draai interval en vooruitrijden
boolean voor = true;               // automatisch rijden
boolean lnks = false;              //
boolean rchts = false;             //
int tellerke = 1;                  //Tellers
int detected = 0;                  //

#define trigPinvooraan 9    //sensor vooraan   //SENSOR PINNEN
#define echoPinvooraan 8    //sensor vooraan

#define trigPinLinks 11 //sensor rechts
#define echoPinLinks 10 //sensor rechts

#define trigPinRechts 13  //sensor links
#define echoPinRechts 12  //sensor links  

void setup() {
    //Motors
    pinMode(motor1Pin1, OUTPUT);
    pinMode(motor1Pin2, OUTPUT);
    pinMode(enable1Pin, OUTPUT);
    pinMode(motor2Pin1, OUTPUT);
    pinMode(motor2Pin2, OUTPUT);
    pinMode(enable2Pin, OUTPUT);
    digitalWrite(enable1Pin, HIGH);
    digitalWrite(enable2Pin, HIGH);
    //Sensors
    pinMode(trigPinvooraan, OUTPUT);
    pinMode(echoPinvooraan, INPUT);

    Serial.begin(9600);
}

void loop() {
  //Timertje
  unsigned long currentMillis = millis();

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////BLUETOOTH//////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Als er data is zal deze uitgelezen worden 
    if(Serial.available() > 0){     
      state = Serial.read();   
      flag=0;
    } 
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////MANUEEL RIJDEN//////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////     
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
   
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////TEKENEN////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//SENSOR code
else if (state == '8') {
  long durationvooraan, distancevooraan;
  digitalWrite(trigPinvooraan, LOW);  // Added this line
  delayMicroseconds(2); // Added this line
  digitalWrite(trigPinvooraan, HIGH);
  delayMicroseconds(10); // Added this line
  digitalWrite(trigPinvooraan, LOW);
  durationvooraan = pulseIn(echoPinvooraan, HIGH);
  distancevooraan = (durationvooraan/2) / 29.1;
 
  //ALS VOORAAN DETECTED///////////////////////////////////////////////////////////
  if (distancevooraan < 10) 
  {
      STOP();
      delay(3000);
      detected++;
      if(detected > 1)
      {
        LINKS();
        delay(1400);
        detected = 0;
        currentMillis = 0;
        previousMillis = 0;
        voor = true; lnks = false;  rchts = false; tellerke = 1;
      }
  }
  //ALS NIKS ERVOOR STAAT///////////////////AUTOMATISCH RIJDEN/////////////////////
  else 
  {
    if(voor)
    VOORUIT();
       if (voor&&(unsigned long)(currentMillis - previousMillis) >= interval) 
       {
          voor = false;
                      if(tellerke == 4){
                      tellerke = 0;
                      }
                      if(tellerke < 2)
                      {
                      lnks = true;}
                      else if(lnks == false&&tellerke <4){
                      rchts = true;
                      }
                      
          previousMillis = currentMillis;
       }
    if(lnks)
    LINKS();
       if (lnks&&(unsigned long)(currentMillis - previousMillis) >= interval-100) 
       {
          lnks= false;
          voor=true;
          tellerke++;
          previousMillis = currentMillis;
       }
     if(rchts)
     RECHTS();
      if (rchts&&(unsigned long)(currentMillis - previousMillis) >= (interval-200)) 
      {
          rchts= false;
          voor=true;
          tellerke++;
          previousMillis = currentMillis;
      }
   }
}
    
    else if(state == '9'){STOP(); }


  
  
}










//Methodes
void LINKS(){
        digitalWrite(motor1Pin1, LOW); 
        digitalWrite(motor1Pin2, LOW); 
        digitalWrite(motor2Pin1, HIGH);
        digitalWrite(motor2Pin2, LOW); 
  }

void RECHTS(){
        digitalWrite(motor1Pin1, LOW); 
        digitalWrite(motor1Pin2, HIGH); 
        digitalWrite(motor2Pin1, LOW);
        digitalWrite(motor2Pin2, LOW);
  }

void ACHTERUIT(){
        digitalWrite(motor1Pin1, HIGH);
        digitalWrite(motor1Pin2, LOW); 
        digitalWrite(motor2Pin1, LOW);
        digitalWrite(motor2Pin2, HIGH);
  }

void VOORUIT(){
        digitalWrite(motor1Pin1, LOW); 
        digitalWrite(motor1Pin2, HIGH);
        digitalWrite(motor2Pin1, HIGH);
        digitalWrite(motor2Pin2, LOW);

  }

void STOP(){
        digitalWrite(motor1Pin1, LOW); 
        digitalWrite(motor1Pin2, LOW); 
        digitalWrite(motor2Pin1, LOW);
        digitalWrite(motor2Pin2, LOW);

  }
void RECHTSRONDAS(){
        digitalWrite(motor1Pin1, LOW); 
        digitalWrite(motor1Pin2, HIGH); 
        digitalWrite(motor2Pin1, LOW);
        digitalWrite(motor2Pin2, HIGH);
  }
void LINKSRONDAS(){
        digitalWrite(motor1Pin1, HIGH); 
        digitalWrite(motor1Pin2, LOW); 
        digitalWrite(motor2Pin1, HIGH);
        digitalWrite(motor2Pin2, LOW);
  }
  
