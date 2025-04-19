// main.c

#include <soundio/soundio.h>

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <include/octave.h>
#include <include/scales.h>

float frequency_A = 0.0f;
float frequency_B = 0.0f;
float time = 0.0f;
int amplitude = 1;
char c = 0;

double generate_sine(float frequency, float phase){
    return sin((2 * M_PI) * (frequency) * phase);
};

void generate_sinewave(struct SoundIoOutStream *outstream,
        int frame_count_min, int frame_count_max)   
{
    const struct SoundIoChannelLayout *layout = &outstream->layout;
    float float_sample_rate = outstream->sample_rate; // or frames per second defaults to 48000
    float seconds_per_frame = 1.0f / float_sample_rate;  // number of seconds per frame, fixed value
    struct SoundIoChannelArea *areas;
    int frames_left = frame_count_max;
    int err;

    while (frames_left > 0) {

        int frame_count = frames_left; // 606 frames

        if ((err = soundio_outstream_begin_write(outstream, &areas, &frame_count))) {
            fprintf(stderr, "%s\n", soundio_strerror(err));
            exit(1);
        }

        if (!frame_count)
            break;

        for (int frame = 0; frame < frame_count; frame += 1) {
      
            float oscillations_per_second_A = generate_octave(frequency_A, true, 0.5f);
            float oscillations_per_second_B = generate_octave(frequency_B, true, 0.5f);

            float phase = time + frame * seconds_per_frame; 

            // we are going for a two channel duo-phonic synth
            float note_one = amplitude * generate_sine(oscillations_per_second_A, phase);

            // here we play the same A note but 2 octaves below
            float note_two = amplitude * generate_sine(oscillations_per_second_B, phase);
        
            
            for (int channel = 0; channel < layout->channel_count; channel += 1) {
                
               // dividing notes by channel channel 0 is left, channel 1 is right
               if (channel == 0) {
                float *ptr = (float*)(areas[channel].ptr + areas[channel].step * frame);
                *ptr = note_one;
               } else { float *ptr = (float*)(areas[channel].ptr + areas[channel].step * frame); \
                *ptr = note_two;}
            }
        }

        // ensures that sinewave is smooth
        // no fmod because I don't want to reset the wave in the middle of a cycle
        time = time + seconds_per_frame * frame_count;   
       
        if ((err = soundio_outstream_end_write(outstream))) {
            fprintf(stderr, "%s\n", soundio_strerror(err));
            exit(1);
        }

        frames_left -= frame_count;
    };
};

void set_target_voice(float target_frequency, int target_voice){
    if (target_voice == 1 ) {
        frequency_A = target_frequency;
            printf("Setting voice A frequency to:%f\n\n", frequency_A);
            return;
    } 
        
    frequency_B = target_frequency;
    printf("Setting voice B frequency to:%f\n\n", frequency_B);
    return;
}




int main(int argc, char **argv) {


    // Initializing the synth 

    struct A_minor_scale a_minor_scale;
    init_scale(&a_minor_scale);
    
    // sets default frequency
    frequency_A = a_minor_scale.A;
    frequency_B = a_minor_scale.A;
    
    int target_voice = 1; // default is voice A, to change user needs to first inputs target voice, than target note

    // Initializing boring stuff  
    int err;
    struct SoundIo *soundio = soundio_create();
    if (!soundio) {
        fprintf(stderr, "out of memory\n");
        return 1;
    }

    if ((err = soundio_connect(soundio))) {
        fprintf(stderr, "error connecting: %s\n", soundio_strerror(err));
        return 1;
    }

    soundio_flush_events(soundio);

    int default_out_device_index = soundio_default_output_device_index(soundio);
    if (default_out_device_index < 0) {
        fprintf(stderr, "no output device found\n");
        return 1;
    }

    struct SoundIoDevice *device = soundio_get_output_device(soundio, default_out_device_index);
    if (!device) {
        fprintf(stderr, "out of memory\n");
        return 1;
    }

    fprintf(stderr, "Output device: %s\n", device->name);

    struct SoundIoOutStream *outstream = soundio_outstream_create(device);
    if (!outstream) {
        fprintf(stderr, "out of memory\n");
        return 1;
    }
    outstream->format = SoundIoFormatFloat32NE;
    outstream->write_callback = generate_sinewave; // this actually triggers the initial callback

    if ((err = soundio_outstream_open(outstream))) {
        fprintf(stderr, "unable to open device: %s", soundio_strerror(err));
        return 1;
    }

    if (outstream->layout_error)
        fprintf(stderr, "unable to set channel layout: %s\n", soundio_strerror(outstream->layout_error));

    if ((err = soundio_outstream_start(outstream))) {
        fprintf(stderr, "unable to start device: %s\n", soundio_strerror(err));
        return 1;
    }


 

    for (;;){ ;
        soundio_flush_events(soundio); 
  
        // gets input 
        c = getchar(); // by default char = 0
        printf("char: %c\n", c);

        // basic way for me to select a note and a channel
        switch (c)
        {
        case '1':
             target_voice = 1;
            break;
        case '2':
            target_voice = 2;
           break;
        case 'a':
            set_target_voice(a_minor_scale.A, target_voice);
          break;
        case 'w':
            set_target_voice(a_minor_scale.B, target_voice);
        break;
        case 's':
            set_target_voice(a_minor_scale.C, target_voice);
        break;
        case 'e':
            set_target_voice(a_minor_scale.D, target_voice);
        break;
        case 'd':
            set_target_voice(a_minor_scale.E, target_voice);
        break;
        case 'r':
            set_target_voice(a_minor_scale.F, target_voice);
        break;
        case 'f':
            set_target_voice(a_minor_scale.G, target_voice);
        break;
        
        default:
            break;
        }
    }
    
    soundio_outstream_destroy(outstream);
    soundio_device_unref(device);
    soundio_destroy(soundio);
    return 0;
}
