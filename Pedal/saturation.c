/** @file simple_client.c
 *
 * @brief This simple client demonstrates the most basic features of JACK
 * as they would be used by many applications.
 */

#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

#include <jack/jack.h>
#include <math.h>

jack_port_t *input_port;
jack_port_t *output_port;
jack_client_t *client;


void saturation(jack_default_audio_sample_t *in,jack_default_audio_sample_t *out, int i)
{
    float* channelData = in;
    channelData[i] *= 50;
    channelData[i] = (2.f / M_PI) * atan(channelData[i]);
    out[i] = 0.1*channelData[i];
    //printf("%f \n", channelData[i]);
}

void clean(jack_default_audio_sample_t *in,jack_default_audio_sample_t *out, int i)
{
    float* channelData = in;
    out[i] = channelData[i];
}






