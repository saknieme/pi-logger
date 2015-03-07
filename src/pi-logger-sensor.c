/*
 * pi-logger-sensor.c
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


#include <stdio.h>
#include <string.h>

#include "pi-logger-sensor.h"
#include "pi-logger-common.h"

/* Static variables */
static pi_logger_sensor_t g_sensor_list[ PI_LOGGER_SENSOR_MAX_COUNT ];
static unsigned int g_sensor_list_count;

void pi_logger_sensor_init( void )
{
    unsigned int i;
    g_sensor_list_count = 0;
    
    for( i = 0; i < PI_LOGGER_SENSOR_MAX_COUNT; i++ )
    {
        g_sensor_list[ i ].id = -1;
        memset( &g_sensor_list[ i ].name, 0,
            sizeof( g_sensor_list[ i ].name ) );
        g_sensor_list[ i ].status = PI_LOGGER_SENSOR_STATUS_NONE;
        memset( &g_sensor_list[ i ].hw_id, 0,
            sizeof( g_sensor_list[ i ].hw_id ) );
        memset( &g_sensor_list[ i ].values, 0,
            sizeof( g_sensor_list[ i ].values ) );
    }
}

int pi_logger_sensor_add( pi_logger_sensor_t* sensor )
{
    int rc = PI_LOGGER_ERROR_NONE;
    
    if ( g_sensor_list_count == PI_LOGGER_SENSOR_MAX_COUNT )
    {
        return PI_LOGGER_ERROR_MAX_SENSOR_COUNT;
    }
    
    memcpy( &g_sensor_list[ g_sensor_list_count ], sensor,
        sizeof( pi_logger_sensor_t ) );
    g_sensor_list[ g_sensor_list_count ].id = g_sensor_list_count + 1;
    
    printf( "pi_logger_sensor_add: sensor added, id: %d\n",
        g_sensor_list[ g_sensor_list_count ].id );

    g_sensor_list_count++;
        
    return rc;
}

int pi_logger_sensor_remove( signed int id )
{
    int i;
    int rc = PI_LOGGER_ERROR_NONE;
    int sensor_found = 0;
    
    for ( i = 0; i < PI_LOGGER_SENSOR_MAX_COUNT; i++ )
    {
        if ( g_sensor_list[ i ].id == id )
        {
            g_sensor_list[ i ].status = PI_LOGGER_SENSOR_STATUS_NONE;
            sensor_found = 1;
        }
    }
    
    if ( 0 == sensor_found )
    {
        rc = PI_LOGGER_ERROR_SENSOR_NOT_FOUND;
    }
    
    return rc;
}
