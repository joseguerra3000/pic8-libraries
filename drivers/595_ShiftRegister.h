/*
 * File:   595_ShiftRegister.h
 * Author: jose
 *
 * Created on 15 de febrero de 2019, 21:34
 */

#ifndef __595_SHIFTREGISTER_H
#define	__595_SHIFTREGISTER_H

#include <stdint.h>


#ifdef	__cplusplus
extern "C" {
#endif /* __cplusplus */


    /**
     * @brief 
     * Perform the Shift Register 595 driver initialization.
     * 
     * @param 
     * None
     * 
     * @return 
     * None
     * 
     * @pre 
     * __595ShiftRegister_DATA, __595ShiftRegister_CLOCK and 
     * __595ShiftRegister_STROBE macros should must be defined on 
     * 595_ShiftRegister_config.h header. See 595_ShiftRegister_config.h
     * 
     * @author Jose Guerra Carmenate
     * @version 1.0
     * @date    15/02/2019
     */
    inline void ShiftReg595_Initialize();
    
    
    /**
     * @brief 
     * Send a byte to Shift Register starting from Least Significant Bit
     * 
     * @param[in] data Byte to send.
     * 
     * @return None
     * 
     * @pre ShiftReg595_Initialize routine should must be called first
     * 
     * @author Jose Guerra Carmenate
     * @version 1.0
     * @date 15/02/2019
     */
    void ShiftReg595_SendByteLSBFirst( uint8_t data );
    
    
    /**
     * @brief 
     * Send a byte to Shift Register starting from Most Significant Bit
     * 
     * @param[in] data Byte to send.
     * 
     * @return None
     * 
     * @pre ShiftReg595_Initialize routine should must be called first
     * 
     * @author Jose Guerra Carmenate
     * @version 1.0
     * @date 15/02/2019
     */    
    void ShiftReg595_SendByteMSBFirst( uint8_t data );
    


#ifdef	__cplusplus
}
#endif /* __cplusplus */

#endif	/* __595_SHIFTREGISTER_H */

