/*
* Made by Jurica Resetar
* All rights reserved
*
*/

#include "SSBle.h"
#include "ble/BLE.h"
#include "GapAdvertisingData.h"
#include "SSConfig.h"
#include "data.h"

#if PRINT_ON_RTT
    #include "SEGGER_RTT.h"
    #define printf(...) SEGGER_RTT_printf(0, __VA_ARGS__)
#else
    #define printf(...)
#endif

extern advertisingFormat g_advertisingData;
GapAdvertisingData advData = GapAdvertisingData();

union{
    float f;
    unsigned char byte[4];
}UVAIndex;

union{
    float f;
    unsigned char byte[4];
}UVBIndex;

void onBleInitError(BLE &ble, ble_error_t error){
    /* Avoid compiler warnings */
    (void) ble;
    (void) error;
    printf("Ble init error.\n");
}

void updateGAPData(BLE *ble)
{
    static uint8_t flag = 0;
    static uint8_t nekaj = 0;

    if(!nekaj)
        UVAIndex.f += 0.1;
    else
        UVAIndex.f -= 0.1;

    if(UVAIndex.f > 8)
        nekaj = 1;
    //UVBIndex.f += 0.2;
    int i;

    for(i=0; i<4; i++)
    {
        *(g_advertisingData.UVAFactor + i) = *((char*)&UVAIndex + 4 - i - 1);
    }

    /*
    for(i=0; i<4; i++)
    {
        *(g_advertisingData.UVBFactor + i) = *((char*)&UVBIndex + 4 - i -1);
    }
    */
    flag = !flag;
    g_advertisingData.flag = flag;

    advData = ble->getAdvertisingData();
    advData.updateData(advData.MANUFACTURER_SPECIFIC_DATA,
        (uint8_t *)&g_advertisingData, sizeof(advertisingFormat));
    ble->setAdvertisingData(advData);

}

void bleInitComplete(BLE::InitializationCompleteCallbackContext *params){
    BLE &ble = params->ble;
    const char completeLocalName[NAME_SIZE_B] = "Smart sun";

    /* setup advertising */
    ble.gap().accumulateAdvertisingPayload(
        GapAdvertisingData::MANUFACTURER_SPECIFIC_DATA,
        (uint8_t *)&g_advertisingData, sizeof(advertisingFormat));
    ble.gap().accumulateAdvertisingPayload(
        GapAdvertisingData::COMPLETE_LOCAL_NAME,
        (uint8_t*)completeLocalName, NAME_SIZE_B);
    ble.gap().setAdvertisingInterval(ADV_INTERVAL_MS);
    ble.gap().startAdvertising();
}

void onConnectionCallback(const Gap::ConnectionCallbackParams_t *params){
    printf("Device is connected.\n");
}

void disconnectionCallback(const Gap::DisconnectionCallbackParams_t *params){
    printf("Device is disconnected.\n");
    BLE::Instance().gap().startAdvertising();
}
