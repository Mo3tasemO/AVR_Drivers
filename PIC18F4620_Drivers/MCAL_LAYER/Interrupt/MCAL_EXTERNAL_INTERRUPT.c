/* 
 * File:   MCAL_EXTERNAL_INTERRUPT.c
 * Author: Moata
 *
 * Created on February 21, 2026, 10:38 PM
 */

#include "MCAL_EXTERNAL_INTERRUPT.h"


static INTERRUPT_HANDLER INT0_INTERRUPT_HANDLER = NULL;
static INTERRUPT_HANDLER INT1_INTERRUPT_HANDLER = NULL;
static INTERRUPT_HANDLER INT2_INTERRUPT_HANDLER = NULL;

static INTERRUPT_HANDLER RB4_INTERRUPT_HANDLER_HIGH = NULL;
static INTERRUPT_HANDLER RB4_INTERRUPT_HANDLER_LOW = NULL;
static INTERRUPT_HANDLER RB5_INTERRUPT_HANDLER_HIGH = NULL;
static INTERRUPT_HANDLER RB5_INTERRUPT_HANDLER_LOW = NULL;
static INTERRUPT_HANDLER RB6_INTERRUPT_HANDLER_HIGH = NULL;
static INTERRUPT_HANDLER RB6_INTERRUPT_HANDLER_LOW = NULL;
static INTERRUPT_HANDLER RB7_INTERRUPT_HANDLER_HIGH = NULL;
static INTERRUPT_HANDLER RB7_INTERRUPT_HANDLER_LOW = NULL;

static Std_ReturnType INTERRUPT_INTx_ENABLE(const interrupt_INTx_t *interrupt_obj);
static Std_ReturnType INTERRUPT_INTx_DISABLE(const interrupt_INTx_t *interrupt_obj);
static Std_ReturnType INTERRUPT_INTx_PRIORITY_INIT(const interrupt_INTx_t *interrupt_obj);
static Std_ReturnType INTERRUPT_INTx_EDGE_INIT(const interrupt_INTx_t *interrupt_obj);
static Std_ReturnType INTERRUPT_INTx_PIN_INIT(const interrupt_INTx_t *interrupt_obj);
static Std_ReturnType INTERRUPT_INTx_CLEAR_FLAG(const interrupt_INTx_t *interrupt_obj);


static Std_ReturnType INT0_SET_INTERRUPT_HANDLER(void (*INTERRUPT_HANDLER)(void));
static Std_ReturnType INT1_SET_INTERRUPT_HANDLER(void (*INTERRUPT_HANDLER)(void));
static Std_ReturnType INT2_SET_INTERRUPT_HANDLER(void (*INTERRUPT_HANDLER)(void));
static Std_ReturnType INTERRUPT_INTx_SET_INTERRUPT_HANDLER(const interrupt_INTx_t *interrupt_obj);



static Std_ReturnType INTERRUPT_RBx_ENABLE(const interrupt_RBx_t *interrupt_obj);
static Std_ReturnType INTERRUPT_RBx_DISABLE(const interrupt_RBx_t *interrupt_obj);
static Std_ReturnType INTERRUPT_RBx_PRIORITY_INIT(const interrupt_RBx_t *interrupt_obj);
static Std_ReturnType INTERRUPT_RBx_PIN_INIT(const interrupt_RBx_t *interrupt_obj);






void INT0_ISR(void){
    /* The Flag of INT0 Must be Cleared*/
    EXTERNAL_INTERRUPT_INT0_FLAG_CLEAR();
    /*Check The Interrupt Handler Pointer To Function if it is equal to address of the Application Interrupt handler
     And It callback the function gets called every time this ISR executes*/
    if(INT0_INTERRUPT_HANDLER){
        INT0_INTERRUPT_HANDLER();
    }
}


void INT1_ISR(void){
    /* The Flag of INT1 Must be Cleared*/
    EXTERNAL_INTERRUPT_INT1_FLAG_CLEAR();
    /*Check The Interrupt Handler Pointer To Function if it is equal to address of the Application Interrupt handler
     And It callback the function gets called every time this ISR executes*/
    if(INT1_INTERRUPT_HANDLER){
        INT1_INTERRUPT_HANDLER();
    }
}

void INT2_ISR(void){
    /* The Flag of INT2 Must be Cleared*/
    EXTERNAL_INTERRUPT_INT2_FLAG_CLEAR();
    /*Check The Interrupt Handler Pointer To Function if it is equal to address of the Application Interrupt handler
     And It callback the function gets called every time this ISR executes*/
    if(INT2_INTERRUPT_HANDLER){
        INT2_INTERRUPT_HANDLER();
    }
}
void RB4_ISR(uint8 RBx_Source){
    /* The Flag of ON Change Must be Cleared*/
    EXTERNAL_INTERRUPT_ON_CHANGE_FLAG_DISABLE();
    /*Check The Interrupt Handler Pointer To Function if it is equal to address of the Application Interrupt handler
     And It callback the function gets called every time this ISR executes*/
    if(1 == RBx_Source){
        if(RB4_INTERRUPT_HANDLER_HIGH){
            RB4_INTERRUPT_HANDLER_HIGH();
        }
        else{/*Nothing*/}
    }
    else if(0 == RBx_Source){
        if(RB4_INTERRUPT_HANDLER_LOW){
            RB4_INTERRUPT_HANDLER_LOW();
        }
        else{/*Nothing*/}
    }
    else{
        /*Nothing*/
    }
}

void RB5_ISR(uint8 RBx_Source){
    /* The Flag of ON Change Must be Cleared*/
    EXTERNAL_INTERRUPT_ON_CHANGE_FLAG_DISABLE();
    /*Check The Interrupt Handler Pointer To Function if it is equal to address of the Application Interrupt handler
     And It callback the function gets called every time this ISR executes*/
    if(1 == RBx_Source){
        if(RB5_INTERRUPT_HANDLER_HIGH){
            RB5_INTERRUPT_HANDLER_HIGH();
        }
        else{/*Nothing*/}
    }
    else if(0 == RBx_Source){
        if(RB5_INTERRUPT_HANDLER_LOW){
            RB5_INTERRUPT_HANDLER_LOW();
        }
        else{/*Nothing*/}
    }
    else{
        /*Nothing*/
    }
}

void RB6_ISR(uint8 RBx_Source){
    /* The Flag of ON Change Must be Cleared*/
    EXTERNAL_INTERRUPT_ON_CHANGE_FLAG_DISABLE();
    /*Check The Interrupt Handler Pointer To Function if it is equal to address of the Application Interrupt handler
     And It callback the function gets called every time this ISR executes*/
    if(1 == RBx_Source){
        if(RB6_INTERRUPT_HANDLER_HIGH){
            RB6_INTERRUPT_HANDLER_HIGH();
        }
        else{/*Nothing*/}
    }
    else if(0 == RBx_Source){
        if(RB6_INTERRUPT_HANDLER_LOW){
            RB6_INTERRUPT_HANDLER_LOW();
        }
        else{/*Nothing*/}
    }
    else{
        /*Nothing*/
    }
}

void RB7_ISR(uint8 RBx_Source){
    /* The Flag of ON Change Must be Cleared*/
    EXTERNAL_INTERRUPT_ON_CHANGE_FLAG_DISABLE();
    /*Check The Interrupt Handler Pointer To Function if it is equal to address of the Application Interrupt handler
     And It callback the function gets called every time this ISR executes*/
    if(1 == RBx_Source){
        if(RB7_INTERRUPT_HANDLER_HIGH){
            RB7_INTERRUPT_HANDLER_HIGH();
        }
        else{/*Nothing*/}
    }
    else if(0 == RBx_Source){
        if(RB7_INTERRUPT_HANDLER_LOW){
            RB7_INTERRUPT_HANDLER_LOW();
        }
        else{/*Nothing*/}
    }
    else{
        /*Nothing*/
    }
}


/**
 * 
 * @param interrupt_obj
 * @return 
 */
Std_ReturnType INTERRUPT_INTx_INIT(const interrupt_INTx_t *interrupt_obj){
    Std_ReturnType ret = E_OK;
    if(NULL == interrupt_obj){
        ret = E_NOT_OK;
    }
    else{                   /* The purpose of | bitwise or is if one function fail*/
        /* Disable External Interrupt*/
        ret = INTERRUPT_INTx_DISABLE(interrupt_obj);
        /* Clear External Interrupt Flag*/
        ret |= INTERRUPT_INTx_CLEAR_FLAG(interrupt_obj);
        #ifdef INTERRUPT_PRIORITY_LEVELS_ENABLE
        /* Configure External Interrupt Priority*/
        ret |= INTERRUPT_INTx_PRIORITY_INIT(interrupt_obj);
        #endif
        /* Configure External Interrupt I/O Pin*/
        ret |= INTERRUPT_INTx_PIN_INIT(interrupt_obj);
        /* Configure Default Interrupt CallBack*/
        ret |= INTERRUPT_INTx_SET_INTERRUPT_HANDLER(interrupt_obj);
        /* Enable External Interrupt*/
        ret |= INTERRUPT_INTx_ENABLE(interrupt_obj);
    }
    return ret;
}
/**
 * 
 * @param interrupt_obj
 * @return 
 */
Std_ReturnType INTERRUPT_INTx_DEINIT(const interrupt_INTx_t *interrupt_obj){
    Std_ReturnType ret = E_OK;
    if(NULL == interrupt_obj){
        ret = E_NOT_OK;
    }
    else{
        /* Disable External Interrupt*/
        ret = INTERRUPT_INTx_DISABLE(interrupt_obj);
        /* Clear External Interrupt Flag*/
        ret |= INTERRUPT_INTx_CLEAR_FLAG(interrupt_obj);
    }
    return ret;
}
/**
 * 
 * @param interrupt_obj
 * @return 
 */
Std_ReturnType INTERRUPT_RBx_INIT(const interrupt_RBx_t *interrupt_obj){
    Std_ReturnType ret = E_OK;
    if(NULL == interrupt_obj){
        ret = E_NOT_OK;
    }
    else{
        /* Disable External Interrupt*/
        EXTERNAL_INTERRUPT_ON_CHANGE_DISABLE();
        /* Clear Flag*/
        EXTERNAL_INTERRUPT_ON_CHANGE_FLAG_DISABLE();
#ifdef INTERRUPT_PRIORITY_LEVELS_ENABLE
        ret = INTERRUPT_RBx_PRIORITY_INIT(interrupt_obj);
#else
                INTERRUPT_GlobalInterruptEnable();
                INTERRUPT_Peripheral_Interrupt_Enable();       
#endif
        ret = INTERRUPT_RBx_ENABLE(interrupt_obj);
    }
    return ret;
}
/**
 * 
 * @param interrupt_obj
 * @return 
 */
Std_ReturnType INTERRUPT_RBx_DEINIT(const interrupt_RBx_t *interrupt_obj){
    Std_ReturnType ret = E_OK;
    if(NULL == interrupt_obj){
        ret = E_NOT_OK;
    }
    else{
        /* Disable External Interrupt*/
        EXTERNAL_INTERRUPT_ON_CHANGE_DISABLE();
        /* Clear Flag*/
        EXTERNAL_INTERRUPT_ON_CHANGE_FLAG_DISABLE();
    }
    return ret;
}
/**
 * 
 * @param interrupt_obj
 * @return 
 */
static Std_ReturnType INTERRUPT_INTx_ENABLE(const interrupt_INTx_t *interrupt_obj){
    Std_ReturnType ret = E_OK;
    if(NULL == interrupt_obj){
        ret = E_NOT_OK;
    }
    else{
        switch(interrupt_obj->interrupt_source){
            case INTERRUPT_EXTERNAL_INT0: 
#ifdef INTERRUPT_PRIORITY_LEVELS_ENABLE
                INTERRUPT_GlobalInterruptHighEnable();
                INTERRUPT_Priority_Level_Enable();
#else
                INTERRUPT_GlobalInterruptEnable();
                INTERRUPT_Peripheral_Interrupt_Enable();       
#endif
                EXTERNAL_INTERRUPT_INT0_ENABLE();
                break;
            case INTERRUPT_EXTERNAL_INT1:
#ifdef INTERRUPT_PRIORITY_LEVELS_ENABLE
                INTERRUPT_Priority_Level_Enable();
                if(INTERRUPT_LOW_PRIORITY == interrupt_obj->interrupt_priority){
                    INTERRUPT_GlobalInterruptLowEnable();
                    EXTERNAL_INTERRUPT_INT1_PRIORITY_LOW();
                }
                else if(INTERRUPT_HIGH_PRIORITY == interrupt_obj->interrupt_priority){
                    INTERRUPT_GlobalInterruptHighEnable();
                    EXTERNAL_INTERRUPT_INT1_PRIORITY_HIGH();
                }
                else {/*Nothing*/}
#else
                INTERRUPT_GlobalInterruptEnable();
                INTERRUPT_Peripheral_Interrupt_Enable();       
#endif
                EXTERNAL_INTERRUPT_INT1_ENABLE(); 
                break;
            case INTERRUPT_EXTERNAL_INT2: 
#ifdef INTERRUPT_PRIORITY_LEVELS_ENABLE
                INTERRUPT_Priority_Level_Enable();
                if(INTERRUPT_LOW_PRIORITY == interrupt_obj->interrupt_priority){
                    INTERRUPT_GlobalInterruptLowEnable();
                    EXTERNAL_INTERRUPT_INT2_PRIORITY_LOW();
                }
                else if(INTERRUPT_HIGH_PRIORITY == interrupt_obj->interrupt_priority){
                    INTERRUPT_GlobalInterruptHighEnable();
                    EXTERNAL_INTERRUPT_INT2_PRIORITY_HIGH();
                }
                else {/*Nothing*/}
#else
                INTERRUPT_GlobalInterruptEnable();
                INTERRUPT_Peripheral_Interrupt_Enable();       
#endif
                EXTERNAL_INTERRUPT_INT2_ENABLE(); 
                break;
            default: ret = E_NOT_OK;
        }
    }
    return ret;
}
/**
 * 
 * @param interrupt_obj
 * @return 
 */
static Std_ReturnType INTERRUPT_INTx_DISABLE(const interrupt_INTx_t *interrupt_obj){
    Std_ReturnType ret = E_OK;
    if(NULL == interrupt_obj){
        ret = E_NOT_OK;
    }
    else{
         switch(interrupt_obj->interrupt_source){
            case INTERRUPT_EXTERNAL_INT0: 
                EXTERNAL_INTERRUPT_INT0_DISABLE(); 
                break;
            case INTERRUPT_EXTERNAL_INT1: 
                EXTERNAL_INTERRUPT_INT1_DISABLE(); 
                break;
            case INTERRUPT_EXTERNAL_INT2: 
                EXTERNAL_INTERRUPT_INT2_DISABLE(); 
                break;
            default: ret = E_NOT_OK;
        }
    }
    return ret;
}
/**
 * 
 * @param interrupt_obj
 * @return 
 */
#ifdef INTERRUPT_PRIORITY_LEVELS_ENABLE
static Std_ReturnType INTERRUPT_INTx_PRIORITY_INIT(const interrupt_INTx_t *interrupt_obj){
    Std_ReturnType ret = E_OK;
    if(NULL == interrupt_obj){
        ret = E_NOT_OK;
    }
    else{
         switch(interrupt_obj->interrupt_source){
            case INTERRUPT_EXTERNAL_INT1: 
                if(INTERRUPT_LOW_PRIORITY == interrupt_obj->interrupt_priority){
                    EXTERNAL_INTERRUPT_INT1_PRIORITY_LOW();
                }
                else if(INTERRUPT_HIGH_PRIORITY == interrupt_obj->interrupt_priority){
                    EXTERNAL_INTERRUPT_INT1_PRIORITY_HIGH();
                }
                else {/*Nothing*/}
                break;
            case INTERRUPT_EXTERNAL_INT2: 
                if(INTERRUPT_LOW_PRIORITY == interrupt_obj->interrupt_priority){
                    EXTERNAL_INTERRUPT_INT2_PRIORITY_LOW();
                }
                else if(INTERRUPT_HIGH_PRIORITY == interrupt_obj->interrupt_priority){
                    EXTERNAL_INTERRUPT_INT2_PRIORITY_HIGH();
                }
                else {/*Nothing*/}
                break;
            default: ret = E_NOT_OK;
        }
    }
    return ret;
}
#endif

/**
 * 
 * @param interrupt_obj
 * @return 
 */
static Std_ReturnType INTERRUPT_INTx_EDGE_INIT(const interrupt_INTx_t *interrupt_obj){
    Std_ReturnType ret = E_OK;
    if(NULL == interrupt_obj){
        ret = E_NOT_OK;
    }
    else{
         switch(interrupt_obj->interrupt_edge){
            case INTERRUPT_EXTERNAL_INT0: 
                if(INTERRUPT_FALLING_EDGE == interrupt_obj->interrupt_edge){
                    EXTERNAL_INTERRUPT_INT0_FALLING_EDGE_ENABLE();
                }
                else if(INTERRUPT_RISING_EDGE == interrupt_obj->interrupt_edge){
                    EXTERNAL_INTERRUPT_INT0_RISING_EDGE_ENABLE();
                }
                else {/*Nothing*/}
                break;
             case INTERRUPT_EXTERNAL_INT1: 
                if(INTERRUPT_FALLING_EDGE == interrupt_obj->interrupt_edge){
                    EXTERNAL_INTERRUPT_INT1_FALLING_EDGE_ENABLE();
                }
                else if(INTERRUPT_RISING_EDGE == interrupt_obj->interrupt_edge){
                    EXTERNAL_INTERRUPT_INT1_RISING_EDGE_ENABLE();
                }
                else {/*Nothing*/}
                break;
            case INTERRUPT_EXTERNAL_INT2: 
                if(INTERRUPT_FALLING_EDGE == interrupt_obj->interrupt_edge){
                    EXTERNAL_INTERRUPT_INT2_FALLING_EDGE_ENABLE();

                }
                else if(INTERRUPT_RISING_EDGE == interrupt_obj->interrupt_edge){
                    EXTERNAL_INTERRUPT_INT2_RISING_EDGE_ENABLE();
                }
                else {/*Nothing*/}
                break;
            default: ret = E_NOT_OK;
        }
    }
    return ret;
}

/**
 * 
 * @param interrupt_obj
 * @return 
 */
static Std_ReturnType INTERRUPT_INTx_PIN_INIT(const interrupt_INTx_t *interrupt_obj){
    Std_ReturnType ret = E_OK;
    if(NULL == interrupt_obj){
        ret = E_NOT_OK;
    }
    else{
        gpio_pin_initialize(&(interrupt_obj->interrupt_pin));
    }
    return ret;
}

static Std_ReturnType INTERRUPT_INTx_CLEAR_FLAG(const interrupt_INTx_t *interrupt_obj){
    Std_ReturnType ret = E_OK;
    if(NULL == interrupt_obj){
        ret = E_NOT_OK;
    }
    else{
        switch(interrupt_obj->interrupt_source){
            case INTERRUPT_EXTERNAL_INT0: 
                EXTERNAL_INTERRUPT_INT0_FLAG_CLEAR();
                break;
            case INTERRUPT_EXTERNAL_INT1: 
                EXTERNAL_INTERRUPT_INT1_FLAG_CLEAR();
                break;
            case INTERRUPT_EXTERNAL_INT2: 
                EXTERNAL_INTERRUPT_INT2_FLAG_CLEAR();
                break;
            default: ret = E_NOT_OK;
        }
    }
    return ret;
}
/**
 * 
 * @param interrupt_obj
 * @return 
 */
static Std_ReturnType INTERRUPT_RBx_ENABLE(const interrupt_RBx_t *interrupt_obj){
    Std_ReturnType ret = E_OK;
    if(NULL == interrupt_obj){
        ret = E_NOT_OK;
    }
    else{
    ret = gpio_pin_initialize(&(interrupt_obj->interrupt_pin));
    switch(interrupt_obj->interrupt_pin.pin){
        case GPIO_PIN4:
            RB4_INTERRUPT_HANDLER_HIGH = interrupt_obj->INTERRUPT_HANDLER_HIGH;
            RB4_INTERRUPT_HANDLER_LOW = interrupt_obj->INTERRUPT_HANDLER_LOW;
            break;
        case GPIO_PIN5:
            RB5_INTERRUPT_HANDLER_HIGH = interrupt_obj->INTERRUPT_HANDLER_HIGH;
            RB5_INTERRUPT_HANDLER_LOW = interrupt_obj->INTERRUPT_HANDLER_LOW;
            break;
        case GPIO_PIN6:
            RB6_INTERRUPT_HANDLER_HIGH = interrupt_obj->INTERRUPT_HANDLER_HIGH;
            RB6_INTERRUPT_HANDLER_LOW = interrupt_obj->INTERRUPT_HANDLER_LOW;
            break;
        case GPIO_PIN7:
            RB7_INTERRUPT_HANDLER_HIGH = interrupt_obj->INTERRUPT_HANDLER_HIGH;
            RB7_INTERRUPT_HANDLER_LOW = interrupt_obj->INTERRUPT_HANDLER_LOW;
            break;
        default:
            ret = E_NOT_OK;
        }
        EXTERNAL_INTERRUPT_ON_CHANGE_ENABLE();
    }
    return ret;
}
/**
 * 
 * @param interrupt_obj
 * @return 
 */
static Std_ReturnType INTERRUPT_RBx_DISABLE(const interrupt_RBx_t *interrupt_obj){
    Std_ReturnType ret = E_OK;
    if(NULL == interrupt_obj){
        ret = E_NOT_OK;
    }
    else{
        /* Disable External Interrupt*/
        EXTERNAL_INTERRUPT_ON_CHANGE_DISABLE();
        /* Clear Flag*/
        EXTERNAL_INTERRUPT_ON_CHANGE_FLAG_DISABLE();
    }
    return ret;   
}
/**
 * 
 * @param interrupt_obj
 * @return 
 */
#ifdef INTERRUPT_PRIORITY_LEVELS_ENABLE
static Std_ReturnType INTERRUPT_RBx_PRIORITY_INIT(const interrupt_RBx_t *interrupt_obj){
    Std_ReturnType ret = E_OK;
    if(NULL == interrupt_obj){
        ret = E_NOT_OK;
    }
    else{
        INTERRUPT_Priority_Level_Enable();
        if(INTERRUPT_LOW_PRIORITY == interrupt_obj->interrupt_priority){
            INTERRUPT_GlobalInterruptLowEnable();
            EXTERNAL_INTERRUPT_ON_CHANGE_LOW_PRIORITY();
        }
        else if(INTERRUPT_HIGH_PRIORITY == interrupt_obj->interrupt_priority){
            INTERRUPT_GlobalInterruptHighEnable();
            EXTERNAL_INTERRUPT_ON_CHANGE_HIGH_PRIORITY();
        }
        else {/*Nothing*/}
    }
    return ret;    
}
#endif
/**
 * 
 * @param interrupt_obj
 * @return 
 */
static Std_ReturnType INTERRUPT_RBx_PIN_INIT(const interrupt_RBx_t *interrupt_obj){
    Std_ReturnType ret = E_OK;
    if(NULL == interrupt_obj){
        ret = E_NOT_OK;
    }
    else{
        ret = gpio_pin_initialize(&(interrupt_obj->interrupt_pin));
    }
    return ret;    
}
/**
 * 
 * @param interrupt_obj
 * @return 
 */
static Std_ReturnType INT0_SET_INTERRUPT_HANDLER(void (*INTERRUPT_HANDLER)(void)){
    Std_ReturnType ret = E_OK;
    if(NULL == INTERRUPT_HANDLER){
        ret = E_NOT_OK;
    }
    else{
        INT0_INTERRUPT_HANDLER = INTERRUPT_HANDLER;
    }
    return ret;  
}
/**
 * 
 * @param interrupt_obj
 * @return 
 */
static Std_ReturnType INT1_SET_INTERRUPT_HANDLER(void (*INTERRUPT_HANDLER)(void)){
    Std_ReturnType ret = E_OK;
    if(NULL == INTERRUPT_HANDLER){
        ret = E_NOT_OK;
    }
    else{
        INT1_INTERRUPT_HANDLER = INTERRUPT_HANDLER;  
    }
    return ret;  
}
/**
 * 
 * @param interrupt_obj
 * @return 
 */
static Std_ReturnType INT2_SET_INTERRUPT_HANDLER(void (*INTERRUPT_HANDLER)(void)){
    Std_ReturnType ret = E_OK;
    if(NULL == INTERRUPT_HANDLER){
        ret = E_NOT_OK;
    }
    else{
        INT2_INTERRUPT_HANDLER = INTERRUPT_HANDLER;        
    }
    return ret;      
}
/**
 * 
 * @param interrupt_obj
 * @return 
 */
static Std_ReturnType INTERRUPT_INTx_SET_INTERRUPT_HANDLER(const interrupt_INTx_t *interrupt_obj){
    Std_ReturnType ret = E_OK;
    if(NULL == interrupt_obj){
        ret = E_NOT_OK;
    }
    else{
        switch(interrupt_obj->interrupt_source){
            case INTERRUPT_EXTERNAL_INT0: 
                ret = INT0_SET_INTERRUPT_HANDLER(interrupt_obj->INTERRUPT_HANDLER);
                break;
            case INTERRUPT_EXTERNAL_INT1: 
                ret = INT1_SET_INTERRUPT_HANDLER(interrupt_obj->INTERRUPT_HANDLER);
                break;
            case INTERRUPT_EXTERNAL_INT2:
                ret = INT2_SET_INTERRUPT_HANDLER(interrupt_obj->INTERRUPT_HANDLER);
                break;
            default: ret = E_NOT_OK;
        }
    }
    return ret;    
}

