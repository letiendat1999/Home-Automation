//Khai báo thư viện
#include <Wire.h>
#include <SoftwareSerial.h>
#include <DHT.h>
//Rx Tx
SoftwareSerial nodemcu(4,5);
#define relay1 13 //đèn led phòng ngủ
#define relay2 12  //đèn led phòng khách
#define button_led_1 6  //nút nhấn đk led ngủ
#define button_led_2 7  //nút nhấn đk led khách
#define BUZZER  2       //còi
#define sensor1 A0 // Gas sensor
#define sensor2 A3
#define DHTTYPE DHT11
DHT dht(sensor2, DHTTYPE);

#define quat      10  //quạt phòng khách
#define mayLanh   11  //máy lạnh phòng ngủ
#define button_quat     A1  //nút nhấn đk quạt
#define button_mayLanh  A2  //nút nhấn đk máy lạnh

long int data; 
int sdata1 = 0; // temperature data
long int sdata2 = 0; // pressure data
int sdata3 = 0; // altitude data



String cdata; // complete data

void setup()
{
Serial.begin(9600); 
nodemcu.begin(9600);
pinMode(relay1, OUTPUT);  //đèn led phòng ngủ 
pinMode(relay2, OUTPUT);  //đèn led phòng khách
pinMode(button_led_1, INPUT_PULLUP);  //nút nhấn led ngủ
pinMode(button_led_2, INPUT_PULLUP);  //nút nhấn led khách
pinMode(BUZZER, OUTPUT);          //còi
pinMode(sensor1, INPUT);          //gas sensor
pinMode(button_quat, INPUT_PULLUP);     //nút nhấn quạt
pinMode(button_mayLanh, INPUT_PULLUP);  //nút nhấn máy lạnh
pinMode(quat, OUTPUT);                  //quạt
pinMode(mayLanh, OUTPUT);               //máy lạnh
       
dht.begin();

}

void loop()
{
 thietbi();
 den();
 quatVaMayLanh();
 sensor();
 
  
}

void den(){                  //đồng bộ nút nhấn cho 2 bóng đèn
  if(digitalRead(relay1)==HIGH){  //nếu đèn led ngủ sáng
    if(digitalRead(button_led_1)==LOW){//nếu nút nhấn ấn
     
      digitalWrite(relay1, LOW);          //tắt đèn led ngủ
      
    }
    else{}
  }
  else{                                     //nếu đèn tắt
    if(digitalRead(button_led_1)==LOW){    //nếu nút ấn
    
        digitalWrite(relay1, HIGH);          //đèn sáng
      
      
    }
    else{}
  }
  if(digitalRead(relay2)==HIGH){  //nếu đèn led ngủ sáng
    if(digitalRead(button_led_2)==LOW){//nếu nút nhấn ấn
      
      digitalWrite(relay2, LOW);          //tắt đèn led ngủ
      
    }
    else{}
  }
  else{                                     //nếu đèn tắt
    if(digitalRead(button_led_2)==LOW){    //nếu nút ấn
      
        digitalWrite(relay2, HIGH);          //đèn sáng
     }
     else{} 
   }
    
}
void quatVaMayLanh(){           //đồng bộ nút nhấn cho quạt và máy lạnh
  if(digitalRead(quat)==HIGH){  //nếu đèn led ngủ sáng
    if(analogRead(button_quat)==LOW){//nếu nút nhấn ấn
     
      digitalWrite(quat, LOW);          //tắt đèn led ngủ
      
    }
    else{}
  }
  else{                                     //nếu đèn tắt
    if(analogRead(button_quat)==LOW){    //nếu nút ấn
    
        digitalWrite(quat, HIGH);          //đèn sáng
      
      
    }
    else{}
  }
  if(digitalRead(mayLanh)==HIGH){  //nếu đèn led ngủ sáng
    if(analogRead(button_mayLanh)==LOW){//nếu nút nhấn ấn
      
      digitalWrite(mayLanh, LOW);          //tắt đèn led ngủ
      
    }
    else{}
  }
  else{                                     //nếu đèn tắt
    if(analogRead(button_mayLanh)==LOW){    //nếu nút ấn
      
        digitalWrite(mayLanh, HIGH);          //đèn sáng
     }
     else{} 
   }
  
  
} 


void sensor(){
  sdata1 = analogRead(sensor1);             //đọc cảm biến gas
  sdata2 = dht.readHumidity();
  sdata3 = dht.readTemperature();
  if(sdata1 > 450) //co gas hoac co khoi
  {
     digitalWrite(BUZZER,LOW); 
     delay(1000);
  }
  else{                           //không có khói
   digitalWrite(BUZZER,HIGH); 
  }
  delay(1000);
   cdata = cdata + sdata1+","+sdata2+","+sdata3; // comma will be used a delimeter
   Serial.println(cdata);     
   nodemcu.println(cdata);      //gửi về cho nodemcu, về blynk server
   delay(1000); // 100 milli seconds
   cdata = ""; 
}




void thietbi(){

 
  if ( nodemcu.available() > 0 ) 
  {
    data = nodemcu.parseInt();                //đọc dữ liệu từ blynk
    delay(100); 
    Serial.println(data); 
 
 if(data == 10){
  digitalWrite(relay1,LOW);
  
 }
 if(data == 12){
  digitalWrite(relay2,LOW);
 }
 if(data == 11){
  digitalWrite(relay1,HIGH);
  
 }
 if(data == 13){
  digitalWrite(relay2,HIGH);
  
 }
 
 if(data == 1210){
  digitalWrite(relay1,LOW);
  digitalWrite(relay2,LOW);
 }
 if(data == 1012){
  digitalWrite(relay1,LOW);
  digitalWrite(relay2,LOW);
 }
 if(data == 1311){
  digitalWrite(relay1,HIGH);
  digitalWrite(relay2,HIGH);
 }
 if(data == 1113){
  digitalWrite(relay1,HIGH);
  digitalWrite(relay2,HIGH);
 }
 if(data == 1013){
  digitalWrite(relay1,LOW);
  digitalWrite(relay2,HIGH);
 }
 if(data == 1310){
  digitalWrite(relay1,LOW);
  digitalWrite(relay2,HIGH);
 }
 if(data == 1112){
  digitalWrite(relay1,HIGH);
  digitalWrite(relay2,LOW);
 }
 if(data == 1211){
  digitalWrite(relay1,HIGH);
  digitalWrite(relay2,LOW);
 }
 if(data == 1010){
  digitalWrite(relay1,LOW);
  }
  if(data == 1111){
  digitalWrite(relay1,HIGH);
  }
  if(data == 1212){
  digitalWrite(relay2,LOW);
  }
  if(data == 1313){
  digitalWrite(relay2,HIGH);
  }
 if(data == 14){
  digitalWrite(quat,LOW);
  
 }
 if(data == 15){
  digitalWrite(quat,HIGH);
  
 }
 if(data == 16){
  digitalWrite(mayLanh,LOW);
  
 }
 if(data == 17){
  digitalWrite(mayLanh,HIGH);
  
 }
 if(data == 1416){
  digitalWrite(quat,LOW);
  digitalWrite(mayLanh,LOW);
 }
 if(data == 1614){
  digitalWrite(quat,LOW);
  digitalWrite(mayLanh,LOW);
 }
 if(data == 1517){
  digitalWrite(quat,HIGH);
  digitalWrite(mayLanh,HIGH);
 }
 if(data == 1715){
  digitalWrite(quat,HIGH);
  digitalWrite(mayLanh,HIGH);
 }
 if(data == 1417){
  digitalWrite(quat,LOW);
  digitalWrite(mayLanh,HIGH);
 }
 if(data == 1714){
  digitalWrite(quat,LOW);
  digitalWrite(mayLanh,HIGH);
 }
 if(data == 1516){
  digitalWrite(quat,HIGH);
  digitalWrite(mayLanh,LOW);
 }
 if(data == 1615){
  digitalWrite(quat,HIGH);
  digitalWrite(mayLanh,LOW);
 }
 if(data == 1414){
  digitalWrite(quat,LOW);
 
 }
  if(data == 1515){
  digitalWrite(quat,HIGH);
 
 }
 if(data == 1616){
  digitalWrite(mayLanh,LOW);
 
 }
 if(data == 1717){
  digitalWrite(mayLanh,HIGH);
 
 }
 
  }
}


