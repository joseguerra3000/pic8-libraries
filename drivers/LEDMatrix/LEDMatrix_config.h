/* 
 * File:   LEDMatrix_config.h
 * Author: jose
 *
 * Created on 21 de octubre de 2019, 19:28
 */

#ifndef LEDMATRIX_CONFIG_H
#define	LEDMATRIX_CONFIG_H
#include <xc.h>
// Incluir cabecera con las rutinas spi
#include "SPISoft.h"

#define CS PORTDbits.RD4
#define CS_TRIS TRISDbits.TRISD4

/**
 * Especificar numero de matrices a utilizar
 */
#define NUMBER_OF_MATRIX 2

// funcion para inicializar SPI
#define spiInit() SPISoft_Initialize()

// funcion para enviar un byte via SPI
#define sendByte(x) SPISoft_SendByteMode00((x))

// funcion para comprobar disponibilidad del bus spi
#define isBusy() false



#endif	/* LEDMATRIX_CONFIG_H */

