#include <stdio.h>

struct A_minor_scale {
    float A; 
    float B; 
    float C;
    float D;
    float E; 
    float F;
    float G;
};


const A  = 440.0f;
float B  = A + A  * 3/12;
float C = A + A * 4/12;
float D = A + A * 6/12;
float E = A + A * 8/12;
float F = A + A * 8/12;
float G = A + A * 8/12;


static void initScale(struct A_minor_scale *s) {
    s->A = A;  
    s->B = B;
    s->C = C;
    s->D = D;
    s->E = E;
    s->F = F;
    s->G = G;
};

// A_minor_scale static s1 = (A_minor_scale){
//     .A = A,  
//     .B = B,
//     .C = C,
//     .D = D,
//     .E = E,
//     .F = F,
//     .G = G,
// };