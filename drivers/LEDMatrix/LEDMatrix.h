/**
 * @file   LEDMatrix.h
 * @author Jose Guerra Carmenate
 * 
 * @brief Controlador de Matriz Led 8x8 utilizando el integrado 
 * MAX7219/MAX7221. 
 *
 * @note Es necesario configurar correctamente el archivo de cabecera LEDMatrix_config.h
 * 
 * @date 21 de octubre de 2019, 19:06
 */

#ifndef LEDMATRIX_H
#define	LEDMATRIX_H

#include <stdint.h>
#include <stdbool.h>

/**
 @brief Permite seleccionar la fila de la matriz en algunas rutinas
 **/
typedef enum{
    ROW_0 = 0,///< Fila 0
    ROW_1 = 1,///< Fila 1
    ROW_2 = 2,///< Fila 2
    ROW_3 = 3,///< Fila 3
    ROW_4 = 4,///< Fila 4
    ROW_5 = 5,///< Fila 5
    ROW_6 = 6,///< Fila 6
    ROW_7 = 7,///< Fila 7
} ROWS;

/**
 @brief Permite seleccionar la columna de la matriz en algunas rutinas
 **/
typedef enum{
    COL_0 = 0<<4,///< Columna 0
    COL_1 = 1<<4,///< Columna 1
    COL_2 = 2<<4,///< Columna 2
    COL_3 = 3<<4,///< Columna 3
    COL_4 = 4<<4,///< Columna 4
    COL_5 = 5<<4,///< Columna 5
    COL_6 = 6<<4,///< Columna 6
    COL_7 = 7<<4,///< Columna 7
} COLS;

/**
 @brief Registros disponibles en el chip MAX7219/MAX7221.
 **/
typedef enum{
    REG_NO_OPERATION    = 0x00, ///< comando nop
    REG_DIGIT0          = 0x01, ///< Registro de digito 0
    REG_DIGIT1          = 0x02, ///< Registro de digito 1
    REG_DIGIT2          = 0x03, ///< Registro de digito 2
    REG_DIGIT3          = 0x04, ///< Registro de digito 3
    REG_DIGIT4          = 0x05, ///< Registro de digito 4
    REG_DIGIT5          = 0x06, ///< Registro de digito 5
    REG_DIGIT6          = 0x07, ///< Registro de digito 6
    REG_DIGIT7          = 0x08, ///< Registro de digito 7
    REG_DECODE_MODE     = 0x09, ///< Registro de modo de decodificacion.(ver macros DECODE_MODE_xxx)
    REG_INTENSITY       = 0x0A, ///< Registro de intensidad. Valor: 0x0-0xF
    REG_SCAN_LIMIT      = 0x0B, ///< Registro de limite de scaner. Valor: 0x0-0x7
    REG_MODE            = 0x0C, ///< Registro de modo de operacion. (ver macros MODE_xxx para posibles asignaciones)
    REG_DISPLAY_TEST    = 0x0D  ///< Registro de display test. (ver macros DISPLAY_TEST_xxx)
} LEDMAT_REGISTER;

/**
 @brief Modo Shutdown, desactiva las salidas del chip
*/
#define MODE_SHUTDOWN   0x00u

/**
 @brief Modo de operacion normal
*/
#define MODE_NORMAL     0x01u

/**
 @brief El controlador no decodifica el dato enviado
*/
#define DECODE_MODE_NO_DECODE       0x00    // no decodifica

/**
 @brief El controlador decodifica solo el digito 0
*/
#define DECODE_MODE_CODE_DIGIT0     0x01    // decodifica el digito 0

/**
 @brief El controlador decodifica los digitos del 0-3
*/
#define DECODE_MODE_CODE_LOWNIBBLE  0x0F    // decodifica los digitos 0-3

/**
 @brief El controlador decodifica todos los digitos
*/
#define DECODE_MODE_CODE_ALL        0xFF    // decodifica todos los digitos

/**
 @brief Desactiva la prueba de display. Funcionamiento normal
*/
#define DISPLAY_TEST_OFF    0x00

/**
 @brief Activa la prueba de display. Enciende todos los leds
*/
#define DISPLAY_TEST_ON     0x01


#ifdef	__cplusplus
extern "C" {
#endif
    
    /**
     * @brief Inicializa los MAX7219/MAX7221 conectados en cascada
     * 
     * Esta funcion configura los MAX7219/MAX7221 conectados en cascada.
     * La cantidad de matrices y las funciones para el envio de comandos
     * son definidos en el archivo de cabecera LEDMatrix_config.h.  
     * 
     * @note El archivo de cabecera LEDMatrix_config.h debe estar correctamente
     * configurado
     **/
    void LEDMatrix_Initialize( );
    
    /**
     * @brief Modificar un pixel de una matriz
     
     * @param[in] disp especifica en que matriz actuar. Debe ser un
     * numero en el intervalo: 0-NUMBER_OF_MATRIX.
     * 
     * @param[in] pixel OR entre dos elementos de los enum: ROWS y COLS.
     * solo uno de cada tipo.
     * @param[in] value <c>true</c> - encender bit, <c>false</c> - apagar bit. 
     * 
     * @note Si la opcion autoflush no esta activada es necesario ejecutar
     * la rutina LEDMatrix_Flush(disp) para efectuar los cambios.
     *
     * <b>Example</b>
     * @code
     * LEDMatrix_DrawPixel( 0, ROW_1 | COL_2, true );   // enciende el led de la
     *                                                  // tercera columna de la
     *                                                  // segunda fila de la
     *                                                  // primera matriz.
     * @endcode
     */
    void LEDMatrix_DrawPixel( uint8_t disp, uint8_t pixel, bool value );
    
    /**
     * @brief Muestra un patron de leds en una matriz
     *
     * @param[in] disp Matriz a modificar
     * @param[in] stCol Columna inicial
     * @param[in] m Arreglo de 8 elementos que contiene el patron
     * a mostrar en la matriz.
     * @param[in] cnt Cantidad de columnas a escribir
     * <b>Example</b>
     *  @code
     *   uint8_t pp[] = { 0xFF, 0xAA, 0xFF };
     *   LEDMatrix_DrawMatrix(0, 2, pp, 3); // en la primera matriz
     *                                      // empezando en la columna 2
     *                                      // dibujar el patron pp
     *                                      // de 3 columnas de longitud
     *  @endcode      
     */
    void LEDMatrix_DrawMatrix( uint8_t disp, uint8_t stCol, uint8_t *m,  uint8_t cnt );
    
    /**
     * @brief Modifica la columna especificada
     * @param[in] disp Especifica en que matriz actuar.
     * @param[in] col Columna a modificar [0-8]
     * @param[in] value Byte con la configuracion de la columna 
     *  (bits en 1 encendidos y en 0 apagados)
     * 
     * @note Si la opcion autoflush no esta activada es necesario ejecutar
     * la rutina LEDMatrix_Flush(disp) para efectuar los cambios.
     * 
     * <b>Example</b>
     * @code
     *    LEDMatrix_DrawCol( 1, 0, 0b10101010 );  // alterna los leds de 
     *                                                  // la primera columna de
     *                                                  // de la segunda matrix
     * @endcode
     */
    void LEDMatrix_DrawCol( uint8_t disp, uint8_t col, uint8_t value );
    
    /**
     * @brief Apaga todos los leds de la matriz indicada
     * @param[in] disp matriz sobre la cual actuar
     * 
     * @note Si la opcion autoflush no esta activada es necesario ejecutar
     * la rutina LEDMatrix_Flush o LEDMatrix_FlushAll para efectuar los cambios
     * en la matriz.
     * 
     * <b>Example</b>
     * @code
     * LEDMatrix_Clear( 2 ); //apaga todos los leds de la tercera matriz
     * @endcode
     */
    void LEDMatrix_Clear( uint8_t disp );
    
    
    /**
     * @brief Apaga todos los leds de todas las matrices 
     * 
     * @note Si la opcion autoflush no esta activada es necesario ejecutar
     * la rutina LEDMatrix_Flush o LEDMatrix_FlushAll para efectuar los cambios
     * en la matriz.
     * 
     * <b>Example</b>
     * @code
     * LEDMatrix_ClearAll(); //apaga todos los leds de todas las matrices
     * @endcode
     */
    void LEDMatrix_ClearAll();
    
    
    /**
     * @brief Modifica el modo de operacion de la matriz indicada
     * @param[in] disp matriz 
     * @param[in] mode modo de operacion. Valores:
     *      - MODE_SHUTDOWN (Pone la matriz en modo de bajo consumo),
     *      - MODE_NORMAL (La matriz funciona normalmente)
     *
     * <b>Example</b>
     * @code
     * LEDMatrix_SetMode( 0,  MODE_SHUTDOWN); // pone la primera matriz en modo
     *                                        // de bajo consumo   
     * @endcode
     */
    void LEDMatrix_SetMode( uint8_t disp, uint8_t mode );
    
    /**
     * @brief Habilita el refrescamiento automatico. 
     *
     * Cuando es activado las funciones de Draw y Clear modifican 
     * automaticamente la matriz de lo contrario es necesario ejecutar 
     * las rutinas LEDMatrix_Flush o LEDMatrix_FlushAll.
     * 
     * @param[in] mode <c> true</c> activar, <c>false</c> desactivar
     * 
     * <b>Example</b>
     * @code
     * LEDMatrix_AutoFlush(true); // activa el auto refrescamiento   
     * @endcode
     */
    void LEDMatrix_AutoFlush( _Bool mode );
    
    /**
     * @brief Pone la matriz <c> disp</c> en modo de bajo consumo
     */    
#define LEDMatrix_Shutdown( disp ) LEDMatrix_SetMode( disp, MODE_SHUTDOWN )

    /**
     * @brief Pone todas las matrices en modo de bajo consumo
     */
    void LEDMatrix_ShutdownAll();
    
    /**
     * @brief Configura la intensidad de los leds de todas las matrices
     * 
     * @param intensity Especifica la intensidad del brillo de los leds.
     *  Los valores admisibles estan en el rango: 0-15.
     * 
     * <b>Example</b>
     * @code
     * LEDMatrix_SetIntensity(0); // brillo de los leds al minimo   
     * @endcode
     **/
    void LEDMatrix_SetIntensity( uint8_t intensity );
    
    /**
     * @brief Actualiza la informacion del buffer hacia la matiz
     * @param disp matriz a actualizar
     * 
     * <b>Example</b>
     * @code
     *  LEDMatrix_AutoFlush(false);             // desactivar el auto-refrescamiento
     *  LEDMatrix_DrawCol( 1, 0, 0b10101010 );  // se modifica sol el buffer
     *  LEDMatrix_Flush( 1 );                   // actualizar la segunda matriz 
     * @endcode
     */
    void LEDMatrix_Flush( uint8_t disp );

    /**
     * @brief Actualiza la informacion del buffer de todas las matrices
     *
     * <b>Example</b>
     * @code
     *  LEDMatrix_AutoFlush(false);             // desactivar el auto-refrescamiento
     *  LEDMatrix_DrawCol( 1, 0, 0b10101010 );  // se modifica sol el buffer
     *  LEDMatrix_DrawCol( 0, 5, 0b11011011 );  // se modifica sol el buffer
     *  LEDMatrix_FlushAll( );                  // actualizar todas las matrices 
     * @endcode
     */
    void LEDMatrix_FlushAll( );
    



#ifdef	__cplusplus
}
#endif

#endif	/* LEDMATRIX_H */

