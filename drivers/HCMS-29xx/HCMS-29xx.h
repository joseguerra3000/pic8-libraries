/**
  @author Jose Guerra Carmenate

  @file
    HCMS-29xx.h

  @brief
    This is the header file for HCMS-29xx Display driver using PIC MCUs

    This header file provides generic APIs for driver the HCMS-29xx Display.
    List of compatible displays:
    @verbatim
        HCMS-2905    HCMS-2902    HCMS-2904    HCMS-2901    HCMS-2903
        HCMS-2915    HCMS-2912    HCMS-2914    HCMS-2911    HCMS-2913
        HCMS-2925    HCMS-2922    HCMS-2924    HCMS-2921    HCMS-2923
        HCMS-2965    HCMS-2962    HCMS-2964    HCMS-2961    HCMS-2963
        HCMS-2975    HCMS-2972    HCMS-2974    HCMS-2971    HCMS-2973
    @endverbatim
  <b>Circuit</b>
  @verbatim                                      
 +------------------------+            +-------------------------------+ 
 |       ALPHA_DISPLAY_Din|------------| Din                           | 
 |  PIC  ALPHA_DISPLAY_RS |------------| RS          HCMS-29xx         | 
 |  MCU  ALPHA_DISPLAY_CLK|------------| CLK          Display          |     ___
 |       ALPHA_DISPLAY_CE |------------| CE                         RST|--+-|___|--Vcc
 +------------------------+            +-------------------------------+  |   R
                                                                         === Cap
                                                                          |
                                                                         GND 
  @endverbatim   
  
  @note To control multiple displays, connect all the control lines except the 
     data line in parallel. The data line can be daisy-chained from right to 
     left, with data out from the first display going to data in of the 
     second, and so forth.                                   
*/

#ifndef HCMS_29xx_H
#define	HCMS_29xx_H

/******************************************************************************
 *********************** Section: Included Files ******************************
 ******************************************************************************/

#include <xc.h>
#include <stdint.h>
#include "HCMS-29xx_config.h"


/******************************************************************************
 ************************ Section: Define Macros ******************************
 ******************************************************************************/

#define ALPHA_DISPLAY_MAX_LENGTH 32u

// control macros (See datasheet)

// CONTROL WORD 0 MACROS

#define _CONTROL_WORD0                  0x00u ///< select the control word 0
#define _CONTROL_WORD0_BRIGHT_PWM_MASK  0x0Fu ///< mask for bright adjust (PWM) (See datasheet)
#define _CONTROL_WORD0_BRIGHT_PEAK_MASK 0x30u ///< mask for bright adjust (Peak Current) (See datasheet)
#define _CONTROL_WORD0_SLEEP_MODE_ON    0x00u ///< put the display on sleep mode
#define _CONTROL_WORD0_SLEEP_MODE_OFF   0x40u ///< put the display on normal mode

// CONTROL WORD 1 MACROS

#define _CONTROL_WORD1                              0x80u ///< select the control word 1
#define _CONTROL_WORD1_DATA_OUT_SERIAL_MODE         0x00u ///< put display on serial mode   
#define _CONTROL_WORD1_DATA_OUT_SIMULTANEOUS_MODE   0x01u ///< put display on simultaneous mode
#define _CONTROL_WORD1_OSC_DIV_1                    0x00u ///< off prescaler oscillator
#define _CONTROL_WORD1_OSC_DIV_8                    0x02u ///< set prescaler oscillator to 8



#ifdef	__cplusplus
extern "C" {
#endif
    
/******************************************************************************
 ********************* Section: HCMS-29xx Display APIs ************************
 ******************************************************************************/
    
    /**
     * @brief Initialize the HCMS-29xx Dislay
     * 
     *  This routine take the number of characters, one buffer and the buffer size
     * and perform the inicialization routine.
     *  This routine configure the pins for comunication
     *  This routine must be called before any other LedDisplay routine.
     * 
     * @pre
     *  HCMS-29xx_config.h mus be configurated
     * 
     * @param[in] _displayLen Amount of caracters.
     * @param[in,out] _displayBuffer Buffer used for store the characters to print on display.
     * @param[in] _bufferSize Size of `_displayBuffer`, need be major or equal that _displayLen.
     *  
     * 
     * <b>Example</b>
     * @code
     * char __bufferForDisplay[16];
     * LedDisplay_Initialize( 8, __bufferForDisplay, 16 );
     * @endcode
     **/
    void LedDisplay_Initialize(uint8_t _displayLen, char* _displayBuffer, uint8_t _bufferSize);
    
    /**
     * @brief
     *  Set the brightness for HCMS-29xx Display
     * 
     *  This routine take one number between [0-15] for set the leds's brightness
     * 
     * @pre
     *  \ref LedDisplay_Initialize routine need be called before.
     * 
     * @param[in] bright: unsigned integer between [0-15]. Value 0 off the led and 
     * value 15 set the maximum bright.
     *      
     * @note
     *  In case of multiple displays the bright is set of all of them.
     * 
     * <b>Example</b>
     * @code
     * char __bufferForDisplay[16];
     * LedDisplay_Initialize( 4, __bufferForDisplay, 10 );
     * LedDisplay_SetBrightness( 14 );
     * @endcode
     **/
    #define LedDisplay_SetBrightness(bright)  LedDisplay_LoadAllControlRegisters( _CONTROL_WORD0 | _CONTROL_WORD0_BRIGHT_PEAK_MASK | _CONTROL_WORD0_SLEEP_MODE_OFF | (_CONTROL_WORD0_BRIGHT_PWM_MASK & bright)  );
    
    /**
     * @brief Load the data stored on the buffer to HCMS-29xx Display.
     * 
     *  This routine load the data stored on the buffer to HCMS-29xx Display
     * having in count the shift operation performed.
     * 
     * @pre LedDisplay_Initialize routine need be called before.
     * 
     * 
     * @note In case of multiple display the data be loaded with out problems.
     * For example: Imagine two HCMS-2973 Display ( 8 characters every one ) 
     * and no shift operation performed.
     * The data stored on buffer be loaded as follow:
     *  - Positions [0-7] loaded to left display.
     *  - Positions [8-15] loaded to right display
     * 
     * 
     * <b>Example</b> 
     * @code
     * char __bufferForDisplay[16];
     * LedDisplay_Initialize( 4, __bufferForDisplay, 10 );
     * LedDisplay_SetBrightness( 14 );
     * strncpy(__display_buffer, "PicMicro", 8);
     * LedDisplay_LoadDotRegister();
     * @endcode
     **/
    void LedDisplay_LoadDotRegister();
    
    /**
     * @brief Load one control word in one HCMS-29xx Display.
     * 
     *  This routine load one control word in one HCMS-29xx Display.
     * 
     * @pre
     *  LedDisplay_Initialize routine need be called before.
     * 
     * @param[in] controlWord: control word to send. See datasheet for details.
     * 
     * <b>Example</b>
     *  
     * @todo Put a code example
     **/    
    void LedDisplay_LoadControlRegister( uint8_t controlWord );
    
    /**
     * @brief
     *  Load one control word on all HCMS-29xx Display.
     * 
     *  This routine load one control word on all HCMS-29xx Display.
     * 
     * @pre
     *  LedDisplay_Initialize routine need be called before.
     * 
     * @param[in] controlWord: control word to send. See datasheet for details.
     * 
     * <b>Example</b>
     *  
     * @todo Put one code example
     **/    
    void LedDisplay_LoadAllControlRegisters( uint8_t controlWord );
    
    /** Display Functions **/

#if HCMS_29xx_USE_FONT5X7 == 1
    /**
     * @brief
     *  Take one character an return one pointer to one char array that
     * have the correspondent map.
     * 
     *  This routine take one character an return one pointer to one char array that
     * have the correspondent map. 
     * One map consist of 5 bytes that together make the representation of 
     * one 5x7 character.
     * 
     * @pre
     *  LedDisplay_Initialize routine need be called before.
     * 
     * @param[in] x: char for get the map
     * 
     * @return const unsigned char* : pointer to the map of x
     * 
     * @note
     *  If HCMS_29xx_USE_FONT5X7 on HCMS-29xx_config.h is definde as 0
     * this function have to be implemented by the user on their source code.
     * 
     * <b>Example</b>
     * @code
     * const unsigned char* fontSpaceSimbol = { 0x00, 0x00, 0x00, 0x00, 0x00 };
    * const unsigned char* fontNumSimbol = { 0x14, 0x7F, 0x14, 0x7F, 0x14 };
    * const unsigned char* fontPercentSimbol = { 0x23, 0x13, 0x08, 0x64, 0x62};
    * const unsigned char* _FONT5x7_CHAR_TO_MAP( char x ){
    * 
    *  switch( x ){
    *      case '#':
    *          return fontNumSimbol;
    * 
    *      case '%':
    *          return fontPercentSimbol;
    * 
    *      default:
    *          return fontSpaceSimbol;
    * 
    *  }
    * }
     * 
     * @endcode
     **/    
    extern const unsigned char* _FONT5x7_CHAR_TO_MAP( char x );
    
#endif
    
    /**
     * @brief Clear the display (make all its characters equal to space ' ') and
     *  positions the cursor in the left side. 
     * 
     *  This routine clear the display makeing all its characters equal to ' '(space),
     * the buffer will also be cleaned and positions the cursor in the left side.
     * 
     * @pre LedDisplay_Initialize routine need be called before.
     * 
     * <b>Example</b>
     * @code
     * LedDisplay_Initialize( 8, __display_buffer, 16 );
     * LedDisplay_SetBrightness( 12 );
     * LedDisplay_PrintInt16( 123, 10 );
     * LedDisplay_Clear();
     * LedDisplay_PrintString( "Ok!" );
     * @endcode
     **/    
    void LedDisplay_Clear( void );
    
    /**
     * @brief
     *  Put the cursor on the first Display's position 
     * 
     *  This routine put the cursor on the first Display's position.
     * 
     * @pre
     *  LedDisplay_Initialize routine need be called before.
     *  
     * <b>Example</b>
     * @code
     * LedDisplay_Initialize( 8, __display_buffer, 16 );
     * LedDisplay_SetBrightness( 12 );
     * LedDisplay_PrintInt16( 123, 10 );
     * LedDisplay_Home();
     * LedDisplay_PrintString( "Ok" );
     * @endcode
     **/ 
    #define LedDisplay_Home()  LedDisplay_SetCursor( 0u );
    
    
    /**
     * @brief
     *  Take an integer and put the cursor on the specified position.
     * 
     * 
     *  This routine, take an integer and put the cursor on the specified position.
     * 
     * @pre
     *  LedDisplay_Initialize routine need be called before.
     * 
     * @param[in] cursorPos: position for the cursor, from `0` to `bufferSize
     * 
     * <b>Example</b>
     * @code
     * LedDisplay_Initialize( 8, __display_buffer, 16 );
     * LedDisplay_SetBrightness( 12 );
     * LedDisplay_PrintInt16( 123, 10 );
     * LedDisplay_SetCursor( 1 );
     * LedDisplay_PrintString( "Ok" );
     * @endcode
     **/
    inline void LedDisplay_SetCursor( uint8_t cursorPos );
    
#if __HCMS_29xx_COMPILE_LedDisplay_GetCursor==1
    
    /**
     * @brief
     *  Return the current cursor position
     * 
     * 
     *  This routine return the current cursor position.
     * 
     * @pre
     *  LedDisplay_Initialize routine need be called before.
     * 
     * @return uint8_t The current cursor position
     * 
     * <b>Example</b>
     * @code
     * LedDisplay_Initialize( 8, __display_buffer, 16 );
     * LedDisplay_SetBrightness( 12 );
     * LedDisplay_PrintInt16( 123, 10 );
     * LedDisplay_SetCursor( 1 );
     * LedDisplay_PrintString( "Ok" );
     * @endcode
     **/
    inline uint8_t LedDisplay_GetCursor();
#endif
    
#if __HCMS_29xx_COMPILE_LedDisplay_Scroll == 1
    
    /**
     * @brief
     *  Take one integer and scroll the display text.
     * 
     * 
     *  This routine take one integer and scroll the display text. if the
     *  argument is positive scroll from left to right, if negative scroll
     *  from right to left.
     * 
     * @pre
     *  LedDisplay_Initialize routine need be called before.
     * 
     * @param[in] dir: number of characters to scroll (the sign define de direction)
     * 
     * <b>Example</b>
     * @code
     * LedDisplay_Initialize( 8, __display_buffer, 16 );
     * LedDisplay_SetBrightness( 12 );
     * LedDisplay_PrintInt16( 123, 10 );
     * LedDisplay_SetCursor( 1 );
     * LedDisplay_PrintString( "Ok" );
     * LedDisplay_Scroll( -2 );
     * __delay_ms(250);
     * LedDisplay_Scroll( 1 );
     * __delay_ms(250);
     * LedDisplay_Scroll( 1 );
     * __delay_ms(250);
     * LedDisplay_Scroll( 1 );
     * __delay_ms(250);
     * LedDisplay_Scroll( 1 );
     * __delay_ms(250);
     * @endcode
     **/
    inline void LedDisplay_Scroll( int8_t dir );
#endif
    
    /**
     * @brief
     *  Take one character map and print it.
     * 
     * 
     *  This routine take one character map and print it.
     * 
     * @pre
     *  LedDisplay_Initialize routine need be called before.
     * 
     * @param map: character map to show on the display
     * 
     * <b>Example</b>
     * @code
     * const unsigned char* fontSpaceSimbol = { 0x00, 0x00, 0x00, 0x00, 0x00 };
     * const unsigned char* fontNumSimbol = { 0x14, 0x7F, 0x14, 0x7F, 0x14 };
     * const unsigned char* fontPercentSimbol = { 0x23, 0x13, 0x08, 0x64, 0x62};
     * //...
     * LedDisplay_Initialize( 8, __display_buffer, 16 );
     * LedDisplay_SetBrightness( 12 );
     * LedDisplay_PutUserChar( fontNumSimbol );
     * LedDisplay_SetCursor( 2 );
     * LedDisplay_PutUserChar( fontPercentSimbol );
     * @endcode
     **/
    void LedDisplay_PutUserChar( const unsigned char *map );  
    
    
    /**
     * @brief
     *  Take one string and print it to the display.
     * 
     *  This routine take one string and print it to the display.
     * 
     * @pre
     *  LedDisplay_Initialize routine need be called before.
     * 
     * @param[in] txt: string to print on the display
     * 
     * <b>Example</b>
     * @code
     * const unsigned char* fontSpaceSimbol = { 0x00, 0x00, 0x00, 0x00, 0x00 };
     * const unsigned char* fontNumSimbol = { 0x14, 0x7F, 0x14, 0x7F, 0x14 };
     * const unsigned char* fontPercentSimbol = { 0x23, 0x13, 0x08, 0x64, 0x62};
     * ...
     * LedDisplay_Initialize( 8, __display_buffer, 16 );
     * LedDisplay_SetBrightness( 12 );
     * LedDisplay_PrintString( "PicMicro" );
     * @endcode
     **/
    void LedDisplay_PrintString( const char *txt);
    
    
    /**
     * @brief
     *  Take one character and print it on the HCMS-29xx Display.
     * 
     * 
     *  This routine take one character and print it on the HCMS-29xx Display.
     * 
     * @pre
     *  LedDisplay_Initialize routine need be called before.
     * 
     * @param[in] x: character that will be printed on the HCMS-29xx Display.
     *  
     * <b>Example</b>
     * @code
     * //...
     * LedDisplay_Initialize( 8, __display_buffer, 16 );
     * LedDisplay_SetBrightness( 12 );
     * LedDisplay_PrintChar( 'Z' );
     * @endcode
     **/
    inline void LedDisplay_PrintChar( char x );
    
#if __HCMS_29xx_COMPILE_LedDisplay_PrintUInt16 == 1
    
    /**
     * @brief
     *  Print a 16-bits unsigned integer number on a specified base on the HCMS-29xx Display.
     * 
     *  This routine take a number (and a base) to print it on the HCMS-29xx Display.
     * 
     * @pre
     *  LedDisplay_Initialize routine need be called before.
     * 
     * @param[in] x: integer that will be printed on the HCMS-29xx Display.
     * @param[in] b: base used for print the integer
     * 
     * <b>Example</b>
     * @code
     * //...
     * LedDisplay_Initialize( 8, __display_buffer, 16 );
     * LedDisplay_SetBrightness( 12 );
     * LedDisplay_PrintUInt16( 156, 2 ); // print 156 on base 2
     * @endcode
     **/
    inline void LedDisplay_PrintUInt16( uint16_t x, uint8_t b );
#endif

#if __HCMS_29xx_COMPILE_LedDisplay_PrintInt16 == 1
    
    /**
     * @brief
     *  Print a 16-bits integer number on a specified base on the HCMS-29xx Display.
     * 
     * 
     *  This routine take a number (and a base) and print it on the HCMS-29xx Display.
     * 
     * @pre
     *  LedDisplay_Initialize routine need be called before.
     * 
     * @param[in] x: integer that will be printed on the HCMS-29xx Display.
     * @param[in] b: base used for print the integer
     * 
     * <b>Example</b>
     * @code
     * //...
     * LedDisplay_Initialize( 8, __display_buffer, 16 );
     * LedDisplay_SetBrightness( 12 );
     * LedDisplay_PrintInt16( 213, 8 ); // print 213 on base 8
     * @endcode
     **/
    inline void LedDisplay_PrintInt16( int16_t x, uint8_t b );
#endif
    
#if __HCMS_29xx_COMPILE_LedDisplay_PrintFloat == 1
    
    /**
     * @brief
     *  Print a float number on the HCMS-29xx Display.
     * 
     * 
     *  This routine take a float number and print it on the HCMS-29xx Display.
     * 
     * @pre
     *  LedDisplay_Initialize routine need be called before.
     * 
     * @param[in] x: float number that will be printed on the HCMS-29xx Display.
     * @param[in] afterpoint: precision used for print 
     * 
     * <b>Example</b>
     * @code
     * //...
     * LedDisplay_Initialize( 8, __display_buffer, 16 );
     * LedDisplay_SetBrightness( 12 );
     * LedDisplay_PrintFloat( 12.5, 2 );
     * @endcode
     **/
    inline void LedDisplay_PrintFloat( float x, uint8_t afterpoint );
#endif
    
#ifdef	__cplusplus
}
#endif

#endif	/* DISPLAY_H */

