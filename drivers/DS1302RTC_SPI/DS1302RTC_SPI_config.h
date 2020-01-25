/* 
 * File:   DS1302RTC_SPI_config.h
 * Author: Jose Guerra Carmenate
 * Comments:
 * Esta cabecera debe ser modificada para configurar correctamente el driver
 * DS1302RTC_SPI. En esta se especifica los registros TRIS y PORT 
 * correspondientes al bit utilizado para controlar la senal del pin 
 * CE (tambien conocido como /RST) del DS1302.
 * 
 * Revision history: 
 */

// This is a guard condition so that contents of this file are not included
// more than once.  
#ifndef __DS1302RTC_SPI_CONFIG_H
#define	__DS1302RTC_SPI_CONFIG_H

#include <xc.h> // include processor files - each processor file is guarded.  

/* 
 * @brief
 * Registro TRIS correspondiente al bit utilizado para controlar la senal del 
 * pin CE (tambien conocido como /RST) del DS1302.
*/
#define _DS1302_CE_TRIS TRISCbits.TRISC2

/* 
 * @brief
 * Registro PORT correspondiente al bit utilizado para controlar la senal del 
 * pin CE (tambien conocido como /RST) del DS1302.
*/
#define _DS1302_CE_PORT PORTCbits.RC2


#endif	/* XC_HEADER_TEMPLATE_H */

