/* 
 * File:   595_ShiftRegister_config.h
 * Author: jose
 *
 * Created on 15 de febrero de 2019, 21:37
 */

#ifndef __595_SHIFTREGISTER_CONFIG_H
#define	__595_SHIFTREGISTER_CONFIG_H

/**
 * @brief 
 * This macro define the microcontroller's pin attached to 596's DS(Serial data) input 
 * <p><b>Example</b></p>
 * <code>
 * #define __595ShiftRegister_DATA  GP0
 * </code>
 */
#define __595ShiftRegister_DATA     GP0

/**
 * @brief 
 * This macro define the microcontroller's pin attached to 596's SH_CP(shift register clock) input 
 * <p><b>Example</b></p>
 * <code>
 * #define __595ShiftRegister_CLOCK    GP1
 * </code>
 */
#define __595ShiftRegister_CLOCK    GP1

/**
 * @brief 
 * This macro define the microcontroller's pin attached to 596's ST_CP(storage register clock) input
 * <p><b>Example</b></p>
 * <code>
 * #define __595ShiftRegister_STROBE   GP2
 * </code>
 */
#define __595ShiftRegister_STROBE   GP2


/**
 * @brief 
 * This macro define the Tri-State register for pin attached to 596's DS(Serial data) input 
 * <p><b>Example</b></p>
 * <code>
 * #define __595ShiftRegister_DATA  GP0<br>
 * #define __595ShiftRegister_DATA_Dir TRISIO0
 * </code>
 */
#define __595ShiftRegister_DATA_Dir     TRISIO0


/**
 * @brief 
 * This macro define the Tri-State register for pin attached to 596's SH_CP(shift register clock) input 
 * <p><b>Example</b></p>
 * <code>
 * #define __595ShiftRegister_CLOCK    GP1<br>
 * #define __595ShiftRegister_CLOCK_Dir TRISIO1
 * </code>
 */
#define __595ShiftRegister_CLOCK_Dir    TRISIO1


/**
 * @brief 
 * This macro define the Tri-State register for pin attached to 596's ST_CP(storage register clock) input
 * <p><b>Example</b></p>
 * <code>
 * #define __595ShiftRegister_STROBE   GP2<br>
 * #define __595ShiftRegister_STROBE_Dir   TRISIO2
 * </code>
 */
#define __595ShiftRegister_STROBE_Dir   TRISIO2


/**
 * @brief 
 * This macro define the High time for clock signals.
 * <p><b>Example</b></p>
 * <code>
 * // High Time = 500 us delay                          <br>
 * #define __595ShiftRegister_Delay __delay_us(500);    <br><br>
 * // High Time = Fosc/4                                <br>
 * #define __595ShiftRegister_Delay                     <br>
 * </code>
 */
#define __595ShiftRegister_Delay


#endif	/* 595_SHIFTREGISTER_CONFIG_H */

