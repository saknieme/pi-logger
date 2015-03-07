/*
 * pi-logger-sensor.h
 * 
 * Copyright 2015 Sakari Niemelä <zake@ProBook>
 * 
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA 02110-1301, USA.
 * 
 * 
 */


#ifndef __PI_LOGGER_SENSOR_H
#define __PI_LOGGER_SENSOR_H

/* Constants */
#define PI_LOGGER_SENSOR_MAX_NAME_LENGTH    20
#define PI_LOGGER_SENSOR_MAX_HW_ID_LENGTH   16
#define PI_LOGGER_SENSOR_HISTORY_SIZE       10
#define PI_LOGGER_SENSOR_MAX_COUNT           3

/* Enum for sensor statuses. */
typedef enum pi_logger_sensor_status_s
{
    PI_LOGGER_SENSOR_STATUS_NONE = 0,
    PI_LOGGER_SENSOR_STATUS_CONFIGURED,
    PI_LOGGER_SENSOR_STATUS_ACTIVE,
    PI_LOGGER_SENSOR_STATUS_FAULT,
    PI_LOGGER_SENSOR_STATUS_LAST
} pi_logger_sensor_status_t;

/* Struct for sensor values. */
typedef struct pi_logger_sensor_values_s
{
    float current;
    float max;
    float min;
    float history[ PI_LOGGER_SENSOR_HISTORY_SIZE ];
} pi_logger_sensor_values_t;

/* Struct for sensor properties. */
typedef struct pi_logger_sensor_s
{
    signed int id;
    char name[ PI_LOGGER_SENSOR_MAX_NAME_LENGTH ];
    pi_logger_sensor_status_t status;
    char hw_id[ PI_LOGGER_SENSOR_MAX_HW_ID_LENGTH ];
    pi_logger_sensor_values_t values;
} pi_logger_sensor_t;

/* Function for initializing the sensor table. */
void pi_logger_sensor_init( void );

/* Function for adding a new sensor into the sensor table. */
int pi_logger_sensor_add( pi_logger_sensor_t* sensor );

/* Function for removing a sensor from sensor table. */
int pi_logger_sensor_remove( signed int id );
 
#endif /* PI_LOGGER_SENSOR_H */
