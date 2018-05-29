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
    char reg = IDReg;
    char success;

    success = aconnoI2C->sendCommand(&reg, 1, buffer, 2, true);

    return success;
}
