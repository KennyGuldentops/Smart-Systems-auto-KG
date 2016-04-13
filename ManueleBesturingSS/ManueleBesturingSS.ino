
// Initializeren van den pinnen en waarmee ze verbonden zijn
int motor1Pin1 = 3; // pin 2 on L293D IC
int motor1Pin2 = 4; // pin 7 on L293D IC
int enable1Pin = 6; // pin 1 on L293D IC
int motor2Pin1 = 8; // pin 10 on L293D IC
int motor2Pin2 = 9; // pin 15 on L293D IC
int enable2Pin = 11; // pin 9 on L293D IC

#define trigPin 2
#define echoPin 5                                              

int state;			// kiest uit vooruit / achteruit / links / rechts
int flag=0;        //zorgt ervoor dat de status maar 1x geprint wordt
int stateStop=0;	//staat samen met een delay zodat na een LINKS input hij niet blijft doordraaien
void setup() {
    // zet alle pinnen als output
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
    // initialize serial communication at 9600 bits per second:
    Serial.begin(9600);
}

void loop() {
  //Sesnor
long duration, distance;
  digitalWrite(trigPin, LOW);  // Added this line
  delayMicroseconds(2); // Added this line
  digitalWrite(trigPin, HIGH);
//  delayMicroseconds(1000); - Removed this line
  delayMicroseconds(10); // Added this line
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = (duration/2) / 29.1;
  if (distance < 10) {  
 STOP();
}

  if (distance >= 200 || distance <= 0){
    Serial.println("Out of range");
  }
  else {
    Serial.print(distance);
    Serial.println(" cm");
  }
  delay(500);
// 

    

    //Als er data is zal deze uitgelezen worden 
    if(Serial.available() > 0){     
      state = Serial.read();   
      flag=0;
    }   
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
        RECHTS();
        if(flag == 0){
          Serial.println("Go Forward!");
          flag=1;
        }
    }
    
    // Als de status 3 is zal het autotje stoppen. Of als stateStop 1 is wat gebeurt na de 1.5 seconde bij een bocht
    else if (state == '3' || stateStop == 1) {
        STOP();
        if(flag == 0){
          Serial.println("STOP!");
          flag=1;
        }
        stateStop=0;
    }
    // Als de status 2 is zal het autotje links draaien
    else if (state == '4') {
        LINKS();
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
    Serial.println(state);  //voor debugging
}

//Methodes

void LINKS(){
        digitalWrite(motor1Pin1, HIGH); 
        digitalWrite(motor1Pin2, LOW); 
        digitalWrite(motor2Pin1, LOW);
        digitalWrite(motor2Pin2, LOW);
  }

void RECHTS(){
        digitalWrite(motor1Pin1, LOW); 
        digitalWrite(motor1Pin2, LOW); 
        digitalWrite(motor2Pin1, LOW);
        digitalWrite(motor2Pin2, HIGH);
  }

void VOORUIT(){
        digitalWrite(motor1Pin1, HIGH);
        digitalWrite(motor1Pin2, LOW); 
        digitalWrite(motor2Pin1, LOW);
        digitalWrite(motor2Pin2, HIGH);
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

  
