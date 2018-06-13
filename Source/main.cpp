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
uint8_t flag = 0;

DigitalIn reset(p18);
DigitalOut done(p20);
//DigitalIn wake(p19);
InterruptIn wakeUp(p19);

void wakeUpHandler()
{
	printf("Probudio sam se.\n");
	flag = 1;
}

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

    Timer t;
    t.start();

    done = 1;
    wait_ms(1);
    done = 0;

	wakeUp.rise(&wakeUpHandler);

    printf("Pocinje.\n");

    while(1){

        if(flag)
        {
			flag = 0;
            t.stop();
            printf("Done signal is set.\n");
            printf("The time taken was %d seconds\n", t.read_ms()/1000);
            done = 1;
            wait_ms(1);
            done = 0;
            t.reset();
            t.start();
        }
    }
}
