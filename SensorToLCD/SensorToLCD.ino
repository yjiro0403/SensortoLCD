#include <LiquidCrystal.h>
#include <stdlib.h>
#define E_num 10 //要素数

LiquidCrystal lcd(8,9, 4, 5, 6, 7);

void setup(){
  lcd.begin(16, 2);
  Serial.begin(9600);
}

int buf_check(char tmp[],char buf,int j,char mes[])
{  
     if(buf == ',' || buf == '\0'){  
       lcd.clear();
       lcd.setCursor(0,0);
       lcd.print(mes);       

       tmp[j] = '\0';

       lcd.print(tmp);
              
       return 0;
     }else{
       return 1;
     }
  
}

void loop() {
 char buf='d',IP[E_num],tem[E_num],humi[E_num],no1[E_num]; //左から端末番号,温度,湿度
 char num;
 int val,j,i=0;
 int flag_n=0;
 
   for(j=0;buf != '\0';j++){
   while(!Serial.available()); //wait till data coming
     buf = Serial.read();
     switch(flag_n){
       case 0:
          if(buf_check(IP,buf,j,"IP:"))
            IP[j] = buf;         
          else{
            flag_n++;
            j = -1;
          }
       break;
       case 1:
          if(buf_check(tem,buf,j,"tem:"))       
             tem[j] = buf;
             else{
            flag_n++;
            j = -1;
          }
          break;

       case 2:
          if(buf_check(humi,buf,j,"humi:"))
             humi[j] = buf;
           else{
            flag_n++;
            j = -1;
          }
             break;

       case 3:
          if(buf_check(no1,buf,j,"no1:"))
             no1[j] = buf;
           else{
            flag_n = 0;
            j = -1;
          }
             break;


       default: break;
     }
 
   }  
   
}


