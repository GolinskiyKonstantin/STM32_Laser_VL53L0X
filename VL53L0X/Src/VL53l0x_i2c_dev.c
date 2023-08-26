
#include "vl53l0x_api.h"


//----------------------------------------------------------------------
VL53L0X_Error VL53L0X_WriteMulti(VL53L0X_DEV Dev, uint8_t index, uint8_t *pdata, uint32_t count)
{
	VL53L0X_Error status = VL53L0X_ERROR_NONE;
	int32_t status_int;
	
	status_int = HAL_I2C_Mem_Write( &Dev->hi2cx, Dev->I2cDevAddr, (uint16_t)index, I2C_MEMADD_SIZE_8BIT, pdata, count, 500);
	if (status_int != HAL_OK) {
        status = VL53L0X_ERROR_CONTROL_INTERFACE;
    }
	
	return status;
}
//----------------------------------------------------------------------

//----------------------------------------------------------------------
VL53L0X_Error VL53L0X_ReadMulti(VL53L0X_DEV Dev, uint8_t index, uint8_t *pdata, uint32_t count)
{
	VL53L0X_Error status = VL53L0X_ERROR_NONE;
	int32_t status_int;
	
	status_int = HAL_I2C_Mem_Read( &Dev->hi2cx, Dev->I2cDevAddr, (uint16_t)index, I2C_MEMADD_SIZE_8BIT, pdata, count, 500);
	if (status_int != HAL_OK) {
        status = VL53L0X_ERROR_CONTROL_INTERFACE;
    }
	
	return status;
}
//----------------------------------------------------------------------

//----------------------------------------------------------------------
VL53L0X_Error VL53L0X_WrByte(VL53L0X_DEV Dev, uint8_t index, uint8_t data)
{
	VL53L0X_Error status = VL53L0X_ERROR_NONE;
	int32_t status_int;
	
	status_int = HAL_I2C_Mem_Write( &Dev->hi2cx, Dev->I2cDevAddr, (uint16_t)index, I2C_MEMADD_SIZE_8BIT, &data, 1, 500);
	if (status_int != HAL_OK) {
        status = VL53L0X_ERROR_CONTROL_INTERFACE;
    }
	
	return status;
}
//----------------------------------------------------------------------

//----------------------------------------------------------------------
VL53L0X_Error VL53L0X_RdByte(VL53L0X_DEV Dev, uint8_t index, uint8_t *data)
{
	VL53L0X_Error status = VL53L0X_ERROR_NONE;
	int32_t status_int;
	
	status_int = HAL_I2C_Mem_Read( &Dev->hi2cx, Dev->I2cDevAddr, (uint16_t)index, I2C_MEMADD_SIZE_8BIT, data, 1, 500);
	if (status_int != HAL_OK) {
        status = VL53L0X_ERROR_CONTROL_INTERFACE;
    }
	
	return status;
}
//----------------------------------------------------------------------

//----------------------------------------------------------------------
VL53L0X_Error VL53L0X_WrWord(VL53L0X_DEV Dev, uint8_t index, uint16_t data)
{
	uint8_t tmp[2]={	((uint16_t)(data&0xff00)>>8) ,	((uint16_t)data&0x00ff)	};
	VL53L0X_Error status = VL53L0X_ERROR_NONE;
	int32_t status_int;
	
	status_int = HAL_I2C_Mem_Write( &Dev->hi2cx, Dev->I2cDevAddr, (uint16_t)index, I2C_MEMADD_SIZE_8BIT, tmp, 2, 500);
	if (status_int != HAL_OK) {
        status = VL53L0X_ERROR_CONTROL_INTERFACE;
    }
	
	return status;
}
//----------------------------------------------------------------------

//----------------------------------------------------------------------
VL53L0X_Error VL53L0X_WrDWord(VL53L0X_DEV Dev, uint8_t index, uint32_t data)
{
	uint8_t tmp[4]={	((data&0xff000000)>>24),((data&0x00ff0000)>>16),((data&0x0000ff00)>>8),((data&0x000000ff))};
	VL53L0X_Error status = VL53L0X_ERROR_NONE;
	int32_t status_int;
	
	status_int = HAL_I2C_Mem_Write( &Dev->hi2cx, Dev->I2cDevAddr, (uint16_t)index, I2C_MEMADD_SIZE_8BIT, tmp, 4, 500);
	if (status_int != HAL_OK) {
        status = VL53L0X_ERROR_CONTROL_INTERFACE;
    }
	
	return status;
}
//----------------------------------------------------------------------

//----------------------------------------------------------------------
VL53L0X_Error VL53L0X_RdWord(VL53L0X_DEV Dev, uint8_t index, uint16_t *data)
{
	uint8_t tmp[2];
	uint8_t* p=(uint8_t*)data;
	VL53L0X_Error status = VL53L0X_ERROR_NONE;
	int32_t status_int;
	
	status_int = HAL_I2C_Mem_Read( &Dev->hi2cx, Dev->I2cDevAddr, (uint16_t)index, I2C_MEMADD_SIZE_8BIT, tmp, 2, 500);
	if (status_int != HAL_OK) {
        status = VL53L0X_ERROR_CONTROL_INTERFACE;
    }
	else{
		p[0]=tmp[1];
		p[1]=tmp[0];
	}
	
	return status;
}
//----------------------------------------------------------------------

//----------------------------------------------------------------------
VL53L0X_Error VL53L0X_RdDWord(VL53L0X_DEV Dev, uint8_t index, uint32_t *data)
{
	uint8_t tmp[4];
	uint8_t* p=(uint8_t*)data;
	VL53L0X_Error status = VL53L0X_ERROR_NONE;
	int32_t status_int;
	
	status_int = HAL_I2C_Mem_Read( &Dev->hi2cx, Dev->I2cDevAddr, (uint16_t)index, I2C_MEMADD_SIZE_8BIT, tmp, 4, 500);
	if (status_int != HAL_OK) {
        status = VL53L0X_ERROR_CONTROL_INTERFACE;
    }
	else{
		p[0]=tmp[3];
		p[1]=tmp[2];
		p[2]=tmp[1];
		p[3]=tmp[0];
	}
	
	return status;
}
//----------------------------------------------------------------------

//----------------------------------------------------------------------
VL53L0X_Error VL53L0X_UpdateByte(VL53L0X_DEV Dev, uint8_t index, uint8_t AndData, uint8_t OrData)
{
	uint8_t tmp;
	VL53L0X_Error status = VL53L0X_ERROR_NONE;
	int32_t status_int;
	
	status_int = HAL_I2C_Mem_Read( &Dev->hi2cx, Dev->I2cDevAddr, (uint16_t)index, I2C_MEMADD_SIZE_8BIT, &tmp, 1, 500);
	tmp=(tmp & AndData) | OrData;
	
	if( status_int == HAL_OK){
		status_int = HAL_I2C_Mem_Write( &Dev->hi2cx, Dev->I2cDevAddr, (uint16_t)index, I2C_MEMADD_SIZE_8BIT, &tmp, 1, 500);
	}
	
	if (status_int != HAL_OK) {
        status = VL53L0X_ERROR_CONTROL_INTERFACE;
    }
	
	return status;
}
//----------------------------------------------------------------------

//----------------------------------------------------------------------
VL53L0X_Error VL53L0X_PollingDelay(VL53L0X_DEV Dev)
{
	VL53L0X_Error status = VL53L0X_ERROR_NONE;
	
	DELAY_FUNC(5);
	return status;
}
//----------------------------------------------------------------------   

