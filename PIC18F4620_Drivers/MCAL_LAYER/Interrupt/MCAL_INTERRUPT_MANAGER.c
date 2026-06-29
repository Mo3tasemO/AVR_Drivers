/* 
 * File:   MCAL_INTERRUPT_MANAGER.c
 * Author: Moata
 *
 * Created on February 21, 2026, 10:38 PM
 */


#include "MCAL_INTERRUPT_MANAGER.h"

#if INTERRUPT_PRIORITY_LEVELS_ENABLE==INTERRUPT_FEATURE_ENABLE

//static volatile uint8 RB4_Flag = 1, RB5_Flag = 1, RB6_Flag = 1, RB7_Flag = 1;



void __interrupt() InterruptManagerHigh(void){
//    if((INTCONbits.INT0E == INTERRUPT_ENABLE) && (INTCONbits.INT0F == INTERRUPT_OCCUR)){
//        INT0_ISR();
//    }
//    else{
//        /*Nothing*/
//    }
//    if((INTCON3bits.INT2E == INTERRUPT_ENABLE) && (INTCON3bits.INT2F == INTERRUPT_OCCUR)){
//        INT2_ISR();
//    }
//    else{
//        /*Nothing*/
//    }
//    if((INTCONbits.RBIE == INTERRUPT_ENABLE) && (INTCONbits.RBIF == INTERRUPT_OCCUR) && 
//       (PORTBbits.RB4 == 0) && (0 == RB4_Flag)){
//        RB4_Flag = 1;
//        RB4_ISR(0);
//    }
//    else{
//        /*Nothing*/
//    }
//    if((INTCONbits.RBIE == INTERRUPT_ENABLE) && (INTCONbits.RBIF == INTERRUPT_OCCUR) && 
//       (PORTBbits.RB4 == 1) && (1 == RB4_Flag)){
//        RB4_Flag = 0;
//        RB4_ISR(1);
//    }
//    else{
//        /*Nothing*/
//    }
//    if((INTCONbits.RBIE == INTERRUPT_ENABLE) && (INTCONbits.RBIF == INTERRUPT_OCCUR) && 
//       (PORTBbits.RB5 == 0) && (0 == RB5_Flag)){
//        RB5_Flag = 1;
//        RB5_ISR(0);
//    }
//    else{
//        /*Nothing*/
//    }
//    if((INTCONbits.RBIE == INTERRUPT_ENABLE) && (INTCONbits.RBIF == INTERRUPT_OCCUR) && 
//       (PORTBbits.RB5 == 1) && (1 == RB5_Flag)){
//        RB5_Flag = 0;
//        RB5_ISR(1);
//    }
//    else{
//        /*Nothing*/
//    }
//    if((INTCONbits.RBIE == INTERRUPT_ENABLE) && (INTCONbits.RBIF == INTERRUPT_OCCUR) && 
//       (PORTBbits.RB6 == 0) && (0 == RB6_Flag)){
//        RB6_Flag = 1;
//        RB6_ISR(0);
//    }
//    else{
//        /*Nothing*/
//    }
//    if((INTCONbits.RBIE == INTERRUPT_ENABLE) && (INTCONbits.RBIF == INTERRUPT_OCCUR) && 
//       (PORTBbits.RB6 == 1) && (1 == RB6_Flag)){
//        RB6_Flag = 0;
//        RB6_ISR(1);
//    }
//    else{
//        /*Nothing*/
//    }
//    if((INTCONbits.RBIE == INTERRUPT_ENABLE) && (INTCONbits.RBIF == INTERRUPT_OCCUR) && 
//       (PORTBbits.RB7 == 0) && (0 == RB7_Flag)){
//        RB7_Flag = 1;
//        RB7_ISR(0);
//    }
//    else{
//        /*Nothing*/
//    }
//    if((INTCONbits.RBIE == INTERRUPT_ENABLE) && (INTCONbits.RBIF == INTERRUPT_OCCUR) && 
//       (PORTBbits.RB7 == 1) && (1 == RB7_Flag)){
//        RB7_Flag = 0;
//        RB7_ISR(1);
//    }
//    else{
//        /*Nothing*/
//    }
}
void __interrupt(low_priority) InterruptManagerLow(void){
//    if((INTCON3bits.INT1E == INTERRUPT_ENABLE) && (INTCON3bits.INT1F == INTERRUPT_OCCUR)){
//        INT1_ISR();
//    }
//    else{
//        /*Nothing*/
//    }
}


#else
void __interrupt() InterruptManager(void){
    
    if((INTCONbits.INT0E == INTERRUPT_ENABLE) && (INTCONbits.INT0F == INTERRUPT_OCCUR)){
        INT0_ISR();
    }
    else{
        /*Nothing*/
    }
    if((INTCON3bits.INT2E == INTERRUPT_ENABLE) && (INTCON3bits.INT2F == INTERRUPT_OCCUR)){
        INT2_ISR();
    }
    if((PIE1bits.ADIE == INTERRUPT_ENABLE) && (PIR1bits.ADIF == INTERRUPT_OCCUR)){
        ADC_ISR();
    }
    else{
        /*Nothing*/
    }
    if((INTCONbits.TMR0IE == INTERRUPT_ENABLE) && (INTCONbits.TMR0IF == INTERRUPT_OCCUR)){
        TMR0_ISR();
    }
    else{
        /*Nothing*/
    }
    if((PIE1bits.TMR1IE == INTERRUPT_ENABLE) && (PIR1bits.TMR1IF == INTERRUPT_OCCUR)){
        TMR1_ISR();
    }
    else{
        /*Nothing*/
    }
}

#endif