/* 
 * File:   SSD2.h
 * Author: jose
 *
 * Created on 17 de mayo de 2019, 16:38
 * 
 * Cabecera del Controlador SSD2 (Seven Segment Display Double) 
 * para pantallas 7 segmentos con dos visualizadores y un pin de 
 * multiplexacion
 * 
 * Conexiones:
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
 * Nota: Los pines CC tienen un inversor entre ellos para que 
 *  cuando un visualizador encienda, el otro se apage.
 */
#ifndef _SSD2_H
#define	_SSD2_H

#include <stdint.h>

/**
 * Objeto SSD
 **/
typedef struct{
    uint8_t digit0, // digito mas significativo
            digit1; // digito menos significativo
    
    volatile uint8_t *port; // puerto utilizado
} ssd_t;

/**
 * @Descripcion: 
 *   Recibe un puntero al objeto SSD y la direccion del puerto a 
 *  utilizar y lo configura para su uso.
 * 
 * @Param
 *  - ssd: puntero al objeto ssd_t a configurar
 *  - port: puerto a utilizar
 * 
 * @Retorno
 *  - 1: Si el puerto fue configurado satisfactoriamente
 *  - 0: Si el puerto no esta configurado correctamente 
 * 
 * @Notas:
 *   - Los canales analogicos, del puerto a utilizar, deben ser 
 *   deshabilitados
 *   - Un error de configuracion puede ser por canales analogicos no  
 *   apagados o por que el puerto no es valido.
 * 
 * @Ejemplo:
 *  if( !SSD_Initialize( &mySSD, &PORTB ) ){
 *      //error de configuracion
 *  }
 **/
__bit SSD_Initialize( ssd_t* ssd, volatile uint8_t *port );

/**
 * @Descripcion: 
 *  Define el numero que sera mostrado en el modulo
 * 
 * @Param
 *  - ssd: puntero al objeto ssd_t a configurar
 *  - number: numero a mostrar
 *  
 * 
 * @Ejemplo:
 *  SSD_PrintNumber( &mySSD, 66 );
 **/
void SSD_PrintNumber( ssd_t* ssd, uint8_t number );

/**
 * @Descripcion: 
 *  Apaga la pantalla
 * 
 * @Param
 *  - ssd: puntero al objeto ssd_t a configurar
 * 
 * @Ejemplo:
 *  SSD_Clear( &mySSD );
 **/
inline void SSD_Clear( ssd_t* ssd );

/**
 * @Descripcion: 
 *  Es la funcion que se encarga de la multiplexacion.
 * Debe ser ejecutada con una frecuencia mayor a 120Hz
 * para una correcta visualizacion de la informacion
 * 
 * @Param
 *  - ssd: puntero al objeto ssd_t a configurar
 * 
 * @Ejemplo:
 * 
 * void __interrupt() isr(){
 *   if( TMR0IF ){
 *     SSD_Mux();
 *     TMR0IF = 0;   
 *   }
 * }
 **/
inline void SSD_Mux( ssd_t *ssd );

#endif	/* SSD_H */

