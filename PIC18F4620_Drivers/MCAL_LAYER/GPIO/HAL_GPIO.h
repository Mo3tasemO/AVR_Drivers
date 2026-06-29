/* 
 * File:   HAL_GPIO.h
 * Author: Moata
 *
 * Created on September 30, 2025, 6:28 PM
 */

#ifndef HAL_GPIO_H
#define	HAL_GPIO_H

#define _XTAL_FREQ 8000000UL



// Section: Includes
#include "../MCAL_STD_TYPES.h"
#include "../GPIO/HAL_GPIO_CFG.h"

// Section: Data Type Declarations

typedef enum{
    GPIO_LOW = 0,
    GPIO_HIGH
}logic_t;

typedef enum{
    GPIO_OUTPUT = 0,
    GPIO_INPUT
}direction_t;

typedef enum{
    PORTA_INDEX = 0,
    PORTB_INDEX,
    PORTC_INDEX,
    PORTD_INDEX,
    PORTE_INDEX
}port_index_t;

typedef enum{
    GPIO_PIN0 = 0,
    GPIO_PIN1,
    GPIO_PIN2,
    GPIO_PIN3,
    GPIO_PIN4,
    GPIO_PIN5,
    GPIO_PIN6,
    GPIO_PIN7,
}pin_index_t;

typedef struct{
    uint8 port : 3; // Due to we have a 5 ports only in mcu then in bin the 5 is : 0101 then take a first 3 bits only
    uint8 pin : 3; // Same as port
    uint8 direction : 1; // Here we have a 2 logics only if 0 or 1 then 1 bit only
    uint8 logic : 1; // Same as direction
}pin_config_t;


// Section: Macro Declarations

#define BIT_MASK    (uint8)1
#define GPIO_MAX_PIN_NUMBER 8
#define GPIO_MAX_PORT_NUMBER 5
#define TOGGLE_MASK          0xFF
// Section: Macro Functions Declarations


#define HW_REG8(_X)     (*(volatile Std_ReturnType *(_X)))

#define SET_BIT(REG,BIT_NUM)    (REG |= (BIT_MASK << BIT_NUM))
#define CLEAR_BIT(REG,BIT_NUM)    (REG &= ~(BIT_MASK << BIT_NUM))
#define TOGGLE_BIT(REG,BIT_NUM)    (REG ^= (BIT_MASK << BIT_NUM))
#define READ_BIT(REG,BIT_NUM)    ((REG >> BIT_NUM) & BIT_MASK)


// Section: Function Declarations
Std_ReturnType gpio_pin_set_direction(const pin_config_t *_pin_config);
Std_ReturnType gpio_pin_read_direction(const pin_config_t *_pin_config, direction_t *dir_status);
Std_ReturnType gpio_pin_write_logic(const pin_config_t *_pin_config, logic_t logic);
Std_ReturnType gpio_pin_read_logic(const pin_config_t *_pin_config, logic_t *logic);
Std_ReturnType gpio_pin_toggle(const pin_config_t *_pin_config);
Std_ReturnType gpio_pin_initialize(const pin_config_t *_pin_config);


Std_ReturnType gpio_port_set_direction(port_index_t port, uint8 direction);
Std_ReturnType gpio_port_read_direction(port_index_t port, uint8 *dir_status);
Std_ReturnType gpio_port_write_logic(port_index_t port, uint8 logic);
Std_ReturnType gpio_port_read_logic(port_index_t port, uint8 *logic);
Std_ReturnType gpio_port_toggle(port_index_t port); 


#endif	/* HAL_GPIO_H */

