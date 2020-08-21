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

// SENSOR Includes ===========================================================

#include "../inc/sensor.h"
#include <math.h>
#include "sapi.h"

/*=====[Definition macros of private constants]===============================*/

const double ADC2ALTITUDE = 100/pow(2,10);

/*=====[Definitions of private data types]====================================*/


/*=====[Prototypes (declarations) of private functions]=======================*/


// SENSOR IMPLEMENTATIONS (public)===========================================

void sensor_create( sensor_t * self)
{
	   /* Inicializar AnalogIO */
	   /* Posibles configuraciones:
	    *    ADC_ENABLE,  ADC_DISABLE,
	    *    ADC_ENABLE,  ADC_DISABLE,
	    */
	   adcConfig( ADC_ENABLE ); /* ADC */
}

double sensor_getmeasurement( sensor_t * self )
{
	double raw_measure = (double) adcRead( CH1 );
	return raw_measure * ADC2ALTITUDE;
}

void sensor_destroy( sensor_t * self )
{

}
// SENSOR IMPLEMENTATIONS (private)===========================================
