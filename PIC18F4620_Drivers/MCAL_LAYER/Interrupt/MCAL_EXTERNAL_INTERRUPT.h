/* 
 * File:   MCAL_EXTERNAL_INTERRUPT.h
 * Author: Moata
 *
 * Created on February 21, 2026, 10:38 PM
 */

#ifndef MCAL_EXTERNAL_INTERRUPT_H
#define	MCAL_EXTERNAL_INTERRUPT_H



// Section: Includes
#include "MCAL_INTERRUPT_CONFIG.h"



// Section: Data Type Declarations
typedef void (*INTERRUPT_HANDLER)(void);

typedef enum {
    INTERRUPT_EXTERNAL_INT0 = 0,
    INTERRUPT_EXTERNAL_INT1,
    INTERRUPT_EXTERNAL_INT2,
}interrupt_INTx_source;
typedef enum {
    INTERRUPT_FALLING_EDGE = 0,
    INTERRUPT_RISING_EDGE,
}interrupt_edge;
typedef struct {
    void (* INTERRUPT_HANDLER)(void);
    pin_config_t interrupt_pin;
    interrupt_priority_t interrupt_priority;
    interrupt_INTx_source interrupt_source;
    interrupt_edge interrupt_edge;
}interrupt_INTx_t;
typedef struct {
    void (* INTERRUPT_HANDLER_HIGH)(void);
    void (* INTERRUPT_HANDLER_LOW)(void);
    pin_config_t interrupt_pin;
    interrupt_priority_t interrupt_priority;
}interrupt_RBx_t;

// Section: Macro Declarations

#ifdef EXTERNAL_INTERRUPT_INTx_FEATURE_ENABLE
/*Enable External Interrupt Enable*/
#define EXTERNAL_INTERRUPT_INT0_ENABLE()                (INTCONbits.INT0E = 1)
/*Disable External Interrupt Enable*/
#define EXTERNAL_INTERRUPT_INT0_DISABLE()               (INTCONbits.INT0E = 0)
/*Clear External Interrupt Flag*/
#define EXTERNAL_INTERRUPT_INT0_FLAG_CLEAR()            (INTCONbits.INT0F = 0)
/*Enable External Interrupt Rising Edge*/
#define EXTERNAL_INTERRUPT_INT0_RISING_EDGE_ENABLE()    (INTCON2bits.INTEDG0 = 1)
/*Enable External Interrupt Falling Flag*/
#define EXTERNAL_INTERRUPT_INT0_FALLING_EDGE_ENABLE()   (INTCON2bits.INTEDG0 = 0)

/*Enable External Interrupt Enable*/
#define EXTERNAL_INTERRUPT_INT1_ENABLE()                (INTCON3bits.INT1E = 1)
/*Disable External Interrupt Enable*/
#define EXTERNAL_INTERRUPT_INT1_DISABLE()               (INTCON3bits.INT1E = 0)
/*Clear External Interrupt Flag*/
#define EXTERNAL_INTERRUPT_INT1_FLAG_CLEAR()            (INTCON3bits.INT1F = 0)
/*Enable External Interrupt Rising Edge*/
#define EXTERNAL_INTERRUPT_INT1_RISING_EDGE_ENABLE()    (INTCON2bits.INTEDG1 = 1)
/*Enable External Interrupt Falling Flag*/
#define EXTERNAL_INTERRUPT_INT1_FALLING_EDGE_ENABLE()   (INTCON2bits.INTEDG1 = 0)

/*Enable External Interrupt Enable*/
#define EXTERNAL_INTERRUPT_INT2_ENABLE()                (INTCON3bits.INT2E = 1)
/*Disable External Interrupt Enable*/
#define EXTERNAL_INTERRUPT_INT2_DISABLE()               (INTCON3bits.INT2E = 0)
/*Clear External Interrupt Flag*/
#define EXTERNAL_INTERRUPT_INT2_FLAG_CLEAR()            (INTCON3bits.INT2F = 0)
/*Enable External Interrupt Rising Edge*/
#define EXTERNAL_INTERRUPT_INT2_RISING_EDGE_ENABLE()    (INTCON2bits.INTEDG2 = 1)
/*Enable External Interrupt Falling Flag*/
#define EXTERNAL_INTERRUPT_INT2_FALLING_EDGE_ENABLE()   (INTCON2bits.INTEDG2 = 0)

#ifdef INTERRUPT_PRIORITY_LEVELS_ENABLE
/*Enable External Interrupt High Priority*/
#define EXTERNAL_INTERRUPT_INT1_PRIORITY_HIGH()         (INTCON3bits.INT1IP = 1)
/*Disable External Interrupt Low Priority*/
#define EXTERNAL_INTERRUPT_INT1_PRIORITY_LOW()          (INTCON3bits.INT1IP = 0)
/*Enable External Interrupt High Priority*/
#define EXTERNAL_INTERRUPT_INT2_PRIORITY_HIGH()         (INTCON3bits.INT2IP = 1)
/*Disable External Interrupt Low Priority*/
#define EXTERNAL_INTERRUPT_INT2_PRIORITY_LOW()          (INTCON3bits.INT2IP = 0)
#endif


#endif

#ifdef EXTERNAL_INTERRUPT_ON_CHANGE_FEATURE_ENABLE


/*Enable External Interrupt On Change*/
#define EXTERNAL_INTERRUPT_ON_CHANGE_ENABLE()           (INTCONbits.RBIE = 1)
/*Disable External Interrupt On Change*/
#define EXTERNAL_INTERRUPT_ON_CHANGE_DISABLE()          (INTCONbits.RBIE = 0)
/*Enable External Interrupt On Change Flag*/
#define EXTERNAL_INTERRUPT_ON_CHANGE_FLAG_ENABLE()      (INTCONbits.RBIF = 1)
/*Disable External Interrupt On Change Flag*/
#define EXTERNAL_INTERRUPT_ON_CHANGE_FLAG_DISABLE()     (INTCONbits.RBIF = 0)


#ifdef INTERRUPT_PRIORITY_LEVELS_ENABLE

/*External Interrupt On Change HIGH Priority*/
#define EXTERNAL_INTERRUPT_ON_CHANGE_HIGH_PRIORITY()  (INTCON2bits.RBIP = 1)
/*External Interrupt On Change LOW Priority*/
#define EXTERNAL_INTERRUPT_ON_CHANGE_LOW_PRIORITY() (INTCON2bits.RBIP = 0)

#endif



#endif



// Section: Macro Functions Declarations
// Section: Function Declarations



/**
 * 
 * @param interrupt_obj
 * @return 
 */
Std_ReturnType INTERRUPT_INTx_INIT(const interrupt_INTx_t *interrupt_obj);
/**
 * 
 * @param interrupt_obj
 * @return 
 */
Std_ReturnType INTERRUPT_INTx_DEINIT(const interrupt_INTx_t *interrupt_obj);
/**
 * 
 * @param interrupt_obj
 * @return 
 */
Std_ReturnType INTERRUPT_RBx_INIT(const interrupt_RBx_t *interrupt_obj);
/**
 */
Std_ReturnType INTERRUPT_RBx_DEINIT(const interrupt_RBx_t *interrupt_obj);





#endif	/* MCAL_EXTERNAL_INTERRUPT_H */

