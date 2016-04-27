
// Initializeren van den pinnen en waarmee ze verbonden zijn
int motor1Pin1 = 3; // pin 2 on L293D IC
int motor1Pin2 = 4; // pin 7 on L293D IC
int enable1Pin = 6; // pin 1 on L293D IC
int motor2Pin1 = 8; // pin 10 on L293D IC
int motor2Pin2 = 9; // pin 15 on L293D IC
int enable2Pin = 11; // pin 9 on L293D IC
int state;      // kiest uit vooruit / achteruit / links / rechts (bluetooth)
int flag=0;        //zorgt ervoor dat de status maar 1x geprint wordt

bool Automatic = false;
bool Tekenen = false;
bool Manueel = true;
bool scherpebocht = false;

#define trigPin 2       //SENSOR PINNEN
#define echoPin 5
#define trigPinLinks 7
#define echoPinLinks 10 
#define trigPinRechts 13
#define echoPinRechts 12    //////                                           


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
 

if(state == '6'){ Automatic = true; Tekenen = false; Manueel = false;}
else if(state == '7'){Manueel = true; Automatic = false; Tekenen = false; }
else if(state == '8'){Tekenen = true; Automatic = false; Manueel = false; }



///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////AUTOMATICH RIJDEN//////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


if(Automatic == true){
   Serial.println("AUTOMATISCH");

/////////////////////////////////////////////Sensor LINKSVOOR/////////////////////////////////////
long durationlinks, distancelinks;
  digitalWrite(trigPinLinks, LOW); 
  delayMicroseconds(2); 
  digitalWrite(trigPinLinks, HIGH);
  delayMicroseconds(10); 
  digitalWrite(trigPinLinks, LOW);
  durationlinks = pulseIn(echoPinLinks, HIGH);
  distancelinks = (durationlinks/2) / 29.1;
                                                if (distancelinks < 5) {  
                                                  RECHTSRONDAS();
                                                }
  ///////////// SERIAL PRINT //////////////////
  if (distancelinks >= 200 || distancelinks <= 0){
    Serial.println("Out of range");
  }
  else {
    Serial.print(distancelinks);
    Serial.println(" cm links");
  }
  delay(500);
  /////////////////////////////////////////////Sensor RECHTSSVOOR//////////////////////////////
long durationrechts, distancerechts;
  digitalWrite(trigPinRechts, LOW); 
  delayMicroseconds(2);
  digitalWrite(trigPinRechts, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPinRechts, LOW);
  durationrechts = pulseIn(echoPinRechts, HIGH);
  distancerechts = (durationrechts/2) / 29.1;
                                                  if (distancerechts < 5) {  
                                                       LINKSRONDAS();
                                                  } 
  ///////////// SERIAL PRINT //////////////////
  if (distancerechts >= 200 || distancerechts <= 0){
    Serial.println("Out of range");
  }
  else {
    Serial.print(distancerechts);
    Serial.println(" cm rechts");
  }
  delay(500);
    //////////////////////////////////////////////Sesnor VOORAAN///////////////////////////////
long duration, distance;
  digitalWrite(trigPin, LOW); 
  delayMicroseconds(2); 
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10); 
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = (duration/2) / 29.1;
  if (distance < 10) {
   if(distancerechts > distancelinks){RECHTS();}  
   else if(distancelinks > distancerechts){LINKS();}
   else if(distancelinks == distancelinks){RECHTS();}
    
  }else{
  VOORUIT();
  }

   ///////////// SERIAL PRINT //////////////////
  if (distance >= 200 || distance <= 0){
    Serial.println("Out of range");
  }
  else {
    Serial.print(distance);
    Serial.println(" cm");
  }
  delay(500);
}



///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////TEKENEN////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

if(Tekenen == true){
  Serial.println("Tekenen");

/////////////////////////////////////////////Sensor RECHTS ACHTERAAN /////////////////////////////////////
long durationRA, distanceRA;
long durationRV, distanceRV;
  digitalWrite(trigPinLinks, LOW);  // Added this line
  delayMicroseconds(2); // Added this line
  digitalWrite(trigPinLinks, HIGH);
//  delayMicroseconds(1000); - Removed this line
  delayMicroseconds(10); // Added this line
  digitalWrite(trigPinLinks, LOW);
  durationRA = pulseIn(echoPinLinks, HIGH);
  distanceRA = (durationRA/2) / 29.1;
  if (distanceRA < distanceRV) {  
 RECHTSRONDAS();
}
  if (distanceRA >= 200 || distanceRA <= 0){
    Serial.println("Out of range");
  }
  else {
    Serial.print(distanceRA);
    Serial.println(" cm RA");
  }
  delay(500);
  /////////////////////////////////////////////Sensor RECHTS VOORAAN //////////////////////////////


  digitalWrite(trigPinRechts, LOW);  // Added this line
  delayMicroseconds(2); // Added this line
  digitalWrite(trigPinRechts, HIGH);
//  delayMicroseconds(1000); - Removed this line
  delayMicroseconds(10); // Added this line
  digitalWrite(trigPinRechts, LOW);
  durationRV = pulseIn(echoPinRechts, HIGH);
  distanceRV = (durationRV/2) / 29.1;
  if (distanceRV < distanceRA) {  
 LINKSRONDAS();
}
  if (distanceRV >= 200 || distanceRV <= 0){
    Serial.println("Out of range");
  }
  else {
    Serial.print(distanceRV);
    Serial.println(" cm RV");
  }
  delay(500);

  //////////////////////////////////////////////Sesnor VOORAAN VOOR TEKENEN///////////////////////////////
long duration, distance;
  digitalWrite(trigPin, LOW);  // Added this line
  delayMicroseconds(2); // Added this line
  digitalWrite(trigPin, HIGH);
//  delayMicroseconds(1000); - Removed this line
  delayMicroseconds(10); // Added this line
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = (duration/2) / 29.1;
  if (distanceRA == distanceRV) {
   VOORUIT();
 
}
  if (distance >= 200 || distance <= 0){
    Serial.println("Out of range");
  }
  else {
    Serial.print(distance);
    Serial.println(" cm");
  }
  delay(500);
}




///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////MANUEEL RIJDEN//////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



if(Manueel == true){
   Serial.println("Manueel");

    // Als de status 1 is zal het autotje vooruit rijden
    if (state == '1') {
       VOORUIT();
        if(flag == 0){
          Serial.println("Go Forward!");
          flag=1;
        }
    }
    
    // Als de status 2 is zal het autotje Rechts draaien
    else if (state == '2') {
        RECHTSRONDAS();
        if(flag == 0){
          Serial.println("Go Forward!");
          flag=1;
        }
    }
    
    // Als de status 3 is zal het autotje stoppen. 
    else if (state == '3') {
        STOP();
        if(flag == 0){
          Serial.println("STOP!");
          flag=1;
        }
        
    }
    // Als de status 2 is zal het autotje links draaien
    else if (state == '4') {
        LINKSRONDAS();
        if(flag == 0){
          Serial.println("Go Forward!");
          flag=1;
        }
    }
    // Als de status 1 is zal het autotje achteruit rijden
    else if (state == '5') {
        ACHTERUIT();
        if(flag == 0){
          Serial.println("Reverse!");
          flag=1;
        }
    }
 
}
}

//Methodes

void LINKS(){
        digitalWrite(motor1Pin1, HIGH); 
        digitalWrite(motor1Pin2, LOW); 
        digitalWrite(motor2Pin1, LOW);
        digitalWrite(motor2Pin2, LOW);
        if(Tekenen == true ){
          delay(975);
        }
  }

void RECHTS(){
        digitalWrite(motor1Pin1, LOW); 
        digitalWrite(motor1Pin2, LOW); 
        digitalWrite(motor2Pin1, LOW);
        digitalWrite(motor2Pin2, HIGH);
        if(Tekenen == true ){
          delay(975);
        }
  }

void VOORUIT(){
        digitalWrite(motor1Pin1, HIGH);
        digitalWrite(motor1Pin2, LOW); 
        digitalWrite(motor2Pin1, LOW);
        digitalWrite(motor2Pin2, HIGH);
        if(Tekenen == true ){
          delay(2500);
          RECHTS();
        }
  }

void ACHTERUIT(){
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

  
