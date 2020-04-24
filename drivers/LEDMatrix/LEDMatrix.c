/**
 * @file   LEDMatrix.c
 * @author Jose Guerra Carmenate
 * 
 * @brief Implementacio'n de la API del controlador de Matriz Led 8x8 
 * utilizando el integrado MAX7219/MAX7221. 
 *
 * @note Es necesario configurar correctamente el archivo de cabecera LEDMatrix_config.h
 * 
 * @date 21 de octubre de 2019
 */

#include <xc.h>
#include "LEDMatrix.h"
#include "LEDMatrix_config.h"
#include "device_config.h" // _XTAL_MACRO

/**
 @brief Envia una palabra (16-bits) utilizando la macro <c>sendByte</c> 
 especificada en el archivo de cabecera LEDMatrix_config.h
*/
#define writeWord( reg, value ) do{         \
                        sendByte(reg);      \
                        while( isBusy() );  \
                        sendByte(value);    \
                        while( isBusy() );  \
                        }while(0)

/**
 @brief Buffer con la informacion de las matrices
*/
static uint8_t buffer[NUMBER_OF_MATRIX*8]; 

/**
 @brief Bit para el modo autoFlush. Cuando es puesto a uno las funciones
 Draw y Clear actualizan la matriz automaticamente. En caso contrario es
 necesario ejecutar la rutina LEDMatrix_FlushAll, LEDMatrix_Flush.
*/
__bit autoFlush;                    

/**
 @brief Variable auxiliar. Utilizada en varios procesos
*/
uint8_t upper;

/**
 @brief Variable auxiliar. Utilizada en varios procesos
*/
uint8_t i;                   // variables auxiliares

/**
 @brief Variable auxiliar. Utilizada en varios procesos
*/
uint8_t *offset;                    

/**
 * @brief Asigna un valor a un registro especifico de la matriz indicada 
 * @param[in] disp Especifica en que matriz actuar. Valor: 0-NUMBER_OF_MATRIX 
 * @param[in] reg Especifica que registro modificar. Un elemento del enum LEDMAT_REGISTER
 * @param[in] value Valor para el registro 
 * 
 */
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

/**
 * @brief Asigna valor a un registro especifico de todas las matriz 
 * @param[in] reg Especifica que registro modificar. Un elemento del enum LEDMAT_REGISTER
 * @param[in] value Valor para el registro 
 * 
 */
static void setRegisterForAll( LEDMAT_REGISTER reg, uint8_t value ){
    CS = 0;
    for( uint8_t i = NUMBER_OF_MATRIX; i ; i-- ){
        writeWord( reg, value );
    }
    CS = 1;   
}

/*
 * Ver cabecera LEDMatrix.h
 */
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

/* Draw Functions */

/*
 * Ver cabecera LEDMatrix.h
 */
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

/*
 * Ver cabecera LEDMatrix.h
 */
void LEDMatrix_DrawCol( uint8_t disp, uint8_t col, uint8_t value ){
    if( disp >= NUMBER_OF_MATRIX || col > 7 )
        return;
    
    buffer[ (disp<<3) + col ] = value;

    if( autoFlush )
        LEDMatrix_Flush(disp);

}

/*
 * Ver cabecera LEDMatrix.h
 */
void LEDMatrix_DrawMatrix( uint8_t disp, uint8_t stCol, uint8_t *p, uint8_t cnt ){
    if( disp >= NUMBER_OF_MATRIX || stCol > 7 )
        return;
    
    offset = buffer + (disp<<3) + stCol;
    
    for( i = 0; i < cnt; i++ ){
        *offset = p[i];
        offset++;
    }
    
    if( autoFlush )
        LEDMatrix_Flush(disp);
}

/*
 * Ver cabecera LEDMatrix.h
 */
void LEDMatrix_Clear(uint8_t disp){
    if( disp >= NUMBER_OF_MATRIX )
        return;
        
    offset = buffer+(disp<<3);
    i = 8;
    while( i-- ){
        *offset = 0;
        offset++;
    }
    
    if( autoFlush )
        LEDMatrix_Flush(disp);
}

/*
 * Ver cabecera LEDMatrix.h
 */
void LEDMatrix_ClearAll(){
    i = NUMBER_OF_MATRIX << 3;
    while( i-- ){
        buffer[i] = 0;
    }
    
    if( autoFlush )
        LEDMatrix_FlushAll();

}

/*
 * Ver cabecera LEDMatrix.h
 */
void LEDMatrix_Flush(uint8_t disp){
    offset = buffer + (disp<<3) +8;
    
    for( uint8_t c = 8; c; c-- ){ // por cada columna o digito
        setRegister( disp, c, *(--offset) );
    }
}

/*
 * Ver cabecera LEDMatrix.h
 */
void LEDMatrix_FlushAll( ){
    for( uint8_t c = 8; c; c-- ){ // por cada columna (o digito)
        CS = 0;
        for( uint8_t i = NUMBER_OF_MATRIX-1; i != 255; i-- ){ // de cada display
            writeWord( c, buffer[(i<<3) + c-1] );               // dar valor
        }
        CS = 1;
    }
}

/* Control Functions */

/*
 * Ver cabecera LEDMatrix.h
 */
void LEDMatrix_AutoFlush( _Bool active ){
    autoFlush = active;
}

/*
 * Ver cabecera LEDMatrix.h
 */
void LEDMatrix_SetIntensity(uint8_t intensity){
    setRegisterForAll( REG_INTENSITY, intensity );
}

/*
 * Ver cabecera LEDMatrix.h
 */
void LEDMatrix_ShutdownAll(){
    setRegisterForAll( REG_MODE, MODE_SHUTDOWN );
}
