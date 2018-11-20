/**
  ADC Driver API Header File

  @Author
   Jose Guerra Carmenate

  @File Name
    adc.h

  @Summary
    This is the header file for the ADC driver on MCUs

  @Description

*/


#ifndef _ADC_H
#define _ADC_H

#define _HEADER_NOT_FOUND


#ifdef _16F887
 #include "adc_peripheral/adc_16f887.h"
 #undef _HEADER_NOT_FOUND
#endif

#ifdef _HEADER_NOT_FOUND
#error Device-specific header could not be found for target chip
#endif

#endif