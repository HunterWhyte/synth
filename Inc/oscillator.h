/*
 * oscillator.h
 *
 *  Created on: Dec. 4, 2020
 *      Author: hunter
 */
#ifndef OSCILLATOR_H_
#define OSCILLATOR_H_

#include <stdint.h>
#include "tables.h"
#include "adsr.h"



typedef struct Oscillator
{
	uint32_t jump;
	uint32_t pos;
    uint16_t amp;
    uint8_t note;
    float amp_scaler;
    ADSR* env;
} osc;



osc updateOsc(osc o, unsigned char wave, uint16_t pitchMod, uint16_t ampMod);


#endif /* OSCILLATOR_H_ */
