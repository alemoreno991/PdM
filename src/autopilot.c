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

// AUTOPILOT Includes ===========================================================

#include "../inc/autopilot.h"
#include "../inc/controller.h"
#include "../inc/sensor.h"
#include "../inc/telemetry.h"

#include "sapi.h"

/*=====[Definitions of private data types]====================================*/

typedef fsmState_t (*transitionCallback)(autopilot_t *ptr);

typedef void (*stateCallback)(autopilot_t *ptr);

/*=====[Prototypes (declarations) of private functions]=======================*/

static void error( autopilot_t * self );

static void state(autopilot_t *self, stateCallback entry, stateCallback inside,
							transitionCallback transition, stateCallback exit);

static void takeoffentry(autopilot_t *ptr);

static void takeoffinside(autopilot_t *ptr);

static fsmState_t takeofftransition(autopilot_t *ptr);

static void takeoffexit(autopilot_t *ptr);

static void ascententry(autopilot_t *ptr);

static void ascentinside(autopilot_t *ptr);

static fsmState_t ascenttransition(autopilot_t *ptr);

static void ascentexit(autopilot_t *ptr);

static void cruiseentry(autopilot_t *ptr);

static void cruiseinside(autopilot_t *ptr);

static fsmState_t cruisetransition(autopilot_t *ptr);

static void cruiseexit(autopilot_t *ptr);

static void descententry(autopilot_t *ptr);

static void descentinside(autopilot_t *ptr);

static fsmState_t descenttransition(autopilot_t *ptr);

static void descentexit(autopilot_t *ptr);

static void landentry(autopilot_t *ptr);

static void landinside(autopilot_t *ptr);

static fsmState_t landtransition(autopilot_t *ptr);

static void landexit(autopilot_t *ptr);

// AUTOPILOT IMPLEMENTATIONS (public)===========================================

// FSM Constructor Function
void autopilot_create( autopilot_t * self )
{
	unsigned int i;
	self->fsmState = STATE_TAKEOFF;   // Set initial state

	for (i = 0; i < NUM_STATES; i++){
		self->flagState[i] = false;
	}

	controller_create(&self->ctrler);
	sensor_create(&self->sensor);
	telemetry_create(&self->telemetry, UART_USB, 115200);
}


// FSM Update State Function
void autopilot_run( autopilot_t * self )
{
	switch( self->fsmState ){

      // ----------------------------------------------------------------------
      // STATE TAKEOFF
      // ----------------------------------------------------------------------
      case STATE_TAKEOFF:
    	  state(self, takeoffentry, takeoffinside, takeofftransition, NULL);
      break;

      // ----------------------------------------------------------------------
      // STATE ASCENT
      // ----------------------------------------------------------------------
      case STATE_ASCENT:
    	  state(self, ascententry, ascentinside, ascenttransition, NULL);
      break;

      // ----------------------------------------------------------------------
      // STATE CRUISE
      // ----------------------------------------------------------------------
      case STATE_CRUISE:
    	  state(self, cruiseentry, cruiseinside, cruisetransition, NULL);
      break;

      // ----------------------------------------------------------------------
      // STATE DESCENT
      // ----------------------------------------------------------------------
      case STATE_DESCENT:
    	  state(self, descententry, descentinside, descenttransition, NULL);
      break;

      // ----------------------------------------------------------------------
      // STATE LANDING
      // ----------------------------------------------------------------------
      case STATE_LANDING:
    	  state(self, landentry, landinside, landtransition, NULL);
      break;


      default:
         error(self);
      break;
   }
}

// FSM Destructor Function
void autopilot_destroy( autopilot_t * self )
{

}

// AUTOPILOT IMPLEMENTATIONS (private)===========================================

// FSM Error Handler Function
void error( autopilot_t * self )
{
   // Error handler, example, restart FSM:
   self->fsmState = STATE_TAKEOFF;
}

void state(autopilot_t *self, stateCallback entry, stateCallback inside,
						transitionCallback transition, stateCallback exit)
{
	fsmState_t entryState = self->fsmState;

    // ENTRY ----------------------------------------
    if( self->flagState[entryState] == false )
    {
    	self->flagState[entryState] = true;
    	if (entry != NULL)
    		(*entry)(self);
    }

    // UPDATE OUTPUTS -------------------------------
    // Code for update outputs in this state...
    if (inside != NULL)
    	(*inside)(self);

    // CHECK TRANSITION CONDITIONS ------------------
    // Code for check transitions from this state to others (some ifs)...

    if (transition != NULL)
    	self->fsmState = (*transition)(self);

    // EXIT ------------------------------------------
    if( self->fsmState != entryState )
    {
    	self->flagState[entryState] = false;
    	if (exit != NULL)
    		(*exit)(self);
    }
}



void takeoffentry(autopilot_t *ptr)
{
	gpioWrite( LED1, OFF);
	gpioWrite( LED2, OFF);
	gpioWrite( LED3, OFF);
	gpioWrite( LEDR, OFF);
	gpioWrite( LEDG, OFF);
	gpioWrite( LEDB, OFF);

	controller_fullthrottle(&ptr->ctrler);
	controller_elevatormaxdeflexion(&ptr->ctrler);
}

void takeoffinside(autopilot_t *ptr)
{
	double hhat = -10;

    /* Obtengo una medicion de altura */
    hhat = sensor_getmeasurement(&ptr->sensor);

    /*Comunico los datos a la estacion terrena */
    telemetry_send(&ptr->telemetry, hhat);

}

fsmState_t takeofftransition(autopilot_t *ptr)
{
	if (sensor_getmeasurement(&ptr->sensor) > TAKEOFF_LIMIT){
		return STATE_ASCENT;
	} else {
		return STATE_TAKEOFF;
	}
}

void takeoffexit(autopilot_t *ptr)
{

}


void ascententry(autopilot_t *ptr)
{
	gpioWrite( LED1, OFF);
	gpioWrite( LED2, OFF);
	gpioWrite( LED3, OFF);
	gpioWrite( LEDR, OFF);
	gpioWrite( LEDG, OFF);
	gpioWrite( LEDB, OFF);

	controller_fullthrottle(&ptr->ctrler);
}

void ascentinside(autopilot_t *ptr)
{
	double hhat = -10;
	double vahat = 15;

    /* Obtengo una medicion de altura */
    hhat = sensor_getmeasurement(&ptr->sensor);

    /* Computar la fuerza de control para controlar la velocidad mediante pitch*/
	 controller_airspeedfrompitch(&ptr->ctrler, ptr->vac, vahat );

    /*Comunico los datos a la estacion terrena */
    telemetry_send(&ptr->telemetry, hhat);

}

fsmState_t ascenttransition(autopilot_t *ptr)
{
	if (sensor_getmeasurement(&ptr->sensor) > (CRUISE_LOW_LIMIT + DELTA)){
		return STATE_CRUISE;
	} else {
		return STATE_ASCENT;
	}
}

void ascentexit(autopilot_t *ptr)
{

}

void cruiseentry(autopilot_t *ptr)
{
	gpioWrite( LED1, OFF);
	gpioWrite( LED2, OFF);
	gpioWrite( LED3, OFF);
	gpioWrite( LEDR, OFF);
	gpioWrite( LEDG, OFF);
	gpioWrite( LEDB, OFF);
}

void cruiseinside(autopilot_t *ptr)
{
	double hhat = -10;
	double vahat = 15;

    /* Obtengo una medicion de altura */
    hhat = sensor_getmeasurement(&ptr->sensor);

    /* Computar la fuerza de control para controlar la altura*/
	controller_altitudefrompitch(&ptr->ctrler, ptr->hc, hhat );

	 /* Computar la fuerza de control para controlar la velocidad mediante throttle*/
	 controller_airspeedfromthrottle(&ptr->ctrler, ptr->vac, vahat );

    /*Comunico los datos a la estacion terrena */
    telemetry_send(&ptr->telemetry, hhat);

}

fsmState_t cruisetransition(autopilot_t *ptr)
{
	double hhat = sensor_getmeasurement(&ptr->sensor);

	if (hhat > (CRUISE_HIGH_LIMIT + DELTA)){
		return STATE_DESCENT;
	}

	if (hhat < (CRUISE_LOW_LIMIT - DELTA)){
		return STATE_ASCENT;
	} else {
		return STATE_CRUISE;
	}
}

void cruiseexit(autopilot_t *ptr)
{

}

void descententry(autopilot_t *ptr)
{
	gpioWrite( LED1, OFF);
	gpioWrite( LED2, OFF);
	gpioWrite( LED3, OFF);
	gpioWrite( LEDR, OFF);
	gpioWrite( LEDG, OFF);
	gpioWrite( LEDB, OFF);
}

void descentinside(autopilot_t *ptr)
{
	double hhat = -10;
	double vahat = 15;

    /* Obtengo una medicion de altura */
    hhat = sensor_getmeasurement(&ptr->sensor);

    /* Computar la fuerza de control para controlar la velocidad mediante pitch*/
	 controller_airspeedfrompitch(&ptr->ctrler, ptr->vac, vahat );

    /*Comunico los datos a la estacion terrena */
    telemetry_send(&ptr->telemetry, hhat);

}

fsmState_t descenttransition(autopilot_t *ptr)
{
	double hhat = sensor_getmeasurement(&ptr->sensor);

	if (hhat < (CRUISE_HIGH_LIMIT - DELTA)){
		return STATE_CRUISE;
	}

	if (hhat < (LANDING_LIMIT)){
		return STATE_LANDING;
	} else {
		return STATE_DESCENT;
	}
}

void descentexit(autopilot_t *ptr)
{

}

void landentry(autopilot_t *ptr)
{
	gpioWrite( LED1, OFF);
	gpioWrite( LED2, OFF);
	gpioWrite( LED3, OFF);
	gpioWrite( LEDR, OFF);
	gpioWrite( LEDG, OFF);
	gpioWrite( LEDB, OFF);

	controller_minthrottle(&ptr->ctrler);

}

void landinside(autopilot_t *ptr)
{
	double hhat = -10;

    /* Obtengo una medicion de altura */
    hhat = sensor_getmeasurement(&ptr->sensor);

    /* Computar la fuerza de control para controlar la altura*/
	controller_altitudefrompitch(&ptr->ctrler, ptr->hc, hhat );

    /*Comunico los datos a la estacion terrena */
    telemetry_send(&ptr->telemetry, hhat);

}

fsmState_t landtransition(autopilot_t *ptr)
{
	return STATE_LANDING;
}

void landexit(autopilot_t *ptr)
{

}
