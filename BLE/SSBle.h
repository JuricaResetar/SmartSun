/*
* Made by Jurica Resetar
* All rights reserved
*
*/

#ifndef __SSBLE_H__
#define __SSBLE_H__

#include "mbed.h"
#include "ble/BLE.h"
#include "GapAdvertisingData.h"

/**
 * Ble init error callback
 * @param ble   referance to BLE object
 * @param error Error code
 */
void onBleInitError(BLE &ble, ble_error_t error);

/**
 * ble init complete callback
 * @param params
 */
void bleInitComplete(BLE::InitializationCompleteCallbackContext *params);

void updateGAPData(BLE *ble, float data);

#endif // __SSBLE_H__
