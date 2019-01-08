/**
  HCMS-29xx Display Lite Version Driver File

  @Author
    Jose Guerra Carmenate.

  @File Name
    HCMS-29xx_lite.c

  @Summary
    This is the driver implementation file for the HCMS-29xx lite version driver using PIC MCUs 8bits.
    List of compatible displays:
        HCMS-2905    HCMS-2902    HCMS-2904    HCMS-2901    HCMS-2903
        HCMS-2915    HCMS-2912    HCMS-2914    HCMS-2911    HCMS-2913
        HCMS-2925    HCMS-2922    HCMS-2924    HCMS-2921    HCMS-2923
        HCMS-2965    HCMS-2962    HCMS-2964    HCMS-2961    HCMS-2963
        HCMS-2975    HCMS-2972    HCMS-2974    HCMS-2971    HCMS-2973

  @Description
    Compiler          :  XC8 2.00
    MPLAB             :  MPLAB X 5.10
*/

#include "HCMS-29xx.h"

#include "HCMS-29xx_config.h"
#include "../util/num2str.h"

#if HCMS_29xx_USE_FONT5X7==1

#include "../util/font5x7.h"
#define _FONT5x7_CHAR_TO_MAP FONT5x7_CHAR_TO_MAP

#endif


#if HCMS_29xx_VERSION == __HCMS_29xx_LITE_VERSION

#define CE _HCMS_29xx_DISPLAY_CE
#define CLK _HCMS_29xx_DISPLAY_CLK
#define Din _HCMS_29xx_DISPLAY_Din
#define RS _HCMS_29xx_DISPLAY_RS

#ifdef _HCMS_29xx_DISPLAY_RST
#define RST _HCMS_29xx_DISPLAY_RST
#endif

#define CE_Dir _HCMS_29xx_DISPLAY_CE_Dir
#define CLK_Dir _HCMS_29xx_DISPLAY_CLK_Dir
#define Din_Dir _HCMS_29xx_DISPLAY_Din_Dir
#define RS_Dir _HCMS_29xx_DISPLAY_RS_Dir

#ifdef _HCMS_29xx_DISPLAY_RST_Dir
#define RST_Dir _HCMS_29xx_DISPLAY_RST_Dir
#endif

char *displayBuffer;
uint8_t bufferSize;
uint8_t displayLen;
uint8_t cursorPosition;

#if __HCMS_29xx_COMPILE_LedDisplay_Scroll==1
int8_t cursorShift;
#endif

/** See header for more information **/
void LedDisplay_LoadControlRegister( uint8_t controlWord ){
    //Select the control register
    RS = 1u;
    //Enable display for write
    CE = 0u;
    //Data out (MSB first)
    for( uint8_t j = 7u; j != 255u; j-- ){ //unitl overflow
        Din = (controlWord>>j)&0x01u;
        CLK = 1u;
#ifdef CLK_DELAY
        CLK_DELAY;
#endif
        CLK = 0u;
#ifdef CLK_DELAY
        CLK_DELAY;
#endif
    }
    //Release the display and load register
    CE = 1u;
}

/** See header for more information **/
void LedDisplay_LoadAllControlRegisters( uint8_t controlWord ){
    // Every chip drives four characters
    uint8_t chipCount = displayLen/4u;
    
    // Configure every chip for simultaneous mode
    for( uint8_t i = 0; i < chipCount; i++ )
        LedDisplay_LoadControlRegister( _CONTROL_WORD1 | _CONTROL_WORD1_DATA_OUT_SIMULTANEOUS_MODE );
    
    // Load the value on control register
    LedDisplay_LoadControlRegister( controlWord );
    
    // Configure every chip for serial mode
    LedDisplay_LoadControlRegister( _CONTROL_WORD1 | _CONTROL_WORD1_DATA_OUT_SERIAL_MODE );  
}

/** See header for more information **/
void LedDisplay_LoadDotRegister() {
    
    for( int8_t displayPos = 0; displayPos < displayLen; displayPos++ ){
#if __HCMS_29xx_COMPILE_LedDisplay_Scroll==1
        if( displayPos - cursorShift < 0 || displayPos - cursorShift >= bufferSize )
            LedDisplay_PutUserChar( _FONT5x7_CHAR_TO_MAP( ' ' ) );
        else if( displayPos - cursorShift < bufferSize )
            LedDisplay_PutUserChar( _FONT5x7_CHAR_TO_MAP( displayBuffer[displayPos-cursorShift] ) );
#else
        LedDisplay_PutUserChar( _FONT5x7_CHAR_TO_MAP( displayBuffer[displayPos] ) );
#endif
    }
    CE = 1;
}

/********************** Interface Functions ***********************/

/** See header for more information **/
void LedDisplay_Initialize(uint8_t _displayLen, char* _displayBuffer, uint8_t _bufferSize){
    displayLen =  _displayLen;
    displayBuffer = _displayBuffer;
    bufferSize = _bufferSize;
    cursorPosition = 0u;
#if __HCMS_29xx_COMPILE_LedDisplay_Scroll == 1u
    cursorShift = 0u;
#endif
    // Set all pin as output
    Din_Dir = 0u;
    CE_Dir = 0u;
    CLK_Dir = 0u;
    RS_Dir = 0u;
    
    
#ifdef RST
    //reset display
    RST_Dir = 0u;
    RST = 0u;
    __delay_ms(10u);
    RST = 1u;
#endif
    // Fill the  display with spaces (' ')
    LedDisplay_Clear();
    // Set normal mode and maximum brightness for all displays
    LedDisplay_LoadAllControlRegisters( 0b01111111 );
}

/** See header for more information **/
void LedDisplay_Clear( void ){
    //fill the buffer with spaces
    for( uint8_t i = 0; i < bufferSize; i++ ){
        displayBuffer[i] = ' ';
    }
     // load dot register with lows(spaces)
    LedDisplay_LoadDotRegister();
}

/** See header for more information **/
inline void LedDisplay_SetCursor(uint8_t cursorPos){
    // set the cursor position
    cursorPosition = cursorPos;
}


#if (__HCMS_29xx_COMPILE_LedDisplay_GetCursor==1) && (__HCMS_29xx_COMPILE_LedDisplay_SetCursor==1)
/** See header for more information **/
inline uint8_t LedDisplay_GetCursor(){
    // get the current cursor position
    return cursorPosition;
}
#endif

#if __HCMS_29xx_COMPILE_LedDisplay_Scroll == 1
/** See header for more information **/
inline void LedDisplay_Scroll( int8_t direction ){
    cursorShift += direction;
    LedDisplay_LoadDotRegister();
}
#endif

/** See header for more information **/
void LedDisplay_PutUserChar( const unsigned char *map ){
    
    // Select Dot register
    RS = 0;     // Low
    CLK = 0;    // Not rising
    CE = 0;     // falling edge
    
    // Write character to display
    for( uint8_t i = 0; i < 5; i++ ){
        unsigned char b = map[i];
        // Send data (MSB first)
        for( uint8_t j = 7; j != 255; j-- ){ 
            Din = (b>>j)&0x01;
            CLK = 1;
#ifdef CLK_DELAY
        CLK_DELAY;
#endif            
            CLK = 0;
#ifdef CLK_DELAY
        CLK_DELAY;
#endif
        }
    }
}

/** See header for more information **/
void LedDisplay_PrintString( const char *p){
    // load string to buffer
    do{
        displayBuffer[cursorPosition++] = *(++p);
    }while( *p );
    // load dot register from the buffer
    LedDisplay_LoadDotRegister();
}

/** See header for more information **/
inline void LedDisplay_PrintChar( char x ){
    // put character on buffer
    displayBuffer[ cursorPosition++ ] = x;
    // load dot register from the buffer
    LedDisplay_LoadDotRegister();
}


#if __HCMS_29xx_COMPILE_LedDisplay_PrintUInt16 == 1
/** See header for more information **/
inline void LedDisplay_PrintUInt16( uint16_t x, uint8_t _base ){
    //put the unsigned integer on the buffer
    cursorPosition += (uint8_t)uint2str( x, _base, displayBuffer+cursorPosition );
    // load dot register from the buffer
    LedDisplay_LoadDotRegister();
}
#endif

#if __HCMS_29xx_COMPILE_LedDisplay_PrintInt16 == 1
/** See header for more information **/
inline void LedDisplay_PrintInt16( int16_t x, uint8_t _base ){
    //put the integer on the buffer
    cursorPosition += (uint8_t)int2str( x, _base, displayBuffer+cursorPosition );
    // load dot register from the buffer
    LedDisplay_LoadDotRegister();
}
#endif

#if __HCMS_29xx_COMPILE_LedDisplay_PrintFloat == 1
/** See header for more information **/
inline void LedDisplay_PrintFloat( float x, uint8_t afterpoint ){
    //put the float number on the buffer
    cursorPosition += (uint8_t)float2str( x, afterpoint, displayBuffer+cursorPosition);
    // load dot register from the buffer
    LedDisplay_LoadDotRegister();
}
#endif

#endif// if lite version