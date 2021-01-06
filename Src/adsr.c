//  adsr.c
//
//  Modified from code Originally Created by Nigel Redmon on 12/18/12.
//  EarLevel Engineering: earlevel.com
//  Copyright 2012 Nigel Redmon
//  C Port 2013 Francesco D'Este

//
//  For a complete explanation of the ADSR envelope generator and code,
//  read the series of articles by the author, starting here:
//  http://www.earlevel.com/main/2013/06/01/envelope-generators/
//
//  License:
//
//  This source code is provided as is, without warranty.
//  You may copy and distribute verbatim copies of this document.
//  You may modify and use this source code to create binary code for your own purposes, free or commercial.
//


#include "adsr.h"
float calculateADSR(ADSR* env){
	switch (env->state) {
	        case IDLE:
	            break;
	        case ATTACK:
	        	env->output = env->output + env->attackRate;
	            if (env->output >= 0xFF00) {
	            	//env->output = 1.0;
	            	env->state = DECAY;
	            }
	            break;
	        case DECAY:
	        	env->output = env->output - env->decayRate;
	            if (env->output <= env->sustainLevel) {
	            	//env->output = env->sustainLevel;
	            	env->state = SUSTAIN;
	            }
	            break;
	        case SUSTAIN:
	            break;
	        case RELEASE:
	        	env->output = env->output - env->releaseRate;
	            if (env->output <= 0x0100) {
	            	env->output = 0;
	            	env->state = IDLE;
	            }
		}
		return (float)env->output/65280.0;
}

/*
float processADSR(ADSR* env){
	switch (env->state) {
	        case IDLE:
	            break;
	        case ATTACK:
	        	env->output = env->attackBase + env->output * env->attackCoef;
	            if (env->output >= 1.0) {
	            	env->output = 1.0;
	            	env->state = DECAY;
	            }
	            break;
	        case DECAY:
	        	env->output = env->decayBase + env->output * env->decayCoef;
	            if (env->output <= env->sustainLevel) {
	            	env->output = env->sustainLevel;
	            	env->state = SUSTAIN;
	            }
	            break;
	        case SUSTAIN:
	            break;
	        case RELEASE:
	        	env->output = env->releaseBase + env->output * env->releaseCoef;
	            if (env->output <= 0.0) {
	            	env->output = 0.0;
	            	env->state = IDLE;
	            }
		}
		return env->output;
}


void reset(ADSR* env) {
    env->state = IDLE;
    env->output = 0.0;
}

void setAttackRate(ADSR* env, float rate) {
    env->attackRate = rate;
    env->attackCoef = calcCoef(rate, env->targetRatioA);
    env->attackBase = (1.0 + env->targetRatioA) * (1.0 - env->attackCoef);
}

void setDecayRate(ADSR* env,float rate) {
    env->decayRate = rate;
    env->decayCoef = calcCoef(rate, env->targetRatioDR);
    env->decayBase = (env->sustainLevel - env->targetRatioDR) * (1.0 - env->decayCoef);
}

void setReleaseRate(ADSR* env, float rate) {
    env->releaseRate = rate;
    env->releaseCoef = calcCoef(rate, env->targetRatioDR);
    env->releaseBase = -env->targetRatioDR * (1.0 - env->releaseCoef);
}

float calcCoef(float rate, float targetRatio) {
    return exp(-log((1.0 + targetRatio) / targetRatio) / rate);
}

void setSustainLevel(ADSR* env, float level) {
    env->sustainLevel = level;
    env->decayBase = (env->sustainLevel - env->targetRatioDR) * (1.0 - env->decayCoef);
}

void setTargetRatioA(ADSR* env, float targetRatio) {
    if (targetRatio < 0.000000001)
        targetRatio = 0.000000001;  // -180 dB
    env->targetRatioA = targetRatio;
    env->attackBase = (1.0 + env->targetRatioA) * (1.0 - env->attackCoef);
}

void setTargetRatioDR(ADSR* env, float targetRatio) {
    if (targetRatio < 0.000000001)
        targetRatio = 0.000000001;  // -180 dB
    env->targetRatioDR = targetRatio;
    env->decayBase = (env->sustainLevel - env->targetRatioDR) * (1.0 - env->decayCoef);
    env->releaseBase = -env->targetRatioDR * (1.0 - env->releaseCoef);
}
*/
