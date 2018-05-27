/**
 * Made by Jurica Resetar
 * ResetarJurica@gmail.com
 *
 * Data formats definitions file
 *
 * All rights reserved.
 */

#ifndef __DATA_H__
#define __DATA_H__

#define DEVICE_NAME   ("Smart sun")
#define NAME_SIZE_B   (10)

typedef struct __attribute__((packed, aligned(1))) advertisingFormat_t
{
    uint16_t header;
    uint8_t UVAFactor;
    uint8_t UVBFactor;
}advertisingFormat;

#endif //__DATA_H__
