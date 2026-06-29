/* 
 * File:   ECU_LCD.c
 * Author: Moata
 *
 * Created on January 1, 2026, 2:07 PM
 */

#include "ECU_LCD.h"

static Std_ReturnType LCD_SENT_4_BIT(const LCD_4_BIT_T *lcd, uint8 command);
static Std_ReturnType LCD_SENT_4_BIT_ENABLE(const LCD_4_BIT_T *lcd);
static Std_ReturnType LCD_4BIT_SET_CURSOR_POS(const LCD_4_BIT_T *lcd, uint8 row, uint8 column);

static Std_ReturnType LCD_SENT_8_BIT_ENABLE(const LCD_8_BIT_T *lcd);
static Std_ReturnType LCD_8BIT_SET_CURSOR_POS(const LCD_8_BIT_T *lcd, uint8 row, uint8 column);

/*LCD_4_BIT_INTERFACE*/


Std_ReturnType LCD_4_BIT_INIT(const LCD_4_BIT_T *lcd)
{
    Std_ReturnType ret = E_OK;
    uint8 DATA_COUNTER_LCD = 0;
    if(NULL == lcd){
        ret = E_NOT_OK;
    }
    else{
        ret = gpio_pin_initialize(&(lcd->lcd_rs));
        ret = gpio_pin_initialize(&(lcd->lcd_e));
        for(DATA_COUNTER_LCD = 0; DATA_COUNTER_LCD < 4; DATA_COUNTER_LCD++){
            ret = gpio_pin_initialize(&(lcd->lcd_data[DATA_COUNTER_LCD]));
        }
        __delay_ms(20);
        ret = LCD_4_BIT_SEND_COMMAND(lcd, DISPLAY_ON_8_BIT_2_LINE_5X8_FONT);
        __delay_ms(5);
        ret = LCD_4_BIT_SEND_COMMAND(lcd, DISPLAY_ON_8_BIT_2_LINE_5X8_FONT);
        __delay_us(150);
        ret = LCD_4_BIT_SEND_COMMAND(lcd, DISPLAY_ON_8_BIT_2_LINE_5X8_FONT);
        
        ret = LCD_4_BIT_SEND_COMMAND(lcd, CLEAR_DISPLAY);
        ret = LCD_4_BIT_SEND_COMMAND(lcd, RETURN_HOME);
        ret = LCD_4_BIT_SEND_COMMAND(lcd, DISPLAY_ON_INCREAMENT_NO_SHIFT_DISPLAY);
        ret = LCD_4_BIT_SEND_COMMAND(lcd, DISPLAY_ON_CURSOR_OFF_BLINK_OFF);
        ret = LCD_4_BIT_SEND_COMMAND(lcd, DISPLAY_ON_4_BIT_2_LINE_5X8_FONT);
        ret = LCD_4_BIT_SEND_COMMAND(lcd, 0x80);        
    }
    return ret;
}
Std_ReturnType LCD_4_BIT_SEND_COMMAND(const LCD_4_BIT_T *lcd, uint8 command)
{
    Std_ReturnType ret = E_OK;
    if(NULL == lcd){
        ret = E_NOT_OK;
    }
    else{
        ret = gpio_pin_write_logic(&(lcd->lcd_rs), GPIO_LOW);
        ret = LCD_SENT_4_BIT(lcd, (command >> 4));
        ret = LCD_SENT_4_BIT_ENABLE(lcd);
        ret = LCD_SENT_4_BIT(lcd, command);
        ret = LCD_SENT_4_BIT_ENABLE(lcd);
    }
    return ret;
}
Std_ReturnType LCD_4_BIT_SEND_CHR_DATA(const LCD_4_BIT_T *lcd, uint8 data)
{
    Std_ReturnType ret = E_OK;
    if(NULL == lcd){
        ret = E_NOT_OK;
    }
    else{
        ret = gpio_pin_write_logic(&(lcd->lcd_rs), GPIO_HIGH);
        ret = LCD_SENT_4_BIT(lcd, (data >> 4));
        ret = LCD_SENT_4_BIT_ENABLE(lcd);
        ret = LCD_SENT_4_BIT(lcd, data);
        ret = LCD_SENT_4_BIT_ENABLE(lcd);
    }
    return ret;
}
Std_ReturnType LCD_4_BIT_SEND_CHR_DATA_POS(const LCD_4_BIT_T *lcd, uint8 row, uint8 column, uint8 data)
{
    Std_ReturnType ret = E_OK;
    if(NULL == lcd){
        ret = E_NOT_OK;
    }
    else{
        ret = LCD_4BIT_SET_CURSOR_POS(lcd, row, column);
        ret = LCD_4_BIT_SEND_CHR_DATA(lcd, data);
    }
    return ret;
}
Std_ReturnType LCD_4_BIT_SEND_STRING(const LCD_4_BIT_T *lcd, uint8 *str)
{
    Std_ReturnType ret = E_OK;
    if((NULL == lcd) || (NULL == str)){
        ret = E_NOT_OK;
    }
    else{
        while(*str){
            ret = LCD_4_BIT_SEND_CHR_DATA(lcd, *str++);
        }
    }
    return ret;
}
Std_ReturnType LCD_4_BIT_SEND_STRING_POS(const LCD_4_BIT_T *lcd, uint8 row, uint8 column, uint8 *str)
{
    Std_ReturnType ret = E_OK;
    if((NULL == lcd) || (NULL == str)){
        ret = E_NOT_OK;
    }
    else{
        ret = LCD_4BIT_SET_CURSOR_POS(lcd, row, column);
        while(*str){
            ret = LCD_4_BIT_SEND_CHR_DATA(lcd, *str++);
        }
    }
    return ret;
}
Std_ReturnType LCD_4_BIT_SEND_CUSTOM_CHR(const LCD_4_BIT_T *lcd, uint8 row, uint8 column, uint8 chr[], uint8 mem_pos)
{
    Std_ReturnType ret = E_OK;
    uint8 counter = 0;
    if(NULL == lcd){
        ret = E_NOT_OK;
    }
    else{
        ret = LCD_4_BIT_SEND_COMMAND(lcd, CGRAM_START + (mem_pos * 8));
        for(counter = 0; counter < 8; counter++){
            ret = LCD_4_BIT_SEND_CHR_DATA(lcd, chr[counter]);
        }
        ret = LCD_4_BIT_SEND_CHR_DATA_POS(lcd, row, column, mem_pos);
    }
    return ret;
}


/*LCD_8_BIT_INTERFACE*/


Std_ReturnType LCD_8_BIT_INIT(const LCD_8_BIT_T *lcd)
{
    Std_ReturnType ret = E_OK;
    uint8 DATA_COUNTER_LCD = 0;
    if(NULL == lcd){
        ret = E_NOT_OK;
    }
    else{
        __delay_ms(50);
        ret = gpio_pin_initialize(&(lcd->lcd_rs));
        ret = gpio_pin_initialize(&(lcd->lcd_e));
        for(DATA_COUNTER_LCD = 0; DATA_COUNTER_LCD < 8; DATA_COUNTER_LCD++){
            ret = gpio_pin_initialize(&(lcd->lcd_data[DATA_COUNTER_LCD]));
        }
        ret = LCD_8_BIT_SEND_COMMAND(lcd, DISPLAY_ON_8_BIT_2_LINE_5X8_FONT);
        __delay_ms(1);
        ret = LCD_8_BIT_SEND_COMMAND(lcd, DISPLAY_ON_CURSOR_OFF_BLINK_OFF);
        __delay_ms(1);
        ret = LCD_8_BIT_SEND_COMMAND(lcd, CLEAR_DISPLAY);
        __delay_ms(1);
        ret = LCD_8_BIT_SEND_COMMAND(lcd, DISPLAY_ON_INCREAMENT_NO_SHIFT_DISPLAY);
        

        

    }
    return ret;  
}
Std_ReturnType LCD_8_BIT_SEND_COMMAND(const LCD_8_BIT_T *lcd, uint8 command)
{
    Std_ReturnType ret = E_OK;    
    uint8 DATA_COUNTER_LCD = 0;
    if(NULL == lcd){
        ret = E_NOT_OK;
    }
    else{
        ret = gpio_pin_write_logic(&(lcd->lcd_rs), GPIO_LOW);
        for(DATA_COUNTER_LCD = 0; DATA_COUNTER_LCD < 8; DATA_COUNTER_LCD++){
            ret = gpio_pin_write_logic(&(lcd->lcd_data[DATA_COUNTER_LCD]), (command >> DATA_COUNTER_LCD) & (uint8)0x01);
        }
        ret = LCD_SENT_8_BIT_ENABLE(lcd);

    }
    return ret;   
}
Std_ReturnType LCD_8_BIT_SEND_CHR_DATA(const LCD_8_BIT_T *lcd, uint8 data)
{
    Std_ReturnType ret = E_OK;    
    uint8 DATA_COUNTER_LCD = 0;
    if(NULL == lcd){
        ret = E_NOT_OK;
    }
    else{
        ret = gpio_pin_write_logic(&(lcd->lcd_rs), GPIO_HIGH);
        for(DATA_COUNTER_LCD = 0; DATA_COUNTER_LCD < 8; ++DATA_COUNTER_LCD){
            ret = gpio_pin_write_logic(&(lcd->lcd_data[DATA_COUNTER_LCD]), (data >> DATA_COUNTER_LCD) & (uint8)0x01);
        }
        ret = LCD_SENT_8_BIT_ENABLE(lcd);
    }
    return ret;
}
Std_ReturnType LCD_8_BIT_SEND_CHR_DATA_POS(const LCD_8_BIT_T *lcd, uint8 row, uint8 column, uint8 data)
{
    Std_ReturnType ret = E_OK;
    if(NULL == lcd){
        ret = E_NOT_OK;
    }
    else{
        ret = LCD_8BIT_SET_CURSOR_POS(lcd, row, column);
        ret = LCD_8_BIT_SEND_CHR_DATA(lcd, data);
    }
    return ret;
}
Std_ReturnType LCD_8_BIT_SEND_STRING(const LCD_8_BIT_T *lcd, uint8 *str)
{
    Std_ReturnType ret = E_OK;
    if((NULL == lcd) || (NULL == str)){
        ret = E_NOT_OK;
    }
    else{
        while(*str != '\0'){
            ret = LCD_8_BIT_SEND_CHR_DATA(lcd, *str++);
        }
    }
    return ret;
}
Std_ReturnType LCD_8_BIT_SEND_STRING_POS(const LCD_8_BIT_T *lcd, uint8 row, uint8 column, uint8 *str)
{
    Std_ReturnType ret = E_OK;
    if((NULL == lcd) || (NULL == str)){
        ret = E_NOT_OK;
    }
    else{
        ret = LCD_8BIT_SET_CURSOR_POS(lcd, row, column);
        while(*str != '\0'){
            ret = LCD_8_BIT_SEND_CHR_DATA(lcd, *str++);
        }
    }
    return ret;
}
Std_ReturnType LCD_8_BIT_SEND_CUSTOM_CHR(const LCD_8_BIT_T *lcd, uint8 row, uint8 column, uint8 chr[], uint8 mem_pos)
{
    Std_ReturnType ret = E_OK;
    uint8 counter = 0;
    if(NULL == lcd){
        ret = E_NOT_OK;
    }
    else{
        ret = LCD_8_BIT_SEND_COMMAND(lcd, CGRAM_START + (mem_pos * 8));
        for(counter = 0; counter < 8; counter++){
            ret = LCD_8_BIT_SEND_CHR_DATA(lcd, chr[counter]);
        }
        ret = LCD_8_BIT_SEND_CHR_DATA_POS(lcd, row, column, mem_pos);
    }
    return ret; 
}



Std_ReturnType CONVERT_BYTE_TO_STRING(uint8 value, uint8 *str){

    Std_ReturnType ret = E_OK;
    if(NULL == str){
        ret = E_NOT_OK;
    }
    else{
        memset((char *)str, '\0', 4); // 2^8 = 256 -> 3 number + NULL Terminator
        sprintf(str, "%i", value);   
    }
    return ret; 
}
Std_ReturnType CONVERT_SHORT_TO_STRING(uint16 value, uint8 *str){
    Std_ReturnType ret = E_OK;
    uint8 Temp_string[6] = {0};
    uint8 Data_Counter = 0;
    if(NULL == str){
        ret = E_NOT_OK;
    }
    else{
        memset(str, ' ', 5); // 2^16 = ... -> 5 number + NULL Terminator
        str[5] = '\0';
        sprintf((char *)Temp_string, "%i", value);
        while(Temp_string[Data_Counter] != '\0'){
            str[Data_Counter] = Temp_string[Data_Counter];
            Data_Counter++;
        }
    }
    return ret; 
}
Std_ReturnType CONVERT_INT_TO_STRING(uint32 value, uint8 *str){
    Std_ReturnType ret = E_OK;
    if(NULL == str){
        ret = E_NOT_OK;
    }
    else{
        memset((char *)str, '\0', 11); // 2^32 = ... -> 10 number + NULL Terminator
        sprintf(str, "%i", value);   
    }
    return ret; 
}


static Std_ReturnType LCD_SENT_4_BIT(const LCD_4_BIT_T *lcd, uint8 _data_command){
    Std_ReturnType ret = E_OK;
    ret = gpio_pin_write_logic(&(lcd->lcd_data[0]), (_data_command >> 0) & (uint8)0x01);
    ret = gpio_pin_write_logic(&(lcd->lcd_data[1]), (_data_command >> 1) & (uint8)0x01);
    ret = gpio_pin_write_logic(&(lcd->lcd_data[2]), (_data_command >> 2) & (uint8)0x01);
    ret = gpio_pin_write_logic(&(lcd->lcd_data[3]), (_data_command >> 3) & (uint8)0x01);
    return ret;
}


static Std_ReturnType LCD_SENT_4_BIT_ENABLE(const LCD_4_BIT_T *lcd){
    Std_ReturnType ret = E_OK;
    ret = gpio_pin_write_logic(&(lcd->lcd_e), GPIO_HIGH);
    __delay_us(5);
    ret = gpio_pin_write_logic(&(lcd->lcd_e), GPIO_LOW);
    return ret;
}

static Std_ReturnType LCD_SENT_8_BIT_ENABLE(const LCD_8_BIT_T *lcd){
    Std_ReturnType ret = E_OK;
    ret = gpio_pin_write_logic(&(lcd->lcd_e), GPIO_HIGH);
    __delay_us(5);
    ret = gpio_pin_write_logic(&(lcd->lcd_e), GPIO_LOW);
    return ret;
}

static Std_ReturnType LCD_8BIT_SET_CURSOR_POS(const LCD_8_BIT_T *lcd, uint8 row, uint8 column){
    Std_ReturnType ret = E_OK;
    column--;
    switch(row){
        case ROW_1: ret = LCD_8_BIT_SEND_COMMAND(lcd, (0x80 + column)); break;
        case ROW_2: ret = LCD_8_BIT_SEND_COMMAND(lcd, (0xC0 + column)); break;
        case ROW_3: ret = LCD_8_BIT_SEND_COMMAND(lcd, (0x94 + column)); break;
        case ROW_4: ret = LCD_8_BIT_SEND_COMMAND(lcd, (0xD4 + column)); break;
        default: ;
    }
    return ret;
}
static Std_ReturnType LCD_4BIT_SET_CURSOR_POS(const LCD_4_BIT_T *lcd, uint8 row, uint8 column){
    Std_ReturnType ret = E_OK;
    column--;
    switch(row){
        case ROW_1: ret = LCD_4_BIT_SEND_COMMAND(lcd, (0x80 + column)); break;
        case ROW_2: ret = LCD_4_BIT_SEND_COMMAND(lcd, (0xC0 + column)); break;
        case ROW_3: ret = LCD_4_BIT_SEND_COMMAND(lcd, (0x94 + column)); break;
        case ROW_4: ret = LCD_4_BIT_SEND_COMMAND(lcd, (0xD4 + column)); break;
        default: ;
    }
    return ret;
}