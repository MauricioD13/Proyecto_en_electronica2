/* 
 * File:   polling.c
 * Author: guasonito
 *
 * Created on 19 de febrero de 2021, 12:23 PM
 */




#include "numbers.h"
#include "timers.h"
#include "ADC.h"
#include <xc.h>
#define TRANS1 PORTBbits.RB3
#define TRANS2 PORTBbits.RB2
#define _XTAL_FREQ 31000
// CONFIG1
#pragma config FOSC = INTOSC    // Oscillator Selection (INTOSC oscillator: I/O function on CLKIN pin)
#pragma config WDTE = OFF        // Watchdog Timer Enable (WDT enabled)
#pragma config PWRTE = OFF      // Power-up Timer Enable (PWRT disabled)
#pragma config MCLRE = ON       // MCLR Pin Function Select (MCLR/VPP pin function is MCLR)
#pragma config CP = OFF         // Flash Program Memory Code Protection (Program memory code protection is disabled)
#pragma config CPD = ON        // Data Memory Code Protection (Data memory code protection is disabled)
#pragma config BOREN = ON       // Brown-out Reset Enable (Brown-out Reset enabled)
#pragma config CLKOUTEN = OFF   // Clock Out Enable (CLKOUT function is disabled. I/O or oscillator function on the CLKOUT pin)
#pragma config IESO = ON        // Internal/External Switchover (Internal/External Switchover mode is enabled)
#pragma config FCMEN = ON       // Fail-Safe Clock Monitor Enable (Fail-Safe Clock Monitor is enabled)

int i = 0;
int estado = 0;
/*void __interrupt(low_priority) isr(void){
    
    
    i++;
    if(i==10){
        PIR1bits.TMR1IF = 0;
        LED1 = 0;
        i = 0;
    }
}*/
int main() {
    //config_timer(1,0,1,'I');
   
  
    int value;
    PORTB = 0x00;
    PORTA = 0x00;
    TRISA &= 0x00;
    TRISB &= 0x00; 
    ANSELA &= 0x00;
    ANSELB &= 0x00;
    oscillator_module();
    
    config_T1(0,0);
    
    estado = 1;
    config_ADC();
    
    ADC_flag = 0;
    
    PIR1 = 0x00;
    TRANS2 = 1;
    eight();
    __delay_ms(2);
    start_conversion = 1;
    
    while(1){
        if(start_conversion == 0){
            
            value = read_ADC();
            
            
            start_conversion = 1;
            value = (5/1024) * value;
            ADRESL = 0x00;
            ADRESH = 0x00;
         }
    }
        /*if(TMR1H >= 0x0F && TMR1L == 0xFF){
            
           
            if(estado == 1){
                PORTAbits.RA2 = 0;
                estado = 0;
            }else{
                LED_A = 1;
                estado = 1;
            }
            if(start_conversion == 0){
                start_conversion = 1;
            }
        }
        if(ADC_flag == 1){
            value = read_ADC();
            ADRESL = 0x00;
            ADRESH = 0x00;
            ADC_flag = 0;
         }*/
        
        
       
    //config_ADC();
    //start_conversion = 1;
      
}

