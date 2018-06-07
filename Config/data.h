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
    __attribute__((packed, aligned(1))) uint16_t header; // 0- 1
    __attribute__((packed, aligned(1))) uint8_t UVAFactor[4];   // 2 - 5
    //__attribute__((packed, aligned(1))) uint8_t UVBFactor[4];   // 6 - 9
    uint8_t flag;
}advertisingFormat;

#endif //__DATA_H__
