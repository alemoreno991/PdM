/* Copyright 2018, Eric Pernia.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 *
 * 3. Neither the name of the copyright holder nor the names of its
 *    contributors may be used to endorse or promote products derived from this
 *    software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 *
 */

// CONTROLLER Includes ===========================================================

#include <stdlib.h>
#include "sapi.h"

#include "../inc/telemetry.h"


/*=====[Definition macros of private constants]===============================*/

/*=====[Definitions of private data types]====================================*/

/*=====[Prototypes (declarations) of private functions]=======================*/

// CONTROLLER IMPLEMENTATIONS (public)===========================================

void telemetry_create( telemetry_t * self, uartMap_t uart, uint32_t baudrate )
{
	self->uart = uart;
	self->baudrate = baudrate;
	uartConfig( self->uart, self->baudrate );
}

void telemetry_send( telemetry_t * self, double data )
{
    /* Conversión de muestra entera a ascii con base decimal */
    sprintf(self->uartBuff, "%lf", data);

    /* Enviar muestra y Enter */
    uartWriteString( self->uart, "Altura [m] = " );
    uartWriteString( self->uart, self->uartBuff );
    uartWriteString( self->uart, "\r\n" );
}

void telemetry_destroy( telemetry_t * self )
{

}

// CONTROLLER IMPLEMENTATIONS (private)===========================================
