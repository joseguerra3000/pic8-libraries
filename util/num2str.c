/* 
 * File:   num2str.c
 * Author: Jose Guerra Carmenate
 *
 * Created on 5 de enero de 2019, 20:18
 * @Description
 *  This header contain a set of routines implementations for store numbers on 
 * string.
 */

#include <stdint.h>
#include "num2str.h"

uint8_t short2str( int8_t x, uint8_t bas, char *p ){
    int8_t xx = x;
    
    do{
        p++;
        xx /= bas;
    }while( xx );
    
    if( x < 0 ){
        *(p++) = '-';
        x *= -1;
        xx++;
    }
    
    //*p = '\0';
    
    do{
        *(--p) = (uint8_t)(x%bas) + '0';
        x /= bas;
        xx++;
    }while( x );
    
    return (uint8_t)xx;
}

uint8_t int2str( int16_t x, uint8_t bas, char *p ){
    int16_t xx = x;
    if( x < 0 )
        *p++ = '-';
    do{
        p++;
        xx /= bas;
    }while( xx );
    
    if( x < 0 ){
        x *= -1;
        xx++;
    }
    
    //*p = '\0';
    
    do{
        *(--p) = (uint8_t)(x%bas) + '0';
        x /= bas;
        xx++;
    }while( x );
    
    return (uint8_t)xx;
}

uint8_t long2str( int32_t x, uint8_t bas, char *p ){
    
    int32_t xx = x;
    
    do{
        p++;
        xx /= bas;
    }while( xx );
    
    if( x < 0 ){
        *(p++) = '-';
        x *= -1;
        xx++;
    }
    
    //*p = '\0';
    
    do{
        *(--p) = (uint8_t)(x%bas) + '0';
        x /= bas;
        xx++;
    }while( x );
    
    return (uint8_t)xx;
}


uint8_t ushort2str( uint8_t x, uint8_t bas, char *p ){
    
    uint8_t xx = x;
    
    do{
        p++;
        xx /= bas;
    }while( xx );

    //*p = '\0';
    
    do{
        *(--p) = (uint8_t)(x%bas) + '0';
        x /= bas;
        xx++;
    }while( x );
    
    return xx;
}

uint8_t uint2str( uint16_t x, uint8_t bas, char *p ){
    
    uint16_t xx = x;
    
    do{
        p++;
        xx /= bas;
    }while( xx );
  
    //*p = '\0';
    
    do{
        *(--p) = x%bas + '0';
        x /= bas;
        xx++;
    }while( x );
    
    return xx;
}

uint8_t ulong2str( uint32_t x, uint8_t bas, char *p ){
    
    uint32_t xx = x;
    
    do{
        p++;
        xx /= bas;
    }while( xx );
     
    //*p = '\0';
    
    do{
        *(--p) = x%bas + '0';
        x /= bas;
        xx++;
    }while( x );
    
    return xx;
}

uint8_t float2str( float x, uint8_t afterpoint, char *p ){
    int ipart = (int)x; // integer part
    uint8_t sz = 0;
    float fpart = x - (float)ipart; // float part
    sz = int2str( ipart, 10, p );
    
    if( afterpoint != 0 ){
        p[sz++] = '.';
        for( uint8_t i = 0; i < afterpoint; i++ )
            fpart *= 10;
        sz += int2str( (int16_t)fpart, 10, p+sz );
    }
    return sz;
}