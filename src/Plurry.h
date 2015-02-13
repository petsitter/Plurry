#ifndef PLURRY_H_
#define PLURRY_H_

#include <stdint.h>
#include <stdbool.h>
#include <inc/hw_memmap.h>
#include <inc/hw_types.h>
#include <inc/hw_ints.h>
#include <inc/hw_gpio.h>

#include <driverlib/gpio.h>
#include <driverlib/sysctl.h>
#include <driverlib/i2c.h>
#include <driverlib/ssi.h>
#include <driverlib/udma.h>
#include <driverlib/pin_map.h>

#include <xdc/std.h>
#include <xdc/cfg/global.h>
#include <xdc/runtime/Error.h>
#include <xdc/runtime/System.h>
#include <ti/sysbios/family/arm/m3/Hwi.h>

#define LOADCELL_A 0
#define LOADCELL_B 1

struct EncoderParams_typedef{
	int position;
}typedef EncoderParams;

struct LoadCellCommunicationParams_typedef{
	int loadcellNextRead;

	int LoadValueA_raw;
	int LoadValueA_rawMax;
	int LoadValueA_rawMin;
	int LoadValueA_gram;

	int LoadValueB_raw;
	int LoadValueB_rawMax;
	int LoadValueB_rawMin;
	int LoadValueB_gram;

}typedef LoadCellCommuParams;

struct WifiCommunicationParams_typedef{
	char* SSID;
	char* PASSWORD;
	int timeout;
}typedef WifiCommuParams;

struct ActionModuleCommunicationParams_typedef{
	int id;
	char* msg;

}typedef ActionModuleCommuParams;

extern LoadCellCommuParams loadcellParams;
extern WifiCommuParams wifiParams;
extern EncoderParams encoderParams;

#endif
