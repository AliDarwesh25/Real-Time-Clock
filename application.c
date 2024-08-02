/* 
 * File:   Application.c
 * Author: Ali
 *
 * Created on January 23, 2024, 7:16 PM
 */
#include "application.h"

uint8 seconds = 0;
uint8 minutes = 0;
uint8 hours = 0;
uint8 keypad_Value = 0;
uint8 digit_one = 0;
uint8 digit_two= 0;

void timer0_handler(void){
    seconds++;
}

chr_lcd_8bit_t lcd_obj = {
  .lcd_rs.port = PORTC_INDEX,
  .lcd_rs.pin = GPIO_PIN0,
  .lcd_rs.direction = GPIO_DIRECTION_OUTPUT ,
  .lcd_rs.direction = GPIO_LOW ,
  .lcd_en.port = PORTC_INDEX,
  .lcd_en.pin = GPIO_PIN1,
  .lcd_en.direction = GPIO_DIRECTION_OUTPUT ,
  .lcd_en.direction = GPIO_LOW ,
  .lcd_data[0].port = PORTC_INDEX,
  .lcd_data[0].pin = GPIO_PIN2,
  .lcd_data[0].direction = GPIO_DIRECTION_OUTPUT,
  .lcd_data[0].logic = GPIO_LOW,
  .lcd_data[1].port = PORTC_INDEX,
  .lcd_data[1].pin = GPIO_PIN3,
  .lcd_data[1].direction = GPIO_DIRECTION_OUTPUT,
  .lcd_data[1].logic = GPIO_LOW,
  .lcd_data[2].port = PORTC_INDEX,
  .lcd_data[2].pin = GPIO_PIN4,
  .lcd_data[2].direction = GPIO_DIRECTION_OUTPUT,
  .lcd_data[2].logic = GPIO_LOW,
  .lcd_data[3].port = PORTC_INDEX,
  .lcd_data[3].pin = GPIO_PIN5,
  .lcd_data[3].direction = GPIO_DIRECTION_OUTPUT,
  .lcd_data[3].logic = GPIO_LOW,
};

keypad_t keypad1 ={
    .keypad_row_pins[0].port = PORTD_INDEX,
    .keypad_row_pins[0].pin = GPIO_PIN0,
    .keypad_row_pins[0].direction = GPIO_DIRECTION_OUTPUT,
    .keypad_row_pins[0].logic = GPIO_LOW,
    
    .keypad_row_pins[1].port = PORTD_INDEX,
    .keypad_row_pins[1].pin = GPIO_PIN1,
    .keypad_row_pins[1].direction = GPIO_DIRECTION_OUTPUT,
    .keypad_row_pins[1].logic = GPIO_LOW,
    
    .keypad_row_pins[2].port = PORTD_INDEX,
    .keypad_row_pins[2].pin = GPIO_PIN2,
    .keypad_row_pins[2].direction = GPIO_DIRECTION_OUTPUT,
    .keypad_row_pins[2].logic = GPIO_LOW,
    
    .keypad_row_pins[3].port = PORTD_INDEX,
    .keypad_row_pins[3].pin = GPIO_PIN3,
    .keypad_row_pins[3].direction = GPIO_DIRECTION_OUTPUT,
    .keypad_row_pins[3].logic = GPIO_LOW,
    
    .keypad_columns_pins[0].port = PORTD_INDEX,
    .keypad_columns_pins[0].pin = GPIO_PIN4,
    .keypad_columns_pins[0].direction = GPIO_DIRECTION_INPUT,
    .keypad_columns_pins[0].logic = GPIO_LOW,
    
    .keypad_columns_pins[1].port = PORTD_INDEX,
    .keypad_columns_pins[1].pin = GPIO_PIN5,
    .keypad_columns_pins[1].direction = GPIO_DIRECTION_INPUT,
    .keypad_columns_pins[1].logic = GPIO_LOW,
    
    .keypad_columns_pins[2].port = PORTD_INDEX,
    .keypad_columns_pins[2].pin = GPIO_PIN6,
    .keypad_columns_pins[2].direction = GPIO_DIRECTION_INPUT,
    .keypad_columns_pins[2].logic = GPIO_LOW,
    
    .keypad_columns_pins[3].port = PORTD_INDEX,
    .keypad_columns_pins[3].pin = GPIO_PIN7,
    .keypad_columns_pins[3].direction = GPIO_DIRECTION_INPUT,
    .keypad_columns_pins[3].logic = GPIO_LOW,
    
};

segment_t sev_seg={
    .segment_pins[0].port = PORTA_INDEX,
    .segment_pins[0].pin = GPIO_PIN0,
    .segment_pins[0].logic = GPIO_LOW,
    .segment_pins[0].direction = GPIO_DIRECTION_OUTPUT,
    .segment_pins[1].port = PORTA_INDEX,
    .segment_pins[1].pin = GPIO_PIN1,
    .segment_pins[1].logic = GPIO_LOW,
    .segment_pins[1].direction = GPIO_DIRECTION_OUTPUT,
    .segment_pins[2].port = PORTA_INDEX,
    .segment_pins[2].pin = GPIO_PIN2,
    .segment_pins[2].logic = GPIO_LOW,
    .segment_pins[2].direction = GPIO_DIRECTION_OUTPUT,
    .segment_pins[3].port = PORTA_INDEX,
    .segment_pins[3].pin = GPIO_PIN3,
    .segment_pins[3].logic = GPIO_LOW,
    .segment_pins[3].direction = GPIO_DIRECTION_OUTPUT,
    .segment_type = SEGMENT_COMMON_ANODE
};

timer0_t timer_obj={
    .TIMER0_InterruptHandler = timer0_handler,
    .prescaler_enable = TIMER0_PRESCALER_ENABLE_CFG,
    .prescaler_value = TIMER0_PRESCALER_DIV_BY_32,
    .timer0_mode = TIMER0_TIMER_MODE,
    .timer0_register_size = TIMER0_16BIT_REGISTER_MODE,
    .timer0_preload_value = 3036,
};





int main() { 
    Std_ReturnType ret = E_NOT_OK;
    application_intialize();
    ret = lcd_4bit_send_string_pos(&lcd_obj,1,1,"Press 1 To Set Clock");
    while(1){
        do{
            ret = keypad_get_value(&keypad1,&keypad_Value);
            ret = gpio_port_write_logic(PORTB_INDEX, 0x01); // 0011 1110
            ret = gpio_port_write_logic(PORTA_INDEX, ((uint8)(hours/10)));
            __delay_ms(5);
            ret = gpio_port_write_logic(PORTB_INDEX, 0x02); // 0011 1101
            ret = gpio_port_write_logic(PORTA_INDEX, ((uint8)(hours%10)));
            __delay_ms(5);
            ret = gpio_port_write_logic(PORTB_INDEX, 0x04); // 0011 1011
            ret = gpio_port_write_logic(PORTA_INDEX, ((uint8)(minutes/10)));
            __delay_ms(5);
            ret = gpio_port_write_logic(PORTB_INDEX, 0x08); // 0011 0111
            ret = gpio_port_write_logic(PORTA_INDEX, ((uint8)(minutes%10)));
            __delay_ms(5);
            ret = gpio_port_write_logic(PORTB_INDEX, 0x10); // 0010 1111
            ret = gpio_port_write_logic(PORTA_INDEX, ((uint8)(seconds/10)));
            __delay_ms(5);
            ret = gpio_port_write_logic(PORTB_INDEX, 0x20); // 0001 1111
            ret = gpio_port_write_logic(PORTA_INDEX, ((uint8)(seconds%10)));
            __delay_ms(5);
            if(seconds == 60){
                seconds = 0;
                minutes++;
            }
            else{/*Nothing*/}
            if(minutes == 60){
                minutes = 0;
                hours++;
            }
            else{/*Nothing*/}
            if(hours == 24){
                hours=0;
            }
            else{/*Nothing*/}
        }while(keypad_Value == 0);
        if(keypad_Value == '1'){
            __delay_ms(250);
            ret = lcd_4bit_send_string_pos(&lcd_obj,2,1,"Hours:--");
            do{
                ret = keypad_get_value(&keypad1,&digit_one);
            }while(digit_one == 0);
            __delay_ms(250);
            ret = lcd_4bit_send_char_data_pos(&lcd_obj,2,7,digit_one);
            __delay_ms(250);
            do{
                ret = keypad_get_value(&keypad1,&digit_two);
            }while(digit_two == 0);
            __delay_ms(300);
            ret = lcd_4bit_send_char_data_pos(&lcd_obj,2,8,digit_two);
            __delay_ms(300);
            hours = (digit_one-48)*10+(digit_two-48);
            digit_one = 0;
            digit_two = 0;
            ret = lcd_4bit_send_string_pos(&lcd_obj,3,1,"Minutes:--");
            do{
                ret = keypad_get_value(&keypad1,&digit_one);
            }while(digit_one == 0);
            __delay_ms(250);
            ret = lcd_4bit_send_char_data_pos(&lcd_obj,3,9,digit_one);
            __delay_ms(250);
            do{
                ret = keypad_get_value(&keypad1,&digit_two);
            }while(digit_two == 0);
            __delay_ms(300);
            ret = lcd_4bit_send_char_data_pos(&lcd_obj,3,10,digit_two);
            __delay_ms(300);
            minutes = (digit_one-48)*10+(digit_two-48);
            digit_one = 0;
            digit_two = 0;
            ret = lcd_4bit_send_string_pos(&lcd_obj,4,1,"Seconds:--");
            do{
                ret = keypad_get_value(&keypad1,&digit_one);
            }while(digit_one == 0);
            __delay_ms(250);
            ret = lcd_4bit_send_char_data_pos(&lcd_obj,4,9,digit_one);
            __delay_ms(250);
            do{
                ret = keypad_get_value(&keypad1,&digit_two);
            }while(digit_two == 0);
            __delay_ms(300);
            ret = lcd_4bit_send_char_data_pos(&lcd_obj,4,10,digit_two);
            __delay_ms(300);
            seconds = (digit_one-48)*10+(digit_two-48);
            digit_one = 0;
            digit_two = 0;
            keypad_Value = 0;
            lcd_4bit_send_command(&lcd_obj,_LCD_CLEAR);
            ret = lcd_4bit_send_string_pos(&lcd_obj,1,1,"Press 1 To Set Clock");
        }
        else{
            lcd_4bit_send_command(&lcd_obj,_LCD_CLEAR);
            __delay_ms(300);
            ret = lcd_4bit_send_string_pos(&lcd_obj,1,1,"Wrong choice");
            __delay_ms(300);
            lcd_4bit_send_command(&lcd_obj,_LCD_CLEAR);
            __delay_ms(300);
            ret = lcd_4bit_send_string_pos(&lcd_obj,1,1,"Press 1 To Set Clock");
            keypad_Value = 0;
        }
            
            
    }
    return (EXIT_SUCCESS);
}

void application_intialize(void){
    Std_ReturnType ret = E_NOT_OK;
     ret = lcd_4bit_intialize(&lcd_obj);
    ret = keypad_initialize(&keypad1);
    ret = seven_segment_initialize(&sev_seg);
    ret = Timer0_Init(&timer_obj);
    ret = gpio_port_direction_initalize(PORTB_INDEX , GPIO_DIRECTION_OUTPUT);
}


