#include <xdc/std.h>
#include <xdc/cfg/global.h>
#include <xdc/runtime/Log.h>

#include <ti/sysbios/BIOS.h>

#include <ti/drivers/GPIO.h>
// #include <ti/drivers/I2C.h>
// #include <ti/drivers/SPI.h>
// #include <ti/drivers/UART.h>
// #include <ti/drivers/Watchdog.h>
// #include <ti/drivers/WiFi.h>

#include <stdint.h>
#include <stdbool.h>
#include "inc/hw_types.h"
#include "inc/hw_memmap.h"
#include "driverlib/sysctl.h"
#include "driverlib/gpio.h"
#include "inc/hw_ints.h"
#include "driverlib/interrupt.h"
#include "driverlib/timer.h"
#include "driverlib/pwm.h"

/* Example/Board Header files */
#include "Board.h"
#include "src/Plurry.h"

void Plurry_init();

LoadCellCommuParams loadcellParams;
WifiCommuParams wifiParams;
EncoderParams encoderParams;

/* Tasks*/
Void heartBeatFxn(UArg arg0, UArg arg1) {
	while (1) {
		GPIO_toggle(Plurry_TestLED2);
		Task_sleep(500);
	}
}
Void loadCellCommunicationFxn() {
	int i;
	volatile int test;
	while (1) {
		for (i = 0; i < 50; i++) {
			if (i % 2 == 0) {
				GPIO_write(Plurry_LoadcellClock, 0xff);
				if (GPIO_read(Plurry_LoadcellData) > 0) {
					loadcellParams.LoadValueA_raw |= 1 << (25 - (i / 2));
				}
			} else {
				GPIO_write(Plurry_LoadcellClock, 0x00);
			}
		}
		loadcellParams.LoadValueA_gram = 0
				- (loadcellParams.LoadValueA_raw
						- loadcellParams.LoadValueA_rawMax) * 5000
						/ (loadcellParams.LoadValueA_rawMax
								- loadcellParams.LoadValueA_rawMin);
		loadcellParams.LoadValueA_raw = 0;
		Task_sleep(100);
	}
}

Void pwmManagementFxn() {

}

Void ActionModule0Fxn() {

}
Void ActionModule1Fxn() {

}
Void ActionModule2Fxn() {

}
Void ActionModule3Fxn() {

}
Void ActionModule4Fxn() {

}
Void ActionModule5Fxn() {

}

/* interrupt service routines*/
void EncoderCallbackAFunction() {
	GPIO_clearInt(Plurry_ENC_A);
	if(GPIO_read(Plurry_ENC_A) > 0){
		//rising edge
		if(GPIO_read(Plurry_ENC_B) > 0){
			encoderParams.position++;
		}
		else{
			encoderParams.position--;
		}
	}
	else{
		//falling edge
	}
}
void EncoderCallbackBFunction() {
	GPIO_clearInt(Plurry_ENC_B);
	if(GPIO_read(Plurry_ENC_B) > 0){
			//rising edge
			if(GPIO_read(Plurry_ENC_A) > 0){
				encoderParams.position--;
			}
			else{
				encoderParams.position++;
			}
		}
		else{
			//falling edge
		}
}



int main(void) {
	/* Call board init functions */
	Board_initGeneral();
	Board_initGPIO();
	Board_initUART();

	/* Turn on user LED  */

	Plurry_init();

	GPIO_setupCallbacks(&gpioPortACallbacks);

	/* Enable interrupts */
	GPIO_enableInt(Plurry_ENC_A, GPIO_INT_BOTH_EDGES);
	GPIO_enableInt(Plurry_ENC_B, GPIO_INT_BOTH_EDGES);

	/* Start BIOS */
	BIOS_start();

	return (0);
}

void Plurry_init() {
	/*Additional Hardware Initialization code*/
}

