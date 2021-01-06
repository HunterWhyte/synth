#include "midi.h"

// get MIDI input from UART
uint8_t readUserInput(void) {
	uint8_t readBuf[1];
	HAL_UART_Receive(&huart2, (uint8_t*)readBuf, 1, HAL_MAX_DELAY);
	return *readBuf;
}

void noteOff(uint8_t note){

	for(int i = 0; i<numVoices; i++) {
		  if(note == voices[i].note){
			  voices[i].env->state = RELEASE;
			  return;
		 }
	  }
	// should never get here
	return;
}

void noteOn(uint8_t note, uint8_t vel){

	for(int i = 0; i<numVoices; i++) {
		if(voices[i].note == 0){
			voices[i].note=note;
			voices[i].amp_scaler = ((float)velocity_LUT[vel])/128;
			voices[i].pos = 0;
			voices[i].env->state = ATTACK;

			return;
		}
	}
	voices[numVoices-1].note=note;
	voices[numVoices-1].amp_scaler = ((float)velocity_LUT[vel])/128;
	voices[numVoices-1].pos = 0;
	voices[numVoices-1].env->state = ATTACK;

	return;
}

void getMIDI(void){
	uint8_t status, note, vel;

	status = readUserInput();

	  if ((status&0b11110000) == 0b10000000){
		  note = readUserInput();
		  noteOff(note);
	  }

	  else if ((status&0b11110000) == 0b10010000){
		note = readUserInput();
		vel = readUserInput();

		if(vel == 0){
			noteOff(note);
		}
		else{
			noteOn(note,vel);
		}

	  }
}
