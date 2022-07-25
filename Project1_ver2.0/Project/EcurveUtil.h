#ifndef ECURVEUTIL_H
#define ECURVEUTIL_H

#include "miracl.h"

extern miracl* mip;
extern int maxLen;

epoint* NewPoint(big x, big y);			//�½�һ����Բ�����ϵĵ�
epoint* AddEpoint(epoint*, epoint*);	//��Բ�����ϵĵ����
epoint* MultiplyEpoint(big, epoint*);	//��Բ�����ϵĵ�౶������
big PointX(epoint*);					//�����Բ�����ϵ�ĺ�����
big PointY(epoint*);					//�����Բ�����ϵ��������

epoint* his_MultiplyEpoint(big a, epoint* b);
	
int his_ecurve_mult(_MIPD_ big e, epoint* pa, epoint* pt);
epoint* T_MultiplyEpoint(big a, epoint* b);
int naf_window(_MIPD_ big e);

#endif