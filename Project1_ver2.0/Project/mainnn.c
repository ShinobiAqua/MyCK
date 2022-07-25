#pragma warning(disable:4996)
#include<time.h>
#include<windows.h>
#include<stdlib.h>
#include "miracl.h"
#include <math.h>
#include<stdio.h>
#include "111111.h"
#include "resolve.h"
#include <Windows.h>
#include "ConstValue.h"
#include "Sm2Util.h"
#include "heap.h"
#include"EcurveUtil.h"
#include"BigUtil.h"
#include"binary_S.h"
#define uint unsigned int
//using namespace std;
miracl* mip;
int maxLen = 8192;			//ȫ���ַ�����󳤶�
int v = 64;
int PRFL = 0;


void printmess1()
{
	printf("\n------------------------------------------------------------------------------------------\n");
	printf("0:��ӡ��Բ���߲��� 1:�ӽ�����֤ 2:mpЧ�ʲ��� 3:�ֽ��ٶȲ��� 4:˫�����ֽ�鿴 5:���� 6:�˳�\n");
	printf("------------------------------------------------------------------------------------------\n\n");
}

void certi()
{
	//fflush(stdin);
	printf("\n------------------------------------------------------------------------------------------\n");
	printf("1:�ļ����� 2:�ֶ����� 0:����\n");
	printf("------------------------------------------------------------------------------------------\n\n");
	char c;
	getchar();
	while (c = getchar())
	{
		switch (c)
		{
		case '1':  break; 
		case '2':  break; 
		case '0':system("cls"); printmess1(); return;
		case '\n':break;
		default: {printf("���벻�Ϸ�\n"); printf("1:�ļ����룬2:�ֶ�����\n"); while (getchar() != '\n'); break; }
		}
		if (c == '1' || c == '2') break;
		
	}
	CalculateKeys();
	//PrintMess();
	Encryption(c);
	Decryption();
	printmess1();
	return;
}

void case2()
{
	printf("\n***----------------------------------------------------------------------------***\n");
	printf("�ð汾��ʱֻ�ṩ4NAF,Tree-naf-s4-W24��Tree-s4�ıȽ�,��Ҫ���и���Ƚ����ڴ�֮��汾\n");
	printf("***----------------------------------------------------------------------------***\n\n");
	epoint* a1 = epoint_init();
	epoint* b1 = epoint_init();
	big k = mirvar(0);
	big s = mirvar(1);
	set256(k, s);
	big tmp = mirvar(0);

	big n = mirvar(0);
	irand(time(NULL));

	epoint* g = CalculateG();

	big mynun[7000] = { mirvar(0) };
	for (int j = 0; j < 7000; j++)
		mynun[j] = mirvar(0);

	int iteration = 500;
	while(1) {
		printf("���������mp����Ĵ���(0-7000)\n");
		if (!scanf("%d", &iteration))
			exit(1);
		if (iteration > 7000 || iteration < 0)
		{
			printf("�������������Ҫ��Ĵ���\n");
		}
		else break;
		
	}
	printf("\n\n");
	printf("mp�����Ϊ��ʱ�������ĵȴ�........................................................\n\n");

	int i = 0;
	double totaltime1, totaltime2;
	double ss = 0;
	double ssl = 0;

	while (i < iteration)
	{
		bigrand(k, n);
		add(n, s, n);
		copy(n, mynun[i]);
		//cotnum(mynun[i], stdout);
		i++;
	}

	i = 0;
	//double ll = 0;
	clock_t start1, finish1, start2, finish2;
	start1 = clock();
	while (i < iteration) {
		//int t = rand() % 256;
		//bigbits(t, n);
		//bigrand(k, n);
		//add(n, s, n);
		copy(mynun[i], n);
		a1 = his_MultiplyEpoint(n, g);
		i++;
	}
	finish1 = clock();
	totaltime1 = (double)(finish1 - start1) / CLOCKS_PER_SEC;
	printf("**!����ʱ����Ϣ:\n\n");
	printf("//////////////////////////////\n");
	printf("4NAF            time: %lf\n", totaltime1);
	//printf("%lf\n", ll / iteration);
	//printf("mul: %lf\n", ssl);

	i = 0;
	start2 = clock();
	while (i < iteration) {
		copy(mynun[i], n);
		a1 = MultiplyEpoint(n, g);
		i++;
	}
	finish2 = clock();
	totaltime2 = (double)(finish2 - start2) / CLOCKS_PER_SEC;
	printf("Tree-naf-s4-W24 time: %lf\n", totaltime2);


	i = 0;
	start2 = clock();
	while (i < iteration) {
		copy(mynun[i], n);
		a1 = T_MultiplyEpoint(n, g);
		i++;
	}
	finish2 = clock();
	totaltime2 = (double)(finish2 - start2) / CLOCKS_PER_SEC;
	printf("Tree-s4         time: %lf\n", totaltime2);
	printf("//////////////////////////////\n");

	mirkill(n);
	mirkill(k);
	mirkill(s);
	for (int j = 0; j < 7000; j++)
		mirkill(mynun[j]);
	printmess1();
	return;
}

void case3()
{
	printf("\n***----------------------------------------------------------------------------***\n");
	printf("�ð汾��ʱֻ�ṩ4NAF,Tree-naf-s4-W24��Tree-s4�ıȽ�,��Ҫ���и���Ƚ����ڴ�֮��汾\n");
	printf("***----------------------------------------------------------------------------***\n\n");

	big b = mirvar(1);
	clock_t start, finish;
	double totaltime;
	big k = mirvar(0);
	big s = mirvar(0);
	set256(k, s);//k=2^256, s=2^256-1
	big tmp = mirvar(0);
	double sum = 0;
	double sum1 = 0;
	double sum2 = 0;
	double sum3 = 0;

	int iteration = -1;
	while (1) {
		printf("��������зֽ����(����0��������)\n");
		if (!scanf("%d", &iteration))
			exit(1);
		if (iteration < 0)
		{
			printf("�������������Ҫ��Ĵ���\n");
		}
		else break;
	}

	big n = mirvar(0);
	int i = 0;
	int a[256];
	int e[256];
	int c[256];
	int d[256];
	int f[256];
	double sa = 0, sb = 0;

	start = clock();
	while (i < iteration)
	{
		bigrand(k, n);
		add(n, s, n);
		int len = 0; 
		len = naf_window(n);
		i++;
	}
	finish = clock();
	totaltime = (double)(finish - start) / CLOCKS_PER_SEC;
	printf("**!����ʱ����Ϣ:\n\n");
	printf("///////////////////////////////\n");
	printf("4NAF            time: %lf\n", totaltime);


	i = 0;
	start = clock();
	while (i < iteration)
	{
		bigrand(k, n);
		add(n, s, n);
		copy(n, b);
		int len = 0;
		span_dec_23_mod(n, a, e, c, d, &len);
		i++;
	}
	finish = clock();
	totaltime = (double)(finish - start) / CLOCKS_PER_SEC;
	printf("Tree-naf-s4-W24 time: %lf\n", totaltime);

	i = 0;
	start = clock();
	while (i < iteration)
	{
		bigrand(k, n);
		add(n, s, n);
		copy(n, b);
		int len = 0;
		span_dec_23(n, a, e, c, d,&len);
		i++;
	}
	finish = clock();
	totaltime = (double)(finish - start) / CLOCKS_PER_SEC;
	printf("Tree-s4         time: %lf\n", totaltime);
	printf("///////////////////////////////\n");

	mirkill(n);
	mirkill(k);
	mirkill(s);
	mirkill(b);
	printmess1();
	return;

}

void case4()
{
	PRFL = 1;
	int flg;
	printf("\n***-----------------------***\n");
	  printf("���ṩʹ�õķֽⷽ��ΪTree-S4\n");
	  printf("***-----------------------***\n\n");
	while (1) {
		printf("\n------------------------------------------------------------------------------------------\n");
		printf("ѡ���������� 1:256bit�����  2:�ֶ�����int��\n");
		printf("------------------------------------------------------------------------------------------\n\n");
		if (!scanf("%d", &flg))
			exit(1);
		if (flg!=1&&flg!=2)
		{
			printf("���벻�Ϸ�������������\n");
		}
		else break;
	}
	
	
	big k = mirvar(0);
	big s = mirvar(0);
	set256(k, s);//k=2^256, s=2^256-1
	big n = mirvar(0);
	int a[256];
	int e[256];
	int c[256];
	int d[256];
	int f[256];
	bigrand(k, n);
	add(n, s, n);
	int len;
	if(flg==1)
		span_dec_23(n, a, e, c, d, &len);
	else {
		int nn;
		while (1) {
			printf("������һ������\n");
			if (!scanf("%d", &nn))
				exit(1);
			if (nn<0)
			{
				printf("���벻�Ϸ�������������\n");
			}
			else break;
		}
		n = mirvar(nn);
		span_dec_23(n, a, e, c, d, &len);

	}
	mirkill(n);
	mirkill(k);
	mirkill(s);
	PRFL = 0;
	printmess1();
	return;
}
int main()
{
	printf("���ڳ�ʼ�����Ժ�.....\n\n");
	mip = mirsys(512, 0);
	//binary_init();
	ecurve_init(HexCharsToBig(a), HexCharsToBig(b), HexCharsToBig(p), MR_PROJECTIVE);
	//CalculateKeys();
	//PrintMess();
	printf("                                        ***��ӭʹ��***");
	char c;
	printmess1();
	while (c = getchar()) {
		switch (c) {
		case'0':PrintMess();  printmess1(); break;
		case '1':certi(); break;
		case '2':case2(); break;
		case '3':case3(); break;
		case '4':case4(); break;
		case '5':system("cls"); printmess1(); break;
		case'6':return;
		case '\n':break;
		default: printf("���벻�Ϸ�\n"); while (getchar() != '\n'); break;
		}
	}
	

	return 0;
}



//SM2ģ������https://github.com/LS-King/SM2/tree/c391bbb47db9122aaffb718502c43fcde3cd335b