/* 
 * File:   timer2.h
 * Author: Jose Guerra Carmenate
 *
 * Created on 30 de enero de 2019, 2:28
 */

#ifndef _TIMER2_H
#define	_TIMER2_H

#include <stdbool.h>
#include <stdint.h>
#include <xc.h>

#ifdef TMR2

/******************************************************************************
 ****************************** Section: Macros *******************************
 ******************************************************************************/


/******************************************************************************
 **************************** Section: Data types *****************************
 ******************************************************************************/


/**
 * @Description
 *  Timer2 Prescaler Values
 *  This macro defines the list of possible prescaler values.
 **/
typedef enum {
    TMR2_PRESCALER_VALUE_1  = 0x00,
    TMR2_PRESCALER_VALUE_4  = 0x01,
    TMR2_PRESCALER_VALUE_16 = 0x02,
} TMR2_PRESCALER;

/**
 * @Description
 *  Timer2 Postscaler Values
 *  This macro defines the list of possible postscaler values.
 **/
typedef enum {
    TMR2_POSTSCALER_VALUE_1     = 0x00<<3,
    TMR2_POSTSCALER_VALUE_2     = 0x01<<3,
    TMR2_POSTSCALER_VALUE_3     = 0x02<<3,
    TMR2_POSTSCALER_VALUE_4     = 0x03<<3,
    TMR2_POSTSCALER_VALUE_5     = 0x04<<3,
    TMR2_POSTSCALER_VALUE_6     = 0x05<<3,
    TMR2_POSTSCALER_VALUE_7     = 0x06<<3,
    TMR2_POSTSCALER_VALUE_8     = 0x07<<3,
    TMR2_POSTSCALER_VALUE_9     = 0x08<<3,
    TMR2_POSTSCALER_VALUE_10    = 0x09<<3,
    TMR2_POSTSCALER_VALUE_11    = 0x0A<<3,
    TMR2_POSTSCALER_VALUE_12    = 0x0B<<3,
    TMR2_POSTSCALER_VALUE_13    = 0x0C<<3,
    TMR2_POSTSCALER_VALUE_14    = 0x0D<<3,
    TMR2_POSTSCALER_VALUE_15    = 0x0E<<3,
    TMR2_POSTSCALER_VALUE_16    = 0x0F<<3
} TMR2_POSTSCALER;


#ifdef	__cplusplus
extern "C" {
#endif

/******************************************************************************
 ************************ Section: API Implementations ************************
 ******************************************************************************/
// general setup functions

/**
  @Summary
   Inicialize Timer2.

  @Description
   Initialize Timer2

  @Preconditions
   None
  
  @Param 
     - prescaler : Timer2 prescaler to use. See TMR2_PRESCALER for details.
 
     - postscaler: Timer2 postscaler to use. See TMR2_POSTSCALER for details.
   
  @Returns
    None

  @Comment
    Modify T2CON register.

  @Example
    <code>
    
    </code>
  */
    #define TIMER2_Initialize( prescaler, postscaler )                          \
        do{                                                                     \
            T2CON = (T2CON & ~_T2CON_TMR2ON_MASK) | ( (prescaler) | (postscaler) );\
            }while(0)
    

/**
  @Summary
   Configure Timer2 Postscaler.

  @Description
   Configure Timer2 Postscaler.

  @Preconditions
   None
  
  @Param 
     - postscaler: Timer2 postscaler to use. See TMR2_POSTSCALER for details.
   
  @Returns
    None

  @Comment
    Modify T2CON register.

  @Example
    <code>
    
    </code>
  */
    #define TIMER2_PostscalerSelect( postscaler )                    \
    do{                                                             \
        T2CON = (T2CON & ~_T2CON_TOUTPS_MASK) | (postscaler );      \
        }while(0);
    
    /**
  @Summary
   Configure Timer2 Prescaler.

  @Description
   Configure Timer2 Prescaler.

  @Preconditions
   None
  
  @Param 
     - prescaler : Timer2 prescaler to use. See TMR2_PRESCALER for details.
   
  @Returns
    None

  @Comment
    Modify T2CON register.

  @Example
    <code>
    
    </code>
  */
    #define TIMER2_PrescalerSelect( prescaler )                     \
        do{                                                         \
            T2CON = (T2CON & ~_T2CON_T2CKPS_MASK) | (prescaler );   \
            }while(0);
 
 /**
  @Summary
   Enable Timer2.

  @Description
  Enable Timer2

  @Preconditions
   None
  
  @Param
    None
   
  @Returns
    None

  @Comment
    Modify TMR2ON bit from T2CON register

  @Example
    <code>
    
    </code>
  */
#define TIMER2_Start()      do{T2CONbits.TMR2ON = 1;}while(0)

 /**
  @Summary
   Disable Timer2.

  @Description
   Disable Timer2

  @Preconditions
   None
  
  @Param
    None
   
  @Returns
    None

  @Comment
    Modify TMR2ON bit from T2CON register

  @Example
    <code>
    
    </code>
  */
#define TIMER2_Stop()       do{T2CONbits.TMR2ON = 0;}while(0)

// Counter functions 
    
  /**
  @Summary
   Clear the Timer2 counter register.

  @Description
   Clear the Timer2 counter register.

  @Preconditions
   None
  
  @Param
   None
  
  @Returns
    None

  @Comment
    Modify TMR2 register

  @Example
    <code>
    
    </code>
  */
#define TIMER2_CounterClear() do{ TMR2 = 0; }while(0)
   
      
    
 /**
  @Summary
   Set the Timer2 counter register value.

  @Description
   Set the Timer2 counter register value.

  @Preconditions
   None
  
  @Param
   uint8_t - value to be load on Timer2 counter register
  
  @Returns
    None

  @Comment
    Modify TMR2 register

  @Example
    <code>
    
    </code>
  */
#define TIMER2_CounterSet( value ) do{ TMR2 = (value); } while(0)

    
     /**
  @Summary
   Get the Timer2 counter register value.

  @Description
   Get the Timer2 counter register value.

  @Preconditions
    None
  
  @Param
    None
  
  @Returns
      Return the value stored on TMR2 registers

  @Comment
    None

  @Example
    <code>
    
    </code>
  */
#define TIMER2_CounterGet() (TMR2)


 /**
  @Summary
   Get the Timer2 period register value.

  @Description
   Return the Timer2 period register value.

  @Preconditions
    None
  
  @Param
    None
  
  @Returns
      uint8_t - Return the value stored on PR2 registers

  @Comment
    None

  @Example
    <code>
    
    </code>
  */
#define TIMER2_PeriodGet() (PR2)

    
 /**
  @Summary
   Set the Timer2 period register value.

  @Description
   Set the Timer2 period register value.

  @Preconditions
   None
  
  @Param
   - value value to be load on Timer2 counter register
  
  @Returns
    None

  @Comment
    Modify PR2 register

  @Example
    <code>
    
    </code>
  */
#define TIMER2_PeriodSet( value ) do{ PR2 = (value); } while(0)


#ifdef	__cplusplus
}
#endif

#endif /* TMR2 */

#endif	/* _TIMER1_H */

