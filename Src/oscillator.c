/*
 * oscillator.c
 *
 *  Created on: Dec. 4, 2020
 *      Author: hunter
 */
#include "oscillator.h"

float dutyCycle = 0.5; //square wave osc duty cycle

osc updateOsc(osc o, unsigned char wave, uint16_t pitchMod, uint16_t ampMod){
    if(o.env->state != IDLE){
	//if(o.note){
        o.pos = o.pos + o.jump + pitchMod;

        if (wave == 0){
            o.amp = (sin_LUT[(o.pos>>18)]);// sin wave
        	//o.amp = (sin_LUT_big[(o.pos>>20)]);// sin wave
        	/*
        	uint32_t x0;
			uint64_t y;

        	x0 = o.pos>>24;
        	uint16_t y0 = sin_LUT[x0];
        	uint16_t y1 = sin_LUT[x0 + 1];
			if(y1>y0){
				y = (uint64_t) ((o.pos&0x00FFFFFF)*(y1-y0));
				o.amp = y0 + (uint16_t) (y>>24);
			}
			else{
				y = (uint64_t) ((o.pos&0x00FFFFFF)*(y0-y1));
				o.amp = y0 - (uint16_t) (y>>24);
			}*/
            o.amp = (o.amp>>1) + (o.pos>>21); // sawtooth wave

        }
        else if (wave == 1){
            o.amp = 0xFFFF*((o.pos)>=(32767)); // square wave
        }
        else if (wave == 2){
            o.amp = (o.pos); // sawtooth wave
        }

        float ADSRscaler  = calculateADSR(o.env);
        o.amp = (int)(((o.amp + ampMod)*o.amp_scaler)*ADSRscaler);


    }
    else{
    	o.amp = 0x00;
		o.jump = 0;
		o.note = 0;
    }

    return o;
}
