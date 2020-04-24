/**   
   @author Jose Guerra Carmenate
   
   @file HCMS-29xx_config.h

   @brief
    This is the configuration header file for HCMS-29xx Display driver using 8bits PIC MCUs
   

    This file store a set of define macros for configure the HCMS-29xx Display Driver
   		
   <b>Circuit</b> 
   @verbatim                       
  +-----------------------------+            +-------------------------------+ 
  |       _HCMS_29xx_DISPLAY_Din|------------| Din                           | 
  |  PIC  _HCMS_29xx_DISPLAY_RS |------------| RS          HCMS-29xx         | 
  |  MCU  _HCMS_29xx_DISPLAY_CLK|------------| CLK          Display          |     ___
  |       _HCMS_29xx_DISPLAY_CE |------------| CE                         RST|--+-|___|--Vcc
  +-----------------------------+            +-------------------------------+  |   R
                                                                               === Cap
                                                                                |
                                                                               GND
  @endverbatim
 */

#ifndef HCMS_29xx_CONFIG_H
#define	HCMS_29xx_CONFIG_H

/******************************************************************************
 ********************* Section: Configuration Options *************************
 ******************************************************************************/

/**
 * @brief
 *  Permite activar el uso del alfabeto almacenado en font5x7.h
 * 
 * @values
 *  - 1: Utiliza el alfabeto contenido en font5x7.h
 *  - 0: No utiliza el alfabeto contenido en font5x7.h
 * 
 * @note En caso de  asignar 0 es necesario implementar la funcion _FONT5x7_CHAR_TO_MAP.
 * @note Esta funcion recbira un caracter y debe devolver un puntero a la ubicacion
 * del patron de dicho caracter.
 *
 * <b>Ejemplo</b>
 * @code
 * // para #define HCMS_29xx_USE_FONT5X7 0
 * const unsigned char* fontSpaceSymbol = { 0x00, 0x00, 0x00, 0x00, 0x00 };
 * const unsigned char* fontNumSymbol = { 0x14, 0x7F, 0x14, 0x7F, 0x14 };
 * const unsigned char* fontPercentSymbol = { 0x23, 0x13, 0x08, 0x64, 0x62};
 * 
 * const unsigned char* _FONT5x7_CHAR_TO_MAP( char x ){
 *   switch( x ){
 *      case '#':
 *          return fontNumSymbol;
 * 
 *      case '%':
 *          return fontPercentSymbol;
 * 
 *      default:
 *          return fontSpaceSymbol;
 *   }
 * }
 * 
 * @endcode
 * 
 * 
 **/
#define HCMS_29xx_USE_FONT5X7 1



/* Data In pin Macros */

#define _HCMS_29xx_DISPLAY_Din 		GP0       ///< Bit del registro PORT del puerto (pin utilizado para Din) 
#define _HCMS_29xx_DISPLAY_Din_Dir 	TRISIO0 ///< Bit del registro TRIS del puerto (pin utilizado para Din)

/** Register Select pin Macros **/

#define _HCMS_29xx_DISPLAY_RS  		GP1       ///< Bit del registro PORT del puerto (pin utilizado para RS)
#define _HCMS_29xx_DISPLAY_RS_Dir	TRISIO1   ///< Bit del registro TRIS del puerto (pin utilizado para RS)

/** Clock pin Macros **/

#define _HCMS_29xx_DISPLAY_CLK 		GP2 		  ///< Bit del registro PORT del puerto (pin utilizado para CLK)
#define _HCMS_29xx_DISPLAY_CLK_Dir 	TRISIO2 ///< Bit del registro TRIS del puerto (pin utilizado para CLK)

/** Chip Enable pin Macros **/

#define _HCMS_29xx_DISPLAY_CE  		GP5       ///< Bit del registro PORT del puerto (pin utilizado para CE)
#define _HCMS_29xx_DISPLAY_CE_Dir  	TRISIO5 ///< Bit del registro TRIS del puerto (pin utilizado para CE)

/** Reset pin Macros (optionaly)**/

#define _HCMS_29xx_DISPLAY_RST GP5         ///< Bit del registro PORT del puerto (pin utilizado para RST)
#define _HCMS_29xx_DISPLAY_RST_Dir TRISIO5 ///< Bit del registro TRIS del puerto (pin utilizado para RST)

/**
 * 
 * @brief Utilizado para determinar el tiempo en alto (Ton)
 *  y el tiempo en bajo (Toff) de la senal de reloj
 * generada en el pin CLK.
 * @verbatim
  High|  Toff    Ton
      |        _______
  Low |_______|
      +--------------->
  
  Toff = Ton
  @endverbatim
 * @note
 *  Comentar para Toff = Ton = Fosc
 **/
//#define CLK_DELAY __delay_us(1)



#endif	/* DISPLAY_CONFIG_H */

