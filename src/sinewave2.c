#include <soundio/soundio.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <include/octave.h>
#include <include/scales.h>

static float seconds_offset = 0.0f;
static void generate_sinewave(struct SoundIoOutStream *outstream,
        int frame_count_min, int frame_count_max)   
{
    const struct SoundIoChannelLayout *layout = &outstream->layout;
    float float_sample_rate = outstream->sample_rate; // or frames per second defaults to 48000
    float seconds_per_frame = 1.0f / float_sample_rate;  // number of seconds per frame 
    struct SoundIoChannelArea *areas;
    int frames_left = frame_count_max;
    int err;

    struct A_minor_scale a_minor_scale;
    initScale(&a_minor_scale);

    while (frames_left > 0) {

        int frame_count = frames_left;

        if ((err = soundio_outstream_begin_write(outstream, &areas, &frame_count))) {
            fprintf(stderr, "%s\n", soundio_strerror(err));
            exit(1);
        }

        if (!frame_count)
            break;

        float note_frequency = 440.0f;
        for (int frame = 0; frame < frame_count; frame += 1) {

  
            // we are going for a two channel polyphonic synth
            float note_one = sin((seconds_offset + frame * seconds_per_frame) * generate_octave(a_minor_scale.A, true, 0.75) * M_PI);

            // here we play the same A note but 2 octaves below
            float note_two = sin((seconds_offset + frame * seconds_per_frame) * generate_octave(a_minor_scale.B, true, .50f) * M_PI);
        
            
            for (int channel = 0; channel < layout->channel_count; channel += 1) {
                
               // dividing notes by channel channel 0 is left, channel 1 is right
               if (channel == 0) {
                float *ptr = (float*)(areas[channel].ptr + areas[channel].step * frame);
                *ptr = note_one;
               } else {
                float *ptr = (float*)(areas[channel].ptr + areas[channel].step * frame);
                *ptr = note_two;
               }
            }
        }
        seconds_offset = fmod(seconds_offset + seconds_per_frame * frame_count, 1.0);

        if ((err = soundio_outstream_end_write(outstream))) {
            fprintf(stderr, "%s\n", soundio_strerror(err));
            exit(1);
        }

        frames_left -= frame_count;
    };
};

