/*
HEADER
*/

#ifndef ADXL345
#define ADXL345

#include "stm32f1xx_hal.h"

// Register Adress
#define DEVICEID		 			0X00
#define	THRESH_TAP 	 			0X1D
#define	OFSX							0X1E
#define	OFSY							0X1F
#define	OFSZ							0X20
#define	DUR								0X21
#define	Latent 						0X22
#define	Window						0X23
#define	THRESH_ACT				0X24
#define	THRESH_INACT			0X25
#define	TIME_INACT				0X26
#define	ACT_IANCT_CTL			0X27
#define	THRESH_FF					0X28
#define TIME_FF						0X29
#define	TAP_AXES					0X2A
#define	ACT_TAP_STATUS		0X2B
#define	BW_RATE						0X2C
#define	POWER_CTL					0X2D
#define	INT_ENABLE				0X2E
#define	INT_MAP						0X2F
#define	INT_SOURCE				0X30
#define	DATA_FORMAT				0X31
#define	DATAX0						0X32
#define	DATAX1						0X33
#define	DATAY0						0X34
#define	DATAY1						0X35
#define	DATAZ0						0X36
#define	DATAZ1						0X37
#define	FIFO_CTL 					0X38
#define	FIFO_STATUS_adxl	0X39

//Register value for initialization
#define DEVICEID_DEFAULT_VALUE		0X5F
#define POWER_CTL_SET_VALUE				0X08
#define DATA_FORMAT_SETVALUE			0X04
#define BW_RATE_SET_VALUE					0X0A

//Range setting for adxl
#define RANGE_2G 					0X00
#define RANGE_4G					0X01
#define RANGE_8G					0X02
#define RANGE_16G					0X03

//Sensitive for the selected range
#define SENSITIVE_2G 			0.0039
#define SENSITIVE_4G 			0.0078
#define SENSITIVE_8G 			0.0159
#define SENSITIVE_16G 		0.0312
#define WRONG_SENS				-1.0

//Which axis to read
#define READ_MASK 							0X80
#define X_AXIS 									0
#define Y_AXIS 									1
#define Z_AXIS 									2
#define AXIS_SELECTION_ERROR 		-1



//funkcja inicjalizujaca
void adxl345_Init(SPI_HandleTypeDef hspi, uint8_t set_Range );

//odczyt z rejestru adxl
int read_From_Adxl345(SPI_HandleTypeDef hspi, uint8_t reg);

//zapis do rejestru adxl
void write_To_Adxl345(SPI_HandleTypeDef hspi, uint8_t reg, uint8_t data);

//odczyt przyspieszenie z osi
float read_Axis_From_Adxl345(SPI_HandleTypeDef hspi, int axis_Select);


#endif
