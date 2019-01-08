/**
  Usesful function 

  @Author
   Jose Guerra Carmenate

  @File Name
    utils.h

  @Summary

  @Description

*/


#ifndef _UTILS_H
#define _UTILS_H

/**
 Macros for Bit Manipulation 
 **/

#define BIT_SetMask( var, mask ) 		( var |= (mask) )
#define BIT_SetBit( var, bit ) 			BIT_SetMask( (var), 1u<<(bit) )
#define BIT_ClearMask( var, mask ) 		(var &= ~(mask))
#define BIT_ClearBit( var, bit ) 		BIT_ClearMask( (var), 1u<<(bit) )
#define BIT_Toggle( var, bit )  		( (var) ^=  (1u<<(bit)) )
#define BIT_ToggleMask( var, mask )     ( (var) ^=  (mask) )
#define BIT_GetBitStatus( var, bit ) 	(((var)>>(bit)) & 0x1u)


/**
 Macros to extract the nibbles 
 **/
#define BYTE_GetNibble0to4(x) 		(uint8_t)( (x) & 0x0Fu )
#define BYTE_GetNibble4to8(x) 		(uint8_t)( ((x)>>4) & 0x0Fu )
#define BYTE_GetNibble8to12(x) 		(uint8_t)( ((x)>>8) & 0x0Fu )
#define BYTE_GetNibble12to16(x) 	(uint8_t)( ((x)>>16) & 0x0Fu )

/**
 Macros to extract the Bytes
 **/
#define BYTE_GetByte0to8(x)    (uint8_t) ((x) & 0xFFu)
#define BYTE_GetByte8to16(x)   (uint8_t) (((x)>>8) & 0xFFu)
#define BYTE_GetByte16to28(x)  (uint8_t) (((x)>>16) & 0xFFu)
#define BYTE_GetByte28to32(x)  (uint8_t) (((x)>>28) & 0xFFu)



#endif
