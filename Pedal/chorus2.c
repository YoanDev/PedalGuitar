
struct SettingsChorus{ 
    int compt;
    int f;
    float amplitude;
    float tab[10000];
};
typedef struct SettingsChorus SettingsChorus;

float_t Delay_Buffer_chorus[DELAY_MAX];
uint32_t DelayCounter_chorus = 0;
uint32_t Delay_Depth_chorus = 100;

void chorus2(jack_default_audio_sample_t *in,jack_default_audio_sample_t *out, int i, void* settings)
{
    float* channelData = in;
    SettingsChorus *actualSettings = settings;

    if(actualSettings->compt==10000)
    {
        actualSettings->compt = 0;
    }
    actualSettings->compt++;

    Delay_Buffer_chorus[DelayCounter_chorus] = channelData[i] + Delay_Buffer_chorus[DelayCounter_chorus] * actualSettings->tab[actualSettings->compt]*0.25;
    DelayCounter_chorus++;
    if(DelayCounter_chorus>=Delay_Depth_chorus)
    {
        DelayCounter_chorus = 0;
    }
    out[i] =  Delay_Buffer_chorus[DelayCounter_chorus]*0.5;
    //printf("%f \n",actualSettings->tab[actualSettings->compt]);
    printf("%f\n",out[i]);
    //printf("%f\n",Delay_Buffer_chorus[DelayCounter_chorus]);
}

void sinus (SettingsChorus *settings)
{
    SettingsChorus actualSettings = *settings;
    int i;
    for (i = 0; i <= 10000; i++)
    {
        actualSettings.tab[i] = actualSettings.amplitude * sin((2 * PI * actualSettings.f * ((float) i / 10000))) / 2;
        printf("%f\n",actualSettings.tab[i]);
    }
}