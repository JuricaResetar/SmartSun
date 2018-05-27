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
DigitalOut led(p23);
advertisingFormat g_advertisingData;

char adresa = 0x20;

int main(){
    char buffer[4] = {1, 1, 1, 1};
    char data[3] = {0x0C, 0x00, 0x00};
    char IDReg = 0x07;
    int8_t retValue;
    I2C test (I2C_DATA, I2C_CLK);
    aconno_i2c uvSensor(&test, adresa);
    int16_t UVA = 0;
    wait_ms(500);

    g_advertisingData.header = 0x0059;
    g_advertisingData.UVAFactor = 0xAA;
    g_advertisingData.UVBFactor = 0xBB;

    BLE &ble = BLE::Instance();
    ble.init(bleInitComplete);
    ble.gap().setTxPower(TX_POWER_dB);        // Set TX power to TX_POWER
    while (ble.hasInitialized()  == false) { }
    bleT.start(callback(bleC, &ble));
    //updateAdvT.start(callback(updateDataC, &ble));


    while(1){
        //uvSensor.readFromReg(IDReg, buffer, 2);
        //test.write(adresa & 0xFE, data, 2);
        //retValue = test.read(adresa | 0x01, buffer, 2);
        //uvSensor.sendCommand(&IDReg, 1, buffer, 2, true);
        uvSensor.sendCommand(data, 1, buffer, 2, true);

        printf("Procitao: LSB: 0x%x, MSB: 0x%x\n",
                        buffer[0], buffer[1]);
        UVA = 0;
        UVA = ((uint16_t)(buffer[0]) << 8) | buffer[1];
        printf("UVA = %d\n", UVA);
        led = !led;
        wait_ms(250);
    }
}
