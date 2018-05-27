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

void onBleInitError(BLE &ble, ble_error_t error){
    /* Avoid compiler warnings */
    (void) ble;
    (void) error;
    printf("Ble init error.\n");
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
