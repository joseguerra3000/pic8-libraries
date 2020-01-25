/**
  SPI Driver API Header File for PIC Mid-Range MCUs

  @Author
    Jose Guerra Carmenate

  @File Name
    spi.h

  @Summary
    This is the header file for the SPI driver using PIC Mid-Range MCUs

  @Description
    This header file provides APIs for driver for SPI.
*/

#ifndef _SPI_JGC_H
#define _SPI_JGC_H

/**
  Section: Included Files
*/

#include <xc.h>
#include <stdint.h>

/**
  Section: Configuration Options
*/

// Modificar con el bit de direccion del pin SDI
#define _SDI_TRIS TRISCbits.TRISC4  
// Modificar con el bit de direccion del pin SDO
#define _SDO_TRIS TRISCbits.TRISC5
// Modificar con el bit de direccion del pin SCK
#define _SCK_TRIS TRISCbits.TRISC3
// Modificar con el bit de direccion del pin SS
#define _SS_TRIS  TRISAbits.TRISA5


#ifdef __cplusplus  // Provide C++ Compatibility

    extern "C" {

#endif
        
/**
  Section: Data Types Definitions
*/

/**
 * SPI OPERATION MODE:
 * Para definir el modo de operacion en modo SPI
 **/
typedef enum{
    // Master Modes
    SPI_MODE_MASTER_FOSC_DIV_4  = 0b00000000, // Clock rate: Fosc/4 
    SPI_MODE_MASTER_FOSC_DIV_16 = 0b00000001, // Clock rate: Fosc/16
    SPI_MODE_MASTER_FOSC_DIV_64 = 0b00000010, // Clock rate: Fosc/64
    SPI_MODE_MASTER_TMR2_DIV_2  = 0b00000011, // Clock rate: (TMR2 output)/2
    // Slave Modes
    SPI_MODE_SLAVE_SS_CTRL      = 0b00000100, // SS controled
    SPI_MODE_SLAVE_SS_NO_CTRL   = 0b00000101, // SS no controled
} SPI_MODE;

/**
 * SPI CLOCK POLARITY:
 * Indican las opciones para el estado inactivo del reloj
 **/
typedef enum{
    SPI_CLOCK_POLARITY_IDLE_LOW     = 0b00000,  
    SPI_CLOCK_POLARITY_IDLE_HIGH    = _SSPCON_CKP_MASK
} SPI_CLOCK_POLARITY;

/**
 * SPI OUTPUT DATA PHASE:
 * Indican el flanco de salida de los datos
 **/
typedef enum{
    SPI_OUTPUT_DATA_ON_ACTIVE_TO_IDLE_CLOCK = 0b00000000,
    SPI_OUTPUT_DATA_ON_IDLE_TO_ACTIVE_CLOCK = _SSPSTAT_CKE_MASK
}SPI_OUTPUT_DATA;


/**
 * SPI INPUT SAMPLING PHASE:
 * Indican el momento del tiempo de bit en que los 
 * datos entrantes son muestrados
 **/
typedef enum{
    SPI_INPUT_SAMPLING_IN_MIDDLE  = 0b00000000,
    SPI_INPUT_SAMPLING_AT_END     = _SSPSTAT_SMP_MASK,
} SPI_INPUT_SAMPLING;

/**
 * SPI SPI TRANSMISSION MODE:
 * Permite establecer los bits CKP (SPI_CLOCK_POLARITY)
 *  y CKE (SPI_OUTPUT_DATA)
 **/
typedef enum{
    SPI_TRANSMISSION_MODE00 = 0x40,
    SPI_TRANSMISSION_MODE01 = 0x00,
    SPI_TRANSMISSION_MODE10 = 0x50,
    SPI_TRANSMISSION_MODE11 = 0x10,
            
} SPI_TRANSMISSION_MODE;


/**
  Section: SPI Module APIs
*/

/**
  @Summary
    Configura el modulo SSP/MSSP en modo SPI.
  
  @Description
    Modifica los registros SSPCON y SSPSTAT. Si las macros 
   _SDI_TRIS, _SDO_TRIS, _SCK_TRIS y _SS_TRIS no estan
   definidas en el codigo fuente (spi.c) los bits de 
   direccion deben ser configurados antes de ejecutar esta
   rutina.

 
  @Param mode - Especifica el modo de operacion SPI. 
    Ver enum SPI_MODE para conocer las opciones disponibles.
  
  @Param clkPolarity - Especifica la polaridad del reloj en
    el pin CKL. Ver enum SPI_CLOCK_POLARITY para conocer 
    las opciones disponibles.
  
  @Param clkEdge - Especifica la transicion de la senal CKL
    utilizada para transmitir los bits. Ver enum 
    SPI_OUTPUT_DATA para conocer las opciones disponibles.
   
  @Example
    <code>
    SPI_InitializeMaster( SPI_MODE_MASTER_FOSC_DIV_16, 
                          SPI_CLOCK_POLARITY_IDLE_LOW, 
                          SPI_OUTPUT_DATA_ON_ACTIVE_TO_IDLE_CLOCK,
                          SPI_INPUT_SAMPLING_AT_END );
    </code>
*/
void SPI_Initialize( SPI_MODE mode, SPI_CLOCK_POLARITY clkPolarity, SPI_OUTPUT_DATA clkEdge, SPI_INPUT_SAMPLING inSample);


/**
  @Summary
    Configura el modo de transmision SPI.
  
  @Param txMode - Especifica el modo de transmision SPI. 
    Ver enum SPI_TRANSMISSION_MODE para conocer las 
    opciones disponibles.
  
  @Example
    <code>
    SPI_SetTransmissionMode( SPI_TRANSMISSION_MODE00 );
    </code>
*/
void SPI_SetTransmissionMode( SPI_TRANSMISSION_MODE txMode );

/**
  @Summary
    Escribe un byte en el bufer SPI (registro SSPBUF). 

  @Description
    Escribe un byte en el bufer SPI no espera a que se 
   termine su transmision.

  @Preconditions
    La funcion SPI_Initialize() debe haber sido ejecutada antes de llamar
   esta funcion.
    El indicador de bufer lleno (BF) debe estar limpio (puesto a cero) para
   evitar una colicion de escritura.

  @Param
    byte - byte a escribir en el bufer

  @Example
    <code>
    void __interrupt() irs(){
      if( SSPIF ){
        SSPIF = 0;
        SPI_ReadBuffer();
        SPI_WriteBuffer( 0x45 );
      }
    }
    </code>
*/
#define SPI_WriteBuffer( byte ) do{ SSPBUF = (byte); }while(0)

/**
  @Summary
    Realiza una transferencia. Envia un byte y retorna el recibido.

  @Description
    Envia un byte y espera que termine la transferencia para retornar
   el valor recibido.
 
  @Preconditions
    La funcion SPI_Initialize() debe haber sido ejecutada antes de llamar
   esta funcion.
    El indicador de bufer lleno (BF) debe estar limpio (puesto a cero) para
   evitar una colicion de escritura.
  
  @Returns
    El valor recibido en la transferencia

  @Param
    byte - byte a enviar.

  @Example
    <code>
    SPI_Initialize( ... );
    // ...
    SPI_SendByte( 0x45 );
    </code>
*/
inline uint8_t SPI_SendByte( uint8_t byte );

/**
  @Summary
    Retorna el valor del bufer SPI (registro SSPBUF)

  @Preconditions
    La funcion SPI_Initialize() debe haber sido ejecutada antes de llamar
   esta funcion.

  @Returns
    Registro SSPBUF

  @Example
    <code>
    if( SPI_IsDataReady() )  
       data_rx = SPI_ReadBuffer();
    </code>
 */
#define SPI_ReadBuffer() (SSPBUF)

/**
  @Summary
    Realiza una transferencia y retorna el valor recibido. En
   la transferencia envia un valor basura.
 
  @Description
    Es un alias para SPI_SendByte(0)
 
  @Preconditions
    La funcion SPI_Initialize() debe haber sido ejecutada antes de llamar
   esta funcion.

  @Returns
 Retorna el byte obtenido en la transferencia

  @Example
    <code>
     uint8_t data_rx = SPI_ReadByte();
    </code>
 */
#define SPI_ReadByte() SPI_SendByte( 0 )


/**
  @Summary
    Comprueba si el bufer esta listo para ser leido

  @Description
    Verifica el estado del bufer encuestando el bit BF.

  @Returns
    El valor del bit BF

  @Example
    <code>
    if( SPI_IsDataReady() )
        data_rx = SPI_ReadBuffer();
    </code>
 */
#define SPI_IsDataReady() (SSPSTATbits.BF)




#ifdef __cplusplus  // Provide C++ Compatibility

    }

#endif

#endif	// _SPI_JGC_H
/**
 End of File
*/
