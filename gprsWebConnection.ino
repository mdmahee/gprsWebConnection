#include <SoftwareSerial.h>

SoftwareSerial SIM900(11, 10); // configure software serial port
int REDLed= A2;
int GREENLed= A3;
int BLUELed= 13;

 String content = "";
 
 
int id=7;

void setup() {     
  
  pinMode(REDLed, OUTPUT);
  pinMode(GREENLed, OUTPUT);
  pinMode(GREENLed, OUTPUT);
  SIM900.begin(19200);
  Serial.begin(19200); 
  Serial.print("power up" );
  delay(3000); 

}


 
void loop()
{

  Serial.println("SubmitHttpRequest - started" );
  SubmitHttpRequest();
  Serial.println("SubmitHttpRequest - finished" );
  delay(10000);

}

void SubmitHttpRequest()
{
 
  SIM900.println("AT+CSQ"); // Signal quality check

  delay(100);
 
  ShowSerialData();// this code is to show the data from gprs shield, in order to easily see the 
  //process of how the gprs shield submit a http request, and the following is for this purpose too.
  
  SIM900.println("AT+CGATT?"); //Attach or Detach from GPRS Support
  delay(100);
 
  ShowSerialData();
  SIM900.println("AT+SAPBR=3,1,\"CONTYPE\",\"GPRS\"");//setting the SAPBR, the connection type is using gprs
  delay(1000);
 
  ShowSerialData();


  SIM900.println("AT+SAPBR=3,1,\"APN\",\"airtelgprs.com\"");//setting the APN, Access point name string
  delay(4000);
 
  ShowSerialData();
 
  SIM900.println("AT+SAPBR=1,1");//setting the SAPBR
  delay(2000);
 
  ShowSerialData();
 
  SIM900.println("AT+HTTPINIT"); //init the HTTP request
 
  delay(2000); 
  ShowSerialData();


/*
unsigned long srno=100029;
String api= "0ffuMENHZi9lE0jkMheI4k21ndpzbY4vXUMy4LsFGzQR3Hrdf62tEq0tzg3I";

//http://59.152.101.138:9000/api/bin/
String addr =  "AT+HTTPPARA=\"URL\",\"https://robi.eduine.com/api/bin/";
//String addr =  "AT+HTTPPARA=\"URL\",\"https://smartbin.ashfaqhahmed.com/api/bin/";
addr+=srno;
addr+="?api_token=";
addr+=api;
addr+="&isConnected=";
addr+=conn;
addr+="&filledPercentage=";
addr+=pp;
addr+="&wastageType=";
addr+=wtt;
addr+= "\"";
delay(1000);


mySerial.println(addr);
Serial.println(addr);
 delay(1000);
*/



// https://thectbl.com/gsm/getstate.php?color=All
 // SIM900.println("AT+HTTPPARA=\"URL\",\"sim900test.net46.net/getstate.php?color=All\"");// setting the httppara, the second parameter is the website you want to access
  //SIM900.println("AT+HTTPPARA=\"URL\",\"thectbl.com/gsm/getstate.php?color=All\"");// setting the httppara, the second parameter is the website you want to access

 SIM900.println("AT+HTTPPARA=\"URL\",\"ems.mdmahee.com/api/event/8\"");// setting the httppara, the second parameter is the website you want to access
 
  delay(1000);
 
  ShowSerialData();
 
  SIM900.println("AT+HTTPACTION=0");//submit the request 
  delay(10000);//the delay is very important, the delay time is base on the return from the website, if the return datas are very large, the time required longer.
  //while(!SIM900.available());
 
  ShowSerialData();
 
  SIM900.println("AT+HTTPREAD");// read the data from the website you access
  delay(300);
  contentt();
 // ShowSerialData();
   changeLed();


  SIM900.println("");
  Serial.println("");
  delay(1000);
}


void ShowSerialData()
{
  while(SIM900.available()!=0)
    Serial.write(char (SIM900.read()));
}

 
void contentt()
{
// String content = "";
// String RedState = content.substring();
 while(SIM900.available()!=0)
 {  
    //Serial.write(SIM900.read());
    content = content + String(char (SIM900.read()));
    //Serial.print("content= ");
    //Serial.print(content);
    //Serial.println();
//for (int i = 0; i < 200; i++) {Serial.print(content[i]); }
    
 }
}


void changeLed()
{
      Serial.print("content= "); 
      Serial.print(content); 
 
//ID8DN1DS1TT30T1556D20220415
      
      

     Serial.print(" 35, 36 DN=");  Serial.print(content.substring(35,36)); Serial.println();
     Serial.print(" 38, 39 Ds=");  Serial.print(content.substring(38,39)); Serial.println();
     Serial.print(" 41, 43 TT=");  Serial.print(content.substring(41,43)); Serial.println();
     Serial.print(" 44, 48 T=");  Serial.print(content.substring(44,48)); Serial.println();
     Serial.print(" 49, 57 D=");  Serial.print(content.substring(49,57)); Serial.println();

    
     
  /*   
     
     Serial.println("  30 ");  Serial.print(content.substring(30));
    Serial.println("31 ");  Serial.print(content.substring(31));
    Serial.println("32 ");  Serial.print(content.substring(32));
    Serial.println("33 ");  Serial.print(content.substring(33)) ;
    Serial.println("34 ");  Serial.print(content.substring(34)) ;  
    Serial.println("35 ");  Serial.print(content.substring(35));
   */ 

 
 
 
  if(content.substring(38,39)== "1")
 {
   digitalWrite(REDLed, HIGH);
 }
 
else if (content.substring(38,39)== "0")
 {
   digitalWrite(REDLed, LOW);
 }
 
/*  if(content.substring(31,32)== "1")
 {
   digitalWrite(GREENLed, HIGH);
 }
 else if (content.substring(31,32)== "0")
 {
   digitalWrite(GREENLed, LOW);
 }
 
 if(content.substring(32,33)== "1")
 {
   digitalWrite(BLUELed, HIGH);
 }
 else if (content.substring(32,33)== "0")
 {
   digitalWrite(BLUELed, LOW);
 }
 */
 
    Serial.println();
content = "";
}
