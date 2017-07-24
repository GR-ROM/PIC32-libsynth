/* 
 * File:   main.c
 * Author: exp10der
 *
 * Created on July 23, 2017, 12:50 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include "envelope.h"

/*
 * 
 */


main() 
{
    float buf[48000];
    int i;
    envelope_init(48);
    envelope_set_adsr(0.5f, 0.2f, 0.5f, 0.2f);
    env_gate_on();
    for(;;)
    {
       buf[i++]=envelope_render();
       if (i==50)
       {
           env_gate_off();
       }
       if (i==100)
       {
           i=0;
       }
    }
}

