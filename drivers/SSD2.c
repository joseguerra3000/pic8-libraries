/*
 * File:   SSD2.c
 * Author: jose
 *
 * Created on 17 de mayo de 2019, 16:40
 * 
 *  Archivo fuente del Controlador SSD2 (Seven Segment Display Double) 
 * para pantallas 7 segmentos con dos visualizadores y un pin de 
 * multiplexacion. 
 *  Contiene todas las implementaciones necesarias para dicho controlador.
 */


#include <xc.h>
#include "SSD2.h"

const uint8_t _bcd_to_7seg[] = {
    //.gfedcba
    0b00111111, // 0
    0b00000110, // 1
    0b01011011, // 2
    0b01001111, // 3
    0b01100110, // 4
    0b01101101, // 5
    0b01111101, // 6
    0b00000111, // 7
    0b01111111, // 8
    0b01101111  // 9
};

/**
 * @Descripcion
 * Retorna un puntero al registro TRISx correscondiente
 * con el registro PORTx recibido como parametro
 **/
volatile uint8_t *__getTRIS( volatile uint8_t *port ){
    
#ifdef PORTA
    if( &PORTA == port )
        return &TRISA;
#endif
                
#ifdef PORTB
    if( &PORTB == port )
        return &TRISB;
#endif
    
#ifdef PORTC
    if( &PORTC == port )
        return &TRISC;
#endif
    
#ifdef PORTD
    if( &PORTD == port )
        return &TRISD;
#endif
    
#ifdef PORTE
    if( &PORTE == port )
        return &TRISE;
#endif
    
#ifdef PORTF
    if( &PORTF == port )
        return &TRISF;
#endif
        return 0;
}

__bit SSD_Initialize( ssd_t *ssd, volatile uint8_t *__port ){
    *__getTRIS(__port) = 0x00;  // configura puerto como salida
    //TRISB = 0x00;
    ssd->port = __port;         // almacenar puerto en estructura
    ssd->digit0 = 0u;           // inicializar los
    ssd->digit1 = 0u;           // digitos 
    (*__port) = 0xFF;           // poner todo el puerto a estado alto
    if( (*__port) != 0xFF ){    // si el puerto no esta en estado alto
        return 0;               // los canales analogicos de este estan activos
    }
    (*__port) = 0x00;    
    return 1;
}

void SSD_PrintNumber( ssd_t* ssd, uint8_t number ){
    if( number > 99u )                     // no se puede mostrar
        return;
    ssd->digit1 = _bcd_to_7seg[number%10]; // digito decimal
    ssd->digit0 = _bcd_to_7seg[number/10]; // digito decenas
}


inline void SSD_Clear( ssd_t* ssd ){
    ssd->digit0 = ssd->digit1 = 0;          // apagar todos los segmentos
}


inline void SSD_Mux( ssd_t *ssd ){
    static __bit x = 0;
    uint8_t port;                   // temporal para puerto
    if( x )                         // digito activo?
        port = ssd->digit1;         // actualiza digito 1
    else
        port = ssd->digit0|0x80;    // actualiza digito 0
    
    x ^= 1;                         // cambia actual
   *(ssd->port) = port;             // escribir al puerto
}
