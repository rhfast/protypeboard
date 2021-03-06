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
//raw values from analog channels
float analogX = 0; int analogY = 0; int analogZ = 0;
//voltages
float volX = 0.0; float volY = 0.0; float volZ = 0.0;
//g's
float g_x = 0.0; float g_y = 0.0;float g_z = 0.0; 

//averages used for calibrating while no buzz
float avgX = 0; float avgY; float avgZ;

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
  if (digitalRead(white) == HIGH){
    calibrate();
  }
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

  //adjust voltages down by 11%
  volX = volX - (.11*volX);
  volY = volY - (.11*volY);
  volZ = volZ - (.11*volZ);
}
void getGValues(){
  /*this is made for static acceleration, using side view numbers from technical drawing provided by DFRobot
   g = volts * (g/volts)
   dividing by 1.5 g results in something unitless, but seems to fit with the physics
  was previously 1.65, 1.65, 2.45 as ambient values that were subtracted out*/
  g_x = (volX - avgX) / 1.5 / 0.8;
  g_y = (volY - avgY) / 1.5/ 0.8;
  g_z = (volZ - avgZ) / 1.5 / 0.8;
   
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

void calibrate(){
  float sumX = 0;
  float sumY = 0;
  float sumZ = 0;
  for (int i = 0; i < 1000; i++){
    readMeter();
    sumX = sumX + volX;
    sumY = sumY + volY;
    sumZ = sumZ + volZ;
  }
  avgX = sumX / 1000;
  avgY = sumY / 1000;
  avgZ = sumZ / 1000;
}
