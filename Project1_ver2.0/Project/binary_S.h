#pragma once
#include "miracl.h"

typedef struct bs {
	big a;
	int b0;//3��b0�η�
	int s0;//ϵ��
	int len0;//�����Ƴ���
}bsa;
void binary_init();
void findapprox(big n, int a0, int b0, int* x1, int* x2, int* t1, int* t2);
int bsdecomp(big n);
void windowsize(int x);