#include <xc.h>

#pragma config FOSC = HS        // Oscillator Selection bits (HS oscillator)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled)
#pragma config PWRTE = OFF      // Power-up Timer Enable bit (PWRT disabled)
#pragma config BOREN = OFF      // Brown-out Reset Enable bit (BOR disabled)
#pragma config LVP = OFF        // Low-Voltage (Single-Supply) In-Circuit Serial Programming Enable bit (RB3 is digital I/O, HV on MCLR must be used for programming)
#pragma config CPD = OFF        // Data EEPROM Memory Code Protection bit (Data EEPROM code protection off)
#pragma config WRT = OFF        // Flash Program Memory Write Enable bits (Write protection off; all program memory may be written to by EECON control)
#pragma config CP = OFF         // Flash Program Memory Code Protection bit (Code protection off)

#define _XTAL_FREQ 16000000

int sec =0;
int min =0;
int hour = 0;
int date = 0;
int month = 0;
int year = 0;

#define RS RD4
#define EN RD5
#define D4 RD0
#define D5 RD1
#define D6 RD2
#define D7 RD3
#include "libcd.h"
#include "../../EEE307/PIC16F877a_I2C.h"
#include "../../EEE307/PIC16F877a_DS3231.h"
#include "timer.h"
#define dhtpindir TRISBbits.TRISB4
#define dhtpin PORTBbits.RB4
#define pump PORTBbits.RB2
#define bulb PORTBbits.RB1
#define heater PORTBbits.RB3
#define cooler PORTBbits.RB5
#define DHT11_Data_Pin   PORTBbits.RB4
#define DHT11_Data_Pin_Direction  TRISBbits.TRISB4
unsigned char Check_bit, Temp_byte_1, Temp_byte_2, RH_byte_1, RH_byte_2;
unsigned char temp, RH, Sumation ;

long sh;
float mois;

void Read_Mois(void){
 ADCON0bits.ADON = 1;
    __delay_us(30);
    ADCON0bits.GO_DONE = 1;
    while(GO_DONE);
    sh = 256*ADRESH + ADRESL;
    ADON =0;
    mois = 100-(sh*100)/1023;   
}
void dht11_init(){
 DHT11_Data_Pin_Direction= 0; //Configure RD0 as output
 DHT11_Data_Pin = 0; //RD0 sends 0 to the sensor
 __delay_ms(18);
 DHT11_Data_Pin = 1; //RD0 sends 1 to the sensor
 __delay_us(30);
 DHT11_Data_Pin_Direction = 1; //Configure RD0 as input
 }

/*
 * This will find the dht22 sensor is working or not.
 */

 void find_response(){
 Check_bit = 0;
 __delay_us(40);
 if (DHT11_Data_Pin == 0){
 __delay_us(80);
 if (DHT11_Data_Pin == 1){
    Check_bit = 1;
 }     
 __delay_us(50);}
 }
 
 /*
 This Function is for read dht22.
 */
 
 char read_dht11(){
 char data, for_count;
 for(for_count = 0; for_count < 8; for_count++){
     while(!DHT11_Data_Pin); 
    __delay_us(30);
    if(DHT11_Data_Pin == 0){
        data&= ~(1<<(7 - for_count)); //Clear bit (7-b)
    }
    else{
        data|= (1 << (7 - for_count)); //Set bit (7-b)
        while(DHT11_Data_Pin);
    } //Wait until PORTD.F0 goes LOW
    }
 return data;
 }

void main(void) {
    ADCON0 = 0x41;
    ADCON1 = 0x82;
   PORTA = PORTB =PORTC = PORTE = 0;
     TRISB =0;
     TRISD = 0;
     LCD_INIT();
    __delay_ms(200);
   I2C_Initialize(100);
    Set_Time_Date();
    
    __delay_ms(1500);
    
    while(1){
     __delay_ms(800);
    dht11_init();
      find_response();
    if(Check_bit == 1){
        RH_byte_1 = read_dht11();
        RH_byte_2 = read_dht11();
        Temp_byte_1 = read_dht11();
        Temp_byte_2 = read_dht11();
        Sumation = read_dht11();
        if(Sumation == ((RH_byte_1+RH_byte_2+Temp_byte_1+Temp_byte_2) & 0XFF)){
            temp = Temp_byte_1;
            RH = RH_byte_1;
            LCD_CURSOR(2,1);
            LCD_WRITE_STRING("T:");
            LCD_WRITE_NUM(temp);
            LCD_WRITE_STRING("C");
            LCD_CURSOR(2,7);
            LCD_WRITE_STRING("H:");
            LCD_WRITE_NUM(RH);
            LCD_WRITE_STRING("%");
        }
    }
      //-------------//
   Update_Current_Date_Time();
  // if(!(sec%5) || sec<2){
   TRISA0 = 1;
 ADCON0bits.ADON = 1;
    __delay_us(30);
    ADCON0bits.GO_DONE = 1;
    while(GO_DONE);
    sh = 256*ADRESH + ADRESL;
    mois = 77;
    if(sec >= 20 && min==0){
        mois = 97;
    }else if(min >=1){
        mois = 8;
    }
   // mois = 100-((sh-10)/10);
   // LCD_SCROLL(1,9,2);
   //     LCD_SCROLL(0,9,2);
  // }
        RB0=1;
        __delay_ms(200);
        RB0 = 0;
        __delay_ms(200);
        
        LCD_CURSOR(1,1);
        
       // LCD_WRITE_STRING("Time:");
        LCD_WRITE_NUM(hour);
        LCD_WRITE_STRING(":");
        LCD_WRITE_NUM(min);
        LCD_WRITE_STRING(":");
        LCD_WRITE_NUM(sec);
        LCD_WRITE_STRING(" S:");
        LCD_WRITE_NUM(mois);
        LCD_WRITE_STRING("% ");
       
 
   
    //---------ACTUATORS------------SIGH---------OooooooomooooooOOOO-----Hmm--On//-\\\\\God----
    if(mois < 35) pump =1;
        else pump=0;
  
    
    if(hour<8){
            bulb=1;
        }else{
            bulb=0;
        }
    
    if(temp < 22){
        heater = 1;
        cooler =0;
    }else if(temp > 28){
        cooler = 1;
        heater = 0;
    } else{
        cooler = 0;
        heater = 0;
    }
    
    
    
    
    
    
    
    
    }
    
    return;
}
