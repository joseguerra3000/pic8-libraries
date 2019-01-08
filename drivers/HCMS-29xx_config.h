/* 
 * File:   HCMS-29xx_config.h
 * Author: root
 *
 * Created on 3 de enero de 2019, 13:23
 * 
 * 
 * 
 * 
 * Circuit:
 *                                      
 * +------------------------+            +-------------------------------+ 
 * |       ALPHA_DISPLAY_Din|------------| Din                           | 
 * |  PIC  ALPHA_DISPLAY_RS |------------| RS          HCMS-29xx         | 
 * |  MCU  ALPHA_DISPLAY_CLK|------------| CLK          Display          |     ___
 * |       ALPHA_DISPLAY_CE |------------| CE                         RST|--+-|___|--Vcc
 * +------------------------+            +-------------------------------+  |   R
 *                                                                         === Cap
 *                                                                          |
 *                                                                         GND
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
 *      Esta version ocupa menos espacio en memoria de programa y da datos.
 *      Los pines utilizados deben ser definidos en este fichero
 *   __HCMS_29xx_NORMAL_VERSION:
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
#define __HCMS_29xx_COMPILE_LedDisplay_Scroll 0
#define __HCMS_29xx_COMPILE_LedDisplay_GetCursor 0
#define __HCMS_29xx_COMPILE_LedDisplay_PrintUInt16 1
#define __HCMS_29xx_COMPILE_LedDisplay_PrintInt16 1
#define __HCMS_29xx_COMPILE_LedDisplay_PrintFloat 1



#if (HCMS_29xx_VERSION == __HCMS_29xx_LITE_VERSION)

/** Data In pin Macros **/

#define _HCMS_29xx_DISPLAY_Din GP0           // Data In Port bit register
#define _HCMS_29xx_DISPLAY_Din_Dir TRISIO0   // Data In Tris bit register

/** Register Select pin Macros **/

#define _HCMS_29xx_DISPLAY_RS  GP1           // Register Select Port bit register 
#define _HCMS_29xx_DISPLAY_RS_Dir  TRISIO1   // Register Select Tris bit register

/** Clock pin Macros **/

#define _HCMS_29xx_DISPLAY_CLK GP2           // Clock Port bit register
#define _HCMS_29xx_DISPLAY_CLK_Dir TRISIO2   // Clock Tris bit register

/** Chip Enable pin Macros **/

#define _HCMS_29xx_DISPLAY_CE  GP4           // Chip Enable Port bit register
#define _HCMS_29xx_DISPLAY_CE_Dir  TRISIO4   // Chip Enable Tris bit register

/** Reset pin Macros (optionaly)**/
//#define _HCMS_29xx_DISPLAY_RST GP5         // Reset bit register
//#define _HCMS_29xx_DISPLAY_RST_Dir TRISIO5 // Reset bit register

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
 **/
//#define CLK_DELAY __delay_us(1)


#ifdef	__cplusplus
extern "C" {
#endif




#ifdef	__cplusplus
}
#endif

#endif	/* DISPLAY_CONFIG_H */

