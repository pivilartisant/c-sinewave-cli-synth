#include <stdbool.h>
#include <include/octave.h>
#include <math.h>
static float default_octave = 1.0f; // default octave

/// generate_octave = frequency * (default_octave * new_octave) if change = true 
/// - frequency: frequency of the note
/// - change: set to true if you want to change the octave
/// - new_octave: value in float to divide the default octave by. Set to 0 if change == false
///
float generate_octave(float frequency, bool change, float new_octave){
    if (change) {
        return frequency * (default_octave * new_octave);
    }
    return trunc(frequency * default_octave);
}