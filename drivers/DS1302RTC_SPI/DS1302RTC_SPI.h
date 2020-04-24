/**
 * @file DS1302RTC_SPI.h
 * @author Jose Guerra Carmenate
 * 
 * @brief Esta cabecera provee una API para interactuar con el
 * reloj de tiempo real (RTC) DS1302.
 *
 *  Esta implementacion utiliza el mo'dulo SSP presente en los 
 * microcontrolares PIC de 8 bits por lo tanto solo puede ser utilizada
 * en aquellos dispositivos que lo posean. El pin CE o /RST es indicado
 * mediante la cabecera de configuracio'n (DS1302RTC_SPI_config.h)
 *
 * <b>Circuit:</b>
 * @verbatim
  +------------+         +-----------+
  | PIC MCU    |         |           |
  |         SDI|-+-------|DAT        |
  |            | |       |           |
  |         SDO|-+       |   DS1302  |
  |            |         |           |
  |         SCK|---------|CLK        |
  |            |         |           |
  |          xx|---------|CE         |
  +------------+         +-----------+
  @endverbatim
 * <b>Revision history:</b>
 *  - Initial release.
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
 * @brief Direcciones de los registros internos del DS1302.
 * 
 * Son utilizadas como argumentos en las funciones:
 * DS1302RTC_Read, DS1302RTC_Write.
 */
typedef enum{
    // RTC registers
    _DS1302_ADDRESS_RTC_SECONDS = 0x80u,///< Registro de segundos del RTC
    _DS1302_ADDRESS_RTC_MINUTES = 0x82u,///< Registro de minutos del RTC 
    _DS1302_ADDRESS_RTC_HOURS   = 0x84u,///< Registro de horas del RTC
    _DS1302_ADDRESS_RTC_DATE    = 0x86u,///< Registro de dia del mes del RTC
    _DS1302_ADDRESS_RTC_MONTH   = 0x88u,///< Registro de mes del RTC
    _DS1302_ADDRESS_RTC_DAY     = 0x8Au,///< Registro de dia de semana del RTC
    _DS1302_ADDRESS_RTC_YEAR    = 0x8Cu,///< Registro de anno del RTC
    _DS1302_ADDRESS_RTC_CONTROL = 0x8Eu,///< Registro de control del RTC
    _DS1302_ADDRESS_RTC_TRICKLE = 0x90u,///< Registro trickle del RTC
    _DS1302_ADDRESS_RTC_BURST   = 0xBEu,///< Registro burst del RTC

    // RAM registers
    _DS1302_ADDRESS_RAM_START   = 0xC0u,///< Posicion inicial de RAM
    _DS1302_ADDRESS_RAM_END     = 0xFCu,///< Posicion final de RAM
    _DS1302_ADDRESS_RAM_BURST   = 0xFEu,///< Registro de burst de RAM

} _DS1302_ADDRESS;

/**
 * @brief Permite definir el formato horario a utilizar.
 */
typedef enum{
    _DS1302_HOURS_FORMAT_12HOUR = 0x80,
    _DS1302_HOURS_FORMAT_24HOUR = 0x00
} _DS1302_HOURS_FORMAT;

/**
 * @brief Definicion de los dias de la semana,
 *
 * Es utilizado en la funcion _DS1302_WEEKDAY como parametro
 * para especificar el dia de la semana.
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
 * @brief Permite almacenar toda la informacion
 * proporcionada por el chip DS1302
 */
typedef struct{
    uint8_t seconds;     ///< segundos
    uint8_t minutes;     ///< minutos
    uint8_t hour;        ///< hora
    uint8_t mday;        ///< dia del mes
    uint8_t month;       ///< mes
    _DS1302_WEEKDAY wday;///< dia de la semana
    uint16_t year;       ///< anno
    
} ds1302_time_t;




#ifdef	__cplusplus
extern "C" {
#endif /* __cplusplus */

    /**
     * @brief 
     * Inicializa el bus de comunicacion: 
     *   - Configura el bus SPI en modo 0,0.
     *   - Configura el pin CE como salida y lo pone a nivel bajo
     * 
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
     * @code
     * DS1302RTC_Initialize();
     * ...
     * year = DS1302RTC_Read( _DS1302_ADDRESS_RTC_YEAR );
     * @endcode
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
     * @pre 
     * La rutina DS1302RTC_Initialize debe haber sido ejecutada previamente.
     * La cabecera DS1302RTC_SPI_config.h debe estar correctamente configurada.
     * 
     * @code
     * DS1302RTC_Initialize();
     * ...
     * DS1302RTC_Write( _DS1302_ADDRESS_RTC_YEAR, 19 );
     * @endcode
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
     * @return uint8_t Cantidad de segundos del minuto en curso [0-59]
     * 
     * @pre 
     * La rutina DS1302RTC_Initialize debe haber sido ejecutada previamente.
     * La cabecera DS1302RTC_SPI_config.h debe estar correctamente configurada.
     * 
     * @code
     * DS1302RTC_Initialize();
     * ...
     * printf ( "%d", DS1302RTC_GetSeconds( ) );
     * @endcode
     *
     * @author Jose Guerra Carmenate
     * @version 1.0
     */
    uint8_t DS1302RTC_GetSeconds(); //ok
    
    /**
     * @brief 
     * Permite obtener los minutos.
     * 
     * @return uint8_t Cantidad de minutos [0-59]
     * 
     * @pre 
     * La rutina DS1302RTC_Initialize debe haber sido ejecutada previamente.
     * La cabecera DS1302RTC_SPI_config.h debe estar correctamente configurada.
     * 
     * @code
     * DS1302RTC_Initialize();
     * ...
     * printf ( "%d", DS1302RTC_GetMinutes( ) );
     * @endcode
     *
     * @author Jose Guerra Carmenate
     * @version 1.0
     */
    uint8_t DS1302RTC_GetMinutes(); //ok
    
    /**
     * @brief 
     * Permite obtener las horas.
     * 
     * 
     * @return uint8_t Cantidad de horas [0-23]/[1-12]
     * 
     * @pre 
     * La rutina DS1302RTC_Initialize debe haber sido ejecutada previamente.
     * La cabecera DS1302RTC_SPI_config.h debe estar correctamente configurada.
     * 
     * @code
     * DS1302RTC_Initialize();
     * ...
     * printf ( "%d", DS1302RTC_GetHours( ) );
     * @endcode
     * 
     * @author Jose Guerra Carmenate
     * @version 1.0
     */
    uint8_t DS1302RTC_GetHours(); //ok

    /**
     * @brief 
     * Permite obtener el dia del mes.
     * 
     * 
     * @return uint8_t El dia del mes [1-31]
     * 
     * @pre 
     * La rutina DS1302RTC_Initialize debe haber sido ejecutada previamente.
     * La cabecera DS1302RTC_SPI_config.h debe estar correctamente configurada.
     * 
     * @code
     * DS1302RTC_Initialize();
     * ...
     * printf ( "%d", DS1302RTC_GetDate( ) );
     * @endcode
     * 
     * @author Jose Guerra Carmenate
     * @version 1.0
     */
    uint8_t DS1302RTC_GetDate(); // ok
    
    /**
     * @brief 
     * Permite obtener el mes actual.
     * 
     * 
     * @return uint8_t El Mes [1-12]
     * 
     * @pre 
     * La rutina DS1302RTC_Initialize debe haber sido ejecutada previamente.
     * La cabecera DS1302RTC_SPI_config.h debe estar correctamente configurada.
     * 
     * @code
     * DS1302RTC_Initialize();
     * .
     * .
     * printf ( "%d", DS1302RTC_GetMonth( ) );
     * @endcode
     * @author Jose Guerra Carmenate
     * @version 1.0
     */
    uint8_t DS1302RTC_GetMonth(); //ok

    /**
     * @brief 
     * Permite obtener el dia de la semana.
     * 
     * 
     * @return uint8_t El dia de la semana [1-7]
     * 
     * @pre 
     * La rutina DS1302RTC_Initialize debe haber sido ejecutada previamente.
     * La cabecera DS1302RTC_SPI_config.h debe estar correctamente configurada.
     * 
     * @code
     * DS1302RTC_Initialize();
     * ...
     * printf ( "%d", DS1302RTC_GetWeekDay( ) );
     * @endcode 
     *
     * @author Jose Guerra Carmenate
     * @version 1.0
     */
    uint8_t DS1302RTC_GetWeekDay(); // ok

    /**
     * @brief 
     * Permite obtener el anno.
     * 
     * 
     * @return uint8_t El anno actual [00-99]
     * 
     * @pre 
     * La rutina DS1302RTC_Initialize debe haber sido ejecutada previamente.
     * La cabecera DS1302RTC_SPI_config.h debe estar correctamente configurada.
     * 
     * @code
     * DS1302RTC_Initialize();
     * ...
     * printf ( "%d", DS1302RTC_GetYear( ) );
     * @endcode
     *
     * @author Jose Guerra Carmenate
     * @version 1.0
     */
    uint8_t DS1302RTC_GetYear(); // ok
    
    /**
     * @brief 
     * Permite alamcenar la informacion de fecha y hora en una estructura ds1302_time_t.
     * 
     * @param[out] time puntero a estructura ds1302_time_t, donde se almacena la informacion de hora y fecha
     * actuales en el DS1302. (ver estructura ds1302_time_t para mas informacion)
     *  
     * @pre 
     * La rutina DS1302RTC_Initialize debe haber sido ejecutada previamente.
     * La cabecera DS1302RTC_SPI_config.h debe estar correctamente configurada.
     * 
     * @code
     * DS1302RTC_Initialize();
     * ...
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
     * @endcode 
     *
     * @author Jose Guerra Carmenate
     * @version 1.0
     */    
    void DS1302RTC_GetTimeAndDate( ds1302_time_t *time ); // ok

    /* Set functions */
    
    /**
     * @brief 
     * Permite modificar los segundos del RTC.
     * 
     * @param[in] seconds valor a poner en el registro de segundos
     * 
     * @pre 
     * La rutina DS1302RTC_Initialize debe haber sido ejecutada previamente.
     * La cabecera DS1302RTC_SPI_config.h debe estar correctamente configurada.
     * La proteccion contra escritura del DS1302 tiene que estar deshabilitada
     * 
     * @code
     * DS1302RTC_Initialize();
     * .
     * .
     * DS1302RTC_SetSeconds(13);
     * @endcode
     * 
     * @author Jose Guerra Carmenate
     * @version 1.0
     */
    void DS1302RTC_SetSeconds( uint8_t seconds ); // ok


    /**
     * @brief 
     * Permite modificar los minutos del RTC.
     * 
     * @param[in] minutes valor a poner en el contador de minutos 
     * del RTC
     * 
     * @pre 
     * La rutina DS1302RTC_Initialize debe haber sido ejecutada previamente.
     * La cabecera DS1302RTC_SPI_config.h debe estar correctamente configurada.
     * La proteccion contra escritura del DS1302 tiene que estar deshabilitada
     * 
     * @code
     * DS1302RTC_Initialize();
     * .
     * .
     * DS1302RTC_SetMinutes(32);
     * @endcode
     * 
     * @author Jose Guerra Carmenate
     * @version 1.0
     */
    void DS1302RTC_SetMinutes( uint8_t minutes ); // ok

    /**
     * @brief 
     * Permite modificar las horas del RTC.
     * 
     * @param[in] hours valor a poner en el contador de horas del RTC
     * 
     * @pre 
     * La rutina DS1302RTC_Initialize debe haber sido ejecutada previamente.
     * La cabecera DS1302RTC_SPI_config.h debe estar correctamente configurada.
     * La proteccion contra escritura del DS1302 tiene que estar deshabilitada
     * 
     * @code
     * DS1302RTC_Initialize();
     * .
     * .
     * DS1302RTC_SetHours(14);
     * @endcode
     *
     * @author Jose Guerra Carmenate
     * @version 1.0
     */
    void DS1302RTC_SetHours( uint8_t hours ); // ok
    
   /**
     * @brief 
     * Permite modificar el dia del mes del RTC
     * 
     * @param[in] date valor a poner en el contador de dias del mes
     * 
     * @pre 
     * La rutina DS1302RTC_Initialize debe haber sido ejecutada previamente.
     * La cabecera DS1302RTC_SPI_config.h debe estar correctamente configurada.
     * La proteccion contra escritura del DS1302 tiene que estar deshabilitada
     * 
     * @code
     * DS1302RTC_Initialize();
     * .
     * .
     * DS1302RTC_SetDate(25);
     * @endcode 
     *
     * @author Jose Guerra Carmenate
     * @version 1.0
     */
    void DS1302RTC_SetDate( uint8_t date ); // ok
    
    
   /**
     * @brief 
     * Permite modificar el mes del RTC
     * 
     * @param[in] month valor a poner en el contador de meses
     * 
     * @pre 
     * La rutina DS1302RTC_Initialize debe haber sido ejecutada previamente.
     * La cabecera DS1302RTC_SPI_config.h debe estar correctamente configurada.
     * La proteccion contra escritura del DS1302 tiene que estar deshabilitada
     * 
     * @code
     * DS1302RTC_Initialize();
     * .
     * .
     * DS1302RTC_SetMonth(10);
     * @endcode
     *
     * @author Jose Guerra Carmenate
     * @version 1.0
     */    
    void DS1302RTC_SetMonth( uint8_t month ); //ok

        
    /**
     * @brief 
     * Permite modificar el dia de la semana del RTC
     * 
     * @param[in] day valor a poner en el contador del dia de la 
     * semana. Ver enum _DS1302_WEEKDAY para mas detalles
     * 
     * @pre 
     * La rutina DS1302RTC_Initialize debe haber sido ejecutada previamente.
     * La cabecera DS1302RTC_SPI_config.h debe estar correctamente configurada.
     * La proteccion contra escritura del DS1302 tiene que estar deshabilitada
     * 
     * @code
     * DS1302RTC_Initialize();
     * .
     * .
     * DS1302RTC_SetWeekDay(_DS1302_WEEKDAY_FRIDAY);
     * @endcode
     *
     * @author Jose Guerra Carmenate
     * @version 1.0
     */    
    void DS1302RTC_SetWeekDay( _DS1302_WEEKDAY day ); // ok

    /**
     * @brief 
     * Permite modificar el anno del RTC
     * 
     * @param[in] year valor a poner en el contador de anno del RTC  
     * 
     * @pre 
     * La rutina DS1302RTC_Initialize debe haber sido ejecutada previamente.
     * La cabecera DS1302RTC_SPI_config.h debe estar correctamente configurada.
     * La proteccion contra escritura del DS1302 tiene que estar deshabilitada
     * 
     * @code
     * DS1302RTC_Initialize();
     * .
     * .
     * DS1302RTC_SetYear(19);
     * @endcode
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
     * @param[in] t Estructura ds1302_time_t con la configuracion de 
     * tiempo para configurar el chip DS1302.
     * 
     * @pre 
     * La rutina DS1302RTC_Initialize debe haber sido ejecutada previamente.
     * La cabecera DS1302RTC_SPI_config.h debe estar correctamente configurada.
     * La proteccion contra escritura del DS1302 tiene que estar deshabilitada
     * 
     * @code
     * DS1302RTC_Initialize();
     * .
     * .
     * ds1302_time_t config_time;
     * config_time.seconds = 13;
     * config_time.minutes = 45;
     * config_time.hour = 7;
     * config_time.mday = 23;
     * config_time.month= 6;
     * config_time.wday = _DS1302_WEEKDAY_SATURDAY;
     * config_time.year = 2019;
     * DS1302RTC_SetTimeAndDate( config_time );
     * @endcode
     *
     * @author Jose Guerra Carmenate
     * @version 1.0
     */    
    void DS1302RTC_SetTimeAndDate( ds1302_time_t t ); // ok
    
    /* halt functions */
    
    /**
     * @brief 
     * Permite conocer el estado del oscilador del RTC.
     * 
     * @return __bit 
     * 1 - Oscilador de reloj detenido
     * 0 - Oscilador de reloj activo
     * 
     * @pre 
     * La rutina DS1302RTC_Initialize debe haber sido ejecutada previamente.
     * La cabecera DS1302RTC_SPI_config.h debe estar correctamente configurada.
     * 
     * @code
     * DS1302RTC_Initialize();
     * .
     * .
     * if( DS1302RTC_IsHalt() ){
     * 
     * }
     * @endcode
     * 
     * @author Jose Guerra Carmenate
     * @version 1.0
     */    
    __bit DS1302RTC_IsHalt();   // ok
    
    
    /**
     * @brief 
     * Detiene el oscilador del RTC. 
     *
     *  Esta rutina detiene el oscilador del DS1302. Cuando esto 
     * ocurre el tiempo no se actualiza y se mantienen los datos 
     * invariantes.
     * 
     * @pre 
     * La rutina DS1302RTC_Initialize debe haber sido ejecutada previamente.
     * La cabecera DS1302RTC_SPI_config.h debe estar correctamente configurada.
     * La proteccion contra escritura del DS1302 tiene que estar deshabilitada
     * 
     * @code
     * DS1302RTC_Initialize();
     * .
     * .
     * DS1302RTC_HaltRTC();
     * @endcode
     * 
     * @author Jose Guerra Carmenate
     * @version 1.0
     */    
    void DS1302RTC_HaltRTC();   // ok
    
    
    /**
     * @brief 
     * Activa el oscilador del RTC.
     * 
     * @pre 
     * La rutina DS1302RTC_Initialize debe haber sido ejecutada previamente.
     * La cabecera DS1302RTC_SPI_config.h debe estar correctamente configurada.
     * La proteccion contra escritura del DS1302 tiene que estar deshabilitada
     * 
     * @code
     * DS1302RTC_Initialize();
     * .
     * .
     * DS1302RTC_StartRTC();
     * @endcode
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
     * @return __bit:
     *  - 1: Proteccio'n activada
     *  - 0: Proteccio'n desactivada
     * 
     * @pre 
     * La rutina DS1302RTC_Initialize debe haber sido ejecutada previamente.
     * La cabecera DS1302RTC_SPI_config.h debe estar correctamente configurada.
     * 
     * @code
     * DS1302RTC_Initialize();
     * .
     * .
     * if (DS1302RTC_GetWriteProtectionState() ){
     * 		// do some thing...
     * }
     * @endcode
     * 
     * @author Jose Guerra Carmenate
     * @version 1.0
     */   
    __bit DS1302RTC_GetWriteProtectionState();  // ok
    
    /**
     * @brief 
     * Activa/Desactiva la proteccio'n contra escrituras del DS1302
     * 
     * @param[in] state:
     *  - 1: Activar proteccio'n
     *  - 0: Desactivar proteccio'n
     * 
     * @pre 
     * La rutina DS1302RTC_Initialize debe haber sido ejecutada previamente.
     * La cabecera DS1302RTC_SPI_config.h debe estar correctamente configurada.
     * 
     * @code
     * DS1302RTC_Initialize();
     * .
     * .
     * DS1302RTC_SetWriteProtectionState(1)
     * @endcode
     * @author Jose Guerra Carmenate
     * @version 1.0
     */   
    void DS1302RTC_SetWriteProtectionState( _Bool state ); // ok
    
    

#ifdef	__cplusplus
}
#endif /* __cplusplus */

#endif	/* _DS1302RTC_SPI_H */

