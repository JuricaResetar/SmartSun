/**
*
* SmartSun project
* Jurica Resetar
* ResetarJurica@gmail.com
*
*/

#include "mbed.h"
#include "bsp.h"
#include "SSConfig.h"
#include "aconno_i2c.h"
#include "ble/BLE.h"
#include "GapAdvertisingData.h"
#include "data.h"
#include "SSBle.h"
#include "tasks.h"
#include "veml6075.h"

#if PRINT_ON_RTT
    #include "SEGGER_RTT.h"
    #define printf(...) SEGGER_RTT_printf(0, __VA_ARGS__)
#else
    #define printf(...)
#endif

Thread bleT;
advertisingFormat g_advertisingData;

DigitalOut pullUps(p17);

DigitalOut red(p3);
DigitalOut green(p4);
DigitalOut blue(p5);

union{
    float f;
    unsigned char byte[4];
}UVAIndex;

union{
    float f;
    unsigned char byte[4];
}UVBIndex;

char adresa = 0x20;

int main(){
    char buffer[4] = {1, 1, 1, 1};
    char data[3] = {0x0C, 0x00, 0x00};
    char IDReg = 0x0C;
    int8_t retValue;

    red = 1;
    green = 1;
    blue = 1;

    pullUps = 1;
    wait_ms(100);

    red = 0;
    wait_ms(250);
    red = 1;
    green = 0;
    wait_ms(250);
    green = 1;
    blue = 0;
    wait_ms(250);
    blue = 1;

    I2C test (I2C_DATA, I2C_CLK);
    aconno_i2c uvSensorI2C(&test, adresa);
    veml6075 uvSensor(&uvSensorI2C);


    int i;
    wait_ms(500);

    UVAIndex.f = 1.0;
    UVBIndex.f = 4.0;

    g_advertisingData.header = 0x0059;
    for(i=0; i<4; i++)
    {
        *(g_advertisingData.UVAFactor + i) = *((char*)&UVAIndex + 4 - i - 1);
    }

    for(i=0; i<4; i++)
    {
        *(g_advertisingData.UVBFactor + i) = *((char*)&UVBIndex + 4 - i -1);
    }
    //g_advertisingData.UVAFactor = 0xAA;
    //g_advertisingData.UVBFactor = 0xBB;
    //memcpy(g_advertisingData.UVBFactor, (char*)&UVBIndex, 4);

    BLE &ble = BLE::Instance();
    ble.init(bleInitComplete);
    ble.gap().setTxPower(TX_POWER_dB);        // Set TX power to TX_POWER
    while (ble.hasInitialized()  == false) { }
    bleT.start(callback(bleC, &ble));
    //updateAdvT.start(callback(updateDataC, &ble));

    uvSensor.enable();
    wait_ms(100);

    char floatek[25] = "Bok bok";

    float fUVA;
    float fUVB;
    float fVisibleFactor;
    float fIRFactor;

    while(1){



        fVisibleFactor = uvSensor.getComp1();
        fIRFactor = uvSensor.getComp2();

        sprintf(floatek, "\nfVisibleFactor: %2.5f\n", fVisibleFactor);
        printf("%s", floatek);

        sprintf(floatek, "fIRFactor: %2.5f\n", fIRFactor);
        printf("%s", floatek);

        fUVA = uvSensor.getUVA();
        fUVA = (fUVA) - aFactor*(fVisibleFactor)
                - bFactor*(fIRFactor);
        //fUVA *= UVADark;

        sprintf(floatek, "UVA: %2.5f\n", fUVA);
        printf("%s", floatek);

        fUVB = uvSensor.getUVB();
        fUVB = (fUVB) - cFactor*(fVisibleFactor)
                - dFactor*(fIRFactor);
        //fUVB *= UVBDark;

        sprintf(floatek, "UVB: %2.5f\n", fUVB);
        printf("%s", floatek);

        float UVIndex = ( fUVA + fUVB ) / 2.0;

        sprintf(floatek, "UVIndex: %2.5f\n", UVIndex);
        printf("%s\n", floatek);

        wait_ms(250);

    }
}
