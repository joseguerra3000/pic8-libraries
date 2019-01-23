/* 
 * File:   adc_12f683.h
 * Author: Jose Guerra Carmenate
 *
 * Created on 18 de enero de 2019, 1:21
 */

#ifndef ADC_12f683_H
#define	ADC_12f683_H

#include <stdbool.h>
#include <stdint.h>
#include "adc_12f683_config.h"


/******************************************************************************
 **************************** Section: Data types *****************************
 ******************************************************************************/

/**
 * Data type returned by ADC_GetConversionResult() and ADC_GetConversion()
 * routines.
 **/
#if (_ADC_RESOLUTION == _ADC_RESOLUTION_10BITS)
typedef uint16_t adc_result_t;
#elif (_ADC_RESOLUTION == _ADC_RESOLUTION_8BITS)
typedef uint8_t adc_result_t;
#else
#error "Incorrect value for _ADC_RESOLUTION macro"
#endif


/**
 * Provide options to configure the ADC result format
 **/
typedef enum {
    _ADC_CONVERSION_RESULT_RIGHT_JUSTIFIED = _ADCON0_ADFM_MASK,
    _ADC_CONVERSION_RESULT_LEFT_JUSTIFIED = 0
} _ADC_CONVERSION_RESULT_FORMAT;


/**
 * Provide options to configure the ADC Voltage reference
 **/
typedef enum {
    _ADC_VOLTAGE_REFERENCE_VDD = 0,
    _ADC_VOLTAGE_REFERENCE_VREF= _ADCON0_VCFG_MASK
} _ADC_VOLTAGE_REFERENCE;

/**
 * Provide options to configure the ADC Clock Frecuency
 **/
typedef enum {
    _ADC_CONVERSION_CLOCK_FOSC_DIV_2    = 0b00000000,
    _ADC_CONVERSION_CLOCK_FOSC_DIV_8    = 0b00010000,
    _ADC_CONVERSION_CLOCK_FOSC_DIV_32   = 0b00100000,
    _ADC_CONVERSION_CLOCK_FRC           = 0b00110000,
    _ADC_CONVERSION_CLOCK_FOSC_DIV_4    = 0b01000000,
    _ADC_CONVERSION_CLOCK_FOSC_DIV_16   = 0b01010000,
    _ADC_CONVERSION_CLOCK_FOSC_DIV_64   = 0b01100000,
    
} _ADC_CONVERSION_CLOCK;


#ifdef	__cplusplus
extern "C" {
#endif

#if (_ADC_VERSION_TO_USE == _ADC_VERSION_LITE)
    
/******************************************************************************
 ************************ Section: API Implementations ************************
 ******************************************************************************/
    
        
  /**
  @Summary
    Initializes the ADC

  @Description
    This macro initializes the Initializes the ADC.
    This macro must be called before any other ADC routine is called.
    This macro should only be called once during system initialization.

  @Preconditions
    _ADC_RESOLUTION, _ADC_VOLTAGE_REF and _ADC_CONV_CLOCK macros must be defined
   on adc_12f683_config.h header file.

  @Param
    None

  @Returns
    None

  @Comment
   This is the ADC_Initializer macro for lite version 

  @Example
    <code>
    uint8_t rawValue;

    ADC_Initialize();
    rawValue = ADC_GetConversionResult();
    </code>
*/
#define ADC_Initialize()  { ADCON0 = _ADC_RESOLUTION | _ADC_VOLTAGE_REF; \
                              asm( "CLRF ADRESH");                       \
                              ANSEL = _ADC_CONV_CLOCK;                   \
                              asm( "CLRF ADRESL" );  }                                   

/**
  @Summary
    Allows selection of a channel for conversion

  @Description
    This routine is used to select desired channel for conversion.

  @Preconditions
    ADC_Initialize() macro should have been called before calling this function.

  @Returns
    None

  @Param
    uint8_t - desired channel for conversion
  
  @Coments
    This routine d'not configure the TRIS and ANSEL bits for desired channel.
    TRIS and ANSEL bits from channel must be configured before call this routine
  
   @Example
    <code>
    uint16_t rawValue;

    ADC_Initialize();
    ADC_SelectChannel(0);
    ADC_StartConversion();
    rawValue = ADC_GetConversionResult();
    </code>
*/
void ADC_SelectChannel( uint8_t channel );

/**
  @Summary
    Starts conversion

  @Description
    This macro is used to start conversion of desired channel.
    
  @Preconditions
    ADC_Initialize() macro should have been called before calling this function.
    Desired channel must be selected first
    

  @Returns
    None

  @Param
    None

  @Example
    <code>
    uint16_t rawValue;

    ADC_Initialize();    
    ADC_SelectChannel(2);
    ADC_StartConversion();
    while(!ADC_IsConversionDone());
    rawValue = ADC_GetConversionResult();
    </code>
*/
#define ADC_StartConversion() do{ ADCON0bits.GO_nDONE = 1; }while(0)

/**
  @Summary
    Returns true when the conversion is completed otherwise false.

  @Description
    This macro is used to determine if conversion is completed.
    When conversion is complete routine returns true. It returns false otherwise.

  @Preconditions
    ADC_Initialize() and ADC_StartConversion()
    macros should have been called before calling this function.

  @Returns
    true  - If conversion is complete
    false - If conversion is not completed

  @Param
    None

  @Example
    <code>
    uint16_t convertedValue;

    ADC_Initialize();
    ADC_SelectChannel(2);
    ADC_StartConversion();

    while(!ADC_IsConversionDone());
    convertedValue = ADC_GetConversionResult();
    </code>
 */
#define ADC_IsConversionDone() (!(ADCON0bits.GO_nDONE))

/**
  @Summary
    Returns the ADC conversion value.

  @Description
    This routine is used to get the analog to digital converted value. This
    routine gets converted values from the channel specified.

  @Preconditions
    This routine returns the conversion value only after the conversion is complete.
    Completion status can be checked using
    ADC_IsConversionDone() macro.

  @Returns
    Returns the converted value.

  @Param
    None

  @Example
    <code>
    uint16_t convertedValue;

    ADC_Initialize();
    ADC_StartConversion(AN1_Channel);

    while(ADC_IsConversionDone());

    convertedValue = ADC_GetConversionResult();
    </code>
 */
adc_result_t ADC_GetConversionResult();


/**
  @Summary
    Returns the ADC conversion value
    also allows selection of a channel for conversion.

  @Description
    This routine is used to select desired channel for conversion
    and to get the analog to digital converted value.

  @Preconditions
    ADC_Initialize() macro should have been called before calling this function.

  @Returns
    Returns the converted value.

  @Param
    uint8_t - desired channel for conversion

  @Example
    <code>
    uint16_t convertedValue;

    ADC_Initialize();

    conversion = ADC_GetConversion(2);
    </code>
*/
adc_result_t ADC_GetConversion( uint8_t channel );

#endif

#ifdef	__cplusplus
}
#endif

#endif	/* ADC_H */

