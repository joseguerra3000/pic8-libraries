/* 
 * File:   font5x7.h
 * Author: Jose Guerra Carmenate
 *
 * Created on 15 de febrero de 2019
 */

#ifndef _FONT7SEGMENT_DIGITS_H
#define	_FONT7SEGMENT_DIGITS_H

/**
 * @brief
 *  This macro take one integer digit (range: 0-9) and return it 7Segment code 
 **/
#define FONT7SEG_DIGIT_TO_CODE( x ) font7SegDigit[x]


#define __7SEG_A_BIT    (0u)
#define __7SEG_B_BIT    (1u)
#define __7SEG_C_BIT    (2u)
#define __7SEG_D_BIT    (3u)
#define __7SEG_E_BIT    (4u)
#define __7SEG_F_BIT    (5u)
#define __7SEG_G_BIT    (6u)
#define __7SEG_DOT_BIT  (7u)

#define __7SEG_A_MASK   (1u<<(__7SEG_A_BIT))
#define __7SEG_B_MASK   (1u<<(__7SEG_B_BIT))
#define __7SEG_C_MASK   (1u<<(__7SEG_C_BIT))
#define __7SEG_D_MASK   (1u<<(__7SEG_D_BIT))
#define __7SEG_E_MASK   (1u<<(__7SEG_E_BIT))
#define __7SEG_F_MASK   (1u<<(__7SEG_F_BIT))
#define __7SEG_G_MASK   (1u<<(__7SEG_G_BIT))
#define __7SEG_DOT_MASK (1u<<(__7SEG_DOT_BIT))


#ifdef	__cplusplus
extern "C" {
#endif

// standard ascii 5x7 font
// defines ascii characters 0x20-0x7F (32-127)
static const unsigned char font7SegDigit[] = {
    0xFF ~ (__7SEG_G_MASK|__7SEG_DOT_MASK),                     // 0
    __7SEG_B_MASK | __7SEG_C_MASK,                              // 1
    0xFF ~ (__7SEG_C_MASK|__7SEG_F_MASK|__7SEG_DOT_MASK),       // 2
    0xFF ~ (__7SEG_E_MASK|__7SEG_F_MASK|__7SEG_DOT_MASK),       // 3
    __7SEG_B_MASK|__7SEG_C_MASK|__7SEG_F_MASK|__7SEG_G_MASK,    // 4
    0xFF ~ (__7SEG_B_MASK|__7SEG_E_MASK|__7SEG_DOT_MASK),       // 5
    0xFF ~ (__7SEG_B_MASK|__7SEG_A_MASK|__7SEG_DOT_MASK),       // 6
    __7SEG_A_MASK|__7SEG_B_MASK|__7SEG_C_MASK,                  // 7
    0xFF ~ (__7SEG_DOT_MASK),                                   // 8
    0xFF ~ (__7SEG_DOT_MASK|__7SEG_E_MASK|__7SEG_D_MASK)        // 9
};



#ifdef	__cplusplus
}
#endif

#endif	/* _FONT7SEGMENT_DIGITS_H */

