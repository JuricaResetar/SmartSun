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

#define aFactor         ((float)3.33)
#define bFactor         ((float)2.5)
#define cFactor         ((float)3.66)
#define dFactor         ((float)2.75)
#define UVADark         ((float)0.0011)
#define UVBDark         ((float)0.00125)

class veml6075
{
    public:
        veml6075(aconno_i2c *i2c) : aconnoI2C(i2c){}
        uint8_t readID(char *buffer);
        uint8_t shutDown();
        uint8_t enable();
        float getUVA();
        float getUVB();
		float getDummyData();
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
