/*
 * File:   rtd_switch.c
 * Author: David W
 *
 * Created on November 6, 2016, 5:06 PM
 */


#include <xc.h>
#include "rtd_switch.h"

void switchToRTDOne(){
    SWITCH_A_SetLow();
    SWITCH_B_SetLow();        
    __delay_us(1);
}
void switchToRTDTwo(){
    SWITCH_A_SetLow();
    SWITCH_B_SetHigh();
    __delay_us(1);
}
void switchToRTDThree(){
    SWITCH_A_SetHigh();
    SWITCH_B_SetHigh();    
    __delay_us(1);
}
void switchToRTDFour(){
    SWITCH_A_SetHigh();
    SWITCH_B_SetLow();   
    __delay_us(1);
}
