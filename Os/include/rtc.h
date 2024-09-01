#ifndef RTC_H_
#define RTC_H_

#include <stdint.h>

/********************************************************************************
 * Constant Definitions
 *******************************************************************************/
/**
 * @brief enum with the months of the year
*/
enum {
    January = 1,
    February,
    March,
    April,
    May,
    June,
    July,
    August,
    September,
    October,
    November,
    December
};

/**
 * @brief Enum with the days of the week
*/
enum {
    Sunday,
    Monday,
    Tuesday,
    Wednesday,
    Thursday,
    Friday,
    Saturday
};

/********************************************************************************
 * Data Prototypes
 *******************************************************************************/

/** @brief Control union structure to handle certain number of flags each of them represented by a single bit */
typedef union _Rtcc_Ctrl {
    uint8_t Register;   /* 8 bit variable */
    struct _bits {
        uint8_t clk_en: 1;  /*!< clock enable flag  */
        uint8_t al_set: 1;  /*!< alarm set flag  */
        uint8_t al_active: 1; /*!< alarm active flag  */
        uint8_t none : 4;
    } bits;
} Rtcc_Ctrl_t;

/** @brief Control structure to pass parameter on each interface */
typedef struct _Rtcc_Clock {
    uint8_t         tm_sec;         /*!< seconds, range 0 to 59 */
    uint8_t         tm_min;         /*!< minutes, range 0 to 59 */
    uint8_t         tm_hour;        /*!< hours, range 0 to 23 */
    uint8_t         tm_day;         /*!< day of the month, range 1 to 31 */
    uint8_t         tm_mon;         /*!< month, range 1 to 12 */
    uint16_t        tm_year;        /*!< years, range 1900 to 2100 */
    uint8_t         tm_wday;        /*!< day of the week, range 0 to 6 */
    uint8_t         al_min;         /*!< alarm minutes, range 0 to 59 */
    uint8_t         al_hour;        /*!< alarm hours, range 0 to 23 */
    uint8_t         mt_days[13u];   /*!< max days on each month */
    Rtcc_Ctrl_t     ctrl;           /*!< clock control bits */
} Rtcc_Clock_t;



/********************************************************************************
 * External Functions Prototypes
 *******************************************************************************/
/**
 * @brief Function initialize the RTC clock
 * 
 * \param rtcc pointer to the rtc clock data
 * 
 * \return none
 */
void Rtcc_clockInit(Rtcc_Clock_t *rtcc);

/**
 * @brief Function to set the time values into the rtc clock
 * 
 * \param  rtcc     pointer to the rtc clock data
 * \param  hour     hour data for the RTC clock, range 0 to 23 
 * \param  minutes  minutes data for the RTC clock, range 0 to 59 
 * \param  seconds  seconds data for the RTC clock, range 0 to 59
 * 
 * \return TRUE if the setting was successful, otherwise FALSE 
 */
uint8_t Rtcc_setTime(Rtcc_Clock_t *rtcc, uint8_t hour, uint8_t minutes, uint8_t seconds);

/**
 * @brief Function to set the date values into the rtc clock
 * 
 * \param  rtcc     pointer to the rtc clock data
 * \param  day      day data for the RTC clock, range 1 to 31 
 * \param  month    month data for the RTC clock, range 1 to 12 
 * \param  year     year data for the RTC clock, range 1900 to 2100  
 * 
 * \return TRUE if the setting was successful, otherwise FALSE 
 */
uint8_t Rtcc_setDate(Rtcc_Clock_t *rtcc, uint8_t day, uint8_t month, uint16_t year);

/**
 * @brief Function to set the alarm values into the rtc clock
 * 
 * \param  rtcc     pointer to the rtc clock data
 * \param  hour     hour data for the RTC clock alarm, range 0 to 23 
 * \param  minutes  minutes data for the RTC clock alarm, range 0 to 59
 * 
 * \return TRUE if the setting was successful, otherwise FALSE 
 */
uint8_t Rtcc_setAlarm(Rtcc_Clock_t *rtcc, uint8_t hour, uint8_t minutes);

/**
 * @brief Function to get the current time of the RTC clock
 * 
 * \param  rtcc     pointer to the rtc clock data
 * \param  hour     hour data for the RTC clock alarm, range 0 to 23 
 * \param  minutes  minutes data for the RTC clock alarm, range 0 to 59
 * 
 * \return TRUE if the time was obtenined successfully, otherwise FALSE 
 */
void Rtcc_getTime(Rtcc_Clock_t *rtcc, uint8_t *hour, uint8_t *minutes, uint8_t *seconds, uint8_t *messageType);

/**
 * @brief Function to get the current date of the RTC clock
 * 
 * \param  rtcc     pointer to the rtc clock data
 * \param  day      day data for the RTC clock, range 1 to 31 
 * \param  month    month data for the RTC clock, range 1 to 12 
 * \param  year     year data for the RTC clock, range 1900 to 2100
 * 
 * \return TRUE if the date was obtenined successfully, otherwise FALSE 
 */
void Rtcc_getDate(Rtcc_Clock_t *rtcc, uint8_t* day, uint8_t* month, uint16_t* year, uint8_t* weekDay, uint8_t *messageType);

/**
 * @brief Function to get the alarm values into the rtc clock 
 * 
 * \param  rtcc     pointer to the rtc clock data
 * \param  hour     hour data for the RTC clock alarm, range 0 to 23 
 * \param  minutes  minutes data for the RTC clock alarm, range 0 to 59 
 * 
 * \return TRUE if the alarm was obtenined successfully, otherwise FALSE 
 */
uint8_t Rtcc_getAlarm(Rtcc_Clock_t *rtcc, uint8_t* hour, uint8_t* minutes );

/**
 * @brief Function to delete alarm
 * 
 * \param  rtcc     pointer to the rtc clock data 
 * 
 * \return TRUE if the alarm was cleared successfully, otherwise FALSE 
 */
void Rtcc_clearAlarm( Rtcc_Clock_t *rtcc );

/**
 * @brief Function to get the alarm flag status
 * 
 * \param  rtcc     pointer to the rtc clock data
 * 
 * \return TRUE if the alarm was cleared successfully, otherwise FALSE 
 */
uint8_t Rtcc_getAlarmFlag( Rtcc_Clock_t *rtcc );

/**
 * @brief Function to monitor the time and date values based on any regular clock functionality.
 * 
 * \param  rtcc     pointer to the rtc clock data
 * 
 * \return none
 */
void Rtcc_periodicTask( Rtcc_Clock_t *rtcc );

#endif /* __RTC_H */