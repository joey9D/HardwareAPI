
#include "Hardware_Definitions.h"

const HardwareHandles* HardwareDefinitions::GetHardwareHandles()
{
    return &hwHandles;
}



//HAL_StatusTypeDef HardwareDefinitions::Register_FDCAN_ExtendedID_Filters(FDCAN_HandleTypeDef *hfdcan,
//                                                    const uint32_t *ext_ids,
//                                                    uint32_t num_ids,
//                                                    uint32_t fifo_num)
//{
//   for (uint32_t i = 0; i < num_ids; i += 2) {
//       FDCAN_FilterTypeDef sFilterConfig = {0};
//       sFilterConfig.IdType = FDCAN_EXTENDED_ID;
//       sFilterConfig.FilterIndex = i / 2;
//       sFilterConfig.FilterType = FDCAN_FILTER_LIST;
//       sFilterConfig.FilterConfig = (fifo_num == 1) ? FDCAN_FILTER_TO_RXFIFO1 : FDCAN_FILTER_TO_RXFIFO0;
//       sFilterConfig.FilterID1 = ext_ids[i];
//       sFilterConfig.FilterID2 = (i+1 < num_ids) ? ext_ids[i+1] : 0;
//
//       HAL_StatusTypeDef ret = HAL_FDCAN_ConfigFilter(hfdcan, &sFilterConfig);
//       if (ret != HAL_OK) {
//           // Optional: print which ID failed, or handle error
//           return ret;
//       }
//   }
//   return HAL_OK;
//}




void HardwareDefinitions::MX_FDCAN1_Init(uint16_t baud)
{

    static uint8_t isInit = 0;
	/* USER CODE BEGIN CAN_Init 0 */
	if(isInit == 0)
	{
		isInit = 1;
		typedef struct 
        {
            uint32_t Baudrate;
			uint32_t N_Prescaler;
			uint32_t N_SyncJumpWidth;
			uint32_t N_TimeSeg1;
			uint32_t N_TimeSeg2;
            uint32_t D_Prescaler;
            uint32_t D_SyncJumpWidth;
            uint32_t D_TimeSeg1;
            uint32_t D_TimeSeg2;
            uint8_t  StdFilters;
            uint8_t  ExtFilters;

		} FDCAN_Baud_Parameter_t;
        // Define the baud rate parameters for FDCAN
        // Only 250 and 50Kbit are configured here for 64 MHz clock :: Todo :: Add values for more baudrates
        // Todo :: Initially Filters are also set to 0, but can be configured later
		std::array<FDCAN_Baud_Parameter_t,8> para_can =
		{{
			{1000, 2, 0, 0, 0, 0, 0, 0, 0, 0,       0}, // 1000 kbit/s
            {800, 3, 0, 0, 0, 0, 0, 0, 0, 0,        0}, // 800 kbit/s
            {500, 4, 0, 0, 0, 0, 0, 0, 0, 0,        0}, // 500 kbit/s
            {250, 2, 20, 107, 20, 8, 6, 25, 6, 0,   0}, // 250 kbit/s // Set 
            {125, 16, 0, 0, 0, 0, 0, 0, 0, 0,0}, // 125 kbit/s
            {50, 8, 21, 138, 21, 32, 16, 23, 16, 0, 0}, // 50 kbit/s  //Set
            {20, 200, 0, 0, 0, 0, 0, 0, 0, 0,0}, // 20 kbit/s
            {10, 200, 0, 0, 0, 0, 0, 0, 0, 0,0} //10 kbit/s
			
		}};


        FDCAN_Baud_Parameter_t para_can_val = para_can.at(3);//default baudrate 250

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

  	  hfdcan1.Instance = FDCAN1;
	  hfdcan1.Init.ClockDivider = FDCAN_CLOCK_DIV1;
	  hfdcan1.Init.FrameFormat = FDCAN_FRAME_CLASSIC;
	  hfdcan1.Init.Mode = FDCAN_MODE_NORMAL;
	  hfdcan1.Init.AutoRetransmission = DISABLE;
	  hfdcan1.Init.TransmitPause = DISABLE;
	  hfdcan1.Init.ProtocolException = DISABLE;
	  hfdcan1.Init.NominalPrescaler = para_can_val.N_Prescaler;
	  hfdcan1.Init.NominalSyncJumpWidth = para_can_val.N_SyncJumpWidth;
	  hfdcan1.Init.NominalTimeSeg1 = para_can_val.N_TimeSeg1;
	  hfdcan1.Init.NominalTimeSeg2 = para_can_val.N_TimeSeg2;
	  hfdcan1.Init.DataPrescaler = para_can_val.D_Prescaler;
	  hfdcan1.Init.DataSyncJumpWidth = para_can_val.D_SyncJumpWidth;
	  hfdcan1.Init.DataTimeSeg1 = para_can_val.D_TimeSeg1;
	  hfdcan1.Init.DataTimeSeg2 = para_can_val.D_TimeSeg2;
	  hfdcan1.Init.StdFiltersNbr = para_can_val.StdFilters;
	  hfdcan1.Init.ExtFiltersNbr = para_can_val.ExtFilters;
	  hfdcan1.Init.TxFifoQueueMode = FDCAN_TX_FIFO_OPERATION;
	  if (HAL_FDCAN_Init(&hfdcan1) != HAL_OK)
	  {
	    Error_Handler();
	  }
}
}



void HardwareDefinitions::MX_FDCAN2_Init(uint16_t baud)
{
	typedef struct 
	{
		uint32_t Baudrate;
		uint32_t N_Prescaler;
		uint32_t N_SyncJumpWidth;
		uint32_t N_TimeSeg1;
		uint32_t N_TimeSeg2;
		uint32_t D_Prescaler;
		uint32_t D_SyncJumpWidth;
		uint32_t D_TimeSeg1;
		uint32_t D_TimeSeg2;
		uint8_t  StdFilters;
		uint8_t  ExtFilters;
	} FDCAN_Baud_Parameter_t;

	static uint8_t isInit = 0;
	/* USER CODE BEGIN CAN_Init 0 */
	if(isInit == 0)
	{
		isInit = 1;
		// Define the baud rate parameters for FDCAN
		// Only 250 and 50Kbit are configured here for 64 MHz clock :: Todo :: Add values for more baudrates
		// Todo :: Initially Filters are also set to 0, but can be configured later
		std::array<FDCAN_Baud_Parameter_t,8> para_can =
		{{
			{1000, 2, 0, 0, 0, 0, 0, 0, 0, 0,       0}, // 1000 kbit/s
			{800, 3, 0, 0, 0, 0, 0, 0, 0, 0,        0}, // 800 kbit/s
			{500, 4, 0, 0, 0, 0, 0, 0, 0, 0,        0}, // 500 kbit/s
			{250, 2, 20, 107, 20, 8, 6, 25, 6, 0,   7}, // 250 kbit/s // Set 
			{125, 16, 0, 0, 0, 0, 0, 0, 0, 0,0}, // 125 kbit/s
			{50, 8, 21, 138, 21, 32, 16, 23, 16, 0, 7}, // 50 kbit/s  //Set
			{20, 200, 0, 0, 0, 0, 0, 0, 0, 0,0}, // 20 kbit/s
			{10, 200, 0, 0, 0, 0, 0, 0, 0, 0,0} //10 kbit/s
			
		}};


		FDCAN_Baud_Parameter_t para_can_val = para_can.at(3);//default baudrate 250

		for(uint8_t i=0; i<para_can.size(); i++)
		{
			if(baud == para_can.at(i).Baudrate)
			{
				para_can_val = para_can.at(i);
				break;
			}
		}

	  hfdcan2.Instance = FDCAN2;
	  hfdcan2.Init.ClockDivider = FDCAN_CLOCK_DIV1;
	  hfdcan2.Init.FrameFormat = FDCAN_FRAME_CLASSIC;
	  hfdcan2.Init.Mode = FDCAN_MODE_NORMAL;
	  hfdcan2.Init.AutoRetransmission = DISABLE;
	  hfdcan2.Init.TransmitPause = DISABLE;
	  hfdcan2.Init.ProtocolException = DISABLE;
	  hfdcan2.Init.NominalPrescaler = para_can_val.N_Prescaler;
	  hfdcan2.Init.NominalSyncJumpWidth = para_can_val.N_SyncJumpWidth;
	  hfdcan2.Init.NominalTimeSeg1 = para_can_val.N_TimeSeg1;
	  hfdcan2.Init.NominalTimeSeg2 = para_can_val.N_TimeSeg2;
	  hfdcan2.Init.DataPrescaler = para_can_val.D_Prescaler;
	  hfdcan2.Init.DataSyncJumpWidth = para_can_val.D_SyncJumpWidth;
	  hfdcan2.Init.DataTimeSeg1 = para_can_val.D_TimeSeg1;
	  hfdcan2.Init.DataTimeSeg2 = para_can_val.D_TimeSeg2;
	  hfdcan2.Init.StdFiltersNbr = para_can_val.StdFilters;
	  hfdcan2.Init.ExtFiltersNbr = para_can_val.ExtFilters;
	  hfdcan2.Init.TxFifoQueueMode = FDCAN_TX_FIFO_OPERATION;
	  if (HAL_FDCAN_Init(&hfdcan2) != HAL_OK)
	  {
		Error_Handler();
	  }
    }
}
