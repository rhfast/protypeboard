//inputs
int touchy = 3;
int red = 11;
int white = 12;
int yellow = 13;
//output
int vibModule = 2;
//booleans
bool isOn = 0;      //0 = off, 1 = on, buzzes

//analog
#define A_X = 3
#define A_Y = 4
#define A_Z = 5
float analogX = 0; int analogY = 0; int analogZ = 0;
float volX = 0.0; float volY = 0.0; float volZ = 0.0;  
float g_x = 0.0; float g_y = 0.0;float g_z = 0.0;  

void setup() {
  pinMode(touchy, INPUT);
  pinMode(red, INPUT);
  pinMode(white, INPUT);
  pinMode(yellow, INPUT);
  pinMode(vibModule, OUTPUT);
  pinMode(A3, INPUT);
  pinMode(A4, INPUT);
  pinMode(A5, INPUT);
  Serial.begin(9600);
}

void loop() {
  onOff();
  readMeter();
  //buzzModule();
  //stopBuzzing();
  getGValues();
  printGValues();
}

void buzzModule() {
  if (digitalRead(white) == HIGH) {
    digitalWrite(vibModule, HIGH);
    delay(2000);
    digitalWrite(vibModule, LOW);
    //Serial.println("Short buzz");
  }
  else if (digitalRead(yellow) == HIGH) {
    digitalWrite(vibModule, HIGH);
    //Serial.println("keep buzzing");
  }
}
void stopBuzzing() {
  if (digitalRead(red) == HIGH) {
    digitalWrite(vibModule, LOW);
    //Serial.println("Stop buzzing");
  }
}
void onOff() {
  if (digitalRead(touchy) == HIGH) {    
    delay(100);
    isOn = !isOn;                        
    digitalWrite(vibModule, isOn);        
    Serial.println("Switch");
  }
  delay(50);
}
void readMeter() {
  analogX = analogRead(A3); 
  analogY = analogRead(A4);
  analogZ = analogRead(A5);

  //float voltage= sensorValue * (5.0 / 1024.0)
  volX = analogX * (5.0 / 1024.0);
  volY = analogY * (5.0 / 1024.0);
  volZ = analogZ * (5.0 / 1024.0);
}
void getGValues(){
  /*this is made for static acceleration, using side view numbers from technical drawing provided by DFRobot
   g = volts * (g/volts)
   dividing by 1.5 g results in something unitless, but seems to fit with the physics
  was previously 1.65, 1.65, 2.45 as ambient values that were subtracted out*/
  g_x = (volX - 1.67) / 1.5 / 0.8;
  g_y = (volY - 1.78) / 1.5/ 0.8;
  g_z = (volZ - 2.19) / 1.5 / 0.8;
   
  /*Serial.print("X: ");  Serial.print(g_x); Serial.print("\t");
  Serial.print("Y: ");  Serial.print(g_y); Serial.print("\t");
  Serial.print("Z: ");  Serial.println(g_z);*/
  
}
void printGValues() {
  //original version
   /*Serial.print("X: ");  Serial.print(g_x); Serial.print("\t");
  Serial.print("Y: ");  Serial.print(g_y); Serial.print("\t");
  Serial.print("Z: ");  Serial.println(g_z);*/
  //version for excel datastreamer
  Serial.print(g_x);
  Serial.print(",");
  Serial.print(g_y);
  Serial.print(",");
  Serial.print(g_z);
  Serial.print(",");Serial.println();
}
