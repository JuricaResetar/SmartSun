/**
 * Made by Jurica Resetar
 * ResetarJurica@gmail.com
 *
 * Tasks definitions file
 *
 * All right reserved
 *
 */

#include "mbed.h"
#include "tasks.h"
#include "ble/BLE.h"

void bleC(BLE *ble)
{
    while(1)
    {
        ble->waitForEvent();
    }
}
