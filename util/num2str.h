/* 
 * File:   num2str.h
 * Author: Jose Guerra Carmenate
 *
 * @Description:
 * This header contain a set of routines prototypes for store numbers on 
 * string.
 */

#ifndef NUM2STR_H
#define	NUM2STR_H

#include <stdint.h>

#ifdef	__cplusplus
extern "C" {
#endif
    
    uint8_t ushort2str( uint8_t x, uint8_t bas, char *res );
    uint8_t uint2str( uint16_t x, uint8_t bas, char *res );
    uint8_t ulong2str( uint32_t x, uint8_t bas, char *res );

    uint8_t short2str( int8_t x, uint8_t bas, char *res );
    uint8_t int2str( int16_t x, uint8_t bas, char *res );
    uint8_t long2str( int32_t x, uint8_t bas, char *res );
    
    uint8_t float2str( float x, uint8_t afterpoint, char *res );
        
    
    

#ifdef	__cplusplus
}
#endif

#endif	/* STRING_CONVERT_H */

