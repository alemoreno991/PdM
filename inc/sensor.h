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

#ifndef _SENSOR_H_
#define _SENSOR_H_

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

} sensor_t;

/*=====[Prototypes (declarations) of public functions]=======================*/

void sensor_create( sensor_t * self );

double sensor_getmeasurement( sensor_t * self );

void sensor_destroy( sensor_t * self );

/*=====[Prototypes (declarations) of public interrupt functions]=============*/

/*=====[C++ - end]===========================================================*/

#ifdef __cplusplus
}
#endif

/*=====[Avoid multiple inclusion - end]======================================*/

#endif /* _SENSOR_H_ */
