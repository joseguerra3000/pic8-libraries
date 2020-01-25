/* 
 * File:   software_uart.c
 * Author: Jose Guerra Carmenate
 *
 * Created on 19 de enero de 2019
 */

/******************* Section: Include *******************/
#include <xc.h>
#include "software_uart.h"
#include "software_uart_config.h"

#include "hardware.h"

/******************* Section: Macros *******************/

#define ONE_BIT_DELAY (1000000/BAUDRATE)
#define maskSet( w, x ) do{ ((w) |= (x)); }while(0)
#define maskClear(w,x) do{ ((w) &= ~(x)); }while(0)


__bit RD_ERROR; // 1 - last read invalid, 0 - las read ok

// auxiliar variables
uint8_t aux;
uint8_t tx_mask;
uint8_t rx_mask;

/*************** Section: API Implementation ***********/

void SoftUART_SelectActive(  software_uart_t * const p ){
  tx_mask = 1u<<(p->tx_pin);
  rx_mask = 1u<<(p->rx_pin);
}

void SoftUART_Initialize(software_uart_t * const uart){
  SoftUART_SelectActive(uart);
  
  RX_TRIS |= 1u<<(uart->tx_pin); // rx input

  aux = uart->tx_pin;
  aux = 1u<<aux;
  TX_TRIS &= ~(aux);  // tx output
  TX_PORT |= aux;     // tx idle high
}

void SoftUART_WriteByte( uint8_t data_tx ){
    aux = DATA_BIT_COUNT;
    
    // Send start Bit
    maskClear( TX_PORT, tx_mask );
    __delay_us(ONE_BIT_DELAY);
    
    // Send bit by bit
    do{
      if( (__bit)(data_tx) ){
        maskSet(TX_PORT, tx_mask);
      }
      else{
        maskClear(TX_PORT, tx_mask);
      }
      data_tx >>= 1;
      __delay_us(ONE_BIT_DELAY);
    }while(aux--);
    //Send Stop
    maskSet(TX_PORT, tx_mask);
    __delay_us(ONE_BIT_DELAY);
}

uint8_t SoftUART_ReadByte( void ){  
  uint8_t mask = 1;
  aux = 0; // store value to return
  
  RD_ERROR = 0;
  
  while( (RX_PORT&rx_mask) );

  __delay_us(ONE_BIT_DELAY); // wait on bit time (start bit)
  __delay_us(ONE_BIT_DELAY/2); // wait half bit time (for sample on center of bit)

  do{
      if( RX_PORT&rx_mask )
          aux |= mask;
      mask <<= 1;
      __delay_us(ONE_BIT_DELAY);
  }while(mask);
   __delay_us(ONE_BIT_DELAY);
  if(RX_PORT&rx_mask){
      return aux;
  }
  else{
    RD_ERROR = 1;
    return 0x00;
  }
}

void SoftUART_PrintString( char *txt ){
  while( *txt )
    SoftUART_WriteByte( *txt++ );
}


__bit SoftUART_ReadError(){
  return RD_ERROR;
}

