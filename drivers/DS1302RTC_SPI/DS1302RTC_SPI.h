/* 
 * File:   DS1302RTC_SPI.h
 * Author: Jose Guerra Carmenate
 * Comments:
 * +------------+         +-----------+
 * | PIC MCU    |         |           |
 * |         SDI|-+-------|DAT        |
 * |            | |       |           |
 * |         SDO|-+       |   DS1302  |
 * |            |         |           |
 * |         SCK|---------|CLK        |
 * |            |         |           |
 * |          xx|---------|CE         |
 * +------------+         +-----------+
 * 
 * Revision history: 
 */

// This is a guard condition so that contents of this file are not included
// more than once.  
#ifndef _DS1302RTC_SPI_H
#define	_DS1302RTC_SPI_H

#include <xc.h> // include processor files - each processor file is guarded.  
#include <stdint.h>
#include <time.h>

/* Section: Data Type Definition */

/**
 * Direcciones de los Registros del RTC DS1302
 */
typedef enum{
    // RTC registers
    _DS1302_ADDRESS_RTC_SECONDS = 0x80u,
    _DS1302_ADDRESS_RTC_MINUTES = 0x82u,
    _DS1302_ADDRESS_RTC_HOURS   = 0x84u,
    _DS1302_ADDRESS_RTC_DATE    = 0x86u,
    _DS1302_ADDRESS_RTC_MONTH   = 0x88u,
    _DS1302_ADDRESS_RTC_DAY     = 0x8Au,
    _DS1302_ADDRESS_RTC_YEAR    = 0x8Cu,
    _DS1302_ADDRESS_RTC_CONTROL = 0x8Eu,
    _DS1302_ADDRESS_RTC_TRICKLE = 0x90u,
    _DS1302_ADDRESS_RTC_BURST   = 0xBEu,

    // RAM registers
    _DS1302_ADDRESS_RAM_START   = 0xC0u,
    _DS1302_ADDRESS_RAM_END     = 0xFCu,
    _DS1302_ADDRESS_RAM_BURST   = 0xFEu,
    // 
} _DS1302_ADDRESS;

typedef enum{
    _DS1302_HOURS_FORMAT_12HOUR = 0x80,
    _DS1302_HOURS_FORMAT_24HOUR = 0x00
} _DS1302_HOURS_FORMAT;

/**
 * Definicion de los dias de la semana 
 */
typedef enum{
    _DS1302_WEEKDAY_SUNDAY    = 0x01,
    _DS1302_WEEKDAY_MONDAY    = 0x02,
    _DS1302_WEEKDAY_TUESDAY   = 0x03,
    _DS1302_WEEKDAY_WEDNESDAY = 0x04,
    _DS1302_WEEKDAY_THURSDAY  = 0x05,
    _DS1302_WEEKDAY_FRIDAY    = 0x06,
    _DS1302_WEEKDAY_SATURDAY  = 0x07
} _DS1302_WEEKDAY;


/**
 * Tipo de dato que permite almacenar toda la informacion
 * proporcionada por el RTC DS1302
 */
typedef struct{
    uint8_t seconds;     // segundos
    uint8_t minutes;     // minutos
    uint8_t hour;        // hora
    uint8_t mday;        // dia del mes
    uint8_t month;       // mes
    _DS1302_WEEKDAY wday;// dia de la semana
    uint16_t year;        // anno
    
} DS1302_time;

/* Section: Macros */

// Read/Write operations
#define _DS1302_READ  1u
#define _DS1302_WRITE 0u

/// Bit 7 of the Seconds registers
#define _DS1302_CH_bit       0x07u // clock halt flag ( 1 - halt, 0 - start)
#define _DS1302_CH          (1u<<(_DS1302_CH_bit))

/// Bit 7 of the Control register
#define _DS1302_WP_bit       0x07u // write-protect ( 1 - active, 0 - no active)
#define _DS1302_WP           (1u<<(_DS1302_WP_bit))

/// Bit 5 of the Hour register
#define _DS1302_AM_PM_bit    0x05u
#define _DS1302_AM_PM        (1u<<(_DS1302_AM_PM_bit))

///

/// Command Byte Options

//         bits :   7     6      5    4    3    2    1      0  
// Command byte : | 1 | RAM/CK | A4 | A3 | A2 | A1 | A0 | RD/WR |

#define _DS1302_RAM          0x80u // operation over RAM data 
#define _DS1302_CK           0x00u // operation over clock/calendar data

#define _DS1302_RD           0x01u // read operation
#define _DS1302_WR           0x00u // write operation



#ifdef	__cplusplus
extern "C" {
#endif /* __cplusplus */

    /**
     * @brief 
     * Inicializa el bus de comunicacion: 
     *   - Configura el bus SPI en modo 0,0.
     *   - Configura el pin CE como salida y lo pone a nivel bajo
     * 
     * @param 
     * None
     * 
     * @return 
     * None
     * 
     * @pre 
     * La cabecera DS1302RTC_SPI_config.h debe estar correctamente configurada
     * 
     * @author Jose Guerra Carmenate
     * @version 1.0
     */
    void DS1302RTC_Initialize(  ); //ok

    /**
     * @brief 
     * Permite leer una direccion de memoria del DS1302
     * 
     * @param[in] address La direccion a obtener. Ver enum _DS1302_ADDRESS para
     * comprobar las opciones disponibles
     * 
     * @return 
     * uint8_t El valor de la direccion especificada como parametro. El numero
     * esta codificado como BCD.
     * 
     * @pre 
     * La rutina DS1302RTC_Initialize debe haber sido ejecutada previamente.
     * La cabecera DS1302RTC_SPI_config.h debe estar correctamente configurada.
     * 
     * @example
     * DS1302RTC_Initialize();
     * .
     * .
     * .
     * year = DS1302RTC_Read( _DS1302_ADDRESS_RTC_YEAR );
     * 
     * @author Jose Guerra Carmenate
     * @version 1.0
     */    
    uint8_t DS1302RTC_Read( _DS1302_ADDRESS address ); //ok

    /**
     * @brief 
     * Permite escribir una direccion de memoria del DS1302
     * 
     * @param[in] address La direccion a escribir. Ver enum _DS1302_ADDRESS para
     * comprobar las opciones disponibles
     * 
     * @param[in] value El valor a escribir
     * 
     * @return 
     * None
     * 
     * @pre 
     * La rutina DS1302RTC_Initialize debe haber sido ejecutada previamente.
     * La cabecera DS1302RTC_SPI_config.h debe estar correctamente configurada.
     * 
     * @example
     * DS1302RTC_Initialize();
     * .
     * .
     * .
     * DS1302RTC_Write( _DS1302_ADDRESS_RTC_YEAR, 19 );
     * 
     * @author Jose Guerra Carmenate
     * @version 1.0
     */        
    void DS1302RTC_Write( _DS1302_ADDRESS address, uint8_t value ); //ok
    
    /* Get functions */
    
    /**
     * @brief 
     * Permite obtener los segundos del minuto en curso.
     * 
     * @param
     *  None
     * 
     * @return uint8_t Cantidad de segundos del minuto en curso [0-59]
     * 
     * 
     * @pre 
     * La rutina DS1302RTC_Initialize debe haber sido ejecutada previamente.
     * La cabecera DS1302RTC_SPI_config.h debe estar correctamente configurada.
     * 
     * @example
     * DS1302RTC_Initialize();
     * .
     * .
     * printf ( "%d", DS1302RTC_GetSeconds( ) );
     * 
     * @author Jose Guerra Carmenate
     * @version 1.0
     */
    uint8_t DS1302RTC_GetSeconds(); //ok
    
    /**
     * @brief 
     * Permite obtener los minutos.
     * 
     * @param
     *  None
     * 
     * @return uint8_t Cantidad de minutos [0-59]
     * 
     * 
     * @pre 
     * La rutina DS1302RTC_Initialize debe haber sido ejecutada previamente.
     * La cabecera DS1302RTC_SPI_config.h debe estar correctamente configurada.
     * 
     * @example
     * DS1302RTC_Initialize();
     * .
     * .
     * printf ( "%d", DS1302RTC_GetMinutes( ) );
     * 
     * @author Jose Guerra Carmenate
     * @version 1.0
     */
    uint8_t DS1302RTC_GetMinutes(); //ok
    
    /**
     * @brief 
     * Permite obtener las horas.
     * 
     * @param
     *  None
     * 
     * @return uint8_t Cantidad de horas [0-23]/[1-12]
     * 
     * @pre 
     * La rutina DS1302RTC_Initialize debe haber sido ejecutada previamente.
     * La cabecera DS1302RTC_SPI_config.h debe estar correctamente configurada.
     * 
     * @example
     * DS1302RTC_Initialize();
     * .
     * .
     * printf ( "%d", DS1302RTC_GetHours( ) );
     * 
     * @author Jose Guerra Carmenate
     * @version 1.0
     */
    uint8_t DS1302RTC_GetHours(); //ok

    /**
     * @brief 
     * Permite obtener el dia del mes.
     * 
     * @param
     *  None
     * 
     * @return uint8_t El dia del mes [1-31]
     * 
     * @pre 
     * La rutina DS1302RTC_Initialize debe haber sido ejecutada previamente.
     * La cabecera DS1302RTC_SPI_config.h debe estar correctamente configurada.
     * 
     * @example
     * DS1302RTC_Initialize();
     * .
     * .
     * printf ( "%d", DS1302RTC_GetDate( ) );
     * 
     * @author Jose Guerra Carmenate
     * @version 1.0
     */
    uint8_t DS1302RTC_GetDate(); // ok
    
    /**
     * @brief 
     * Permite obtener el mes actual.
     * 
     * @param
     *  None
     * 
     * @return uint8_t El Mes [1-12]
     * 
     * @pre 
     * La rutina DS1302RTC_Initialize debe haber sido ejecutada previamente.
     * La cabecera DS1302RTC_SPI_config.h debe estar correctamente configurada.
     * 
     * @example
     * DS1302RTC_Initialize();
     * .
     * .
     * printf ( "%d", DS1302RTC_GetMonth( ) );
     * 
     * @author Jose Guerra Carmenate
     * @version 1.0
     */
    uint8_t DS1302RTC_GetMonth(); //ok

    /**
     * @brief 
     * Permite obtener el dia de la semana.
     * 
     * @param
     *  None
     * 
     * @return uint8_t El dia de la semana [1-7]
     * 
     * @pre 
     * La rutina DS1302RTC_Initialize debe haber sido ejecutada previamente.
     * La cabecera DS1302RTC_SPI_config.h debe estar correctamente configurada.
     * 
     * @example
     * DS1302RTC_Initialize();
     * .
     * .
     * printf ( "%d", DS1302RTC_GetWeekDay( ) );
     * 
     * @author Jose Guerra Carmenate
     * @version 1.0
     */
    uint8_t DS1302RTC_GetWeekDay(); // ok

    /**
     * @brief 
     * Permite obtener el anno.
     * 
     * @param
     *  None
     * 
     * @return uint8_t El ano actual [00-99]
     * 
     * @pre 
     * La rutina DS1302RTC_Initialize debe haber sido ejecutada previamente.
     * La cabecera DS1302RTC_SPI_config.h debe estar correctamente configurada.
     * 
     * @example
     * DS1302RTC_Initialize();
     * 
     * 
     * printf ( "%d", DS1302RTC_GetYear( ) );
     * 
     * @author Jose Guerra Carmenate
     * @version 1.0
     */
    uint8_t DS1302RTC_GetYear(); // ok
    
    /**
     * @brief 
     * Permite obtener Fecha y Hora en una estructura DS1302_time.
     * 
     * @param[out] DS1302_time t se almacenan los datos de hora y fecha
     * actuales en el DS1302.
     *  
     * 
     * @return 
     * None
     * 
     * @pre 
     * La rutina DS1302RTC_Initialize debe haber sido ejecutada previamente.
     * La cabecera DS1302RTC_SPI_config.h debe estar correctamente configurada.
     * 
     * @example
     * DS1302RTC_Initialize();
     * .
     * .
     * config_time.seconds = 13;
     * config_time.minutes = 45;
     * config_time.hour = 2;
     * config_time.mday = 23;
     * config_time.month= 6;
     * config_time.wday = _DS1302_WEEKDAY_SATURDAY;
     * config_time.year = 2019;
     * 
     * DS1302RTC_GetTimeAndDate( &config_time );
     * printf( "Hora: %d", config_time.tm_year );
     * printf( "Min : %d", config_time.tm_min );
     * printf( "Sec : %d", config_time.tm_sec );
     * 
     * @author Jose Guerra Carmenate
     * @version 1.0
     */    
    void DS1302RTC_GetTimeAndDate( DS1302_time * ); // ok

    /* Set functions */
    
    /**
     * @brief 
     * Permite modificar los segundos del Reloj.
     * 
     * @param[in] seconds valor a poner en el registro de segundos
     * 
     * @return
     * None
     * 
     * @pre 
     * La rutina DS1302RTC_Initialize debe haber sido ejecutada previamente.
     * La cabecera DS1302RTC_SPI_config.h debe estar correctamente configurada.
     * La proteccion contra escritura del DS1302 tiene que estar deshabilitada
     * 
     * @example
     * DS1302RTC_Initialize();
     * .
     * .
     * DS1302RTC_SetSeconds(13);
     * 
     * @author Jose Guerra Carmenate
     * @version 1.0
     */
    void DS1302RTC_SetSeconds( uint8_t seconds ); // ok


    /**
     * @brief 
     * Permite modificar los minutos del Reloj.
     * 
     * @param[in] minutes valor a poner en el registro de minutos
     * 
     * @return
     * None
     * 
     * @pre 
     * La rutina DS1302RTC_Initialize debe haber sido ejecutada previamente.
     * La cabecera DS1302RTC_SPI_config.h debe estar correctamente configurada.
     * La proteccion contra escritura del DS1302 tiene que estar deshabilitada
     * 
     * @example
     * DS1302RTC_Initialize();
     * .
     * .
     * DS1302RTC_SetMinutes(32);
     * 
     * @author Jose Guerra Carmenate
     * @version 1.0
     */
    void DS1302RTC_SetMinutes( uint8_t minutes ); // ok

    /**
     * @brief 
     * Permite modificar las horas del Reloj.
     * 
     * @param[in] hours valor a poner en el registro de horas
     * 
     * @return
     * None
     * 
     * @pre 
     * La rutina DS1302RTC_Initialize debe haber sido ejecutada previamente.
     * La cabecera DS1302RTC_SPI_config.h debe estar correctamente configurada.
     * La proteccion contra escritura del DS1302 tiene que estar deshabilitada
     * 
     * @example
     * DS1302RTC_Initialize();
     * .
     * .
     * DS1302RTC_SetHours(14);
     * 
     * @author Jose Guerra Carmenate
     * @version 1.0
     */
    void DS1302RTC_SetHours( uint8_t hours ); // ok
    
   /**
     * @brief 
     * Permite modificar el dia del mes
     * 
     * @param[in] date valor a poner en el registro de dia de mes
     * 
     * @return
     * None
     * 
     * @pre 
     * La rutina DS1302RTC_Initialize debe haber sido ejecutada previamente.
     * La cabecera DS1302RTC_SPI_config.h debe estar correctamente configurada.
     * La proteccion contra escritura del DS1302 tiene que estar deshabilitada
     * 
     * @example
     * DS1302RTC_Initialize();
     * .
     * .
     * DS1302RTC_SetDate(25);
     * 
     * @author Jose Guerra Carmenate
     * @version 1.0
     */
    void DS1302RTC_SetDate( uint8_t date ); // ok
    
    
   /**
     * @brief 
     * Permite modificar el mes
     * 
     * @param[in] month valor a poner en el registro de mes
     * 
     * @return
     * None
     * 
     * @pre 
     * La rutina DS1302RTC_Initialize debe haber sido ejecutada previamente.
     * La cabecera DS1302RTC_SPI_config.h debe estar correctamente configurada.
     * La proteccion contra escritura del DS1302 tiene que estar deshabilitada
     * 
     * @example
     * DS1302RTC_Initialize();
     * .
     * .
     * DS1302RTC_SetMonth(10);
     * 
     * @author Jose Guerra Carmenate
     * @version 1.0
     */    
    void DS1302RTC_SetMonth( uint8_t month ); //ok

        
    /**
     * @brief 
     * Permite modificar el dia de la semana
     * 
     * @param[in] _DS1302_WEEKDAY day dia de la semana. Ver 
     * enum _DS1302_WEEKDAY para mas detalles
     * 
     * @return
     * None
     * 
     * @pre 
     * La rutina DS1302RTC_Initialize debe haber sido ejecutada previamente.
     * La cabecera DS1302RTC_SPI_config.h debe estar correctamente configurada.
     * La proteccion contra escritura del DS1302 tiene que estar deshabilitada
     * 
     * @example
     * DS1302RTC_Initialize();
     * .
     * .
     * DS1302RTC_SetWeekDay(_DS1302_WEEKDAY_FRIDAY);
     * 
     * @author Jose Guerra Carmenate
     * @version 1.0
     */    
    void DS1302RTC_SetWeekDay( _DS1302_WEEKDAY day ); // ok

    /**
     * @brief 
     * Permite modificar el anno
     * 
     * @param[in] uint8_t year valor a poner en el registro de anno  
     * 
     * @return
     * None
     * 
     * @pre 
     * La rutina DS1302RTC_Initialize debe haber sido ejecutada previamente.
     * La cabecera DS1302RTC_SPI_config.h debe estar correctamente configurada.
     * La proteccion contra escritura del DS1302 tiene que estar deshabilitada
     * 
     * @example
     * DS1302RTC_Initialize();
     * .
     * .
     * DS1302RTC_SetYear(19);
     * 
     * @author Jose Guerra Carmenate
     * @version 1.0
     */    
    void DS1302RTC_SetYear( uint8_t year ); // ok

    /**
     * @brief 
     * Permite modificar todos los parametros de tiempo del DS1302 y habilita
     * la proteccion contra escritura
     * 
     * @param[in] DS1302_time t - configuracion de tiempo para el DS1302
     * 
     * @return
     * None
     * 
     * @pre 
     * La rutina DS1302RTC_Initialize debe haber sido ejecutada previamente.
     * La cabecera DS1302RTC_SPI_config.h debe estar correctamente configurada.
     * La proteccion contra escritura del DS1302 tiene que estar deshabilitada
     * 
     * @example
     * DS1302RTC_Initialize();
     * .
     * .
     * DS1302_time config_time;
     * config_time.seconds = 13;
     * config_time.minutes = 45;
     * config_time.hour = 7;
     * config_time.mday = 23;
     * config_time.month= 6;
     * config_time.wday = _DS1302_WEEKDAY_SATURDAY;
     * config_time.year = 2019;
     * DS1302RTC_SetTimeAndDate( config_time );
     * 
     * @author Jose Guerra Carmenate
     * @version 1.0
     */    
    void DS1302RTC_SetTimeAndDate( DS1302_time t ); // ok
    
    /* halt functions */
    
    /**
     * @brief 
     * Permite conocer el estado del oscilador de reloj.
     * 
     * @param
     * None
     * 
     * @return __bit 
     * 1 - Oscilador de reloj detenido
     * 0 - Oscilador de reloj activo
     * 
     * @pre 
     * La rutina DS1302RTC_Initialize debe haber sido ejecutada previamente.
     * La cabecera DS1302RTC_SPI_config.h debe estar correctamente configurada.
     * 
     * @example
     * DS1302RTC_Initialize();
     * .
     * .
     * if( DS1302RTC_IsHalt() ){
     * 
     * }
     * 
     * @author Jose Guerra Carmenate
     * @version 1.0
     */    
    __bit DS1302RTC_IsHalt();   // ok
    
    
    /**
     * @brief 
     * Detiene el oscilador de reloj. El tiempo no se actualiza y se conservan
     * los datos actuales
     * 
     * @param
     * None
     * 
     * @return
     * None
     * 
     * @pre 
     * La rutina DS1302RTC_Initialize debe haber sido ejecutada previamente.
     * La cabecera DS1302RTC_SPI_config.h debe estar correctamente configurada.
     * La proteccion contra escritura del DS1302 tiene que estar deshabilitada
     * 
     * @example
     * DS1302RTC_Initialize();
     * .
     * .
     * DS1302RTC_HaltRTC();
     * 
     * @author Jose Guerra Carmenate
     * @version 1.0
     */    
    void DS1302RTC_HaltRTC();   // ok
    
    
    /**
     * @brief 
     * Activa el oscilador de reloj.
     * 
     * @param
     * None
     * 
     * @return
     * None
     * 
     * @pre 
     * La rutina DS1302RTC_Initialize debe haber sido ejecutada previamente.
     * La cabecera DS1302RTC_SPI_config.h debe estar correctamente configurada.
     * La proteccion contra escritura del DS1302 tiene que estar deshabilitada
     * 
     * @example
     * DS1302RTC_Initialize();
     * .
     * .
     * DS1302RTC_StartRTC();
     * 
     * @author Jose Guerra Carmenate
     * @version 1.0
     */   
    void DS1302RTC_StartRTC();  // ok
    
    /* write protection functions */
    
    /**
     * @brief 
     * Comprueba la proteccion contra escrituras del DS1302
     * 
     * @param
     * None
     * 
     * @return __bit
     * 1 - Proteccion activada
     * 0 - Proteccion desactivada
     * 
     * @pre 
     * La rutina DS1302RTC_Initialize debe haber sido ejecutada previamente.
     * La cabecera DS1302RTC_SPI_config.h debe estar correctamente configurada.
     * 
     * @example
     * DS1302RTC_Initialize();
     * .
     * .
     * if (DS1302RTC_GetWriteProtectionState() ){
     * 
     * }
     * 
     * @author Jose Guerra Carmenate
     * @version 1.0
     */   
    __bit DS1302RTC_GetWriteProtectionState();  // ok
    
    /**
     * @brief 
     * Activa/Desactiva la proteccion contra escrituras del DS1302
     * 
     * @param[in] bool state
     * 1 - Proteccion activada
     * 0 - Proteccion desactivada
     * 
     * @pre 
     * La rutina DS1302RTC_Initialize debe haber sido ejecutada previamente.
     * La cabecera DS1302RTC_SPI_config.h debe estar correctamente configurada.
     * 
     * @example
     * DS1302RTC_Initialize();
     * .
     * .
     * DS1302RTC_SetWriteProtectionState(1)
     * 
     * @author Jose Guerra Carmenate
     * @version 1.0
     */   
    void DS1302RTC_SetWriteProtectionState( _Bool state ); // ok
    
    

#ifdef	__cplusplus
}
#endif /* __cplusplus */

#endif	/* XC_HEADER_TEMPLATE_H */

