#ifndef ADSR_H_
#define ADSR_H_

#include <stdint.h>
#include <math.h>

// envelope state macros
#define IDLE 0
#define ATTACK 1
#define DECAY 2
#define SUSTAIN 3
#define RELEASE 4
typedef struct
{
    uint8_t state;
	uint16_t output;
	uint8_t attackRate;
	uint8_t decayRate;
	uint8_t releaseRate;
	uint16_t sustainLevel;


} ADSR;

float calculateADSR(ADSR* env);

/*
typedef struct
{
    uint8_t state;
	double output;
	double attackRate;
	double decayRate;
	double releaseRate;
	double attackCoef;
	double decayCoef;
	double releaseCoef;
	double sustainLevel;
    double targetRatioA;
    double targetRatioDR;
    double attackBase;
    double decayBase;
    double releaseBase;

} ADSR;

void setAttackRate(ADSR* env, float rate);
void setDecayRate(ADSR* env, float rate);
void setReleaseRate(ADSR* env, float rate);
void setSustainLevel(ADSR* env, float level);
void setTargetRatioA(ADSR* env, float targetRatio);
void setTargetRatioDR(ADSR* env, float targetRatio);
void reset(ADSR* env);
float calcCoef(float rate, float targetRatio);

*/

#endif /* ADSR_H_ */
