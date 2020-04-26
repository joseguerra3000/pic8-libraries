/**
 * @file  595_ShiftRegister_lite.c
 * @author Jose Guerra Carmenate
 *
 * @date 15 de febrero de 2019, 21:34
 *
 * @brief Este archivo contiene la implementacio'n de la
 * API para registro de desplazamiento 595.
 *
 */

#include "595_ShiftRegister.h"
#include "595_ShiftRegister_config.h"

#include <xc.h>
#include "device_config.h" // _XTAL_MACRO define

#define DATA    __595ShiftRegister_DATA
#define CLK     __595ShiftRegister_CLOCK
#define STROB   __595ShiftRegister_STROBE

#define DATA_Dir __595ShiftRegister_DATA_Dir     
#define CLK_Dir __595ShiftRegister_CLOCK_Dir    
#define STROB_Dir __595ShiftRegister_STROBE_Dir   


/**
 * @brief 
 * This macro generate one pulse clock on SH_CP input
 *
 * @pre ShiftReg595_Initialize routine must be called first
 *
 * @author Jose Guerra Carmenate
 * @version 1.0
 * @date 15/02/2019
*/
#define clock() {                       \
            CLK = 1;                    \
            __595ShiftRegister_Delay;   \
            CLK = 0;                    \
        }


/**
 * @brief 
 * This macro generate one pulse clock on ST_CP input
 *
 * @pre ShiftReg595_Initialize routine must be called first
 *
 * @author Jose Guerra Carmenate
 * @version 1.0
 * @date 15/02/2019
*/
#define strobe() {                      \
            STROB = 1;                  \
            __595ShiftRegister_Delay;   \
            STROB = 0;                  \
        }

/* See 595_ShiftRegister.h for use */
inline void ShiftReg595_Initialize(){
    DATA_Dir = 0;       // DATA is output
    CLK_Dir = 0;        // CLOCK is output
    STROB_Dir = 0;      // STROBE is output
}


/* See 595_ShiftRegister.h for use details */
void ShiftReg595_SendByteLSBFirst( uint8_t byte ){
    uint8_t l = 7;
    while( l != 255 ){          // for each bit
        DATA = (byte) & 0x01;   // put bit on DATA
        clock();                // send it
        byte >>= 1;             // right-shift byte to right
        l--;
    }
    strobe();                   // update data to 595 storage register
}

/* See 595_ShiftRegister.h for use details */
void ShiftReg595_SendByteMSBFirst( uint8_t byte ){
    uint8_t l = 7;
    while( l != 255 ){                                  // for each bit
        byte = (byte<<1) | ( (byte&0x80)?0x01:0x00 );   // cyclic left-shift

        DATA = byte & 0x01;                             // put bit on DATA
        clock();                                        // send it
        l--;
    }
    strobe();                                           // update data to 595 storage register

}

#endif
