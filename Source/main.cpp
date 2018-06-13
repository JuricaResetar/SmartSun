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
uint8_t UUID[16] = {0xe, 0x31, 0x93, 0x09, 0x06, 0xaa, 0xc1, 0x1e};
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
    aconno_i2c uvSensor(&test, adresa);
    int16_t UVA = 0;
    int i;
    wait_ms(500);

    UVAIndex.f = 6.0;

    g_advertisingData.header = 0x0059;
    for(i=0; i<4; i++)
    {
        *(g_advertisingData.UVAFactor + i) = *((char*)&UVAIndex + 4 - i - 1);
    }

    for(i=0; i<8; i++)
    {
        *(g_advertisingData.UUID + i) = *((char*)UUID + 4 - i -1);
    }

    g_advertisingData.flag = 0;

    BLE &ble = BLE::Instance();
    ble.init(bleInitComplete);
    ble.gap().setTxPower(TX_POWER_dB);        // Set TX power to TX_POWER
    while (ble.hasInitialized()  == false) { }
    bleT.start(callback(bleC, &ble));
    //updateAdvT.start(callback(updateDataC, &ble));

    while(1)
	{
        updateGAPData(&ble);
        wait_ms(1000);
    }
}
