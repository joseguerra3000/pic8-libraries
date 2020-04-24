/** 
 * @file  LEDMatrix_config.h
 * @author jose
 *
 * @brief Cabecera de configuracion para la API de matrices 
 * led 8x8 utilizando el integrado MAX7219/MAX7221.
 *
 * @date 21 de octubre de 2019, 19:28
 */

#ifndef LEDMATRIX_CONFIG_H
#define	LEDMATRIX_CONFIG_H

#include <xc.h>
#include "SPISoft.h" // Cabecera con las rutinas spi. Necesaria para las macros spiInit, sendByte y isBusy.

/**
 @brief Definicion del registro PORT del pin utilizado como 
  Chip Select.

 <b>Example</b>
 @code
 #define CS PORTDbits.RD4
 @endcode
*/
#define CS PORTDbits.RD4

/**
 @brief Definicion del registro TRIS del pin utilizado como 
  Chip Select.

 <b>Example</b>
 @code
 #define CS_TRIS TRISDbits.TRISD4
 @endcode
*/
#define CS_TRIS TRISDbits.TRISD4

/**
 * @brief Numero de matrices a conectar en cascada
 
 <b>Example</b>
 @code
 // utilizar 8 matrices en cascada
 #define NUMBER_OF_MATRIX 8
 @endcode
 */
#define NUMBER_OF_MATRIX 2

/**
 @brief Definicion de inicializacion de driver SPI. 
 
 @note Es posible utilizar el modulo SSP o un protocolo implementado por software
*/
#define spiInit() SPISoft_Initialize()

 
/**
 @brief Definicion de la funcion para enviar un byte via SPI. 
 
 @note Es posible utilizar el modulo SSP o un protocolo implementado por software
 
*/
#define sendByte(x) SPISoft_SendByteMode00((x))

// 
/**
 @brief Definicion de la funcion para comprobar disponibilidad del bus spi. 
 
 @note Es posible utilizar el modulo SSP o un protocolo implementado por software.
 En caso de utilizar un protocolo implementado por software debe ser definida como false 
*/
#define isBusy() false



#endif	/* LEDMATRIX_CONFIG_H */

