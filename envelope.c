#include "envelope.h"

// DX7 like envelope linear implementation
// to do: add exponent envelope

 static gen_env_state_t env_state;

void envelope_init(int sampling_rate)
{
    env_state.attackRate=0.0f;
    env_state.decayRate=0.0f;
    env_state.sustainLevel=0.0f;
    env_state.releaseRate=0.0f;
    env_state.output=0.0f;
    env_state.sampling_rate=sampling_rate;
    env_state.gate=ENV_GATE_OFF;
    env_state.stage=ENV_STAGE_WAIT;
    env_state.mode=ENV_MODE_LINEAR;
    env_state.step=1/sampling_rate;
}

void envelope_set_adsr(float attack_rate,
                float decay_rate,
                float sustain_level,
                float release_rate)
{
    env_state.attackRate=1.0f/(attack_rate*env_state.sampling_rate);
    env_state.decayRate=1.0f/(decay_rate*env_state.sampling_rate);
    env_state.releaseRate=1.0f/(release_rate*env_state.sampling_rate);
    env_state.sustainLevel=sustain_level;
}

void env_gate_on()
{
    env_state.output=0.0f;
    env_state.stage=ENV_STAGE_ATTACK;
}

void env_gate_off()
{
    if (env_state.stage!=ENV_STAGE_WAIT)
    {
        env_state.stage=ENV_STAGE_RELEASE;
    }
}

float envelope_render()
{
    switch (env_state.stage)
    {
        case ENV_STAGE_ATTACK:
        {
            env_state.output+=env_state.attackRate;
            if (env_state.output>1.0f)
            {
                env_state.output=1.0f;
                env_state.stage=ENV_STAGE_DECAY;
            }
            break;
        }
        case ENV_STAGE_DECAY:
        {
            env_state.output-=env_state.decayRate;
            if (env_state.output<=env_state.sustainLevel)
            {
                env_state.output=env_state.sustainLevel;
            }
            break;
        }
        case ENV_STAGE_SUSTAIN:
        {
            break;
        }
        case ENV_STAGE_RELEASE:
        {
            env_state.output-=env_state.releaseRate;
            if (env_state.output<=0.0f)
            {
                env_state.output=0.0f;
                env_state.stage=ENV_STAGE_WAIT;
            }
            break;
        }
        default:
        {
            break;
        }
    }
    return env_state.output;
}