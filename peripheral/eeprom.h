/**
  EEPROM Driver API Header File

  @Author
   Jose Guerra Carmenate

  @File Name
    eeprom.h

  @Summary
    This is the header file for the EEPROM driver on MCUs

  @Description

*/


#ifndef _EEPROM_H
#define _EEPROM_H

#define _HEADER_NOT_FOUND


#ifdef _16F887
 #include "eeprom/eeprom_16f887.h"
 #undef _HEADER_NOT_FOUND
#endif

#ifdef _HEADER_NOT_FOUND
#error Device-specific header could not be found for target chip
#endif

#endif
