#include <math.h>
#define pulsePin A1

int av,avg;
float pad =9900;
float thermr = 10000;

// Volatile Variables, used in the interrupt service routine!
volatile int BPM;                   // int that holds raw Analog in 0. updated every 2mS
volatile int Signal;                // holds the incoming raw data
volatile int IBI = 600;             // int that holds the time interval between beats! Must be seeded! 
volatile boolean Pulse = false;     // "True" when User's live heartbeat is detected. "False" when not a "live beat". 
volatile boolean QS = false;        // becomes true when Arduoino finds a beat.

// Regards Serial OutPut  -- Set This Up to your needs
static boolean serialVisual = true;   // Set to 'false' by Default.  Re-set to 'true' to see Arduino Serial Monitor ASCII Visual Pulse 

int ld;

void setup()
{
 //for led assign on every process
 for(ld=4;ld<8;ld++)
  { pinMode(ld,OUTPUT);
  }
  
  Serial.begin(115200);
  pinMode(10, INPUT);  pinMode(11, INPUT); //for ECG 10-> LO+; 11->LO-

delay(1000);
    
interruptSetup();

 
  
}

void loop() {
if(Serial.available()>0)
{
  String command=Serial.readString();
  if(command=="ECG")
   {
     ecg();
     ld=4;
     light(ld);
     delay(2000);
   }
  else if(command=="PULSE")
   {
    int i=0;
    do 
     {
       pulse();
       av=av+BPM;
       i++;
     }while(i<5);
    avg=av/5; 
    Serial.println(avg);
    ld=5;
    light(ld);
    delay(2000);
   }
  else if(command=="TEMP")
   {
     temperature();
     ld=6;
     light(ld);
     delay(2000);
   }
  else if(command=="AIRFLO")
   {
     airflo();
     ld=7;
     light(ld);
     delay(2000);
   }
   else if(command=="Success")
   {
    success();
   }
 }
}
void ecg()
  {
    
   
        if((digitalRead(10) == 1)||(digitalRead(11) == 1)){
       // break;
        Serial.println('!');
          }
          
        else{
     for(int i=0; i<500; i++)
      {      
      Serial.println(analogRead(A0));
      Serial.print(",");
       delay(5);
      }
       
      }
      }


  void airflo()
  {
  for(int i=0; i<300; i++)
    {
      Serial.println(analogRead (A3));
      delay(100);
    }
  }


void temperature() {
float temp=analogRead(A2);
long Resistance;  
float Temp;
Resistance=pad*((1024.0 / temp) - 1);
Temp = log(Resistance);
Temp = 1 / (0.001129148 + (0.000234125 * Temp) + (0.0000000876741 * Temp * Temp * Temp));
Temp = Temp - 273.15;  // Convert Kelvin to Celsius                      
Serial.println(Temp);
}


void pulse()
{
     serialOutput() ;       
    
  if (QS == true){     // A Heartbeat Was Found

        serialOutputWhenBeatHappens();   // A Beat Happened, Output that to serial.     
        QS = false;                      // reset the Quantified Self flag for next time    
  }
     
  delay(20);                             //  take a break
}

void light(int led)
{
digitalWrite(led,HIGH);
delay(2000);
digitalWrite(led,LOW);
delay(1000);
digitalWrite(led,HIGH);
}

void success(){

   for(ld=4;ld<8;ld++)
  { digitalWrite(ld,HIGH);
    delay(800);
   digitalWrite(ld,LOW);
  
  }
}

