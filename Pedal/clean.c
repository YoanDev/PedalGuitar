void clean(jack_default_audio_sample_t *in,jack_default_audio_sample_t *out, int i)
{
    float* channelData = in;
    out[i] = channelData[i];
}