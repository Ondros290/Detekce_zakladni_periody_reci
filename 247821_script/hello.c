/*
 *  Copyright 2010 by Texas Instruments Incorporated.
 *  All rights reserved. Property of Texas Instruments Incorporated.
 *  Restricted rights to use, duplicate or disclose this code are
 *  granted through contract.
 *
 */
/***************************************************************************/
/*                                                                         */
/*     H E L L O . C                                                       */
/*                                                                         */
/*     Basic LOG event operation from main.                                */
/*                                                                         */
/***************************************************************************/

#include <std.h>

#include <log.h>
#include <sts.h>
#include <clk.h>

#include <stdlib.h>
#include <math.h>
#include <stdio.h>

#include <dsk6416.h>
#include <dsk6416_led.h>
#include <dsk6416_dip.h>



#include "hellocfg.h"


#include "dsp.h"

#include "inputData.h"

static Int16 output[SEGMENT_LENGTH] = {0};

/**
    @brief find the fundamental frequency of the signal dividing the signal into 
            segments and computing autocorrelation for each segment
            print the results (frequency estimations for each segment)
 */
void tskProcess( void)
{
	initHammingWin();

	int k;
    printf( "[");

    for (k = 0; k < NUMBER_OF_SEGMENTS; k++)
    {
        removeDC(&audioData[k * SHIFT], &output[0]);

        applyHammingWin(&output[0]);

        autoCorrelation(&output[0]);

        printf( "%d ", output[0]);
    }

    printf( "]");
    printf("\n");
    printf("FINISHED");

	while( 1)
	{
	}

}


void tskStat( void)
{
    while( 1){
#ifdef SIMULATOR
        TSK_sleep(100);
#else
        TSK_sleep(10000);
#endif
        printf( "Narocnost levy/pravy %d/%d\n", STS_left.acc / STS_left.num, STS_right.acc / STS_right.num);
        fflush(stdout);
    }
}


void tskCheck( Arg par)
{
	static int last[2];

	while( 1){
		last[par] = !DSK6416_DIP_get(par);
		if( last[par]){
			DSK6416_LED_on(par);
		} else
			DSK6416_LED_off(par);


#ifdef SIMULATOR
       IRQ_set( IRQ_EVT_RINT2);
       IRQ_set( IRQ_EVT_XINT2);
#endif

		while( last[par] == !DSK6416_DIP_get(par))
			TSK_sleep(1000);
	}
}

void idlLive( void){
	static int count = 0;

	if( 500000 > ++count)
		return;

	DSK6416_LED_toggle(3);
	count = 0;
}

/*
 *  ======== main ========
 */
Void main()
{
   int ver;

    LOG_printf(&trace, "hello world!");

	CSL_init();
	DSK6416_init();
	DSK6416_DIP_init();
	DSK6416_LED_init();

    ver = DSK6416_getVersion();
    if( 1 == ver){
        printf( "Spu�t�no v simul�toru.\n");
#ifndef SIMULATOR
        printf( "V simul�toru nen� audio kodek a proto verze pro kit nebude fungovat.\n");
        exit(-1);
#endif
    } else {
        printf( "Spu�t�no v kitu verze %d.\n", ver);
#ifdef SIMULATOR
        printf( "Verzi pro simul�tor nelze spou�t�t na kitu.\n");
        exit( -1);
#endif
    }


    /* fall into DSP/BIOS idle loop */
    return;
}
