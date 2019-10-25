

#include <xc.h>
#include "LEDMatrix.h"
#include "LEDMatrix_config.h"
#include "system.h"

#define writeWord( reg, value ) do{         \
                        sendByte(reg);      \
                        sendByte(value);    \
                        }while(0)

uint8_t buffer[NUMBER_OF_MATRIX*8];
__bit autoFlush;
uint8_t upper, i;
uint8_t *offset;

static void setRegister( uint8_t disp, LEDMAT_REGISTER reg, uint8_t value ){
    disp++;
    CS = 0;
    for( uint8_t i = NUMBER_OF_MATRIX; i; i-- ){
        if(i == disp)
            writeWord( reg, value );
        else
            writeWord( REG_NO_OPERATION, 0x00 );
    }
    CS = 1;
}

static void setRegisterForAll( LEDMAT_REGISTER reg, uint8_t value ){
    CS = 0;
    for( uint8_t i = NUMBER_OF_MATRIX; i ; i-- ){
        writeWord( reg, value );
    }
    CS = 1;
    
}

void LEDMatrix_Initialize( ){
    spiInit();
    CS_TRIS = 0;
    CS = 1;
    __delay_ms(10);
    
    autoFlush = 0;
    
    // Desactivar el modo Shutdown
    setRegisterForAll( REG_MODE, MODE_NORMAL );
    
    // Utilizar las 8 columnas
    setRegisterForAll( REG_SCAN_LIMIT, 0x07 );
    
    setRegisterForAll( REG_INTENSITY, 0x00 );
    // No decodificar valores de digitos
    setRegisterForAll( REG_DECODE_MODE, DECODE_MODE_NO_DECODE );

}

/** Draw Functions **/

void LEDMatrix_DrawPixel( uint8_t disp, uint8_t pixel, bool value ){
    if( disp >= NUMBER_OF_MATRIX )
        return;
    
    if( value )
        buffer[ (disp<<3) + ((pixel>>4) & 0x0F) ] |= 1u<<(pixel&0x0F); 
    else
        buffer[ (disp<<3) + ((pixel>>4) & 0x0F) ] &= ~(1<<(pixel&0x0F));
    
    if( autoFlush )
        LEDMatrix_Flush(disp);
}

void LEDMatrix_DrawCol( uint8_t disp, uint8_t col, uint8_t value ){
    if( disp >= NUMBER_OF_MATRIX || col > 7 )
        return;
    
    buffer[ (disp<<3) + col ] = value;

    if( autoFlush )
        LEDMatrix_Flush(disp);

}

void LEDMatrix_DrawMatrix( uint8_t disp, uint8_t *m ){
    offset = buffer + (disp<<3);
    
    for( i = 0; i < 8; i++ ){
        *offset = m[i];
        offset++;
    }
    
    if( autoFlush )
        LEDMatrix_Flush(disp);
}


void LEDMatrix_Clear(uint8_t disp){
    disp <<= 3;
    offset = buffer+disp;
    i = 8;
    while( i-- ){
        *offset = 0;
        offset++;
    }

    if( autoFlush )
        LEDMatrix_Flush(disp);
}

void LEDMatrix_ClearAll(){
    i = NUMBER_OF_MATRIX << 3;
    while( i-- ){
        buffer[i] = 0;
    }
    
    if( autoFlush )
        LEDMatrix_FlushAll();

}

void LEDMatrix_Flush(uint8_t disp){
    offset = buffer + (disp<<3) +8;
    
    for( uint8_t c = 8; c; c-- ){ // por cada columna o digito
        
        setRegister( disp, c, *(--offset) );
    }
}

void LEDMatrix_FlushAll( ){
    for( uint8_t c = 8; c; c-- ){ // por cada columna (o digito)
        CS = 0;
        for( uint8_t i = NUMBER_OF_MATRIX-1; i != 255; i-- ){ // de cada display
            writeWord( c, buffer[(i<<3) + c-1] );               // dar valor
        }
        CS = 1;
    }
}



/** Control Functions **/

void LEDMatrix_AutoFlush( _Bool active ){
    autoFlush = active;
}

void LEDMatrix_SetIntensity(uint8_t intensity){
    setRegisterForAll( REG_INTENSITY, intensity );
}

void LEDMatrix_ShutdownAll(){
    setRegisterForAll( REG_MODE, MODE_SHUTDOWN );
}
