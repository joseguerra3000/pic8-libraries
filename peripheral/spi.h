/**
  SPI Driver API Header File

  @Author
   Jose Guerra Carmenate

  @File Name
    spi.h

  @Summary
    This is the header file for the SPI driver on MCUs

  @Description

*/


#ifndef _SPI_H
#define _SPI_H

#define _HEADER_NOT_FOUND


#ifdef _16F887
 #include "spi_peripheral/spi_16f887.h"
 #undef _HEADER_NOT_FOUND
#endif

#ifdef _HEADER_NOT_FOUND
#error Device-specific header could not be found for target chip
#endif

#endif
