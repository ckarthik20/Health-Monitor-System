
#include <ESP8266WiFi.h>
const char* ssid     = "";
const char* password = "";
const char* host = "";
const int httpPort = 80;
String PostData="";
String PostData1="";
boolean capture=false;
int ledState = LOW;  
int counter = 0;
String ECG="";
String PULSE1="";
String TEMP="";
String AIRFLO="";
WiFiClient client;
uint32_t id=ESP.getChipId();
void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
  Serial.begin(115200);
  delay(10);

  // We start by connecting to a WiFi network

  WiFi.begin(ssid, password);
  
  while (WiFi.status() != WL_CONNECTED) {
      digitalWrite(LED_BUILTIN, LOW);   
      delay(500);                      
      digitalWrite(LED_BUILTIN, HIGH); 
      delay(500);   
  }              
  digitalWrite(LED_BUILTIN, HIGH);  
}

int value = 0;

void loop() {
  delay(5000);
  ++value;
  // Use WiFiClient class to create TCP connections
  if (!client.connect(host, httpPort)) {
    digitalWrite(LED_BUILTIN, LOW);   
      delay(1000);                      
      digitalWrite(LED_BUILTIN, HIGH); 
      delay(1000);  
    return;
   }
  if(counter==0)
   {
    Serial.print("ECG");
    do
    {
    for(int i=0; i<1; i++)
      {      
      ECG =Serial.readString();
      Serial.print(ECG);
      delay(5);
      }
     counter=1;
   }while(Serial.available()>0);
   }
   else if(counter==1)
    {
        Serial.print("PULSE");
    do
    {
    for(int j=0; j<1; j++)
      {      
      PULSE1 =Serial.readString();
      Serial.print(PULSE1);
      delay(2000);
      }
     counter=2;
   }while(Serial.available()>0);
   }
   else if(counter==2)
    {
        Serial.print("TEMP");
    do
    {
    for(int k=0; k<1; k++)
      {      
      TEMP =Serial.readString();
      Serial.print(TEMP);
      delay(5);
      }
     counter=3;
   }while(Serial.available()>0);
    }
   else if(counter==3)
    {
        Serial.print("AIRFLO");
    do
    {
    for(int l=0; l<1; l++)
      {      
      AIRFLO =Serial.readString();
      Serial.print(AIRFLO);
      delay(5);
      }
     counter=4;
   }while(Serial.available()>0);
    }
   else if(counter==4)
    {
        Serial.print("Success");
        delay(500);
           PostData = "ECG=" + ECG + "&PULSE=" + PULSE1 + "&TEMP=" + TEMP  + "&DEVICE=" + id;
  PostData1 = "AIRFLO=" + AIRFLO + "&DEVICE=" + id;
        delay(800);
     post();
     post1();
     counter=5;
    }
   
} 
void post()
{
  if (client.connect(host,80)) {
client.println("POST /secure/esp.php HTTP/1.1");
client.println("Host: 192.168.1.102");
client.println("Cache-Control: no-cache");
client.println("Content-Type: application/x-www-form-urlencoded");
client.println("Connection: close");
client.print("Content-Length: ");
client.println(PostData.length());
client.println();
client.println(PostData);
client.println();

long interval = 2000;
unsigned long currentMillis = millis(), previousMillis = millis();

while(!client.available()){

  if( (currentMillis - previousMillis) > interval ){
         digitalWrite(LED_BUILTIN, LOW);   
      delay(1000);                      
      digitalWrite(LED_BUILTIN, HIGH); 
      delay(1000);  
   // Serial.println("Timeout");
    client.stop();     
    return;
  }
  currentMillis = millis();
}

while (client.connected())
 {
  if ( client.available() )
  {
    char str=client.read();
   //Serial.println(str);
  }      
 }
   }
    }
void post1()
{
  if (client.connect(host,80)) {
client.println("POST /secure/airflow.php HTTP/1.1");
client.println("Host: 192.168.1.102");
client.println("Cache-Control: no-cache");
client.println("Content-Type: application/x-www-form-urlencoded");
client.println("Connection: close");
client.print("Content-Length: ");
client.println(PostData1.length());
client.println();
client.println(PostData1);
client.println();

long interval = 2000;
unsigned long currentMillis = millis(), previousMillis = millis();

while(!client.available()){

  if( (currentMillis - previousMillis) > interval ){
         digitalWrite(LED_BUILTIN, LOW);   
      delay(1000);                      
      digitalWrite(LED_BUILTIN, HIGH); 
      delay(1000);  
   // Serial.println("Timeout");
    client.stop();     
    return;
  }
  currentMillis = millis();
}

while (client.connected())
 {
  if ( client.available() )
  {
    char str=client.read();
   //Serial.println(str);
  }      
 }
   }
    }



