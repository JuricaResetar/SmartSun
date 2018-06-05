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

#define aFactor         ((float)2.22)
#define bFactor         ((float)1.33)
#define cFactor         ((float)2.95)
#define dFactor         ((float)1.74)
#define UVADark         ((float)0.001461)
#define UVBDark         ((float)0.002591)

class veml6075
{
    public:
        veml6075(aconno_i2c *i2c) : aconnoI2C(i2c){}
        uint8_t readID(char *buffer);
        uint8_t shutDown();
        uint8_t enable();
        float getUVA();
        float getUVB();
        float getComp1();
        float getComp2();
    private:
        uint8_t getRawUVA(char *buffer);
        uint8_t getRawUVB(char *buffer);
        uint8_t getRawComp1(char *buffer);
        uint8_t getRawComp2(char *buffer);
        aconno_i2c *aconnoI2C;

};

#endif //__VEML6075_H__
