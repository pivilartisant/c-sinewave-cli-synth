//scales.c

#include <stdio.h>
#include <math.h>

#include <include/scales.h>

void init_scale(struct A_minor_scale *s) { 
    float A = 440.0f;
    float B = A + A * 2.0f / 12.0f;
    float C = A + A * 3.0f / 12.0f;
    float D = A + A * 5.0f / 12.0f;
    float E = A + A * 7.0f / 12.0f;
    float F = A + A * 8.0f / 12.0f;
    float G = A + A * 10.0f / 12.0f;

    
    s->A = A;
    s->B = B;
    s->C = C;
    s->D = D;
    s->E = E;
    s->F = F;
    s->G = G;
}
