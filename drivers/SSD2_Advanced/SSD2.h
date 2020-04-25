/**
 * @file SSD2.h
 * @author Jose Guerra Carmenate
 *
 * @date 17 de mayo de 2019, 16:38
 * 
 * @brief Cabecera del Controlador SSD2 (Seven Segment Display Double) 
 * para pantallas 7 segmentos con dos visualizadores y un pin de 
 * multiplexacion
 * 
 * <b>Conexiones</b>
 * @verbatim
 * +------------+           +--------------+   
 * |    PIC  Rx0|-----------| a    Dos     |
 * |         Rx1|-----------| b Pantallas  | 
 * |    MCU  Rx2|-----------| c     7      |
 * |         Rx3|-----------| d    Seg     |
 * |         Rx4|-----------| e            |
 * |         Rx5|-----------| f            |
 * |         Rx6|-----------| g            |
 * |         Rx7|-----------| CC(Cat comun)|
 * +------------+           +--------------+
 * @endverbatim
 * @note Los pines CC tienen un inversor entre ellos para que 
 *  cuando un visualizador encienda, el otro se apage.
 */
#ifndef _SSD2_H
#define	_SSD2_H

#include <stdint.h>

/**
 * Objeto SSD
 **/
typedef struct{
    uint8_t digit0, ///< digito mas significativo 
            digit1; ///< digito menos significativo
    
    volatile uint8_t *port; ///< puerto utilizado
} ssd_t;

/**
 * @brief 
 *   Recibe un puntero al objeto SSD y la direccio'n del puerto a 
 *  utilizar y lo configura para su uso.
 * 
 * @param[in] ssd Puntero al objeto ssd_t a configurar
 * @param[in] port Puerto a utilizar
 * 
 * @return __bit:
 *  - 1: Si el puerto fue configurado satisfactoriamente
 *  - 0: Si el puerto no esta' configurado correctamente 
 * 
 * @note Los canales analogicos, del puerto a utilizar, deben ser 
 *   deshabilitados
 * @note Un error de configuracio'n puede ser por canales analo'gicos no  
 *   apagados o por que el puerto no es valido.
 * 
 * <b>Ejemplo</b>
 *  @code
 *  if( !SSD_Initialize( &mySSD, &PORTB ) ){
 *      //error de configuracion
 *  }
 *  @endcode
 **/
__bit SSD_Initialize( ssd_t* ssd, volatile uint8_t *port );

/**
 * @brief
 *  Muestra un nu'mero en la pantalla
 * 
 * @param[in] ssd Puntero al objeto ssd_t a configurar
 * @param[in] number Numero a mostrar
 *  
 * 
 * <b>Ejemplo </b>
 * @code
 *  SSD_PrintNumber( &mySSD, 66 );
 * @endcode
 **/
void SSD_PrintNumber( ssd_t* ssd, uint8_t number );

/**
 * @brief
 *  Apaga todos los segmentos de ambos visualizadores
 * 
 * @param[in] ssd Puntero al objeto ssd_t a configurar
 * 
 * <b>Ejemplo</b>
 *  @code
 *  SSD_Clear( &mySSD );
 *  @endcode
 **/
inline void SSD_Clear( ssd_t* ssd );

/**
 * @brief 
 *  Es la funcion que se encarga de la multiplexacion.
 * Debe ser ejecutada con una frecuencia mayor a 120Hz
 * para una correcta visualizacion de la informacion.
 * 
 * @param[in] ssd Puntero al objeto ssd_t a configurar
 * 
 * <b>Ejemplo</b>
 * @code
 * void __interrupt() isr(){
 *   if( TMR0IF ){
 *     SSD_Mux();
 *     TMR0IF = 0;   
 *   }
 * }
 * @endcode
 **/
inline void SSD_Mux( ssd_t *ssd );

#endif	/* SSD_H */

