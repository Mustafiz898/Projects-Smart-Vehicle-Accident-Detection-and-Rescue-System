int vibr_sensr = 13;
#include<SoftwareSerial.h>
#include <LiquidCrystal.h>
#include <TinyGPS++.h>

LiquidCrystal lcd(12, 11, 2, 3, 4, 5);
SoftwareSerial gpsSerial(10,9); //RX=pin 0, TX=pin 1

TinyGPSPlus gps;                          //This is the GPS object that will pretty much do all the grunt work with the NMEA data
SoftwareSerial mySerial(7,8 );


void setup()
{ Serial.begin(9600);
pinMode(vibr_sensr, INPUT); //set vibr_Pin input for measurment
  
  gpsSerial.begin(9600);
  
  lcd.begin(16, 2);// set up the LCD's number of columns and rows
  
  delay(1000);
  mySerial.begin(9600);   // Setting the baud rate of GSM Module 

}

void loop()
{
  long measurement = Vibration();
  delay(100);

 Serial.println(measurement);  // Serial.print("measurment = ");
if( measurement > 2000){
  
    lcd.setCursor(4,0);
    lcd.print("DANGER!!");
    delay(5000);
    lcd.clear();
  
 
   if (gpsSerial.available() > 0)
    {gps.encode(gpsSerial.read());
    Serial.write(gpsSerial.read());
    } 

      if (gps.location.isUpdated())
      {
       Serial.print("LAT=");  Serial.println(gps.location.lat(), 6);
       Serial.print("LONG="); Serial.println(gps.location.lng(), 6);
      
      }
       
    Serial.print("LATTITUDE="); Serial.println(gps.location.lat(),6);
   Serial.print("LONGITUDE="); Serial.println(gps.location.lng(),6);
  delay(3000);
 
      
      
      lcd.println("Accident Happenen");
      lcd.setCursor(0,1);
      lcd.println("ed at location :");
      
      delay(5000);
      lcd.clear();
      
      
      lcd.print("LAT:");lcd.println (gps.location.lng(),6);
      lcd.setCursor(0,1);
      lcd.print("LONG:");lcd.println (gps.location.lng(),6);
     
      delay(2000);
 

      Serial.println("GSM SIM900A BEGIN"); 
      delay(100);
      char ch='s';
      switch(ch)
      {
        case 's':
        SendMessage();
        break;
      }
       if (mySerial.available()>0){
        Serial.write(mySerial.read());
        exit(0);
     
    }
    
    
    } 
   
    
}

void SendMessage()
{
  float a,b;
  mySerial.println("AT+CMGF=1");    //Sets the GSM Module in Text Mode
  delay(500);  // Delay of 1000 milli seconds or 1 second
  mySerial.println("AT+CMGS=\"+8801703193698\"\r"); // Replace x with mobile number
  delay(200);
  mySerial.println("Accident Happened to Your Car at Location:\n");
  delay(1000);
  mySerial.println("Latitude:");
  mySerial.println(gps.location.lat(), 6);
  delay(100);
  mySerial.println("Longitude:");
  mySerial.println(gps.location.lng(), 6);
  delay(100);
  mySerial.println("http://www.google.com/maps/place/gps.location.lat(),gps.location.lng()");
  delay(100);
  mySerial.println((char)26);// ASCII code of CTRL+Z
  delay(1000);
}
long Vibration(){
  long measurement=pulseIn (vibr_sensr, HIGH);  //wait for the pin to get HIGH and returns measurement
  return measurement;
  
  
}
