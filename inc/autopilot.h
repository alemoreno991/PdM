/*=====[Module Name]===========================================================
 * Copyright YYYY Author Alejandro Moreno <ale.moreno991@gmail.com>
 * All rights reserved.
 * License: license text or at least name and link
         (example: BSD-3-Clause <https://opensource.org/licenses/BSD-3-Clause>)
 *
 * Version: 1.0.0
 * Creation Date: 2020/08/17
 */

/*=====[Avoid multiple inclusion - begin]====================================*/

#ifndef _AUTOPILOT_H_
#define _AUTOPILOT_H_

/*=====[Inclusions of public function dependencies]==========================*/

#include "sapi.h"

#include "../inc/controller.h"
#include "../inc/sensor.h"
#include "../inc/telemetry.h"

/*=====[C++ - begin]=========================================================*/

#ifdef __cplusplus
extern "C" {
#endif

/*=====[Definition macros of public constants]===============================*/

#define NUM_STATES 5

#define TAKEOFF_LIMIT 10

#define LANDING_LIMIT 20

#define CRUISE_LOW_LIMIT 50

#define CRUISE_HIGH_LIMIT 70

#define DELTA 5

/*=====[Public function-like macros]=========================================*/

/*=====[Definitions of public data types]====================================*/

typedef enum{
   STATE_TAKEOFF,
   STATE_ASCENT,
   STATE_CRUISE,
   STATE_DESCENT,
   STATE_LANDING
} fsmState_t;

typedef struct{
	fsmState_t fsmState;
	bool_t flagState[NUM_STATES];
	controller_t ctrler;
	sensor_t sensor;
	telemetry_t telemetry;
	double vac;
	double hc;
} autopilot_t;

/*=====[Prototypes (declarations) of public functions]=======================*/

void autopilot_create( autopilot_t * self );

void autopilot_run( autopilot_t * self );

void autopilot_destroy( autopilot_t * self );

/*=====[Prototypes (declarations) of public interrupt functions]=============*/

/*=====[C++ - end]===========================================================*/

#ifdef __cplusplus
}
#endif

/*=====[Avoid multiple inclusion - end]======================================*/

#endif /* _AUTOPILOT_H_ */
