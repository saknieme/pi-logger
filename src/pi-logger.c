/*
 * pi-logger.c
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

#include <pthread.h>

#include "pi-logger.h"
#include "pi-logger-thread.h"

/* Error codes */
#define PI_LOGGER_ERROR_NONE                        0
#define PI_LOGGER_ERROR_MAX_THREAD_COUNT            1

/* Constants */
#define PI_LOGGER_MAX_THREAD_COUNT 3

typedef struct pi_logger_thread_s
{
    unsigned int valid_configuration;
    unsigned int configuration_active;
    pthread_t thread_id;
    
    
} pi_logger_thread_t;

typedef struct pi_logger_thread_list_s
{
    pi_logger_thread_t pi_logger_threads[ PI_LOGGER_MAX_THREAD_COUNT ];
    unsigned int pi_logger_thread_count;
} pi_logger_thread_list_t;

/* Local variables */
pi_logger_thread_list_t pi_logger_thread_list;

/* Initialize thread list */
static void pi_logger_init_thread_list(
    pi_logger_thread_list_t* list )
{
    memset( list, 0, sizeof( pi_logger_thread_list_t ) );
}

static int pi_logger_create_thread_and_add_to_list(
    pi_logger_thread_list_t* list,
    pi_logger_thread_t* thread )
{
    int rc = PI_LOGGER_ERROR_NONE;
    
    rc = pthread_create(
        &thread->thread_id, NULL, pi_logger_thread, NULL );
    
    if ( PI_LOGGER_ERROR_NONE == rc )
    {
        if ( PI_LOGGER_MAX_THREAD_COUNT ==
            list->pi_logger_thread_count )
        {
            rc = PI_LOGGER_ERROR_MAX_THREAD_COUNT;
        }
        else
        {
            list->pi_logger_threads[
                list->pi_logger_thread_count ] = *thread;
            list->pi_logger_thread_count++;
        }
    }
    
    return rc;
}

static int pi_logger_remove_thread_from_list(
    pi_logger_thread_list_t* list,
    pthread_t thread_id )
{
    unsigned int i;
    
    for ( i = 0; i < list->pi_logger_thread_count; i++ )
    {
        if ( list->pi_logger_threads[ i ].thread_id == thread_id )
        {
            
        }
    }
}

int main(int argc, char **argv)
{
	int rc = PI_LOGGER_ERROR_NONE;
    pi_logger_thread_t thread_props;
    
    rc = pi_logger_create_thread_and_add_to_list(
        &pi_logger_thread_list, &thread_props );
    printf( "pi_logger_create_pi_logger_thread returns: %d\n", rc );

    rc = pi_logger_create_thread_and_add_to_list(
        &pi_logger_thread_list, &thread_props );
    printf( "pi_logger_create_pi_logger_thread returns: %d\n", rc );

    while ( 1 );
    
	return 0;
}

