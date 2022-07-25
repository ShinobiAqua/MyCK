#ifndef RESOLVE_H
#define RESOLVE_H
#include "miracl.h"


void init();

void dec_23(big n, int* let);

void span_dec_23(big n, short sPOW2[], short sPOW3[], short sISM[], short sprm[], int* let);

void span_dec_23_mod(big n, short POW2[], short POW3[], short ISM[], short prm[], int* let);
#endif