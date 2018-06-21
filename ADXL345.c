
#include "ADXL345.h"
//#include "stm32f1xx_hal_spi.h"
#include "stm32f1xx_hal.h"

#define CE_RESET HAL_GPIO_WritePin(SPI2_CE_GPIO_Port, SPI2_CE_Pin, 0)
#define CE_SET HAL_GPIO_WritePin(SPI2_CE_GPIO_Port, SPI2_CE_Pin, 1)

float sensitive; 

void adxl345_Init(SPI_HandleTypeDef hspi, uint8_t set_Range )
{
	read_From_Adxl345(hspi, DEVICEID);
	write_To_Adxl345(hspi, POWER_CTL, POWER_CTL_SET_VALUE);
	write_To_Adxl345(hspi, DATA_FORMAT, DATA_FORMAT_SETVALUE | set_Range);
	write_To_Adxl345(hspi, BW_RATE, BW_RATE_SET_VALUE);
	switch(set_Range)
	{
		case 0:
		{
			sensitive = SENSITIVE_2G;
			break;
		}
		case 1:
		{
			sensitive = SENSITIVE_4G;
			break;
		}
		case 2:
		{
			sensitive = SENSITIVE_8G;
			break;
		}
		case 3: 
		{
			sensitive = SENSITIVE_16G;
			break;
		}
		default:
		{
			sensitive = WRONG_SENS;
			break;
		}
	}
}


int read_From_Adxl345(SPI_HandleTypeDef hspi, uint8_t reg)
{
	uint8_t receive_Data = 0;
	reg |= READ_MASK;
	CE_RESET;
	HAL_SPI_Transmit(&hspi, &reg, 1, 100);
	HAL_SPI_Receive(&hspi, &receive_Data, 1, 100);
	CE_SET;
	return receive_Data;
}


void write_To_Adxl345(SPI_HandleTypeDef hspi, uint8_t reg, uint8_t data)
{
	CE_RESET;
	HAL_SPI_Transmit(&hspi, &reg, 1, 100);
	HAL_SPI_Transmit(&hspi, &data, 1, 100);
	CE_SET;
}


float read_Axis_From_Adxl345(SPI_HandleTypeDef hspi, int axis_Select)
{
	int16_t ret_value = 0;
	switch(axis_Select)
	{
		case 0:
			{
				ret_value = read_From_Adxl345(hspi, DATAX0);
				ret_value |= read_From_Adxl345(hspi, DATAX1) << 8;
				break;
			}
		case 1:
			{
				ret_value = read_From_Adxl345(hspi, DATAY0);
				ret_value |= read_From_Adxl345(hspi, DATAY1) << 8;
				break;
			}
		case 2:
			{
				ret_value = read_From_Adxl345(hspi, DATAZ0);
				ret_value |= read_From_Adxl345(hspi, DATAZ1) << 8;
				break;
			}
		default:
			{
				ret_value = AXIS_SELECTION_ERROR;
				break;
			}
	}
	return ret_value * sensitive;
}