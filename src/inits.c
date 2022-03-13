#include "inits.h"

#include <malloc.h>

#include "MDR32F9Qx_rst_clk.h"
#include "MDR32F9Qx_eeprom.h"
#include "MDR32F9Qx_eth.h"
#include "class/tcpip.h"

void Clock_Init()
{
	/* Enable HSE (High Speed External) clock */
	RST_CLK_HSEconfig(RST_CLK_HSE_ON);
	while (RST_CLK_HSEstatus() != SUCCESS);

	/* Configures the CPU_PLL clock source */
	RST_CLK_CPU_PLLconfig(RST_CLK_CPU_PLLsrcHSEdiv2, RST_CLK_CPU_PLLmul16);

	/* Enables the CPU_PLL */
	RST_CLK_CPU_PLLcmd(ENABLE);
	while (RST_CLK_CPU_PLLstatus() == ERROR);

	/* Enables the RST_CLK_PCLK_EEPROM */
	RST_CLK_PCLKcmd(RST_CLK_PCLK_EEPROM, ENABLE);
	/* Sets the code latency value */
	EEPROM_SetLatency(EEPROM_Latency_5);

	/* Select the CPU_PLL output as input for CPU_C3_SEL */
	RST_CLK_CPU_PLLuse(ENABLE);
	/* Set CPUClk Prescaler */
	RST_CLK_CPUclkPrescaler(RST_CLK_CPUclkDIV1);

	/* Select the CPU clock source */
	RST_CLK_CPUclkSelection(RST_CLK_CPUclkCPU_C3);
}

void initNetwork()
{
	static ETH_InitTypeDef  ETH_InitStruct;
	volatile	uint32_t	ETH_Dilimiter;

	// Сброс тактирования Ethernet
	ETH_ClockDeInit();

	//	Включение генератора HSE2 = 25МГц
	RST_CLK_HSE2config(RST_CLK_HSE2_ON);
    while (RST_CLK_HSE2status() != SUCCESS);

	// Тактирование PHY от HSE2 = 25МГц
	ETH_PHY_ClockConfig(ETH_PHY_CLOCK_SOURCE_HSE2, ETH_PHY_HCLKdiv1);

	// Без делителя
	ETH_BRGInit(ETH_HCLKdiv1);

	// Включение тактирования блока MAC
	ETH_ClockCMD(ETH_CLK1, ENABLE);

	//	Сброс регистров блока MAC
	ETH_DeInit(MDR_ETHERNET1);

	//  Инициализация настроек Ethernet по умолчанию
	ETH_StructInit(&ETH_InitStruct);

	//	Переопределение настроек PHY:
	//   - разрешение автонастройки, передатчик и приемник включены
	ETH_InitStruct.ETH_PHY_Mode = ETH_PHY_MODE_AutoNegotiation;
	ETH_InitStruct.ETH_Transmitter_RST = SET;
	ETH_InitStruct.ETH_Receiver_RST = SET;

	//	Режим работы буферов
	ETH_InitStruct.ETH_Buffer_Mode = ETH_BUFFER_MODE_LINEAR;
	//ETH_InitStruct.ETH_Buffer_Mode = ETH_BUFFER_MODE_FIFO;
	//ETH_InitStruct.ETH_Buffer_Mode = ETH_BUFFER_MODE_AUTOMATIC_CHANGE_POINTERS;

  // HASH - Фильтрация отключена
	ETH_InitStruct.ETH_Source_Addr_HASH_Filter = DISABLE;

	//	Задание МАС адреса микроконтроллера
	ETH_InitStruct.ETH_MAC_Address[2] = (MAC_0<<8)|MAC_1;
	ETH_InitStruct.ETH_MAC_Address[1] = (MAC_2<<8)|MAC_3;
	ETH_InitStruct.ETH_MAC_Address[0] = (MAC_4<<8)|MAC_5;

	//	Разделение общей памяти на буферы для приемника и передатчика
	ETH_InitStruct.ETH_Dilimiter = 0x1000;

	//	Разрешаем прием пакетов только на свой адрес,
	//	Прием коротких пакетов также разрешен
	ETH_InitStruct.ETH_Receive_All_Packets 			  	= DISABLE;
	ETH_InitStruct.ETH_Short_Frames_Reception 			= ENABLE;
	ETH_InitStruct.ETH_Long_Frames_Reception 	    	= DISABLE;
	ETH_InitStruct.ETH_Broadcast_Frames_Reception 		= DISABLE;
	ETH_InitStruct.ETH_Error_CRC_Frames_Reception 		= DISABLE;
	ETH_InitStruct.ETH_Control_Frames_Reception 		= DISABLE;
	ETH_InitStruct.ETH_Unicast_Frames_Reception 		= ENABLE;
	ETH_InitStruct.ETH_Source_Addr_HASH_Filter 	  		= DISABLE;

	//	Инициализация блока Ethernet
	ETH_Init(MDR_ETHERNET1, &ETH_InitStruct);

	TCPIP_init();

	// Запуск блока PHY
	ETH_PHYCmd(MDR_ETHERNET1, ENABLE);

	ETH_Start(MDR_ETHERNET1);
}
