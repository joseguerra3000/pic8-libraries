/* 
 * File:   software_uart_config.h
 * Author: root
 *
 * Created on 19 de enero de 2019, 2:56
 */

#ifndef SOFTWARE_UART_CONFIG_H
#define	SOFTWARE_UART_CONFIG_H

/**
 * BAUDRATE
 * 
 * Define la velocidad de la comunicacion. Este parametro es compartido por
 * todos los software_uart_t
 * @example
 *  #define BAUDRATE 9600
 */
#define BAUDRATE 9600                      // bps

/**
 * DATA_BIT_COUNT
 * 
 * Define la cantidad de bits de informacion en cada transferencia.
 * 
 * @note
 *  Esta caracteristica es comun a todos los sofware_uart_t
 * 
 * @example
 *  #define DATA_BIT_COUNT 8
 */
#define DATA_BIT_COUNT 8                   // no parity, no flow control

/**
 * TX_PORT
 * 
 * Define el puerto a utilizar para los pines de transmision de sofware_uart_t.
 * Los software_uart_t solo pueden transmitir utilizando pines de este puerto
 * 
 * @note
 *  Cada software_uart_t define el pin del puerto que utiliza como transmisor
 * 
 * @example
 *  #define TX_PORT PORTC
 */
#define TX_PORT PORTC                 // UART TX Port register

/**
 * RX_PORT
 * 
 * Define el puerto a utilizar para los pines de recepcion de sofware_uart_t.
 * Los software_uart_t solo pueden recibir utilizando pines de este puerto.
 * 
 * @note
 *  Cada software_uart_t define el pin del puerto que utiliza como transmisor
 * 
 * @example
 *  #define RX_PORT PORTD
 */
#define RX_PORT PORTC                 // UART RX Port register

/**
 * TX_TRIS
 * 
 * Define el registro de direccion del puerto a utilizar para los pines de 
 * transmision de sofware_uart_t
 * 
 * @note
 *  Cada software_uart_t define el pin del puerto que utiliza como transmisor
 * 
 * @example
 *  #define TX_TRIS TRISC
 */
#define TX_TRIS TRISC                 // UART TX direction register

/**
 * RX_TRIS
 * 
 * Define el registro de direccion del puerto a utilizar para los pines de 
 * recepcion de sofware_uart_t
 * 
 * @note
 *  Cada software_uart_t define el pin del puerto que utiliza como receptor
 * 
 * @example
 *  #define TX_TRIS TRISC
 */
#define RX_TRIS TRISC                 // UART RX direction register


#endif	/* SOFTWARE_UART_CONFIG_H */

