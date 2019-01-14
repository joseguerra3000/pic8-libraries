/**
  HCMS-29xx Display Driver API Header File for 8bit PIC MCUs

  @Author
    Jose Guerra Carmenate

  @File Name
    HCMS-29xx.h

  @Summary
    This is the header file for HCMS-29xx Display driver using PIC MCUs

  @Description
    This header file provides generic APIs for driver the HCMS-29xx Display.
    List of compatible displays:
        HCMS-2905    HCMS-2902    HCMS-2904    HCMS-2901    HCMS-2903
        HCMS-2915    HCMS-2912    HCMS-2914    HCMS-2911    HCMS-2913
        HCMS-2925    HCMS-2922    HCMS-2924    HCMS-2921    HCMS-2923
        HCMS-2965    HCMS-2962    HCMS-2964    HCMS-2961    HCMS-2963
        HCMS-2975    HCMS-2972    HCMS-2974    HCMS-2971    HCMS-2973

   @Circuit                                      
 +------------------------+            +-------------------------------+ 
 |       ALPHA_DISPLAY_Din|------------| Din                           | 
 |  PIC  ALPHA_DISPLAY_RS |------------| RS          HCMS-29xx         | 
 |  MCU  ALPHA_DISPLAY_CLK|------------| CLK          Display          |     ___
 |       ALPHA_DISPLAY_CE |------------| CE                         RST|--+-|___|--Vcc
 +------------------------+            +-------------------------------+  |   R
                                                                         === Cap
                                                                          |
                                                                         GND 
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

#define _CONTROL_WORD0                  0x00u // select the control word 0
#define _CONTROL_WORD0_BRIGHT_PWM_MASK  0x0Fu // mask for bright adjust (PWM) (See datasheet)
#define _CONTROL_WORD0_BRIGHT_PEAK_MASK 0x30u // mask for bright adjust (Peak Current) (See datasheet)
#define _CONTROL_WORD0_SLEEP_MODE_ON    0x00u // put the display on sleep mode
#define _CONTROL_WORD0_SLEEP_MODE_OFF   0x40u // put the display on normal mode

// CONTROL WORD 1 MACROS

#define _CONTROL_WORD1                              0x80u // select the control word 1
#define _CONTROL_WORD1_DATA_OUT_SERIAL_MODE         0x00u // put display on serial mode   
#define _CONTROL_WORD1_DATA_OUT_SIMULTANEOUS_MODE   0x01u // put display on simultaneous mode
#define _CONTROL_WORD1_OSC_DIV_1                    0x00u // off prescaler oscillator
#define _CONTROL_WORD1_OSC_DIV_8                    0x02u // set prescaler oscillator to 8



#ifdef	__cplusplus
extern "C" {
#endif
    
/******************************************************************************
 ********************* Section: HCMS-29xx Display APIs ************************
 ******************************************************************************/
    
    
    /**
     * @Summary
     *  Initialize the HCMS-29xx Dislay
     * 
     * @Description
     *  This routine take the number of characters, one buffer and the buffer size
     * and perform the inicialization routine.
     *  This routine configure the pins for comunication
     *  This routine must be called before any other LedDisplay routine.
     * 
     * @Preconditions
     *  None
     * 
     * @Param
     *  - _displayLen:    amount of caracters.
     *  - _displayBuffer: buffer used for store the characters to print on display.
     *  - _bufferSize:   size of _displayBuffer, need be major or equal that _displayLen.
     * 
     * @Returns 
     *  None
     * 
     * @Comments
     *  To control multiple displays, connect all the control lines except the 
     * data line in parallel. The data line can be daisy-chained from right to 
     * left, with data out from the first display going to data in of the 
     * second, and so forth.
     * 
     * @Example
     * <code>
     * 
     * char __bufferForDisplay[16];
     * 
     * LedDisplay_Initialize( 8, __bufferForDisplay, 16 );
     * </code>
     **/
    void LedDisplay_Initialize(uint8_t _displayLen, char* _displayBuffer, uint8_t _bufferSize);
    
    /**
     * @Summary
     *  Set the brightness for HCMS-29xx Display
     * 
     * @Description
     *  This routine take one number between [0-15] for set the leds's brightness
     * 
     * @Preconditions
     *  LedDisplay_Initialize routine need be called before.
     * 
     * @Param
     *  - bright: unsigned integer between [0-15]. Value 0 off the led and 
     * value 15 set the maximum bright.
     *      
     * 
     * @Returns 
     *  None
     * 
     * @Comments
     *  In case of multiple displays the bright is set of all of them.
     * 
     * @Example
     * <code>
     * 
     * char __bufferForDisplay[16];
     * 
     * LedDisplay_Initialize( 4, __bufferForDisplay, 10 );
     * LedDisplay_SetBrightness( 14 );
     * </code>
     **/
    #define LedDisplay_SetBrightness(bright)  LedDisplay_LoadAllControlRegisters( _CONTROL_WORD0 | _CONTROL_WORD0_BRIGHT_PEAK_MASK | _CONTROL_WORD0_SLEEP_MODE_OFF | (_CONTROL_WORD0_BRIGHT_PWM_MASK & bright)  );
    
    /**
     * @Summary
     *  Load the data stored on the buffer to HCMS-29xx Display.
     * 
     * @Description
     *  This routine load the data stored on the buffer to HCMS-29xx Display
     * having in count the shift operation performed.
     * 
     * @Preconditions
     *  LedDisplay_Initialize routine need be called before.
     * 
     * @Param
     *  None
     * 
     * @Returns 
     *  None
     * 
     * @Comments
     *  In case of multiple display the data be loaded with out problems.
     * 
     * For example: Imagine two HCMS-2973 Display ( 8 characters every one ) 
     * and no shift operation performed.
     * 
     * The data stored on buffer be loaded as follow:
     * 
     * Positions [0-7] loaded to left display.
     * 
     * Positions [8-15] loaded to right display
     * 
     * 
     * @Example
     *  
     * <code>
     * 
     * char __bufferForDisplay[16];
     * 
     * LedDisplay_Initialize( 4, __bufferForDisplay, 10 );
     * LedDisplay_SetBrightness( 14 );
     * strncpy(__display_buffer, "PicMicro", 8);
     * LedDisplay_LoadDotRegister();
     * </code>
     **/
    void LedDisplay_LoadDotRegister();
    
    /**
     * @Summary
     *  Load one control word in one HCMS-29xx Display.
     * 
     * @Description
     *  This routine load one control word in one HCMS-29xx Display.
     * 
     * @Preconditions
     *  LedDisplay_Initialize routine need be called before.
     * 
     * @Param
     *   - controlWord: control word to send. See datasheet for details.
     * 
     * @Returns 
     *  None
     * 
     * @Comments
     *  None
     * @Example
     *  
     * <code>
     * <TODO: Put one code example>
     * </code>
     **/    
    void LedDisplay_LoadControlRegister( uint8_t controlWord );
    
    /**
     * @Summary
     *  Load one control word on all HCMS-29xx Display.
     * 
     * @Description
     *  This routine load one control word on all HCMS-29xx Display.
     * 
     * @Preconditions
     *  LedDisplay_Initialize routine need be called before.
     * 
     * @Param
     *   - controlWord: control word to send. See datasheet for details.
     * 
     * @Returns 
     *  None
     * 
     * @Comments
     *  None
     * @Example
     *  
     * <code>
     * <TODO: Put one code example>
     * </code>
     **/    
    void LedDisplay_LoadAllControlRegisters( uint8_t controlWord );
    
    /** Display Functions **/
#if HCMS_29xx_USE_FONT5X7 == 0    
    /**
     * @Summary
     *  Take one character an return one pointer to one char array that
     * have the correspondent map.
     * 
     * @Description
     *  This routine take one character an return one pointer to one char array that
     * have the correspondent map. 
     * One map consist of 5 bytes that together make the representation of 
     * one 5x7 character.
     * 
     * @Preconditions
     *  LedDisplay_Initialize routine need be called before.
     * 
     * @Param
     *   - x: char for get the map
     * 
     * @Returns 
     *   - const unsigned char* : pointer to the map of x
     * 
     * @Comments
     *  If HCMS_29xx_USE_FONT5X7 on HCMS-29xx_config.h is definde as 0
     * this function have to be implemented by the user on their source code.
     * 
     * @Example
     * <code>
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
     * </code>
     **/    
    extern const unsigned char* _FONT5x7_CHAR_TO_MAP( char x );
    
#endif
    
    /**
     * @Summary
     *  Clear the buffer and display (make all its characters equal to space ' ')
     * 
     * @Description
     *  This routine clear the display makeing all its characters equal to ' '(space),
     * the buffer will also be cleaned
     * 
     * @Preconditions
     *  LedDisplay_Initialize routine need be called before.
     * 
     * @Param
     *   None
     * 
     * @Returns 
     *   None
     * 
     * @Comments
     *  None
     * 
     * @Example
     * <code>
     * LedDisplay_Initialize( 8, __display_buffer, 16 );
     * LedDisplay_SetBrightness( 12 );
     * LedDisplay_PrintInt16( 123, 10 );
     * LedDisplay_Clear();
     * LedDisplay_PrintString( "Ok!" );
     * </code>
     **/    
    void LedDisplay_Clear( void );
    
    /**
     * @Summary
     *  Put the cursor on the first Display's position 
     * 
     * @Description
     *  This routine put the cursor on the first Display's position.
     * 
     * @Preconditions
     *  LedDisplay_Initialize routine need be called before.
     * 
     * @Param
     *   None
     * 
     * @Returns 
     *   None
     * 
     * @Comments
     *  None
     * 
     * @Example
     * <code>
     * LedDisplay_Initialize( 8, __display_buffer, 16 );
     * LedDisplay_SetBrightness( 12 );
     * LedDisplay_PrintInt16( 123, 10 );
     * LedDisplay_Home();
     * LedDisplay_PrintString( "Ok" );
     * </code>
     **/ 
    #define LedDisplay_Home()  LedDisplay_SetCursor( 0u );
    
    
    /**
     * @Summary
     *  Take an integer and put the cursor on the specified position.
     * 
     * @Description
     *  This routine, take an integer and put the cursor on the specified position.
     * 
     * @Preconditions
     *  LedDisplay_Initialize routine need be called before.
     * 
     * @Param
     *   - cursorPos: position for the cursor, from [0 - bufferSize]
     * 
     * @Returns 
     *   None
     * 
     * @Comments
     *  None
     * 
     * @Example
     * <code>
     * LedDisplay_Initialize( 8, __display_buffer, 16 );
     * LedDisplay_SetBrightness( 12 );
     * LedDisplay_PrintInt16( 123, 10 );
     * LedDisplay_SetCursor( 1 );
     * LedDisplay_PrintString( "Ok" );
     * </code>
     **/
    inline void LedDisplay_SetCursor( uint8_t cursorPos );
    
#if __HCMS_29xx_COMPILE_LedDisplay_GetCursor==1
    
    /**
     * @Summary
     *  Return the current cursor position
     * 
     * @Description
     *  This routine return the current cursor position.
     * 
     * @Preconditions
     *  LedDisplay_Initialize routine need be called before.
     * 
     * @Param
     *   None
     * 
     * @Returns 
     *   uint8_t - The current cursor position
     * 
     * @Comments
     *  None
     * 
     * @Example
     * <code>
     * LedDisplay_Initialize( 8, __display_buffer, 16 );
     * LedDisplay_SetBrightness( 12 );
     * LedDisplay_PrintInt16( 123, 10 );
     * LedDisplay_SetCursor( 1 );
     * LedDisplay_PrintString( "Ok" );
     * </code>
     **/
    inline uint8_t LedDisplay_GetCursor();
#endif
    
#if __HCMS_29xx_COMPILE_LedDisplay_Scroll == 1
    
    /**
     * @Summary
     *  Take one integer and scroll the display text.
     * 
     * @Description
     *  This routine take one integer and scroll the display text. if the
     *  argument is positive scroll from left to right, if negative scroll
     *  from right to left.
     * 
     * @Preconditions
     *  LedDisplay_Initialize routine need be called before.
     * 
     * @Param
     *   - dir: number of characters to scroll (the sign define de direction)
     * 
     * @Returns 
     *   None
     * 
     * @Comments
     *  None
     * 
     * @Example
     * <code>
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
     * </code>
     **/
    inline void LedDisplay_Scroll( int8_t dir );
#endif
    
    /**
     * @Summary
     *  Take one character map and print it.
     * 
     * @Description
     *  This routine take one character map and print it.
     * 
     * @Preconditions
     *  LedDisplay_Initialize routine need be called before.
     * 
     * @Param
     *   - map: character map to show on the display
     * 
     * @Returns 
     *   None
     * 
     * @Comments
     *  None
     * 
     * @Example
     * <code>
     * const unsigned char* fontSpaceSimbol = { 0x00, 0x00, 0x00, 0x00, 0x00 };
     * const unsigned char* fontNumSimbol = { 0x14, 0x7F, 0x14, 0x7F, 0x14 };
     * const unsigned char* fontPercentSimbol = { 0x23, 0x13, 0x08, 0x64, 0x62};
     * ...
     * LedDisplay_Initialize( 8, __display_buffer, 16 );
     * LedDisplay_SetBrightness( 12 );
     * LedDisplay_PutUserChar( fontNumSimbol );
     * LedDisplay_SetCursor( 2 );
     * LedDisplay_PutUserChar( fontPercentSimbol );
     * </code>
     **/
    void LedDisplay_PutUserChar( const unsigned char *map );  
    
    
    /**
     * @Summary
     *  Take one string and print it to the display.
     * 
     * @Description
     *  This routine, take one string and print it to the display.
     * 
     * @Preconditions
     *  LedDisplay_Initialize routine need be called before.
     * 
     * @Param
     *   - txt: string to print on the display
     * 
     * @Returns 
     *   None
     * 
     * @Comments
     *  None
     * 
     * @Example
     * <code>
     * const unsigned char* fontSpaceSimbol = { 0x00, 0x00, 0x00, 0x00, 0x00 };
     * const unsigned char* fontNumSimbol = { 0x14, 0x7F, 0x14, 0x7F, 0x14 };
     * const unsigned char* fontPercentSimbol = { 0x23, 0x13, 0x08, 0x64, 0x62};
     * ...
     * LedDisplay_Initialize( 8, __display_buffer, 16 );
     * LedDisplay_SetBrightness( 12 );
     * LedDisplay_PrintString( "PicMicro" );
     * </code>
     **/
    void LedDisplay_PrintString( const char *txt);
    
    
    /**
     * @Summary
     *  Take one character and print it on the HCMS-29xx Display.
     * 
     * @Description
     *  This routine take one character and print it on the HCMS-29xx Display.
     * 
     * @Preconditions
     *  LedDisplay_Initialize routine need be called before.
     * 
     * @Param
     *   - x: character that will be printed on the HCMS-29xx Display.
     * 
     * @Returns 
     *   None
     * 
     * @Comments
     *  None
     * 
     * @Example
     * <code>
     * ...
     * LedDisplay_Initialize( 8, __display_buffer, 16 );
     * LedDisplay_SetBrightness( 12 );
     * LedDisplay_PrintChar( 'Z' );
     * </code>
     **/
    inline void LedDisplay_PrintChar( char x );
    
#if __HCMS_29xx_COMPILE_LedDisplay_PrintUInt16 == 1
    
    /**
     * @Summary
     *  Print a 16-bits unsigned integer number on a specified base on the HCMS-29xx Display.
     * 
     * @Description
     *  This routine take a number and print it on the HCMS-29xx Display.
     * 
     * @Preconditions
     *  LedDisplay_Initialize routine need be called before.
     * 
     * @Param
     *   - x: integer that will be printed on the HCMS-29xx Display.
     *   - b: base used for print the integer
     * 
     * @Returns 
     *   None
     * 
     * @Comments
     *  None
     * 
     * @Example
     * <code>
     * ...
     * LedDisplay_Initialize( 8, __display_buffer, 16 );
     * LedDisplay_SetBrightness( 12 );
     * LedDisplay_PrintUInt16( 156 );
     * </code>
     **/
    inline void LedDisplay_PrintUInt16( uint16_t x, uint8_t b );
#endif
    
#if __HCMS_29xx_COMPILE_LedDisplay_PrintInt16 == 1
    
    /**
     * @Summary
     *  Print a 16-bits integer number on a specified base on the HCMS-29xx Display.
     * 
     * @Description
     *  This routine take a number and print it on the HCMS-29xx Display.
     * 
     * @Preconditions
     *  LedDisplay_Initialize routine need be called before.
     * 
     * @Param
     *   - x: integer that will be printed on the HCMS-29xx Display.
     *   - b: base used for print the integer
     * 
     * @Returns 
     *   None
     * 
     * @Comments
     *  None
     * 
     * @Example
     * <code>
     * ...
     * LedDisplay_Initialize( 8, __display_buffer, 16 );
     * LedDisplay_SetBrightness( 12 );
     * LedDisplay_PrintInt16( 156 );
     * </code>
     **/
    inline void LedDisplay_PrintInt16( int16_t x, uint8_t b );
#endif
    
#if __HCMS_29xx_COMPILE_LedDisplay_PrintFloat == 1
    
    /**
     * @Summary
     *  Print a float number on a specified base on the HCMS-29xx Display.
     * 
     * @Description
     *  This routine take a float number and print it on the HCMS-29xx Display.
     * 
     * @Preconditions
     *  LedDisplay_Initialize routine need be called before.
     * 
     * @Param
     *   - x: float number that will be printed on the HCMS-29xx Display.
     *   - afterpoint: precision used for print 
     * 
     * @Returns 
     *   None
     * 
     * @Comments
     *  None
     * 
     * @Example
     * <code>
     * ...
     * LedDisplay_Initialize( 8, __display_buffer, 16 );
     * LedDisplay_SetBrightness( 12 );
     * LedDisplay_PrintFloat( 12.5, 2 );
     * </code>
     **/
    inline void LedDisplay_PrintFloat( float x, uint8_t afterpoint );
#endif
    
#ifdef	__cplusplus
}
#endif

#endif	/* DISPLAY_H */

