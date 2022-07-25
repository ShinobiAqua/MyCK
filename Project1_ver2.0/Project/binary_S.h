#pragma once
#include "miracl.h"

typedef struct bs {
	big a;
	int b0;//3的b0次方
	int s0;//系数
	int len0;//二进制长度
}bsa;
void binary_init();
void findapprox(big n, int a0, int b0, int* x1, int* x2, int* t1, int* t2);
int bsdecomp(big n);
void windowsize(int x);