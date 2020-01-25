/* 
 * File:   software_uart.h
 * Author: Jose Guerra Carmenate
 *
 * Created on 19 de enero de 2019, 2:56
 */

#ifndef SOFTWARE_UART_H
#define	SOFTWARE_UART_H

#include <stdint.h>

typedef struct{
    uint8_t tx_pin,
            rx_pin;
} software_uart_t;


#ifdef	__cplusplus
extern "C" {
#endif
    void SoftUART_Initialize( software_uart_t*const);
    
    void SoftUART_SelectActive(  software_uart_t * const p );
    
    void SoftUART_WriteByte( uint8_t data_tx );
    
    uint8_t SoftUART_ReadByte( void );

    void SoftUART_PrintString( char *txt );
    
    #define SoftUART_PrintStringln( txt ) UARTSoft_PrintString( txt ); \
                                          UARTSoft_PrintString( "\n\r" );

#ifdef	__cplusplus
}
#endif

#endif	/* SOFTWARE_UART_H */

