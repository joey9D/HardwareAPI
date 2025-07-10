
#include "Hardware_Definitions.h"

const HardwareHandles* HardwareDefinitions::GetHardwareHandles()
{
    return &hwHandles;
}



void HardwareDefinitions::MX_CAN_Init(uint16_t baud)
{
	static uint8_t isInit = 0;
	/* USER CODE BEGIN CAN_Init 0 */
	if(isInit == 0)
	{
		isInit = 1;
		typedef struct {
			uint32_t Baudrate;
			uint32_t Prescaler;
			uint32_t TimeSeg1;
			uint32_t TimeSeg2;
		} CAN_Baud_Parameter_t;

		std::array<CAN_Baud_Parameter_t,8> para_can =
		{{
			{1000, 8, CAN_BS1_3TQ, CAN_BS2_2TQ},
			{800, 12, CAN_BS1_2TQ, CAN_BS2_2TQ},
			{500, 16, CAN_BS1_3TQ, CAN_BS2_2TQ},
			{250, 16, CAN_BS1_5TQ, CAN_BS2_6TQ},
			{125, 16, CAN_BS1_16TQ, CAN_BS2_7TQ},
			{50, 80, CAN_BS1_7TQ, CAN_BS2_4TQ},
			{20, 200, CAN_BS1_7TQ, CAN_BS2_4TQ},
			{10, 200, CAN_BS1_16TQ, CAN_BS2_7TQ}
		}};

		CAN_Baud_Parameter_t para_can_val = para_can.at(3);//default baudrate 250

		for(uint8_t i=0; i<para_can.size(); i++)
		{
			if(baud == para_can.at(i).Baudrate)
			{
				para_can_val = para_can.at(i);
				break;
			}
		}
	  /* USER CODE END CAN_Init 0 */

	  /* USER CODE BEGIN CAN_Init 1 */

	  /* USER CODE END CAN_Init 1 */
	  hcan.Instance = CAN;
	  hcan.Init.Prescaler = para_can_val.Prescaler;//16;
	  hcan.Init.Mode = CAN_MODE_NORMAL;
	  hcan.Init.SyncJumpWidth = CAN_SJW_1TQ;
	  hcan.Init.TimeSeg1 = para_can_val.TimeSeg1;//CAN_BS1_8TQ;
	  hcan.Init.TimeSeg2 = para_can_val.TimeSeg2;//CAN_BS2_3TQ;
	  hcan.Init.TimeTriggeredMode = DISABLE;
	  hcan.Init.AutoBusOff = DISABLE;
	  hcan.Init.AutoWakeUp = DISABLE;
	  hcan.Init.AutoRetransmission = DISABLE;
	  hcan.Init.ReceiveFifoLocked = DISABLE;
	  hcan.Init.TransmitFifoPriority = DISABLE;
	  if (HAL_CAN_Init(&hcan) != HAL_OK)
	  {
		Error_Handler();
	  }
  /* USER CODE BEGIN CAN_Init 2 */
	}
  /* USER CODE END CAN_Init 2 */

}
