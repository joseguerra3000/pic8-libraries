/* 
 * ADC Driver configuration header File for PIC12F683
 * 
 * @Author
 *      Jose Guerra Carmenate
 * 
 * @File 
 *      adc_12f683.h
 *
 * @Summary
 *      This file provide the configuration for ADC module.
 * 
 * Created on 18 de enero de 2019, 1:24
 */

#ifndef ADC_12f683_CONFIG_H
#define	ADC_12f683_CONFIG_H

#include <xc.h>

/*****************************************************************************
 ****************************** Macros Section *******************************
 ******************************************************************************/

/** 
 * ADC Library version options macros
 */

#define _ADC_VERSION_LITE   1   // The ADC configuration be defined using adc_xxx_config.h file.\
                                   Used mainly for small devices.

#define _ADC_VERSION_NORMAL 2   // The ADC configuration be defined using the ADC_Initialize\
                                  routine. Used for devices with more resorces

/**
 * ADC Resolution macros
 */

#define _ADC_RESOLUTION_10BITS  _ADCON0_ADFM_MASK // The ADC result is RIGHT JUSTIFIED

#define _ADC_RESOLUTION_8BITS   0                 // The ADC result is LEFT JUSTIFIED


/******************************************************************************
 **************************** Configuration Section ***************************
 ******************************************************************************/

/**
 * ADC library Version Select
 * 
 * See _ADC_VERSION_xxxx macros (on macros section of this header) for available options
 */
#define _ADC_VERSION_TO_USE _ADC_VERSION_LITE


/**
 * Define the ADC resolution result
 * See _ADC_RESOLUTION macros (on macros section of this header) for available options
 */
#define _ADC_RESOLUTION _ADC_RESOLUTION_10BITS


/**
 * Define the ADC Voltage reference
 * See _ADC_VOLTAGE_REFERENCE enum (on adc_12f683.h file) for available options
 */
#define _ADC_VOLTAGE_REF _ADC_VOLTAGE_REFERENCE_VDD


/**
 * Define the ADC Conversion Clock
 * See _ADC_CONVERSION_CLOCK enum (on adc_12f683.h file) for available options
 */
#define _ADC_CONV_CLOCK _ADC_CONVERSION_CLOCK_FOSC_DIV_8


/**
 * ADC Acquisition Time (D'not touch)
 * Calibrate using Datasheet information
 */
#define ADC_ACQ_US_DELAY 12


#endif	/* ADC_CONFIG_H */

