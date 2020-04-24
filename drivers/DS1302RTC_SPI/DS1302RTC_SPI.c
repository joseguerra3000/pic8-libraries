/** 
 * @file:   DS1302RTC_SPI.c
 * @author: Jose Guerra Carmenate
 * 
 * @brief Implementacio'n de la API DS1302RTC_SPI
 */


#include "DS1302RTC_SPI.h"
#include "DS1302RTC_SPI_config.h"
#include "device_config.h"
#include "../peripheral/spi.h"
#include "../util/utils.h"

#include <xc.h>

//volatile unsigned char ce_port;
//uint8_t ce_mask;


/* Section: Macros */

// Read/Write operations

/**
 @brief Usado para definir una operacion de lectura
*/
#define _DS1302_READ  1u

/**
 @brief Usado para definir una operacion de escritura
*/
#define _DS1302_WRITE 0u

/**
 @brief Bit de halt clock ubicado en la posicion 7 del registro de segundos
*/
#define _DS1302_CH_bit       0x07u // clock halt flag ( 1 - halt, 0 - start)

/**
 @brief Mapa de Bits del bit halt clock ubicado en la posicion 7 del registro de segundos
*/
#define _DS1302_CH          (1u<<(_DS1302_CH_bit))

/**
 @brief Bit de write-protect ubicado en la posicion 7 del registro de control
*/
#define _DS1302_WP_bit       0x07u // write-protect ( 1 - active, 0 - no active)

/**
 @brief Mapa de bits del bit write-protect ubicado en la posicion 7 del registro de control
*/
#define _DS1302_WP           (1u<<(_DS1302_WP_bit))

/**
 @brief Bit de AM/PM selection ubicado en la posicion 5 del registro de hora
*/
#define _DS1302_AM_PM_bit    0x05u

/**
 @brief Mapa de bits del bit AM/PM selection ubicado en la posicion 5 del registro de hora
*/
#define _DS1302_AM_PM        (1u<<(_DS1302_AM_PM_bit))

// Command Byte Options
//         bits :   7     6      5    4    3    2    1      0  
// Command byte : | 1 | RAM/CK | A4 | A3 | A2 | A1 | A0 | RD/WR |

/**
 @brief Utilizado para realizar operaciones sobre RAM
*/
#define _DS1302_RAM          0x80u // operation over RAM data 

/**
 @brief Utilizado para realizar operaciones sobre RTC
*/
#define _DS1302_CK           0x00u // operation over clock/calendar data

/**
 @brief Usado para operacion de lectura
*/
#define _DS1302_RD           0x01u // read operation

/**
 @brief Usado para operacion de escritura
*/
#define _DS1302_WR           0x00u // write operation


// prototypes for statics functions
/**
 @brief Invierte la posicion de los bits de un byte
 
 Intercambia los bits: 0-7, 1-6, 2-5, 3-4.
 
 @param[in] byte El byte a invertir
 
 @return El byte invertido
*/
static uint8_t BYTE_Invert( uint8_t byte);

/**
 @brief Convierte un entero de 8 bits de notacion BCD a decimal
 @param[in] x entero en notacion BCD
 @return entero en notacio'n decimal
*/
static uint8_t bcd2dec( uint8_t x );

/**
 @brief Convierte un entero de 8 bits de notacion decimal a BCD
 @param[in] x entero en notacion decimal
 @return entero en notacio'n bcd
*/
static uint8_t dec2bcd( uint8_t x );

// API functions

void DS1302RTC_Initialize( ){
    
    //Set CE pin to low
    _DS1302_CE_PORT = 0;
    _DS1302_CE_TRIS = 0;
    
    //Initialize SSP in SPI mode
    SPI_Initialize( SPI_MODE_MASTER_FOSC_DIV_16, 
                    SPI_CLOCK_POLARITY_IDLE_LOW,
                    SPI_OUTPUT_DATA_ON_IDLE_TO_ACTIVE_CLOCK,
                    SPI_INPUT_SAMPLING_IN_MIDDLE);
    
}

uint8_t DS1302RTC_Read( _DS1302_ADDRESS address ){
    uint8_t command;
    
    _DS1302_CE_PORT = 0;
    _DS1302_CE_PORT = 1;    // start comunication    
    command = BYTE_Invert( address | (_DS1302_RD) );
    __delay_us(4);
    _SDO_TRIS = 0;          // enable output SDO
    SPI_WriteBuffer(command); // send command
    while( !SPI_IsDataReady() );
    SPI_ReadBuffer();       // Clear buffer
    
    _SDO_TRIS = 1;          // disable output SDO
    command = SPI_ReadByte(); // read data

    _DS1302_CE_PORT = 0;    // end comunication
    
    return BYTE_Invert(command);
}

void DS1302RTC_Write( _DS1302_ADDRESS address, uint8_t value ){
    address = BYTE_Invert(address);     // invert addres byte
    value = BYTE_Invert( value );       // invert byte
    
    _DS1302_CE_PORT = 1;                // start transaction
    __delay_us(4);                      // wait minimum time
    
    _SDO_TRIS = 0;                      // enable SDO pin
    SPI_SendByte( address );            // set address to write
    SPI_SendByte( value );              // write data
    _DS1302_CE_PORT = 0;                // end transaction
}

// gets functions

uint8_t DS1302RTC_GetSeconds(){
    return bcd2dec(DS1302RTC_Read( _DS1302_ADDRESS_RTC_SECONDS )&0x7F);
}

uint8_t DS1302RTC_GetMinutes(){
    return bcd2dec(DS1302RTC_Read( _DS1302_ADDRESS_RTC_MINUTES ));
}

uint8_t DS1302RTC_GetHours(){
    uint8_t hours = DS1302RTC_Read( _DS1302_ADDRESS_RTC_HOURS );
    if( hours & _DS1302_HOURS_FORMAT_12HOUR )
        hours &= (~_DS1302_AM_PM);          // apaga el bit antes de convertir
    return bcd2dec(hours);
}

uint8_t DS1302RTC_GetDate(){
    return bcd2dec(DS1302RTC_Read( _DS1302_ADDRESS_RTC_DATE ));
}

uint8_t DS1302RTC_GetMonth(){
    return bcd2dec(DS1302RTC_Read( _DS1302_ADDRESS_RTC_MONTH ));
}

uint8_t DS1302RTC_GetWeekDay(){
    return bcd2dec(DS1302RTC_Read( _DS1302_ADDRESS_RTC_DAY ));
}

uint8_t DS1302RTC_GetYear(){
    return bcd2dec(DS1302RTC_Read( _DS1302_ADDRESS_RTC_YEAR ));
}

void DS1302RTC_GetTimeAndDate( ds1302_time_t *t ){
    _DS1302_CE_PORT = 1;    // start comunication    
    
    __delay_us(4);
    _SDO_TRIS = 0;          // enable output SDO
    SPI_WriteBuffer( BYTE_Invert( _DS1302_ADDRESS_RTC_BURST | (_DS1302_RD) ) ); // send command
    while( !SPI_IsDataReady() );
    SPI_ReadBuffer();       // Clear buffer
    
    _SDO_TRIS = 1;          // disable SDO
    
    t->seconds = bcd2dec( BYTE_Invert(SPI_ReadByte()) & 0x7F); // ignora el bit CH
    t->minutes = bcd2dec( BYTE_Invert(SPI_ReadByte()));
    t->hour    = bcd2dec( BYTE_Invert(SPI_ReadByte()) ); // ignora los bits 12/24 y AM/PM
    t->mday    = bcd2dec( BYTE_Invert(SPI_ReadByte()) );
    t->month   = bcd2dec( BYTE_Invert(SPI_ReadByte()) );
    t->wday    = BYTE_Invert(SPI_ReadByte());                // la codificacion bcd y dec coinsiden
    t->year    = bcd2dec(BYTE_Invert(SPI_ReadByte()))+2000;
    
    _DS1302_CE_PORT = 0;    // end comunication   
}

// set functions

void DS1302RTC_SetSeconds( uint8_t seconds ){
    if( seconds > 59u )
        return;
    uint8_t old_value = DS1302RTC_Read(_DS1302_ADDRESS_RTC_SECONDS);

    DS1302RTC_Write( _DS1302_ADDRESS_RTC_SECONDS,
                    (old_value & _DS1302_CH) | dec2bcd(seconds) ); // mantener el estado del bit CH
}

void DS1302RTC_SetMinutes(uint8_t minutes){
    if( minutes > 59u )
        return;
    
    DS1302RTC_Write( _DS1302_ADDRESS_RTC_MINUTES, dec2bcd(minutes));
}

void DS1302RTC_SetHours(uint8_t hours){
    if( hours > 23u )
        return;
    
    DS1302RTC_Write( _DS1302_ADDRESS_RTC_HOURS, dec2bcd(hours) );
}

void DS1302RTC_SetDate(uint8_t date){
    if( date > 31 )
        return;
    DS1302RTC_Write( _DS1302_ADDRESS_RTC_DATE, dec2bcd(date) );
}

void DS1302RTC_SetMonth(uint8_t month){
    if( month > 12 || month == 0 )
        return;
    DS1302RTC_Write( _DS1302_ADDRESS_RTC_MONTH, dec2bcd(month) );
}

void DS1302RTC_SetWeekDay(_DS1302_WEEKDAY day){
    if( day == 0 || day > 7)
        return;
    DS1302RTC_Write( _DS1302_ADDRESS_RTC_DAY, dec2bcd((uint8_t)day) );
}

void DS1302RTC_SetYear( uint8_t year ){
    if( year > 99 )
        return;
    DS1302RTC_Write( _DS1302_ADDRESS_RTC_YEAR, dec2bcd(year) );
}

void DS1302RTC_SetTimeAndDate( ds1302_time_t t ){
    
    t.seconds = BYTE_Invert( dec2bcd(t.seconds) );
    t.minutes = BYTE_Invert( dec2bcd(t.minutes) );
    t.hour = BYTE_Invert( dec2bcd(t.hour) );
    t.mday = BYTE_Invert( dec2bcd(t.mday) );
    t.month = BYTE_Invert( dec2bcd(t.month) );
    t.wday = BYTE_Invert( dec2bcd((uint8_t)t.wday) );
    t.year = BYTE_Invert( dec2bcd((t.year%100)) );
        
    _DS1302_CE_PORT = 1;                // start transaction
    __delay_us(4);                      // wait minimum time
    
    _SDO_TRIS = 0;                      // enable SDO pin
    SPI_SendByte( BYTE_Invert( _DS1302_ADDRESS_RTC_BURST ) );            // set address to write
    SPI_SendByte( t.seconds );          // write data
    SPI_SendByte( t.minutes );          // write data
    SPI_SendByte( t.hour );             // write data
    SPI_SendByte( t.mday );             // write data
    SPI_SendByte( t.month );            // write data
    SPI_SendByte( t.wday );             // write data
    SPI_SendByte( t.year );             // write data
    SPI_SendByte( 0x80 );
    _DS1302_CE_PORT = 0;                // end transaction
}

//halt functions

__bit DS1302RTC_IsHalt(){
    if( DS1302RTC_Read( _DS1302_ADDRESS_RTC_SECONDS ) & _DS1302_CH )
        return 1;
    return 0;
}

void DS1302RTC_HaltRTC(){
    uint8_t old = DS1302RTC_Read( _DS1302_ADDRESS_RTC_SECONDS );
    DS1302RTC_Write( _DS1302_ADDRESS_RTC_SECONDS, old|_DS1302_CH );
}

void DS1302RTC_StartRTC(){
    uint8_t old = DS1302RTC_Read( _DS1302_ADDRESS_RTC_SECONDS );
    old++;
    DS1302RTC_Write( _DS1302_ADDRESS_RTC_SECONDS, old & (~_DS1302_CH) );
}

/* write protection functions */
    
__bit DS1302RTC_GetWriteProtectionState(){
    if( DS1302RTC_Read( _DS1302_ADDRESS_RTC_CONTROL ) & _DS1302_WP)
        return 1;
    return 0;
}

void DS1302RTC_SetWriteProtectionState( _Bool state ){
    uint8_t old = 0;
    if(state == 1)
        old |= _DS1302_WP;

    DS1302RTC_Write( _DS1302_ADDRESS_RTC_CONTROL, old);
}

//static functions
static uint8_t BYTE_Invert( uint8_t byte){
    uint8_t res = 0;
    uint8_t i = 8;
    
    while(i--){
        res <<= 1;
        res |= byte&0x01;
        byte >>= 1;
    }
    return res;
}

static uint8_t bcd2dec( uint8_t x ){
    return ((x>>4)*10) + ( x & 0x0F);
}

static uint8_t dec2bcd( uint8_t x ){
    return ((x/10)<<4) | (x%10);
}
