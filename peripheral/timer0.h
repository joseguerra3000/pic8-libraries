/* 
 * File:   timer0.h
 * Author: Jose Guerra Carmenate
 *
 * Created on 28 de enero de 2019, 0:43
 */

#ifndef _TIMER0_H
#define	_TIMER0_H

#include <xc.h>
#include <stdbool.h>
#include <stdint.h>


/******************************************************************************
 **************************** Section: Data types *****************************
 ******************************************************************************/

/**
 * @Description
 *  Clock sources selection enumeration
 *  This data type defines the different clock sources.
 **/
typedef enum {
    TMR0_CLOCK_SOURCE_INTERNAL               = 0,    // Clock source is the instruction clock = Fosc/4
    TMR0_CLOCK_SOURCE_EXTERNAL_FALLING_EDGE  = 0x20, // Clock source is the external input pin. Incement counter on falling edge (H to L)
    TMR0_CLOCK_SOURCE_EXTERNAL_RISING_EDGE   = 0x30  // Clock source is the external input pin. Incement counter on rising edge (L to H)
} TMR0_CLOCK_SOURCE;


/**
 * @Description
 *  Prescaler Values
 *  This macro defines the list of possible prescaler values.
 **/
typedef enum {
    TMR0_PRESCALER_VALUE_1    = 0x10,
    TMR0_PRESCALER_VALUE_2    = 0x00,
    TMR0_PRESCALER_VALUE_4    = 0x01,
    TMR0_PRESCALER_VALUE_8    = 0x02,
    TMR0_PRESCALER_VALUE_16   = 0x03,
    TMR0_PRESCALER_VALUE_32   = 0x04,
    TMR0_PRESCALER_VALUE_64   = 0x05,
    TMR0_PRESCALER_VALUE_128  = 0x06,
    TMR0_PRESCALER_VALUE_256  = 0x07,
} TMR0_PRESCALER;


#ifdef	__cplusplus
extern "C" {
#endif

/******************************************************************************
 ************************ Section: API Implementations ************************
 ******************************************************************************/

// General setup functions
    
  /**
  @Summary
   Configure Timer0 Clock source and edge for counter increment.

  @Description
   Configure Timer0 Clock source and the Edge used for counter increment.

  @Preconditions
   None
  
  @Param
    - source: Specify the Clock Source to use. See TMR0_CLOCK_SOURCE enums for details
   
  @Returns
    None

  @Comment
    None

  @Example
    <code>
    
    </code>
  */
#define TIMER0_ClockSourceSelect( source )                                          \
             do{                                                                    \
                OPTION_REGbits.T0CS = ((source)>>_OPTION_REG_T0CS_POSITION)&0x01;   \
                OPTION_REGbits.T0SE = ((source)>>_OPTION_REG_T0SE_POSITION)&0x01;   \
               }while(0)

    
  /**
  @Summary
   Configure Timer0 prescaler.

  @Description
   This macro configure Timer0 prescaler.

  @Preconditions
   None
  
  @Param
    - prescaler: Specify the Timer0 Prescaler to set. See TMR0_PRESCALER enums for details.

  @Returns
    None

  @Comment
    None

  @Example
    <code>
    
    </code>
  */
#define TIMER0_PrescalerSelect( prescaler )                                     \
         do{                                                                    \
            CLRWDT();                                                           \
            TMR0 = 0;                                                           \
            OPTION_REGbits.PSA = ((prescaler)>>_OPTION_REG_PSA_POSITION)&0x01;  \
            OPTION_REGbits.PS = (prescaler) & _OPTION_REG_PS_MASK;              \
           }while(0)

    
    // Counter Functions
    
    
  /**
  @Summary
   Clear the Timer0 counter register.

  @Description
   Clear the Timer0 counter register.

  @Preconditions
   None
  
  @Param
   None
  
  @Returns
    None

  @Comment
    None

  @Example
    <code>
    
    </code>
  */
#define TIMER0_CounterClear() do{TMR0 = 0;}while(0)


  /**
  @Summary
   Set the Timer0 counter register value.

  @Description
   Set the Timer0 counter register value.

  @Preconditions
   None
  
  @Param
   uint8_t - value to be load on Timer0 counter register
  
  @Returns
    None

  @Comment
    None

  @Example
    <code>
    
    </code>
  */
#define TIMER0_CounterSet( value ) do{ TMR0 = (value); }while(0)

 /**
  @Summary
   Get the Timer0 counter register value.

  @Description
   Get the Timer0 counter register value.

  @Preconditions
    None
  
  @Param
    None
  
  @Returns
    None

  @Comment
    None

  @Example
    <code>
    
    </code>
  */
#define TIMER0_CounterGet() (TMR0)

#ifdef	__cplusplus
}
#endif

#endif	/* _TIMER0_H */

