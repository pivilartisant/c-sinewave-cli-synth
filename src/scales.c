//scales.c

#include <stdio.h>
#include <math.h>

#include <include/scales.h>

void init_scale(struct A_minor_scale *s) {

    // fn ​= f0 ​× 2^n/12 is the formula to find the interval ratio between notes 
    float A = 440.0f;
    float B = A * pow(2.0f, 2.0f / 12.0f);
    float C = A * pow(2.0f, 3.0f / 12.0f);
    float D = A * pow(2.0f, 5.0f / 12.0f);
    float E = A * pow(2.0f, 7.0f / 12.0f);
    float F = A * pow(2.0f, 8.0f / 12.0f);
    float G = A * pow(2.0f, 10.0f / 12.0f);

    s->A = A;
    s->B = B;
    s->C = C;
    s->D = D;
    s->E = E;
    s->F = F;
    s->G = G; 
    
}
