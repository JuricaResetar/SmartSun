/*
* veml6075 lib
* Made by Jurica Resetar
* ResetarJurica@gmail.com
*
* All rights reserved
*
*/


#ifndef __VEML6075_H__
#define __VEML6075_H__

#include "mbed.h"
#include "aconno_i2c.h"

class veml6075
{
    public:
        veml6075(aconno_i2c *i2c) : aconnoI2C(i2c){}
        uint8_t readID(char *buffer);
    private:
        aconno_i2c *aconnoI2C;

};

#endif //__VEML6075_H__
