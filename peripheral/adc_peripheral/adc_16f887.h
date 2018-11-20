/**
  ADC Driver API Header File for PIC16F887

  @Author
    Jose Guerra Carmenate

  @File Name
    adc_16f887.h

  @Summary
    This is the header file for the ADC driver using PIC16F887 MCUs

  @Description
    This header file provides APIs for driver for ADC.
*/


#ifndef ADC_16f887_H
#define ADC_16f887_H

/**
  Section: Included Files
*/

#include <xc.h>
#include <stdint.h>
#include <stdbool.h>

#ifdef __cplusplus  // Provide C++ Compatibility

    extern "C" {

#endif

        
/**
  Section: Data Types Definitions
*/

/**
 *  result size of an A/D conversion
 */

typedef uint16_t adc_result_t;

/**
 * analog channel tyoe
 **/
typedef uint8_t adc_channel_t;

/**
 * A/D Conversion Clock
 **/
typedef enum{
    CONVERSION_CLOCK_FOSC_DIV_2 =  0b00000000,
    CONVERSION_CLOCK_FOSC_DIV_8 =  0b01000000,
    CONVERSION_CLOCK_FOSC_DIV_32 = 0b10000000,
    CONVERSION_CLOCK_FRC =         0b11000000,
} CONVERSION_CLOCK;

/**
 * A/D Conversion Result Format
 **/
typedef enum{
    CONVERSION_RESULT_RIGHT_JUSTIFIED = 0b00000000,
    CONVERSION_RESULT_LEFT_JUSTIFIED =  0b10000000,
} CONVERSION_FORMAT;

/**
 * A/D Voltage Reference
 **/
typedef enum{
    VOLTAGE_REFERENCE_VDD_TO_VSS            = 0b00000000,
    VOLTAGE_REFERENCE_VREFplus_TO_VSS       = 0b00010000,
    VOLTAGE_REFERENCE_VDD_TO_VREFminus      = 0b00100000,
    VOLTAGE_REFERENCE_VREFplus_TO_VREFminus = 0b00110000, 
} VOLTAGE_REFERENCE;

/**
  Section: ADC Module APIs
*/

/**
  @Summary
    Initializes the ADC

  @Description
    This routine initializes the Initializes the ADC.
    This routine must be called before any other ADC routine is called.
    This routine should only be called once during system initialization.

  @Preconditions
    None

  @Param
    - convClock: A/D conversion clock used.
          "For available Clocks refer to enum CONVERSION_CLOCK"
    
    - convRes: A/D Conversion Result Format.
          "For available Formats refer to enum CONVERSION_FORMAT"
    
    - voltRef: A/D Voltage Reference.
           "For available References refer to enum VOLTAGE_REFERENCE"

  @Returns
    None

  @Comment
    

  @Example
    <code>
    uint16_t convertedValue;

    ADC_Initialize();

    </code>
*/
void ADC_Initialize(CONVERSION_CLOCK convClock, VOLTAGE_REFERENCE voltRef);

#define ADC_InitializeDefault() ADC_Initialize( CONVERSION_CLOCK_FOSC_DIV_32, VOLTAGE_REFERENCE_VDD_TO_VSS )

/**
  @Summary
    Allows selection of a channel for conversion

  @Description
    This routine is used to select desired channel for conversion.

  @Preconditions
    ADC_Initialize() function should have been called before calling this function.

  @Returns
    None

  @Param
    - channel: desired channel for conversion
    "For available channel refer to enum under adc.h file"

  @Example
    <code>
    uint16_t convertedValue;

    ADC_Initialize();
    ADC_SelectChannel(AN1_Channel);
    ADC_StartConversion();
    convertedValue = ADC_GetConversionResult();
    </code>
*/
void ADC_SelectChannel(adc_channel_t channel);

/**
  @Summary
    Starts conversion

  @Description
    This routine is used to start conversion of desired channel.
    
  @Preconditions
    ADC_Initialize() function should have been called before calling this function.

  @Returns
    None

  @Param
    None

  @Example
    <code>
    uint16_t convertedValue;

    ADC_Initialize();    
    ADC_SelectChannel(AN1_Channel);
    ADC_StartConversion();
    convertedValue = ADC_GetConversionResult();
    </code>
*/
void ADC_StartConversion();
#define ADC_StartConversion()     do { ADCON0bits.GO_nDONE = 1; } while(0)

/**
  @Summary
    Returns true when the conversion is completed otherwise false.

  @Description
    This routine is used to determine if conversion is completed.
    When conversion is complete routine returns true. It returns false otherwise.

  @Preconditions
    ADC_Initialize() and ADC_StartConversion(adc_channel_t channel)
    function should have been called before calling this function.

  @Returns
    true  - If conversion is complete
    false - If conversion is not completed

  @Param
    None

  @Example
    <code>
    uint16_t convertedValue;

    ADC_Initialize();
    ADC_SelectChannel(AN1_Channel);
    ADC_StartConversion();

    while(!ADC_IsConversionDone());
    convertedValue = ADC_GetConversionResult();
    </code>
 */
bool ADC_IsConversionDone();
#define ADC_IsConversionDone() (!ADCON0bits.GO_nDONE)

/**
  @Summary
    Returns the ADC conversion value.

  @Description
    This routine is used to get the analog to digital converted value. This
    routine gets converted values from the channel specified.

  @Preconditions
    This routine returns the conversion value only after the conversion is complete.
    Completion status can be checked using
    ADC_IsConversionDone() routine.

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
#define ADC_GetConversionResult() ((adc_result_t)((ADRESH << 8) + ADRESL))


/**
  @Summary
    Returns the ADC conversion value
    also allows selection of a channel for conversion.

  @Description
    This routine is used to select desired channel for conversion
    and to get the analog to digital converted value.

  @Preconditions
    ADC_Initialize() function should have been called before calling this function.

  @Returns
    Returns the converted value.

  @Param
    Pass in required channel number.
    "For available channel refer to enum under adc.h file"

  @Example
    <code>
    uint16_t convertedValue;

    ADC_Initialize();

    conversion = ADC_GetConversion(AN1_Channel);
    </code>
*/
 uint16_t ADC_GetConversion(adc_channel_t channel);
 
/**
  @Summary
    Stop conversion

  @Description
    This routine is used to stop current conversion.
    
  @Preconditions
    ADC_Initialize() and ADC_StartConversion() function should have been 
    called before calling this function.

  @Returns
    None

  @Param
    None

  @Example
    <code>
    uint16_t convertedValue;

    ADC_Initialize();    
    ADC_SelectChannel(AN1_Channel);
    ADC_StartConversion();

    ADC_StopConversion();
    </code>
*/
void ADC_StopConversion();
#define ADC_StopConversion() do{ ADCON0bits.ADON = 0; } while(0)

#ifdef __cplusplus  // Provide C++ Compatibility

    }

#endif

#endif	//ADC_16f887_H 
/**
 End of File
*/

