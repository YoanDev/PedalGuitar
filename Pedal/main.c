#include "delay.c"
#include "saturation.c"
#include "serveurTcp.c"
#include "looper.c"
#include "chorus2.c"
#include <pthread.h>

/**
 * The process callback for this JACK application is called in a
 * special realtime thread once for each audio cycle.
 *
 * This client does nothing more than copy data from its input
 * port to its output port. It will exit when stopped by
 * the user (e.g. using Ctrl-C on a unix-ish operating system)
 */
int process (jack_nframes_t nframes, void* settingsChorus)
{
    jack_default_audio_sample_t *in, *out;
    in = jack_port_get_buffer (input_port, nframes);
    out = jack_port_get_buffer (output_port, nframes);
    int i;
    int state;
    for (i = 0; i < nframes; i++)
    {
        //out[i]=in[i];
        //printf("%s",content);
        
        if (content != NULL) {
            if (strcmp(content, "delayOn") == 0) {
                delay(in, out, i);
            }
            else if (strcmp(content, "satOn") == 0) {
                saturation(in, out, i);
            }
            else if (strcmp(content, "loopStart") == 0) {
                state = 0;
                looper(in, out, i, state);
            }
            else if (strcmp(content, "loopStop") == 0) {
                state = 1;
                looper(in, out, i, state);
            }
            else if (strcmp(content, "clean") == 0)
            {
                clean(in, out, i);
            }
            else if (strcmp(content, "chorus") == 0)
            {
                chorus2(in, out, i, settingsChorus);//add settings
            }
            else
                clean(in,out,i);
            //content = NULL;

        }
    }
    return 0;
}

/**
 * JACK calls this shutdown_callback if the server ever shuts down or
 * decides to disconnect the client.
 */
void jack_shutdown (void *arg)
{
    exit (1);
}

int main (int argc, char *argv[])
{
    const char **ports;
    const char *client_name = "simple";
    const char *server_name = NULL;
    jack_options_t options = JackNullOption;
    jack_status_t status;
    pthread_t thread_id;
    SettingsChorus *settingsChorus = malloc(sizeof *settingsChorus);
    settingsChorus->f = 1;
    settingsChorus->amplitude = 6;
    settingsChorus->compt = 0;

    pthread_create(&thread_id, NULL, myThreadFun, NULL);

    /* open a client connection to the JACK server */
    //sinus(settingsChorus);
    client = jack_client_open (client_name, options, &status, server_name);
    if (client == NULL) {
        fprintf (stderr, "jack_client_open() failed, "
                         "status = 0x%2.0x\n", status);
        if (status & JackServerFailed) {
            fprintf (stderr, "Unable to connect to JACK server\n");
        }
        exit (1);
    }
    if (status & JackServerStarted) {
        fprintf (stderr, "JACK server started\n");
    }
    if (status & JackNameNotUnique) {
        client_name = jack_get_client_name(client);
        fprintf (stderr, "unique name `%s' assigned\n", client_name);
    }

    /* tell the JACK server to call `process()' whenever
       there is work to be done.
    */

    jack_set_process_callback (client, process, settingsChorus);

    /* tell the JACK server to call `jack_shutdown()' if
       it ever shuts down, either entirely, or if it
       just decides to stop calling us.
    */

    jack_on_shutdown (client, jack_shutdown, 0);

    /* display the current sample rate.
     */

    printf ("engine sample rate: %" PRIu32 "\n",
            jack_get_sample_rate (client));

    /* create two ports */

    input_port = jack_port_register (client, "input",
                                     JACK_DEFAULT_AUDIO_TYPE,
                                     JackPortIsInput, 0);
    output_port = jack_port_register (client, "output",
                                      JACK_DEFAULT_AUDIO_TYPE,
                                      JackPortIsOutput, 0);

    if ((input_port == NULL) || (output_port == NULL)) {
        fprintf(stderr, "no more JACK ports available\n");
        exit (1);
    }

    /* Tell the JACK server that we are ready to roll.  Our
     * process() callback will start running now. */

    if (jack_activate (client)) {
        fprintf (stderr, "cannot activate client");
        exit (1);
    }

    /* Connect the ports.  You can't do this before the client is
     * activated, because we can't make connections to clients
     * that aren't running.  Note the confusing (but necessary)
     * orientation of the driver backend ports: playback ports are
     * "input" to the backend, and capture ports are "output" from
     * it.
     */

    ports = jack_get_ports (client, NULL, NULL,
                            JackPortIsPhysical|JackPortIsOutput);
    if (ports == NULL) {
        fprintf(stderr, "no physical capture ports\n");
        exit (1);
    }

    if (jack_connect (client, ports[0], jack_port_name (input_port))) {
        fprintf (stderr, "cannot connect input ports\n");
    }

    free (ports);

    ports = jack_get_ports (client, NULL, NULL,
                            JackPortIsPhysical|JackPortIsInput);
    if (ports == NULL) {
        fprintf(stderr, "no physical playback ports\n");
        exit (1);
    }

    if (jack_connect (client, jack_port_name (output_port), ports[0])) {
        fprintf (stderr, "cannot connect output ports\n");
    }

    free (ports);

    /* keep running until stopped by the user */

    sleep (-1);

    /* this is never reached but if the program
       had some other way to exit besides being killed,
       they would be important to call.
    */

    jack_client_close (client);
    exit (0);
}
