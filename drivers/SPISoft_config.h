/* 
 * File:   SPISoft_config.h
 * Author: jose
 *
 * Created on 21 de octubre de 2019, 20:27
 */

#ifndef SPISOFT_CONFIG_H
#define	SPISOFT_CONFIG_H

#include <stdint.h>

#define COM_PORT PORTD
#define COM_TRIS TRISD

#define SDI_bit 2
#define SDO_bit 7
#define CLK_bit 6
#define DELAY_TIME_MS 0




#define SDI_mask ((uint8_t)1<<(SDI_bit))
#define SDO_mask ((uint8_t)1<<(SDO_bit))
#define CLK_mask ((uint8_t)1<<(CLK_bit))

#define SDO_ON  (COM_PORT |= SDO_mask)
#define SDO_OFF (COM_PORT &= ~(SDO_mask))

#define CLK_ON COM_PORT |= CLK_mask
#define CLK_OFF (COM_PORT &= ~(CLK_mask))


#define wait() __delay_ms(DELAY_TIME_MS/2)

#endif	/* SPISOFT_CONFIG_H */

