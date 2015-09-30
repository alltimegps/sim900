/*
Perodic Report using a Sim900

Created jul/2014 by:Alvaro Moreno
V1.0

Licence GNU

APN: Depend on simcard
Server: sandbox.altimegps.com
Port: 9871
*/

#include <SoftwareSerial.h>
#include <String.h>
 
SoftwareSerial mySerial(7, 8);

String imei="";

void setup(){
  mySerial.begin(19200); 
  Serial.begin(19200);   
  delay(500);
  mySerial.println("AT+GSN");//get imei
  delay(2000); 
  ShowSerialData(5);
}
 
void loop(){  
  String data = "$$" + imei + ",2001,2015/08/17,20:45:39##";
  SendRep(data);
  delay(10000);  
}

void SendRep(String d){
  mySerial.println("AT+CGATT?");
  delay(1000); 
  ShowSerialData(1);  
  
  mySerial.println("AT+CSTT=\"APN\"");
  delay(1000); 
  ShowSerialData(2);
 
  mySerial.println("AT+CIICR");
  delay(3000); 
  ShowSerialData(3);
 
  mySerial.println("AT+CIFSR");
  delay(2000); 
  ShowSerialData(4);
 
  mySerial.println("AT+CIPSPRT=0");
  delay(3000); 
  ShowSerialData(6);
 
  mySerial.println("AT+CIPSTART=\"UDP\",\"sandbox.alltimegps.com\",\"9871\"");//start up the connection
  delay(2000); 
  ShowSerialData(7);
 
  mySerial.println("AT+CIPSEND");//begin send data to remote server
  delay(4000);
  ShowSerialData(8);
  
  mySerial.println(d);
 
  mySerial.println((char)26);//sending
  delay(5000);//waitting for reply, important! the time is base on the condition of internet 
  mySerial.println(); 
  ShowSerialData(9);
 
  mySerial.println("AT+CIPCLOSE");
  delay(100);
  ShowSerialData(10);
}
 
void ShowSerialData(int n){
  String msg;
  char str;
  int cr=0;//carriage return
  while(mySerial.available()!=0){
    str=mySerial.read();
    msg+=str;
    if(n==5){
      if(str==(char)13){
        cr++;        
      }else{
        if(cr==2){
          if((str>=(char)48) && (str<=(char)57))imei+=str;
        }
      } 
    }  
  }  
  Serial.println(msg); 
}
