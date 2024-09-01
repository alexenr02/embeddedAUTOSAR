/**
 * \file buffer.c
 * 
 * Functions call necessary for the circular buffer. The circular buffer will
 * store a specific amount of values and it is operated by a FIFO logic.
 * 
*/

/********************************************************************************
 * Header Files
 *******************************************************************************/

#include <stdio.h>
#include <assert.h>
#include <stdint.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>
#include "scheduler.h"
#include "rtc.h"
#include "common.h"

/********************************************************************************
 * Variable Declarations
 *******************************************************************************/

uint8_t months[13] = {31,28,31,30,31,30,31,30,31,30,31,31};

/********************************************************************************
 * Private Function Prototypes
 *******************************************************************************/

/********************************************************************************
 * Public Function
 *******************************************************************************/

void Rtcc_clockInit(Rtcc_Clock_t *rtcc) {
    rtcc->tm_sec = 0;
    rtcc->tm_min = 0;
    rtcc->tm_hour = 0;
    rtcc->tm_day = 1;
    rtcc->tm_mon = 1;
    rtcc->tm_year = 1900;
    rtcc->tm_wday = 0;
    rtcc->al_min = 0;
    rtcc->al_hour = 0;
    rtcc->mt_days[13] = months[13];
    rtcc->ctrl.Register = 0xFF;
    rtcc->ctrl.bits.clk_en = 0;
    rtcc->ctrl.bits.al_set = 0;
    rtcc->ctrl.bits.al_active = 0;
    rtcc->ctrl.bits.none = 0;
}


uint8_t Rtcc_setTime(Rtcc_Clock_t *rtcc, uint8_t hour, uint8_t minutes, uint8_t seconds) {
    if(hour > 24 || hour < 0 || minutes < 0 || minutes > 59 || seconds < 0 || seconds > 59 ) {
        printf("\n\n Incorrect time format\n\n");
        return FALSE;
    }

    rtcc->tm_hour = hour;
    rtcc->tm_min = minutes;
    rtcc->tm_sec = seconds;
    return TRUE;
}


uint8_t Rtcc_setDate(Rtcc_Clock_t *rtcc, uint8_t day, uint8_t month, uint16_t year) {
    bool leap = FALSE;
    if ( year % 4 == 0 && year % 100 != 0 || year % 400 == 0) {
        leap = TRUE;
    }
    if(day > 31 || day < 0 || month < 1 || month > 12 || year < 1900 || year > 2100 || (leap == FALSE && day == 29) ) {
        printf("\n\n Incorrect Date format, dates out of range\n\n");
        return FALSE;
    }
    

    if (day > months[month - 1]) {
        printf("\n\n Incorrect Date format, day does not match with month\n\n");
        return FALSE;
    }
   
    uint16_t dayOfWeek = year;
    uint8_t lastTwoDigits = year;
    if ( (dayOfWeek - 2000) < 0 ) {
        dayOfWeek = dayOfWeek - 1900;
        lastTwoDigits = dayOfWeek;
    } else {
        dayOfWeek = dayOfWeek - 2000;
        lastTwoDigits = dayOfWeek;
    }
   
    dayOfWeek = dayOfWeek / 4;
    dayOfWeek = dayOfWeek + day;

    rtcc->tm_day = day;
    rtcc->tm_mon = month;
    rtcc->tm_year = year;

    switch (rtcc->tm_mon) {
        case January:
        if ( leap == FALSE ) {
            dayOfWeek = dayOfWeek + 1;
        }
            break;
        case February:
        if ( leap == FALSE) {
            dayOfWeek = dayOfWeek + 4;
        } else {
            dayOfWeek = dayOfWeek + 3;
        }
            break;
        case March:
            dayOfWeek = dayOfWeek + 4;
            break;
        case April:
            dayOfWeek = dayOfWeek + 0;
            break;
        case May:
            dayOfWeek = dayOfWeek + 2; 
            break;
        case June:
            dayOfWeek = dayOfWeek + 5;
            break; 
        case July:
            dayOfWeek = dayOfWeek + 0;
            break;
        case August:
            dayOfWeek = dayOfWeek + 3; 
            break;
        case September:
            dayOfWeek = dayOfWeek + 6;
            break;
        case October:
            dayOfWeek = dayOfWeek + 1;
            break; 
        case November:
            dayOfWeek = dayOfWeek + 4;
            break;
        case December:
            dayOfWeek = dayOfWeek + 6;
            break;
        default:
            break;
            
    }

    if ( (year - 2000) < 0 ) {
        dayOfWeek = dayOfWeek;
    } else {
        dayOfWeek = dayOfWeek + 6;
    }

    dayOfWeek = dayOfWeek + lastTwoDigits;
    dayOfWeek = dayOfWeek % 7;
    if (dayOfWeek == 0) {
        rtcc->tm_wday = 6;
    } else {
        rtcc->tm_wday = dayOfWeek;
    }
    switch (dayOfWeek) {
        case 0:
            rtcc->tm_wday = Saturday;
        break;
        case 1:
            rtcc->tm_wday = Sunday;
        break;
        case 2:
            rtcc->tm_wday = Monday;
        break;
        case 3:
            rtcc->tm_wday = Tuesday;
        break;
        case 4:
            rtcc->tm_wday = Wednesday;
        break;
        case 5:
            rtcc->tm_wday = Thursday;
        break;
        case 6:
            rtcc->tm_wday = Friday;
        break;
        default:
        break;
    }
    return TRUE;
}

uint8_t Rtcc_setAlarm(Rtcc_Clock_t *rtcc, uint8_t hour, uint8_t minutes) {
    if(hour > 23 || hour < 0 || minutes < 0 || minutes > 59 ) {
        printf("\n\n Incorrect Alarm format\n\n");
        return FALSE;
    }
    rtcc->al_hour = hour;
    rtcc->al_min = minutes;
    rtcc->ctrl.bits.al_set = TRUE;
    return TRUE;
}

void Rtcc_getTime(Rtcc_Clock_t *rtcc, uint8_t *hour, uint8_t *minutes, uint8_t *seconds, uint8_t *messageType) {
    *hour = rtcc->tm_hour;
    *minutes = rtcc->tm_min;
    *seconds = rtcc->tm_sec;
    *messageType = HOUR;
}

void Rtcc_getDate(Rtcc_Clock_t *rtcc, uint8_t* day, uint8_t* month, uint16_t* year, uint8_t* weekDay, uint8_t *messageType) {
    *day = rtcc->tm_day;
    *month = rtcc->tm_mon;
    *year = rtcc->tm_year;
    *weekDay = rtcc->tm_wday;
    *messageType = DATE;
}

uint8_t Rtcc_getAlarm(Rtcc_Clock_t *rtcc, uint8_t* hour, uint8_t* minutes ) {
        *hour = rtcc->al_hour;
        *minutes = rtcc->al_min;
        return rtcc->ctrl.bits.al_set;
}

void Rtcc_clearAlarm( Rtcc_Clock_t *rtcc ) {
    if ( rtcc->ctrl.bits.al_active == TRUE && rtcc->al_hour == rtcc->tm_hour && rtcc->al_min == rtcc->tm_min) {
        rtcc->ctrl.bits.al_active = FALSE;
        rtcc->ctrl.bits.al_active = FALSE;
    }
}

uint8_t Rtcc_getAlarmFlag( Rtcc_Clock_t *rtcc ) {
    return rtcc->ctrl.bits.al_active;
}

void Rtcc_periodicTask( Rtcc_Clock_t *rtcc ) {
    rtcc->tm_sec++;
    if ( rtcc->tm_sec > 59 ) {
        rtcc->tm_min++;
        rtcc->tm_sec = 0;
        if ( rtcc->tm_min > 59 ) {
            rtcc->tm_min = 0;
            rtcc->tm_hour++;
            if ( rtcc->tm_hour > 23 ) {
            rtcc->tm_hour = 0;
            rtcc->tm_day++;
            }
            switch (rtcc->tm_mon) {
                case January:
                    if (rtcc->tm_day > months[0]) {
                        rtcc->tm_day = 1;
                        rtcc->tm_mon++;
                    }
                break;
                case February:
                    /* leap year */
                    if ( rtcc->tm_year % 4 == 0 && rtcc->tm_year % 100 != 0 || rtcc->tm_year % 400 == 0) {
                    /* leap year february */
                    if ( rtcc->tm_day > (months[1] + 1 )) {
                            rtcc->tm_day = 1;
                            rtcc->tm_mon++;
                        } 
                    } else {
                        if (rtcc->tm_day > months[1]) {
                            rtcc->tm_day = 1;
                            rtcc->tm_mon++;
                        }
                    }
                break;
                case March:
                    if (rtcc->tm_day > months[2]) {
                        rtcc->tm_day = 1;
                        rtcc->tm_mon++;
                    }
                break;
                case April:
                    if (rtcc->tm_day > months[3]) {
                        rtcc->tm_day = 1;
                        rtcc->tm_mon++;
                    }
                break;
                case May:
                    if (rtcc->tm_day > months[4]) {
                        rtcc->tm_day = 1;
                        rtcc->tm_mon++;
                    }
                break;
                case June:
                    if (rtcc->tm_day > months[5]) {
                        rtcc->tm_day = 1;
                        rtcc->tm_mon++;
                    }
                break;
                case July:
                    if (rtcc->tm_day > months[6]) {
                        rtcc->tm_day = 1;
                        rtcc->tm_mon++;
                    }
                break;
                case August:
                    if (rtcc->tm_day > months[7]) {
                        rtcc->tm_day = 1;
                        rtcc->tm_mon++;
                    }
                break;
                case September:
                    if (rtcc->tm_day > months[8]) {
                        rtcc->tm_day = 1;
                        rtcc->tm_mon++;
                    }
                break;
                case October:
                    if (rtcc->tm_day > months[9]) {
                        rtcc->tm_day = 1;
                        rtcc->tm_mon++;
                    }
                break;
                case November:
                    if (rtcc->tm_day > months[10]) {
                        rtcc->tm_day = 1;
                        rtcc->tm_mon++;
                    }
                break;
                case December:
                    if (rtcc->tm_day > months[11]) {
                        rtcc->tm_day = 1;
                        rtcc->tm_mon = 1;
                        rtcc->tm_year++;
                    }
                break;
                default:
                break;
            }
        }
    }
    //printf("\n|\tTime: %d:%d:%d\t\t\t\t|\n", rtcc->tm_hour, rtcc->tm_min, rtcc->tm_sec);
    //printf("|\tDate: %d/%d/%d\t\t\t\t|\n", rtcc->tm_day, rtcc->tm_mon, rtcc->tm_year);
    //printf("|-----------------------------------------------|");
}

/********************************************************************************
 * Private Function Definitions
 *******************************************************************************/