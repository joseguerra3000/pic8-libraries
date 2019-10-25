/* 
 * File:   timer1.h
 * Author: Jose Guerra Carmenate
 *
 * Created on 29 de enero de 2019, 0:01
 */

#ifndef _TIMER1_H
#define	_TIMER1_H

#include <stdbool.h>
#include <stdint.h>
#include <xc.h>


/******************************************************************************
 ****************************** Section: Macros *******************************
 ******************************************************************************/

#define _TMR1_CLOCK_SOURCE_MASK          0x0E


/******************************************************************************
 **************************** Section: Data types *****************************
 ******************************************************************************/

/**
 * @Description
 *  Clock sources selection enumeration
 *  This data type defines the different clock sources.
 **/
typedef enum {
    TMR1_CLOCK_SOURCE_INTERNAL          = 0,     // Clock source is the internal clock = Fosc/4
    TMR1_CLOCK_SOURCE_EXTERNAL          = 0x06,  // Clock source is the external input pin T1CKI. Asynchronous Counter mode
    TMR1_CLOCK_SOURCE_EXTERNAL_SYNC     = 0x02,  // Clock source is the external input pin T1CKI. Synchronous Counter mode
    TMR1_CLOCK_SOURCE_LP_OSC            = 0x08,  // Use Low Power 32.768 kHz Clock (Only if OSC1 and OSC2 are free)
} TMR1_CLOCK_SOURCE;


/**
 * @Description
 *  Prescaler Values
 *  This macro defines the list of possible prescaler values.
 **/
typedef enum {
    TMR1_PRESCALER_VALUE_1  = 0x00,
    TMR1_PRESCALER_VALUE_2  = 0x01,
    TMR1_PRESCALER_VALUE_4  = 0x02,
    TMR1_PRESCALER_VALUE_8  = 0x03,
} TMR1_PRESCALER;


#ifdef T1GSS_bit
/**
 * @Description
 *  TMR1_GATE_MODE
 *  This macro defines the list of possible timer1 gate operation modes.
 **/
typedef enum {
    TMR1_GATE_MODE_OFF           = 0x00,    // Dont use Gate mode
    TMR1_GATE_MODE_ACTIVE_HIGH   = 0xC0,    // Timer1 count when gate is high    
    TMR1_GATE_MODE_ACTIVE_LOW    = 0x40,    // Timer1 count when gate is low
} TMR1_GATE_MODE;


/**
 * @Description
 *  TMR1_GATE_SOURCE
 *  This macro defines the list of possible timer1 gate source.
 **/
typedef enum {
    TMR1_GATE_SOURCE_T1G_PIN = 0x02,
    TMR1_GATE_SOURCE_CMP_OUTPUT = 0x00
} TMR1_GATE_SOURCE;

#endif

#ifdef	__cplusplus
extern "C" {
#endif

/******************************************************************************
 ************************ Section: API Implementations ************************
 ******************************************************************************/

/**
  @Summary
   Initialize Timer1.

  @Description
   Initialize Timer1

  @Preconditions
   None
  
  @Param 
     - clkSource : The Clock Source to use. See TMR1_CLOCK_SOURCE enums for details

     - prescaler : The Timer1 Prescaler to use. See TMR1_PRESCALER enums for details

     - gateMode  : The Timer1 gate signal operation mode. See TMR1_GATE_MODE enums for details
*/
#ifdef T1GSS_bit
/*
     - gateSource:  The Source for Timer1 gate signal 
*/
#endif
/*
   
  @Returns
    None

  @Comment
    Modify T1CON and CMCON1 registers.

  @Example
    <code>
    
    </code>
  */
#ifdef T1GSS_bit

#define TIMER1_Initialize( clkSource, prescaler,gateMode, gateSource )                          \
        do{                                                                                         \
            T1CON = ( T1CON & ~_T1CON_TMR1ON_MASK ) | ( (clkSource) | (prescaler) | (gateMode)  );  \
            CMCON1bits.T1GSS =  CMCON1bits.T1GSS = (gateSource>>_CMCON1_T1GSS_POSITION)*0x01;       \
            }while(0)

#else

#define TIMER1_Initialize( clkSource, prescaler,gateMode )                          \
        do{                                                                                         \
            T1CON = ( T1CON & ~_T1CON_TMR1ON_MASK ) | ( (clkSource) | (prescaler) | (gateMode)  );  \
            }while(0)


#endif
// general setup functions
 /**
  @Summary
   Enable Timer1.

  @Description
  Enable Timer1

  @Preconditions
   None
  
  @Param
    None
   
  @Returns
    None

  @Comment
    Modify TMR1ON bit from T1CON register

  @Example
    <code>
    
    </code>
  */
#define TIMER1_Start()      do{T1CONbits.TMR1ON = 1;}while(0)

 /**
  @Summary
   Disable Timer1.

  @Description
   Disable Timer1

  @Preconditions
   None
  
  @Param
    None
   
  @Returns
    None

  @Comment
    Modify TMR1ON bit from T1CON register

  @Example
    <code>
    
    </code>
  */
#define TIMER1_Stop()       do{T1CONbits.TMR1ON = 0;}while(0)

// Clock functions
    
  /**
  @Summary
   Configure Timer1 Clock source.

  @Description
   Configure Timer1 Clock source.

  @Preconditions
   None
  
  @Param
    - source: Specify the Clock Source to use. See TMR1_CLOCK_SOURCE enums for details
   
  @Returns
    None

  @Comment
    None

  @Example
    <code>
    
    </code>
  */
#define TIMER1_ClockSourceSelect( source )                      \
    do{                                                         \
        T1CON = (T1CON & ~_TMR1_CLOCK_SOURCE_MASK) | (source);  \
        }while(0) 

    
  /**
  @Summary
   Configure Timer1 prescaler.

  @Description
   This macro configure Timer1 prescaler.

  @Preconditions
   None
  
  @Param
    - prescaler: Specify the Timer1 Prescaler to set. See TMR1_PRESCALER enums for details.

  @Returns
    None

  @Comment
   This macro modify T1CPSx bits form T1CON

  @Example
    <code>
    
    </code>
  */
#define TIMER1_PrescalerSelect( prescaler)                  \
    do{ T1CON = (T1CON & ~_T1CON_T1CKPS_MASK) | (prescaler);} while(0)

// gate functions 

#ifdef T1GINV_bit
  /**
  @Summary
   Configure Timer1 Gate Mode.

  @Description
   This macro configure Timer1 Gate Mode.

  @Preconditions
    None
     
  @Param
    - gateMode: Specify the Timer1 gate signal operation mode. See TMR1_GATE_MODE enums for details.
   
  @Returns
    None

  @Comment
    This macro modify TMR1GE and T1GINV bits from T1CON register.

  @Example
    <code>
    
    </code>
  */
#define TIMER1_GateModeSelect( gateMode )                                           \
    do{                                                                             \
        T1CON = (T1CON & ~(_T1CON_TMR1GE_MASK|_T1CON_T1GINV_MASK)) | (gateMode);    \
      }while(0)

#endif

#ifdef T1GSS_bit
  /**
  @Summary
   Configure Timer1 Gate Source.

  @Description
   This macro configure Timer1 Gate Source.

  @Preconditions
   Gate mode must should be enabled.
  
  @Param
    - gateSource: Specify the source for Timer1 gate signal. See TMR1_GATE_SOURCE enums for details.
   
  @Returns
    None

  @Comment
    This macro modify T1GSS bit from CMCON1 register.

  @Example
    <code>
    
    </code>
  */
#define TIMER1_GateSourceSelect( gateSource )                                       \
    do{                                                                             \
        CMCON1bits.T1GSS = (gateSource>>_CMCON1_T1GSS_POSITION)*0x01;               \
        }while(0)

#endif

// Counter functions 
    
  /**
  @Summary
   Clear the Timer1 counter register.

  @Description
   Clear the Timer1 counter register.

  @Preconditions
   None
  
  @Param
   None
  
  @Returns
    None

  @Comment
    Modify TMR1H and TMR1L registers

  @Example
    <code>
    
    </code>
  */
#define TIMER1_CounterClear() do{ TMR1 = 0; }while(0)
   
      
    
 /**
  @Summary
   Set the Timer1 counter register value.

  @Description
   Set the Timer1 counter register value.

  @Preconditions
   None
  
  @Param
   uint16_t - value to be load on Timer1 counter register
  
  @Returns
    None

  @Comment
    Modify TMR1H and TMR1L registers

  @Example
    <code>
    
    </code>
  */
#define TIMER1_CounterSet( value ) do{ TMR1 = (value); } while(0)

    
     /**
  @Summary
   Get the Timer1 counter register value.

  @Description
   Get the Timer1 counter register value.

  @Preconditions
    None
  
  @Param
    None
  
  @Returns
      Return the value stored on TMR1H:TMR1L registers as a 16 bits integer

  @Comment
    None

  @Example
    <code>
    
    </code>
  */
#define TIMER1_CounterGet() (TMR1)



#ifdef	__cplusplus
}
#endif

#endif	/* _TIMER1_H */

