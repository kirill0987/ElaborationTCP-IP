#include <stdio.h>
#include "MDR32F9Qx_config.h"
#include "MDR32F9Qx_rst_clk.h"

#include "inc/inits.h"
#include "class/tcpip.h"

int main(void)
{
	Clock_Init();
 	initNetwork();

	__enable_irq();

	for (;;)
	{
		 ETH_InputPachetHandler(MDR_ETHERNET1);
		 DoNetworkStuff(MDR_ETHERNET1);
	}
}
