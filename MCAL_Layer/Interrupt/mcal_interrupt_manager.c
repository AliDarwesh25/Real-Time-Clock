/* 
 * File:   mcal_interrupt_manager.c
 * Author: Ali
 * https://www.linkedin.com/in/ali-darwesh-752678216
 * Created on June 21, 2024, 8:41 PM
 */

#include "mcal_interrupt_manager.h"


#if INTERRUPT_PRIORITY_LEVELS_ENABLE==INTERRUPT_FEATURE_ENABLE

void __interrupt(high_priority) InterruptManagerHigh(void){
    
}

void __interrupt(low_priority) InterruptManagerLow(void){
    
}

#else

void __interrupt() InterruptManagerHigh(void){
    if((INTERRUPT_ENABLE == INTCONbits.TMR0IE) && (INTERRUPT_OCCUR == INTCONbits.TMR0IF)){
        Timer0_ISR();
    }
    else{ /* Nothing */ }
    
}

#endif