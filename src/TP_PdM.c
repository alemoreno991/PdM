/*=============================================================================
 * Author: Alejandro Moreno <ale.moreno991@gmail.com>
 * Date: 2020/08/16
 * Version: 1.0
 *===========================================================================*/

/*=====[Inclusions of function dependencies]=================================*/

#include "sapi.h"

#include "../inc/TP_PdM.h"
#include "../inc/autopilot.h"

/*=====[Definition macros of private constants]==============================*/

/*=====[Definitions of extern global variables]==============================*/

/*=====[Definitions of public global variables]==============================*/

/*=====[Definitions of private global variables]=============================*/

/*=====[Implementaciones de funciones publicas]==============================*/

/*=====[Main function, program entry point after power on or reset]==========*/

int main(void){
   /* ------------- INICIALIZACIONES ------------- */

   /* Inicializar la placa */
   boardConfig();

   /* Inicializar piloto automatico*/
   autopilot_t autopilot;
   autopilot_create(&autopilot);

   /* Variables de delays no bloqueantes */
   delay_t delay1;

   /* Inicializar Retardo no bloqueante con tiempo en ms */
   delayConfig( &delay1, 250 );

   /* ------------- REPETIR POR SIEMPRE ------------- */
   while(1) {
      /* delayRead retorna TRUE cuando se cumple el tiempo de retardo */
      if ( delayRead( &delay1 ) ){
    	  autopilot_run(&autopilot);
      }
   }

   /* NO DEBE LLEGAR NUNCA AQUI, debido a que a este programa no es llamado
      por ningun S.O. */
   return 0 ;
}

/*==================[end of file]============================================*/
