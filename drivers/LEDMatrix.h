/* 
 * File:   LEDMatrix.h
 * Author: jose
 * 
 * Controlador de Matriz Led 8x8 utilizando el integrado 
 * MAX7219/MAX7221. Es necesario configurar correctamente 
 * el archivo de cabecera LEDMatrix_config.h
 * 
 * Created on 21 de octubre de 2019, 19:06
 */

#ifndef LEDMATRIX_H
#define	LEDMATRIX_H

#include <stdint.h>
#include <stdbool.h>

typedef enum{
    ROW_0 = 0,
    ROW_1 = 1,
    ROW_2 = 2,
    ROW_3 = 3,
    ROW_4 = 4,
    ROW_5 = 5,
    ROW_6 = 6,
    ROW_7 = 7,
} ROWS;

typedef enum{
    COL_0 = 0<<4,
    COL_1 = 1<<4,
    COL_2 = 2<<4,
    COL_3 = 3<<4,
    COL_4 = 4<<4,
    COL_5 = 5<<4,
    COL_6 = 6<<4,
    COL_7 = 7<<4,
} COLS;

typedef enum{
    REG_NO_OPERATION    = 0x00, // comando nop
    REG_DIGIT0          = 0x01, // digito 0
    REG_DIGIT1          = 0x02, // digito 1
    REG_DIGIT2          = 0x03, // digito 2
    REG_DIGIT3          = 0x04, // digito 3
    REG_DIGIT4          = 0x05, // digito 4
    REG_DIGIT5          = 0x06, // digito 5
    REG_DIGIT6          = 0x07, // digito 6
    REG_DIGIT7          = 0x08, // digito 7
    REG_DECODE_MODE     = 0x09, // modo de decodificacion. Valor: 0x00, 0x01, 0x0F, 0xFF
    REG_INTENSITY       = 0x0A, // intensidad. Valor: 0x0-0xF
    REG_SCAN_LIMIT      = 0x0B, // limite de scan. Valor: 0x0-0x7
    REG_MODE            = 0x0C, // modo de operacion. Valor: 0x0-0x1
    REG_DISPLAY_TEST    = 0x0D  // display test. Valor: 0x00, 0x01
} LEDMAT_REGISTER;


#define MODE_SHUTDOWN   0x00u
#define MODE_NORMAL     0x01u

#define DECODE_MODE_NO_DECODE       0x00    // no decodifica
#define DECODE_MODE_CODE_DIGIT0     0x01    // decodifica el digito 0
#define DECODE_MODE_CODE_LOWNIBBLE  0x0F    // decodifica los digitos 0-3
#define DECODE_MODE_CODE_ALL        0xFF    // decodifica todos los digitos

#define DISPLAY_TEST_OFF    0x00
#define DISPLAY_TEST_ON     0x01


#ifdef	__cplusplus
extern "C" {
#endif
    
    /**
     * Configura las matrices 8x8
     * @Desc Configura los pines y registros necesarios del MCU
     * 
     * @dep
     * Ver archivo de cabecera: LEDMatrix_config.h
     **/
    void LEDMatrix_Initialize( );
    
    /**
     * @desc Modificar un pixel de una matriz
     * @param disp - especifica en que matriz actuar. 
     * @param pixel - OR entre dos elementos de los enum: ROWS y COLS
     * @param value - 1 encender, 0 apagar
     * 
     * @note Si la opcion autoflush no esta activada es necesario ejecutar
     * la rutina LEDMatrix_Flush(disp) para efectuar los cambios.
     */
    void LEDMatrix_DrawPixel( uint8_t disp, uint8_t pixel, bool value );
    
    /**
     * Muestra un patron de leds en una matriz
     * @param disp - matriz a modificar
     * @param m - Arreglo de 8 elementos que contiene el patron
     * a mostrar en la matriz.
     */
    void LEDMatrix_DrawMatrix( uint8_t disp, uint8_t *m );
    
    /**
     * Modifica la columna especificada
     * @param disp - especifica en que matriz actuar.
     * @param col - columna a modificar [0-8]
     * @param value - byte con la configuracion de la columna
     * 
     * @note Si la opcion autoflush no esta activada es necesario ejecutar
     * la rutina LEDMatrix_Flush(disp) para efectuar los cambios.
     */
    void LEDMatrix_DrawCol( uint8_t disp, uint8_t col, uint8_t value );
    
    /**
     * Apaga todos los leds de la matriz indicada
     * @param disp - matriz sobre la cual actuar
     * 
     * @note Si la opcion autoflush no esta activada es necesario ejecutar
     * la rutina LEDMatrix_Flush o LEDMatrix_FlushAll para efectuar los cambios
     * en la matriz.
     */
    void LEDMatrix_Clear( uint8_t disp );
    
    
    /**
     * Apaga todos los leds de todas las matrices 
     * 
     * @note Si la opcion autoflush no esta activada es necesario ejecutar
     * la rutina LEDMatrix_Flush o LEDMatrix_FlushAll para efectuar los cambios
     * en la matriz.
     */
    void LEDMatrix_ClearAll();
    
    
    /**
     * Modifica el modo de operacion de la matriz indicada
     * @param disp - matriz 
     * @param mode - modo de operacion. Valores:
     *      MODE_SHUTDOWN (Pone la matriz en modo de bajo consumo),
     *      MODE_NORMAL (La matriz funciona normalmente)
     */
    void LEDMatrix_SetMode( uint8_t disp, uint8_t mode );
    
    /**
     * Habilita el refrescamiento automatico. Cuando es activado las funciones 
     * de Draw y Clear modifican automaticamente la matriz de lo contrario es
     * necesario ejecutar las rutinas LEDMatrix_Flush o LEDMatrix_FlushAll.
     * @param mode: 1 activar, 0 desactivar
     */
    void LEDMatrix_AutoFlush( _Bool mode );
    
    /**
     * macro para LEDMatrix_SetMode( disp, MODE_SHUTDOWN );
     */    
#define LEDMatrix_Shutdown( disp ) LEDMatrix_SetMode( disp, MODE_SHUTDOWN )

    /**
     * Pone todas las matrices en modo de bajo consumo
     */
    void LEDMatrix_ShutdownAll();
    
    /**
     * Configura la intensidad de los leds de todas las matrices
     * 
     * @param intensity Especifica la intensidad del brillo de los leds. [0-15]
     * 
     **/
    void LEDMatrix_SetIntensity( uint8_t intensity );
    
    /**
     * Actualiza la informacion del buffer hacia la matiz
     * @param disp - matriz 
     */
    void LEDMatrix_Flush( uint8_t disp );

    /**
     * Actualiza la informacion del buffer de todas las matrices
     * @param disp - matriz 
     */
    void LEDMatrix_FlushAll( );
    



#ifdef	__cplusplus
}
#endif

#endif	/* LEDMATRIX_H */

