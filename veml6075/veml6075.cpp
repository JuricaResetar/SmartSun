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

uint8_t veml6075::getUVA(char *buffer)
{
    char reg = VEML6075_UVA_DATA_REG;
    char success;

    success = aconnoI2C->sendCommand(&reg, 1, buffer, 2, true);

    return success;
}

uint8_t veml6075::getUVB(char *buffer)
{
    char reg = VEML6075_UVB_DATA_REG;
    char success;

    success = aconnoI2C->sendCommand(&reg, 1, buffer, 2, true);

    return success;
}

uint8_t veml6075::getComp1(char *buffer)
{
    char reg = VEML6075_UVCOMP1_DATA_REG;
    char success;

    success = aconnoI2C->sendCommand(&reg, 1, buffer, 2, true);

    return success;
}

uint8_t veml6075::getComp2(char *buffer)
{
    char reg = VEML6075_UVCOMP2_DATA_REG;
    char success;

    success = aconnoI2C->sendCommand(&reg, 1, buffer, 2, true);

    return success;
}
