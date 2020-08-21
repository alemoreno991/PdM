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

#include "../inc/controller.h"

#include "sapi.h"

/*=====[Definition macros of private constants]===============================*/

const double MAX_THROTTLE = 100;

const double MIN_THROTTLE = 0;

const double MAX_DEFLEXION_ELEVATOR = 45;


/*=====[Definitions of private data types]====================================*/


/*=====[Prototypes (declarations) of private functions]=======================*/


// CONTROLLER IMPLEMENTATIONS (public)===========================================

void controller_create( controller_t * self )
{

}

double controller_fullthrottle( controller_t * self )
{
	gpioWrite( LED1, ON);
	gpioWrite( LED2, OFF);
	gpioWrite( LED3, OFF);
	gpioWrite( LEDR, OFF);
	gpioWrite( LEDG, OFF);
	gpioWrite( LEDB, OFF);
	return MAX_THROTTLE;
}

double controller_minthrottle( controller_t * self )
{
	gpioWrite( LED1, OFF);
	gpioWrite( LED2, ON);
	gpioWrite( LED3, OFF);
	gpioWrite( LEDR, OFF);
	gpioWrite( LEDG, OFF);
	gpioWrite( LEDB, OFF);
	return MIN_THROTTLE;
}

double controller_elevatormaxdeflexion( controller_t * self )
{
	gpioWrite( LEDB, ON);
	return MAX_DEFLEXION_ELEVATOR;
}

double controller_airspeedfrompitch( controller_t * self,
										const double r, const double yhat )
{
	gpioWrite( LED3, OFF);
	gpioToggle( LEDR );
	gpioWrite( LEDG, OFF);
	gpioWrite( LEDB, OFF);

	//Acá se tendría que ejecutar algun algorimo de control o incluso llamar
	//algun "metodo" de un objeto PID o LQR o algo así.
	return 20.4;
}

double controller_airspeedfromthrottle( controller_t * self,
										const double r, const double yhat )
{

	gpioToggle( LEDG );

	//Acá se tendría que ejecutar algun algorimo de control o incluso llamar
	//algun "metodo" de un objeto PID o LQR o algo así.
	return 20.4;
}

double controller_altitudefrompitch( controller_t * self,
										const double r, const double yhat )
{
	gpioToggle( LED3 );

	//Acá se tendría que ejecutar algun algorimo de control o incluso llamar
	//algun "metodo" de un objeto PID o LQR o algo así.
	return 3.78;
}

void controller_destroy( controller_t * self )
{

}
// CONTROLLER IMPLEMENTATIONS (private)===========================================
