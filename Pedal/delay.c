#include <jack/jack.h>
#include <math.h>

#define DELAY_MAX 48000

//jack_port_t *input_port;
//jack_port_t *output_port;
//jack_client_t *client;

float_t Delay_Buffer[DELAY_MAX];
uint32_t DelayCounter = 0;

void delay(jack_default_audio_sample_t *in,jack_default_audio_sample_t *out, int i)
{
    //float* channelData = in;
    Delay_Buffer[DelayCounter] = Delay_Buffer[DelayCounter]*0.5 + in[i];
    DelayCounter++;
    if(DelayCounter>=DELAY_MAX)
    {
        DelayCounter = 0;
    }
    out[i] = in[i] + Delay_Buffer[DelayCounter]*0.5;
}







