/**
  LCD Driver Configuration Header File for 8bit PIC MCUs

  @Author
    Jose Guerra Carmenate

  @File Name
    lcd_config.h

  @Summary
    This is the header file for LCD driver configuration using PIC MCUs

  @Description
    This header file provides configuration options for driver for LCD.
*/


// Control Bus definition
#define EN      RD0 
#define EN_tris TRISD0

#define RS      RD1
#define RS_tris TRISD1

// Data Bus definition

#define D4      RD4
#define D4_tris TRISD4

#define D5      RD5
#define D5_tris TRISD5

#define D6      RD6
#define D6_tris TRISD6

#define D7      RD7
#define D7_tris TRISD7


