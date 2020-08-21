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

#ifndef _CONTROLLER_H_
#define _CONTROLLER_H_

/*=====[Inclusions of public function dependencies]==========================*/

#include "sapi.h"

/*=====[C++ - begin]=========================================================*/

#ifdef __cplusplus
extern "C" {
#endif

/*=====[Definition macros of public constants]===============================*/

/*=====[Public function-like macros]=========================================*/

/*=====[Definitions of public data types]====================================*/


typedef struct{

} controller_t;

/*=====[Prototypes (declarations) of public functions]=======================*/

void controller_create( controller_t * self );

double controller_fullthrottle( controller_t * self );

double controller_minthrottle( controller_t * self );

double controller_elevatormaxdeflexion( controller_t * self );

double controller_airspeedfrompitch( controller_t * self,
										const double r, const double yhat );

double controller_airspeedfromthrottle( controller_t * self,
											const double r, const double yhat );

double controller_altitudefrompitch( controller_t * self,
											const double r, const double yhat );

void controller_destroy( controller_t * self );

/*=====[Prototypes (declarations) of public interrupt functions]=============*/

/*=====[C++ - end]===========================================================*/

#ifdef __cplusplus
}
#endif

/*=====[Avoid multiple inclusion - end]======================================*/

#endif /* _CONTROLLER_H_ */
