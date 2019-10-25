/* 
 * File:   SPISoft.h
 * Author: jose
 *
 * Implementacion de Protocolo SPI por software.
 * Los pines utilizados para la  comunicacion deben ser especificados en el
 * archivo de cabezera SPISoft_config.h
 * Esta implementacion solo permite ser utilizada como SPI master.
 * 
 * Created on 21 de octubre de 2019, 20:23
 */

#ifndef SPISOFT_H
#define	SPISOFT_H

#include <stdint.h>

/**
 * Configura los pines utilizados para la comunicacion.
 * 
 * @note
 * Si los pines utilizados comparten alguna funcionalidad 
 * analogica esta debe ser deshabilitada antes de ejecutar
 * esta funcion.
 */
void SPISoft_Initialize();

/**
 * Envia un byte utilizando el modo spi 10
 * @param byte - byte a enviar
 * 
 */
void SPISoft_SendByteMode10( uint8_t byte);

/**
 * Envia un byte utilizando el modo spi 00
 * @param byte - byte a enviar
 */
void SPISoft_SendByteMode00( uint8_t byte);



#endif	/* SPISOFT_H */

