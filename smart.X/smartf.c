#pragma config FOSC = HS        // Oscillator Selection bits (HS oscillator)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled)
#pragma config PWRTE = OFF      // Power-up Timer Enable bit (PWRT disabled)
#pragma config BOREN = OFF      // Brown-out Reset Enable bit (BOR disabled)
#pragma config LVP = OFF        // Low-Voltage (Single-Supply) In-Circuit Serial Programming Enable bit (RB3 is digital I/O, HV on MCLR must be used for programming)
#pragma config CPD = OFF        // Data EEPROM Memory Code Protection bit (Data EEPROM code protection off)
#pragma config WRT = OFF        // Flash Program Memory Write Enable bits (Write protection off; all program memory may be written to by EECON control)
#pragma config CP = OFF         // Flash Program Memory Code Protection bit (Code protection off)

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
#define _XTAL_FREQ 16000000
#include <xc.h>
//#include "../../EEE307/PIC16F877a_I2C.h"
//#include "../../EEE307/PIC16F877a_DS3231.h"
#include "lcd.h"

void main(void) {
   
   PORTA = PORTB =PORTC= PORTD = PORTE = 0;
     TRISB =0;
     TRISD = 0;
     Lcd_Start();
    Lcd_Clear();
    Lcd_Set_Cursor(1,1);
     Lcd_Print_String("Welco");
    
    Lcd_Clear();
   // I2C_Initialize(100);
  //  Set_Time_Date();
    __delay_ms(1500);
    
    while(1){
        RB0=1;
        __delay_ms(200);
        RB0 = 0;
    }
    return;
}
