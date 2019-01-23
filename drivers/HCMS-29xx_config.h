/**
   HCMS-29xx Display Driver Configuration Header File for 8bit PIC MCUs
   
   @Author
 	Jose Guerra Carmenate
   
   @File Name
 	HCMS-29xx_config.h

   @Summary
    This is the configuration header file for HCMS-29xx Display driver using 8bits PIC MCUs
   
   @Description
    This file store a set of define macros for configure the HCMS-29xx Display Driver:
    	+===============================+===========================================================+
    	|MACRO							|		Function											|
    	+===============================+===========================================================+
    	|HCMS_29xx_VERSION				|	Select the API to compile ( only LITE is implemented)   |
    	+-------------------------------+-----------------------------------------------------------+
    	|HCMS_29xx_USE_FONT5X7			|	Use the font5x7.h header for character generator		|
    	+-------------------------------+-----------------------------------------------------------+
   		|__HCMS_29xx_COMPILE_<yyyy>		|	Enable/Disable some API function (for optimization)		|
   		|								|  ( Ej: __HCMS_29xx_COMPILE_LedDisplay_Scroll 1)			|
   		+-------------------------------+-----------------------------------------------------------+
   		|_HCMS_29xx_DISPLAY_<yyy>		|	Used for define the Port/Lat register bit for the		|
   		|								|  specified Line. (Ej: _HCMS_29xx_DISPLAY_Din GP0 )		|
   		+-------------------------------+-----------------------------------------------------------+		
   		|_HCMS_29xx_DISPLAY_<yyy>_Dir	| 	Used for define the TRIS register bit for the			|
   		|								|  specified Line. (Ej:_HCMS_29xx_DISPLAY_CLK_Dir TRISIO2 )	|
   		+-------------------------------+-----------------------------------------------------------+								
   		|CLK_DELAY						|	Define the Ton and Toff delay for Clock Signal			|
   		+-------------------------------+-----------------------------------------------------------+
   		
   @Circuit:                                
  +-----------------------------+            +-------------------------------+ 
  |       _HCMS_29xx_DISPLAY_Din|------------| Din                           | 
  |  PIC  _HCMS_29xx_DISPLAY_RS |------------| RS          HCMS-29xx         | 
  |  MCU  _HCMS_29xx_DISPLAY_CLK|------------| CLK          Display          |     ___
  |       _HCMS_29xx_DISPLAY_CE |------------| CE                         RST|--+-|___|--Vcc
  +-----------------------------+            +-------------------------------+  |   R
                                                                               === Cap
                                                                                |
                                                                               GND
 */

#ifndef HCMS_29xx_CONFIG_H
#define	HCMS_29xx_CONFIG_H

/******************************************************************************
 ************************* Section: Local Macros ******************************
 ******************************************************************************/



/**
 * Define for Compile Lite version API
 **/
#define __HCMS_29xx_LITE_VERSION 1



/**
 * Define for Compile Normal version API
 **/
#define __HCMS_29xx_NORMAL_VERSION 2



/******************************************************************************
 ********************* Section: Configuration Options *************************
 ******************************************************************************/

/**
 * HCMS_29xx_VERSION
 * 
 * @Description
 *  Es utilizada para definir cual version compilar:
 *    __HCMS_29xx_LITE_VERSION:
 *      Esta version ocupa menos espacio en memoria de programa y de datos.
 *      Los pines utilizados deben ser definidos en este fichero
 *   __HCMS_29xx_NORMAL_VERSION (no Implementada):
 *      Esta version ocupa mas espacio en memoria de programma y de datos.
 *      Los pines utilizados son definidos mediante la funcion de inicializacion
 * 
 **/
#define HCMS_29xx_VERSION __HCMS_29xx_NORMAL_VERSION




/**
 * HCMS_29xx_USE_FONT5X7
 * 
 * @Description
 *  Permite utilizar el alfabeto almacenado en font5x7.h
 * 
 * @Values
 *  - 1: Utiliza el alfabeto contenido en font5x7.h
 *  - 0: No utiliza el alfabeto contenido en font5x7.h
 * 
 * @Notes
 *  En caso de  asignar 0 es necesario implementar la funcion _FONT5x7_CHAR_TO_MAP
 * Ejemplo:
 * 
 * <Code>
 * 
 * const unsigned char* fontSpaceSimbol = { 0x00, 0x00, 0x00, 0x00, 0x00 };
 * 
 * const unsigned char* fontNumSimbol = { 0x14, 0x7F, 0x14, 0x7F, 0x14 };
 * 
 * const unsigned char* fontPercentSimbol = { 0x23, 0x13, 0x08, 0x64, 0x62};
 * 
 * const unsigned char* _FONT5x7_CHAR_TO_MAP( char x ){
 * 
 *  switch( x ){
 * 
 *      case '#':
 * 
 *          return fontNumSimbol;
 * 
 *          break;
 * 
 *      case '%':
 * 
 *          return fontPercentSimbol;
 * 
 *      default:
 * 
 *          return fontSpaceSimbol;
 * 
 *  }
 * 
 * }
 * 
 * </Code>
 * 
 * Esta funcion recbira un caracter y debe devolver un puntero a la ubicacion
 * del patron de dicho caracter.
 * 
 **/
#define HCMS_29xx_USE_FONT5X7 1




/** Compilar estas funciones( 0 - NO; 1 - SI ) **/

/**
 * @Description
 *  Agrega codigo extra para implementar la funcion LedDisplay_Scroll
 * en caso de no ser necesaria  esta puede ser puesta a cero.
 * @Note
 *  En caso de no ser utilizada el codigo de otras funciones sera simplificado
 * y por tanto ocupará menos espacio en memoria.
 **/
#define __HCMS_29xx_COMPILE_LedDisplay_Scroll 		1


#define __HCMS_29xx_COMPILE_LedDisplay_GetCursor 	1 	// Habilitar/Deshabilitar la Compilacion de la rutina LedDisplay_GetCursor
#define __HCMS_29xx_COMPILE_LedDisplay_PrintUInt16 	1 	// Habilitar/Deshabilitar la Compilacion de la rutina LedDisplay_PrintUInt16
#define __HCMS_29xx_COMPILE_LedDisplay_PrintInt16 	1	// Habilitar/Deshabilitar la Compilacion de la rutina LedDisplay_PrintInt16
#define __HCMS_29xx_COMPILE_LedDisplay_PrintFloat 	1	// Habilitar/Deshabilitar la Compilacion de la rutina LedDisplay_PrintFloat



#if (HCMS_29xx_VERSION == __HCMS_29xx_LITE_VERSION)

/** Data In pin Macros **/

#define _HCMS_29xx_DISPLAY_Din 		GP0       	// Data In Port/Lat bit register
#define _HCMS_29xx_DISPLAY_Din_Dir 	TRISIO0   	// Data In Tris bit register

/** Register Select pin Macros **/

#define _HCMS_29xx_DISPLAY_RS  		GP1       	// Register Select Port/Lat bit register 
#define _HCMS_29xx_DISPLAY_RS_Dir	TRISIO1   	// Register Select Tris bit register

/** Clock pin Macros **/

#define _HCMS_29xx_DISPLAY_CLK 		GP2 		// Clock Port/Lat bit register
#define _HCMS_29xx_DISPLAY_CLK_Dir 	TRISIO2   	// Clock Tris bit register

/** Chip Enable pin Macros **/

#define _HCMS_29xx_DISPLAY_CE  		GP4       	// Chip Enable Port/Lat bit register
#define _HCMS_29xx_DISPLAY_CE_Dir  	TRISIO4   	// Chip Enable Tris bit register

/** Reset pin Macros (optionaly)**/

//#define _HCMS_29xx_DISPLAY_RST GP5         // Reset bit Port/Lat register
//#define _HCMS_29xx_DISPLAY_RST_Dir TRISIO5 // Reset bit Tris register

#endif

/**
 * CLK_DELAY
 * 
 * @Description
 *  Utilizado para determinar el tiempo en alto (Ton)
 *  y el tiempo en bajo (Toff) de la senal de reloj
 * generada en el pin CLK.
 * 
 * High|  Toff    Ton
 *     |        _______
 * Low |_______|
 *     +--------------->
 * 
 * Toff = Ton
 * @Notes
 *  Comentar para Toff = Ton = Fosc
 **/
//#define CLK_DELAY __delay_us(1)



#endif	/* DISPLAY_CONFIG_H */

