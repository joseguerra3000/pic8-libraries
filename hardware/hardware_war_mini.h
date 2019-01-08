/* 
 * File:   hardware_war_mini.h
 * Author: Jose Guerra Carmenate
 * Comments:
 * Revision history: initial release
 */

#ifndef _HARDWARE_WAR_MINI_H
#define	_HARDWARE_WAR_MINI_H

#include <xc.h> // include processor files - each processor file is guarded.  
#include "../util/utils.h"

// PIC16F887 Configuration Bit Settings
// CONFIG1
#pragma config FOSC = HS        // Oscillator Selection bits (HS oscillator: High-speed crystal/resonator on RA6/OSC2/CLKOUT and RA7/OSC1/CLKIN)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled and can be enabled by SWDTEN bit of the WDTCON register)
#pragma config PWRTE = OFF      // Power-up Timer Enable bit (PWRT disabled)
#pragma config MCLRE = ON       // RE3/MCLR pin function select bit (RE3/MCLR pin function is MCLR)
#pragma config CP = OFF         // Code Protection bit (Program memory code protection is disabled)
#pragma config CPD = OFF        // Data Code Protection bit (Data memory code protection is disabled)
#pragma config BOREN = ON       // Brown Out Reset Selection bits (BOR enabled)
#pragma config IESO = ON        // Internal External Switchover bit (Internal/External Switchover mode is enabled)
#pragma config FCMEN = ON       // Fail-Safe Clock Monitor Enabled bit (Fail-Safe Clock Monitor is enabled)
#pragma config LVP = OFF        // Low Voltage Programming Enable bit (RB3 pin has digital I/O, HV on MCLR must be used for programming)

// CONFIG2
#pragma config BOR4V = BOR40V   // Brown-out Reset Selection bit (Brown-out Reset set to 4.0V)
#pragma config WRT = OFF        // Flash Program Memory Self Write Enable bits (Write protection off)


/** 
 * Hardware Specific 
 **/

// Crystal Freq
#define _XTAL_FREQ 20000000

/*********** LEDS Macros ***********/

// LEDS TRIS

#define LED1_TRIS TRISDbits.TRISD4
#define LED2_TRIS TRISDbits.TRISD5
#define LED3_TRIS TRISDbits.TRISD6
#define LED4_TRIS TRISDbits.TRISD7
#define LEDS_TRIS TRISD

// LEDS PORT

#define LED1_PORT PORTDbits.RD4
#define LED2_PORT PORTDbits.RD5
#define LED3_PORT PORTDbits.RD6
#define LED4_PORT PORTDbits.RD7
#define LEDS_PORT PORTD

// LEDS MASK

#define LEDS_MASK 0xF0
#define LED1_MASK 0x80
#define LED2_MASK 0x40
#define LED3_MASK 0x20
#define LED4_MASK 0x10

// get/set LED1 aliases
#define LED1_SetHigh( )              do { LED1_PORT = 1; } while(0)
#define LED1_SetLow( )               do { LED1_PORT = 0; } while(0)
#define LED1_Toggle( )               do { LED1_PORT = ~(LED1_PORT); } while(0)
#define LED1_GetDigitalValue( )      LED1_PORT
#define LED1_SetDigitalInput( )      do { LED1_TRIS = 1; } while(0)
#define LED1_SetDigitalOutput( )     do { LED1_TRIS = 0; } while(0)

// get/set LED2 aliases
#define LED2_SetHigh( )              do { LED2_PORT = 1; } while(0)
#define LED2_SetLow( )               do { LED2_PORT = 0; } while(0)
#define LED2_Toggle( )               do { LED2_PORT = ~(LED2_PORT); } while(0)
#define LED2_GetDigitalValue( )      LED2_PORT
#define LED2_SetDigitalInput( )      do { LED2_TRIS = 1; } while(0)
#define LED2_SetDigitalOutput( )     do { LED2_TRIS = 0; } while(0)

// get/set LED3 aliases
#define LED3_SetHigh( )              do { LED3_PORT = 1; } while(0)
#define LED3_SetLow( )               do { LED3_PORT = 0; } while(0)
#define LED3_Toggle( )               do { LED3_PORT = ~(LED3_PORT); } while(0)
#define LED3_GetDigitalValue( )      LED3_PORT
#define LED3_SetDigitalInput( )      do { LED3_TRIS = 1; } while(0)
#define LED3_SetDigitalOutput( )     do { LED3_TRIS = 0; } while(0)

// get/set LED4 aliases
#define LED4_SetHigh( )              do { LED4_PORT = 1; } while(0)
#define LED4_SetLow( )               do { LED4_PORT = 0; } while(0)
#define LED4_Toggle( )               do { LED4_PORT = ~(LED4_PORT); } while(0)
#define LED4_GetDigitalValue( )      LED4_PORT
#define LED4_SetDigitalInput( )      do { LED4_TRIS = 1; } while(0)
#define LED4_SetDigitalOutput( )     do { LED4_TRIS = 0; } while(0)

// get/set LEDS aliases 
#define LEDS_SetHigh( )              do { BIT_SetMask(LEDS_PORT, LEDS_MASK); } while(0)
#define LEDS_SetLow( )               do { BIT_ClearMask(LEDS_PORT, LEDS_MASK); } while(0)
#define LEDS_Toggle( )               do { BIT_ToggleMask(LEDS_PORT, LEDS_MASK); } while(0)

#define LEDS_SetDigitalOutput( )     do { BIT_ClearMask( LEDS_TRIS, LEDS_MASK ); } while(0)
#define LEDS_SetDigitalInput( )      do { BIT_SetMask( LEDS_TRIS, LEDS_MASK ); } while(0)


/*********** Potentiometer Macros ***********/

// Potentiometer TRIS
#define POT_TRIS TRISAbits.TRISA3

// Potentiometer PORT
#define POT_PORT PORTAbits.RA3

// Potentiometer Analog Channel
#define POT_AN_CHANNEL 3

// Potentiometer ANSEL
#define POT_ANSEL ANSELbits.ANS3

// get/set POT aliases
#define POT_SetHigh( )              do { POT_PORT = 1; } while(0)
#define POT_SetLow( )               do { POT_PORT = 0; } while(0)
#define POT_Toggle( )               do { POT_PORT = ~(POT_PORT); } while(0)
#define POT_GetDigitalValue( )      POT_PORT
#define POT_SetDigitalInput( )      do { POT_TRIS = 1; POT_ANSEL = 0; } while(0)
#define POT_SetDigitalOutput( )     do { POT_TRIS = 0; POT_ANSEL = 0; } while(0)
#define POT_SetAnalogInput( )       do { POT_TRIS = 1; POT_ANSEL = 1; } while(0)

/*********** Temperature Sensor(LM335) Macros ***********/

// LM335 TRIS
#define LM335_TRIS TRISBbits.TRISB4

// LM335 PORT
#define LM335_PORT PORTBbits.RB4

// LM335 Analog Channel
#define LM335_ANALOG_CHANNEL 11

// LM335 ANSEL
#define LM335_ANSEL ANSELHbits.ANS11

// get/set LM335 aliases
#define LM335_SetHigh()            do { LM335_PORT = 1; } while(0)
#define LM335_SetLow()             do { LM335_PORT = 0; } while(0)
#define LM335_Toggle()             do { LM335_PORT = ~LM335_PORT; } while(0)
#define LM335_GetValue()           PORTBbits.RB0
#define LM335_SetDigitalInput()    do { LM335_TRIS = 1; LM335_ANSEL = 0; } while(0)
#define LM335_SetDigitalOutput()   do { LM335_TRIS = 0; } while(0)
#define LM335_SetPullup()          do { WPUBbits.WPUB4 = 1; } while(0)
#define LM335_ResetPullup()        do { WPUBbits.WPUB4 = 0; } while(0)
#define LM335_SetAnalogInput()     do { LM335_TRIS = 1; LM335_ANSEL = 1; } while(0)


#endif	/* XC_HEADER_TEMPLATE_H */

