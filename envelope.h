/* 
 * File:   ADSR.h
 * Author: exp10der
 *
 * Created on July 23, 2017, 12:51 PM
 */

#include <stdint.h>
#include <math.h>

enum{
    ENV_MODE_LINEAR=0,
    ENV_MODE_EXPONENT        
};

enum{
    ENV_STAGE_WAIT=0,
    ENV_STAGE_ATTACK,
    ENV_STAGE_DECAY,
    ENV_STAGE_SUSTAIN,
    ENV_STAGE_RELEASE
};

enum{
    ENV_GATE_ON=0,
    ENV_GATE_OFF
};

typedef struct gen_env_state
{
    float attackRate;
    float decayRate;
    float sustainLevel;
    float releaseRate;
    float step;
    float output;
    int sampling_rate;
    int lenght;
    int mode;
    int stage;
    int gate;
} gen_env_state_t;

void envelope_init(int sampling_rate);
void envelope_set_adsr(float attack_rate,
                float decay_rate,
                float sustain_level,
                float release_rate);
float envelope_render();
void env_gate_off();
void env_gate_on();

