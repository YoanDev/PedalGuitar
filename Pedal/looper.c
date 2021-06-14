#include <stdio.h>
#include <netinet/in.h>

#include <jack/jack.h>
#include <math.h>

#define DELAY_MAX_LOOP 240000
#define PI 3.14

jack_port_t *input_port;
jack_port_t *output_port;
jack_client_t *client;

float_t Delay_Buffer_loop[DELAY_MAX_LOOP];
uint32_t DelayCounterLoop = 0;
uint32_t Delay_Depth_Loop = 240000;

int comptDelay=0;

void looper(jack_default_audio_sample_t *in,jack_default_audio_sample_t *out, int i, int state)
{
    float* channelData = in;
    DelayCounterLoop++;
    if(DelayCounterLoop==Delay_Depth_Loop)
    {
        DelayCounterLoop = 0;
        printf("max\n");
        comptDelay++;
    }
    if(comptDelay == 0) {
        Delay_Buffer_loop[DelayCounterLoop] = channelData[i];
        out[i] = Delay_Buffer_loop[DelayCounterLoop]+ channelData[i];
    }
    else{
        Delay_Buffer_loop[DelayCounterLoop] = Delay_Buffer_loop[DelayCounterLoop]+ channelData[i];
        out[i] = Delay_Buffer_loop[DelayCounterLoop] + channelData[i];
    }
}





