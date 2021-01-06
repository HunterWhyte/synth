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
		o.jump = (MIDI_LUT[o.note]);

        o.pos = o.pos + o.jump + pitchMod;
        //o.amp = (sin_LUT[(o.pos>>4)]);// sin wave

        if (wave == 0){
            o.amp = (sin_LUT[(o.pos>>2)]);// sin wave
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
