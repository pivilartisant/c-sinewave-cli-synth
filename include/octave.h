#include <stdio.h>
#include <math.h>

static float default_octave = 2.0f; // default octave

/// generate_octave = frequency * (default_octave * new_octave) if change = true 
///- frequency: frequency of the note
///- change: set to true if you want to change the octave
///- new_octave: value in float to divide the default octave by. Set to 0 if change == false
///
int generate_octave(float frequency, bool change, float new_octave){
    if (change) {
        return frequency * (default_octave * new_octave);
    }
    return frequency * default_octave;
}