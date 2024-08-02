/* 
 * File:   Application.h
 * Author: Ali
 *
 * Created on January 23, 2024, 7:16 PM
 */

#ifndef APPLICATION_H
#define	APPLICATION_H

/* Section : includes */
#include "ECU_Layer/7_segment/ecu_seven_segment.h"
#include "ECU_Layer/Keypad/ecu_keypad.h"
#include "ECU_Layer/chr_LCD/ecu_chr_lcd.h"
#include "MCAL_Layer/Timer0/hal_timer0.h"
#include "MCAL_Layer/Interrupt/mcal_external_interrupt.h"

/* Section : Macro Declarations*/

/* Section : Macro Functions Declarations*/

/* Section : Data Type Declarations*/

/* Section : Function Declarations*/
void application_intialize(void);;

#endif	/* APPLICATION_H */

