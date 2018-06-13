/*
* veml6075 lib
* Made by Jurica Resetar
* ResetarJurica@gmail.com
*
* All rights reserved
*
*/

#include "veml6075.h"
#include "aconno_i2c.h"
#include "veml6075_regs.h"

#define SUCCESS         (0)
#define PRINT_ON_RTT    (1)

#if PRINT_ON_RTT
    #include "SEGGER_RTT.h"
    #define printf(...) SEGGER_RTT_printf(0, __VA_ARGS__)
#else
    #define printf(...)
#endif

uint8_t veml6075::readID(char *buffer)
{
    char reg = VEML6075_ID_REG;
    char success;

    success = aconnoI2C->sendCommand(&reg, 1, buffer, 2, true);

    return success;
}

uint8_t veml6075::shutDown()
{
    char reg = VEML6075_CONF_REG;
    char success;
    uint16_t VEML6075_conf = VEML6075_CONF_DEFAULT | VEML6075_CONF_SD;

    success = aconnoI2C->writeToReg(reg, (char*)&VEML6075_conf, 2);

    return success;
}

uint8_t veml6075::enable()
{
    char reg = VEML6075_CONF_REG;
    char success;
    uint16_t VEML6075_conf = VEML6075_CONF_DEFAULT;

    success = aconnoI2C->writeToReg(reg, (char*)&VEML6075_conf, 2);

    return success;
}

uint8_t veml6075::getRawUVA(char *buffer)
{
    char reg = VEML6075_UVA_DATA_REG;
    char success;

    success = aconnoI2C->sendCommand(&reg, 1, buffer, 2, true);

    return success;
}

uint8_t veml6075::getRawUVB(char *buffer)
{
    char reg = VEML6075_UVB_DATA_REG;
    char success;

    success = aconnoI2C->sendCommand(&reg, 1, buffer, 2, true);

    return success;
}

uint8_t veml6075::getRawComp1(char *buffer)
{
    char reg = VEML6075_UVCOMP1_DATA_REG;
    char success;

    success = aconnoI2C->sendCommand(&reg, 1, buffer, 2, true);

    return success;
}

uint8_t veml6075::getRawComp2(char *buffer)
{
    char reg = VEML6075_UVCOMP2_DATA_REG;
    char success;

    success = aconnoI2C->sendCommand(&reg, 1, buffer, 2, true);

    return success;
}

float veml6075::getDummyData()
{
	char reg = VEML6075_CONF_HD;
	char success;
	char buffer[2];
	uint16_t dummy;
	float fDummy;

	success = aconnoI2C->sendCommand(&reg, 1, buffer, 2, true);

	if(success != SUCCESS)
	{
		fDummy = -1;
	}
	else
	{
		dummy = *(uint16_t*)buffer;
		fDummy = (float)dummy;
	}

	return dummy;
}

float veml6075::getUVA()
{
    uint16_t UVA;
    float fUVA;
    char buffer[2];
    uint8_t success;

    success = getRawUVA(buffer);

    if(success != SUCCESS)
    {
        fUVA = -1;
    }
    else
    {
        UVA = *(uint16_t*)buffer;
        //printf("Raw UVA: %d\n", UVA);
        fUVA = (float)UVA;
    }

    return fUVA;
}

float veml6075::getUVB()
{
    uint16_t UVB;
    float fUVB;
    char buffer[2];
    uint8_t success;

    success = getRawUVB(buffer);

    if(success != SUCCESS)
    {
        fUVB = -1;
    }
    else
    {
        UVB = *(uint16_t*)buffer;
        //printf("Raw UVB: %d\n", UVB);
        fUVB = (float)UVB;
    }

    return fUVB;
}

float veml6075::getComp1()
{
    uint16_t comp1;
    float fComp1;
    char buffer[2];
    uint8_t success;

    success = getRawComp1(buffer);

    if(success != SUCCESS)
    {
        fComp1 = -1;
    }
    else
    {
        comp1 = *(uint16_t*)buffer;
        fComp1 = (float)comp1;
    }

    return fComp1;
}

float veml6075::getComp2()
{
    uint16_t comp2;
    float fComp2;
    char buffer[2];
    uint8_t success;

    success = getRawComp2(buffer);

    if(success != SUCCESS)
    {
        fComp2 = -1;
    }
    else
    {
        comp2 = *(uint16_t*)buffer;
        fComp2 = (float)comp2;
    }

    return fComp2;
}
