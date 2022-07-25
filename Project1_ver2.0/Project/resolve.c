#include<time.h>
#include<stdlib.h>
#include "miracl.h"
#include <math.h>
#include<stdio.h>
#include"heap.h"
#include"resolve.h"

extern int PRFL;
extern miracl* mip;
void init() {
	miracl* mip = mirsys(1024, 2);
}

void dec_23(big n, int* let) {
	//miracl* mip = mirsys(256, 2);
	//big ans = mirvar(0);
	big origin = mirvar(0);
	//big tmp = mirvar(0);
	//copy(n, origin);
	//big origin = n;
	big mp = mirvar(0);
	big ap = mirvar(0);
	big mn = mirvar(0);
	big an = mirvar(0);
	int fl = 0;
	int POW2[256] = { 0 };
	int POW3[256] = { 0 };
	int ISM[256] = { 0 };
	int mc = 0;
	int pow2 = 0;
	int pow3 = 0;
	fl = remain(n, 3);
	//printf("%d\n",fl);


	while (n->len && !mr_testbit(_MIPP_ n, 0))
	{
		sftbit(n, -1, n);
		fl = fl + (3 - fl * 2);
		fl %= 3;
		pow2 += 1;
	}

	while (n->len == 1 && (fl == 0))
	{
		subdiv(n, 3, n);
		fl = remain(n, 3);

		//cout << "pow " << powm << endl;

		pow3 += 1;
	}
	//cotnum(n, stdout);
	while (1)
	{
		//cotnum(n, stdout);
		++mc;
		POW2[mc] = pow2;
		POW3[mc] = pow3;
		if (n->len == 0)
			break;

		/*mp = mirvar(1);
		ap = mirvar(1);*/
		int mpow2, mpow3, apow2, apow3;
		int mf, af;
		mf = (fl - 1) % 3;
		af = (fl + 1) % 3;
		mpow2 = mpow3 = apow2 = apow3 = 0;
		decr(n, 1, mn);
		incr(n, 1, an);

		while (mn->len && !mr_testbit(_MIPP_ mn, 0))
		{
			sftbit(mn, -1, mn);
			mf = mf + (3 - mf * 2);
			mf %= 3;
			mpow2 += 1;
			//sftbit(mp, 1, mp);
		}

		while (mn->len && (mf == 0))
		{
			subdiv(mn, 3, mn);
			mf = remain(mn, 3);
			mpow3 += 1;
			//premult(mp, 3, mp);
		}



		while (an->len && !mr_testbit(_MIPP_ an, 0))
		{
			sftbit(an, -1, an);
			af = af + (3 - af * 2);
			af %= 3;
			apow2 += 1;
			//sftbit(ap, 1, ap);
		}

		while (an->len && (af == 0))
		{
			subdiv(an, 3, an);
			af = remain(an, 3);
			apow3 += 1;
			//premult(ap, 3, ap);
		}
		if (compare(mn, an) == 1)
		{
			copy(an, n);
			fl = af;
			pow2 += apow2;
			pow3 += apow3;
			ISM[mc] = 1;
		}
		else
		{
			copy(mn, n);
			fl = mf;
			pow2 += mpow2;
			pow3 += mpow3;
		}

		//cout << "2^" << pow2 << "*" << "3" << "^" << pow3 << "+";

	}
	//printf("%d\n", pow3);
	/*big cert = mirvar(0);
	big tmpp = mirvar(0);
	big twop = mirvar(0);
	for (int i = mc-1; i > 1; i--) {

		expb2(POW2[i],twop);
		multiply(pow3n[POW3[i]], twop, tmpp);
		if (ISM[i]) {
			subtract(cert, tmpp, cert);
			printf("- 2^%d*3^%d ", POW2[i], POW3[i]);
		}
		else {
			add(cert, tmpp, cert);
			printf("+ 2^%d*3^%d ", POW2[i], POW3[i]);
		}
		//cotnum(cert, stdout);
	}

	expb2(POW2[1], twop);
	multiply(pow3n[POW3[1]], twop, tmpp);
	if (ISM[1]) {
		subtract(cert, tmpp, cert);
		printf("- 2^%d*3^%d\n ", POW2[1], POW3[1]);
	}
	else {
		add(cert, tmpp, cert);
		printf("+ 2^%d*3^%d\n", POW2[1], POW3[1]);
	}
	cotnum(cert, stdout);
	cotnum(origin, stdout);*/

	* let = mc - 1;
}

//分解的函数
void span_dec_23(big n, short POW2[], short POW3[], short ISM[], short prm[], int* let) {
	//miracl* mip = mirsys(256, 2);
	//big ans = mirvar(0);
	big origin = mirvar(0);
	//big tmp = mirvar(0);
	copy(n, origin);
	big pre_n = mirvar(0);
	big tmp_n = mirvar(0);

	int s[30] = { -1,+1,-5,+5,-7,+7,-11,+11 ,-13,+13,-17,+17,-19,+19,-23,23,-25,25,-29,29,-31,31,-35,35,-37,37,-41,41 };
	int fl = 0;
	int flg = 0;
	/*int POW2[256] = { 0 };
	int POW3[256] = { 0 };
	int ISM[256] = { 0 };
	int prm[256] = { 0 };*/
	int mc = -1;
	int pow2 = 0;
	int pow3 = 0;
	fl = remain(n, 3);
	//printf("%d\n",fl);


	while (n->len && !mr_testbit(_MIPP_ n, 0))
	{
		sftbit(n, -1, n);
		fl = fl + (3 - fl * 2);
		fl %= 3;
		pow2 += 1;
	}

	while (n->len && (fl == 0))
	{
		subdiv(n, 3, n);
		fl = remain(n, 3);

		//cout << "pow " << powm << endl;

		pow3 += 1;
	}
	//cotnum(n, stdout);
	while (1)
	{
		//cotnum(n, stdout);
		//printf("\n");
		++mc;
		POW2[mc] = pow2;
		POW3[mc] = pow3;
		if (n->len == 0)
			break;
		int pre_p2 = 0;
		int pre_p3 = 0;
		int tmp_p3 = 0;
		int tmp_p2 = 0;
		decr(n, 1, pre_n);
		flg = 0;
		if (pre_n->len == 0)
		{
			copy(pre_n, n);
			prm[mc] = -1;
			continue;
		}
		while (!mr_testbit(pre_n, 0) && pre_n->len)
		{
			sftbit(pre_n, -1, pre_n);
			pre_p2++;
		}
		fl = remain(pre_n, 3);
		while (pre_n->len && (fl == 0))
		{
			subdiv(pre_n, 3, pre_n);
			fl = remain(pre_n, 3);
			//cout << "pow " << powm << endl;
			pre_p3++;
		}


		for (int i = 1; i < 4; i++)
		{
			tmp_p2 = tmp_p3 = 0;
			incr(n, s[i], tmp_n);
			if (tmp_n->len == 0)
			{
				pre_p2 = tmp_p2;
				pre_p3 = tmp_p3;
				flg = i;
				copy(tmp_n, pre_n);
				prm[mc] = s[i];
				break;
			}

			while (!mr_testbit(tmp_n, 0) && tmp_n->len)
			{
				sftbit(tmp_n, -1, tmp_n);
				tmp_p2++;
			}
			fl = remain(tmp_n, 3);
			while (tmp_n->len && (fl == 0))
			{
				subdiv(tmp_n, 3, tmp_n);
				fl = remain(tmp_n, 3);
				//cout << "pow " << powm << endl;
				tmp_p3++;
			}
			//if(tmp_p3>=pre_p3)
			if (/*!cpr2_3(pre_p2,pre_p3,tmp_p2,tmp_p3)*/compare(pre_n, tmp_n) == 1)
			{
				//printf("%d\n", s[i]);
				/*int t = cpr2_3(pre_p2, pre_p3, tmp_p2, tmp_p3);
				printf("%d\n", t);*/
				pre_p2 = tmp_p2;
				pre_p3 = tmp_p3;
				flg = i;
				copy(tmp_n, pre_n);
				//break;
			}
		}
		copy(pre_n, n);
		pow2 += pre_p2;
		pow3 += pre_p3;
		prm[mc] = s[flg];

		//cout << "2^" << pow2 << "*" << "3" << "^" << pow3 << "+";

	}
	//printf("%d\n", pow3);
	if (PRFL==1) {
		big cert = mirvar(0);
		big tmpp = mirvar(0);
		big twop = mirvar(0);
		big thrp = mirvar(0);
		mip->IOBASE = 10;
		printf("\nTree-S4方法双基链分解结果为:\n");
		int t;
		for (int i = mc - 1; i > 0; i--) {
			//printf("%d\n", POW2[i]);
			expb2(POW2[i], twop);
			expint(3, POW3[i], thrp);
			multiply(thrp, twop, tmpp);
			premult(tmpp, -1 * prm[i], tmpp);
			//cotnum(tmpp, stdout);
			//cotnum(tmpp, stdout);
			add(cert, tmpp, cert);
			printf("+ 2^%d*3^%d*(%d) ", POW2[i], POW3[i], -prm[i]);

			//cotnum(cert, stdout);
		}

		expb2(POW2[0], twop);
		expint(3, POW3[0], thrp);
		multiply(thrp, twop, tmpp);

		premult(tmpp, -prm[0], tmpp);


		add(cert, tmpp, cert);
		printf("+ 2^%d*3^%d*(%d)\n", POW2[0], POW3[0], -prm[0]);

		printf("\n所分解的数为:\n");
		cotnum(origin, stdout);
		printf("加和验证后的数为:\n");
		cotnum(cert, stdout);
		printf("\n");
	}

	/*let[0] = mc;
	let[1] = POW2[mc - 1];
	let[2] = POW3[mc - 1];*/
	* let = mc-1;
}

void span_dec_23_mod(big n, short POW2[], short POW3[], short ISM[], short prm[], int* let) {
	//miracl* mip = mirsys(256, 2);
	//big ans = mirvar(0);
	big origin = mirvar(0);
	//big tmp = mirvar(0);
	copy(n, origin);
	big pre_n = mirvar(0);
	big tmp_n = mirvar(0);


	int fl = 0;
	int flg = 0;
	/*int POW2[256] = { 0 };
	int POW3[256] = { 0 };
	int ISM[256] = { 0 };
	int prm[256] = { 0 };*/
	int mc = -1;
	int pow2 = 0;
	int pow3 = 0;
	int fk;
	fl = remain(n, 3);

	//printf("%d\n",fl);


	while (n->len && !mr_testbit(_MIPP_ n, 0))
	{
		sftbit(n, -1, n);
		pow2 += 1;
	}

	while (n->len && (fl == 0))
	{
		subdiv(n, 3, n);
		fl = remain(n, 3);
		//cout << "pow " << powm << endl;
		pow3 += 1;
	}
	//cotnum(n, stdout);
	while (1)
	{
		//cotnum(n,stdout);
		mc++;
		POW2[mc] = pow2;
		POW3[mc] = pow3;
		if (n->len == 0)
			break;
		fk = subdiv(n, 24, n);

		if (fk < 12)
		{
			prm[mc] = -fk;
		}
		else
		{
			fk = 24 - fk;
			prm[mc] = fk;
			incr(n, 1, n);
		}
		//printf("%d %d %d\n",fk,pow2,pow3);
		//cout << "2^" << pow2 << "*" << "3" << "^" << pow3 << "+";
		pow2 += 3;
		pow3 += 1;

		while (n->len && !mr_testbit(_MIPP_ n, 0))
		{
			sftbit(n, -1, n);
			pow2 += 1;
		}
		fl = remain(n, 3);
		while (n->len && (fl == 0))
		{
			subdiv(n, 3, n);
			fl = remain(n, 3);

			//cout << "pow " << powm << endl;

			pow3 += 1;
		}

	}
	//printf("%d\n", pow3);
	/*big cert = mirvar(0);
	big tmpp = mirvar(0);
	big twop = mirvar(0);
	int t;
	for (int i = mc - 1; i > 0; i--) {
		//printf("%d\n", POW2[i]);
		expb2(POW2[i], twop);

		multiply(pow3n[POW3[i]], twop, tmpp);
		premult(tmpp, -1 * prm[i], tmpp);
		//cotnum(tmpp, stdout);
		//cotnum(tmpp, stdout);
		add(cert, tmpp, cert);
		printf("+ 2^%d*3^%d*(%d) ", POW2[i], POW3[i], -prm[i]);

		//cotnum(cert, stdout);
	}

	expb2(POW2[0], twop);
	multiply(pow3n[POW3[0]], twop, tmpp);

	premult(tmpp, -prm[0], tmpp);


	add(cert, tmpp, cert);
	printf("+ 2^%d*3^%d*(%d)\n", POW2[0], POW3[0], -prm[0]);

	cotnum(cert, stdout);
	cotnum(origin, stdout);*/
		//let[0] = mc;
		//let[1] = POW2[mc - 1];
		//let[2] = POW3[mc - 1];
	*let = mc - 1;
}

/*void span_dec_23_half(big n, int* let) {
	//miracl* mip = mirsys(256, 2);
	//big ans = mirvar(0);
	big origin = mirvar(0);
	//big tmp = mirvar(0);
	copy(n, origin);
	big pre_n = mirvar(0);
	big tmp_n = mirvar(0);

	int s[30] = { -1,+1,-5 ,+5,-7,+7,-11,+11 ,-13,+13,-17,+17,-19,+19,-23,23,-25,25,-29,29,-31,31,-35,35,-37,37,-41,41 };
	int ps[30] = { -1,+1,-5 ,+5,-7,+7,-11,+11 };
	//int s[10] = { -1,+1,-13,+13,-11,+11,-7,+7 ,-5,+5 };
	int fl = 0;
	int flg = 0;
	int POW2[256] = { 0 };
	int POW3[256] = { 0 };
	int ISM[256] = { 0 };
	int prm[256] = { 0 };
	int mc = -1;
	int pow2 = 0;
	int pow3 = 0;
	fl = remain(n, 3);
	//printf("%d\n",fl);


	while (n->len && !mr_testbit(_MIPP_ n, 0))
	{
		sftbit(n, -1, n);
		fl = fl + (3 - fl * 2);
		fl %= 3;
		pow2 += 1;
	}

	while (n->len && (fl == 0))
	{
		subdiv(n, 3, n);
		fl = remain(n, 3);

		//cout << "pow " << powm << endl;

		pow3 += 1;
	}
	//cotnum(n, stdout);
	while (1)
	{
		//cotnum(n, stdout);
		++mc;
		POW2[mc] = pow2;
		POW3[mc] = pow3;
		if (n->len == 0)
			break;
		int pre_p2 = 0;
		int pre_p3 = 0;
		int tmp_p3 = 0;
		int tmp_p2 = 0;
		decr(n, 1, pre_n);
		flg = 0;
		if (pre_n->len == 0)
		{
			copy(pre_n, n);
			prm[mc] = -1;
			continue;
		}
		while (!mr_testbit(pre_n, 0) && pre_n->len)
		{
			sftbit(pre_n, -1, pre_n);
			pre_p2++;
		}
		fl = remain(pre_n, 3);
		while (pre_n->len && (fl == 0))
		{
			subdiv(pre_n, 3, pre_n);
			fl = remain(pre_n, 3);
			//cout << "pow " << powm << endl;
			pre_p3++;
		}

		for (int j = 0; j <= 1; j++)
		{
			for (int i = 1 - j; i < 4; i++)
			{
				tmp_p2 = tmp_p3 = 0;
				if (j == 0)
					incr(n, s[i], tmp_n);
				else
					incr(n, ps[i], tmp_n);
				if (tmp_n->len == 0)
				{
					pre_p2 = tmp_p2;
					pre_p3 = tmp_p3;
					flg = i;
					copy(tmp_n, pre_n);
					prm[mc] = s[i];
					break;
				}

				//if (compare(tmp_n, mirvar(0)) == -1)
					//continue;

				while (!mr_testbit(tmp_n, 0) && tmp_n->len)
				{
					sftbit(tmp_n, -1, tmp_n);
					tmp_p2++;
				}
				fl = remain(tmp_n, 3);
				while (tmp_n->len && (fl == 0))
				{
					subdiv(tmp_n, 3, tmp_n);
					fl = remain(tmp_n, 3);
					//cout << "pow " << powm << endl;
					tmp_p3++;
				}
				//cotnum(tmp_n, stdout);
				if (compare(pre_n, tmp_n) == 1)//!cpr2_3(pre_p2,pre_p3,tmp_p2,tmp_p3)
				{
					//printf("%d\n", s[i]);
					//int t = cpr2_3(pre_p2, pre_p3, tmp_p2, tmp_p3);
					//printf("%d\n", t);
					pre_p2 = tmp_p2;
					pre_p3 = tmp_p3;
					flg = i;
					copy(tmp_n, pre_n);
					//break;
				}
			}
			//printf("\n");
			premult(n, 2, n);
		}
		//printf("\n");
		copy(pre_n, n);
		//printf("%d ", mc);
		//cotnum(n, stdout);
		//printf("\n");
		//printf("\n");
		//printf("\n");
		pow2 += pre_p2;
		pow3 += pre_p3;
		prm[mc] = s[flg];

		//cout << "2^" << pow2 << "*" << "3" << "^" << pow3 << "+";

	}
	//printf("%d\n", pow3);
	//big cert = mirvar(0);
	//big tmpp = mirvar(0);
	//big twop = mirvar(0);
	//int t;
	//for (int i = mc - 1; i > 0; i--) {
		//printf("%d\n", POW2[i]);
		//expb2(POW2[i], twop);

		//multiply(pow3n[POW3[i]], twop, tmpp);
		//premult(tmpp, -1 * prm[i], tmpp);
		//cotnum(tmpp, stdout);
		//cotnum(tmpp, stdout);
		//add(cert, tmpp, cert);
		//printf("+ 2^%d*3^%d*(%d) ", POW2[i], POW3[i], prm[i]);

		//cotnum(cert, stdout);
	//}

	//expb2(POW2[0], twop);
	//multiply(pow3n[POW3[0]], twop, tmpp);

	//premult(tmpp, -prm[0], tmpp);


	//add(cert, tmpp, cert);
	//printf("+ 2^%d*3^%d*(%d)\n", POW2[0], POW3[0], prm[0]);

	//cotnum(cert, stdout);
	//cotnum(origin, stdout);

	* let = mc;
}

void span_dec_235(big n, short POW2[], short POW3[],short POW5[], short ISM[], short prm[], int* let) {
	big origin = mirvar(0);
	copy(n, origin);
	big pre_n = mirvar(0);
	big tmp_n = mirvar(0);

	int s[30] = { -1,+1,-7,+7,-11,+11 ,-13,+13,-17,+17,-19,+19,-23,23,-25,25,-29,29,-31,31,-35,35,-37,37,-41,41 };
	int fl = 0;
	int ff = 0;
	int flg = 0;
	//int POW2[256] = { 0 };
	//int POW3[256] = { 0 };
	//int POW5[256] = { 0 };
	//int ISM[256] = { 0 };
	//int prm[256] = { 0 };
	int mc = -1;
	int pow2 = 0;
	int pow3 = 0;
	int pow5 = 0;


	//printf("%d\n",fl);


	while (n->len && !mr_testbit(_MIPP_ n, 0))
	{
		sftbit(n, -1, n);
		pow2 += 1;
	}

	fl = remain(n, 3);
	while (n->len && (fl == 0))
	{
		subdiv(n, 3, n);
		fl = remain(n, 3);
		pow3 += 1;
	}

	ff = remain(n, 5);
	while (n->len && (ff == 0))
	{
		subdiv(n, 5, n);
		ff = remain(n, 5, n);
		pow5 += 1;
	}
	//cotnum(n, stdout);
	while (1)
	{
		//cotnum(n, stdout);
		++mc;
		POW2[mc] = pow2;
		POW3[mc] = pow3;
		POW5[mc] = pow5;
		if (n->len == 0)
			break;
		int pre_p2 = 0; int pre_p3 = 0; int pre_p5 = 0;
		int tmp_p2 = 0; int tmp_p3 = 0; int tmp_p5 = 0;
		decr(n, 1, pre_n);
		flg = 0;
		if (pre_n->len == 0)
		{
			copy(pre_n, n);
			prm[mc] = -1;
			continue;
		}

		// minus 1
		while (!mr_testbit(pre_n, 0) && pre_n->len)
		{
			sftbit(pre_n, -1, pre_n);
			pre_p2++;
		}
		fl = remain(pre_n, 3);
		while (pre_n->len && (fl == 0))
		{
			subdiv(pre_n, 3, pre_n);
			fl = remain(pre_n, 3);
			pre_p3++;
		}
		ff = remain(pre_n, 5);
		while (pre_n->len && (ff == 0))
		{
			subdiv(pre_n, 5, pre_n);
			ff = remain(pre_n, 5);
			pre_p5++;
		}

		for (int i = 1; i < 6; i++)
		{
			tmp_p2 = tmp_p3 = tmp_p5 = 0;
			incr(n, s[i], tmp_n);
			if (tmp_n->len == 0)
			{
				pre_p2 = tmp_p2;
				pre_p3 = tmp_p3;
				pre_p5 = tmp_p5;
				flg = i;
				copy(tmp_n, pre_n);
				prm[mc] = s[i];
				break;
			}

			//if (compare(tmp_n, mirvar(0)) == -1)
			//	continue;

			while (!mr_testbit(tmp_n, 0) && tmp_n->len)
			{
				sftbit(tmp_n, -1, tmp_n);
				tmp_p2++;
			}
			fl = remain(tmp_n, 3);
			while (tmp_n->len && (fl == 0))
			{
				subdiv(tmp_n, 3, tmp_n);
				fl = remain(tmp_n, 3);
				tmp_p3++;
			}
			ff = remain(tmp_n, 5);
			while (tmp_n->len && (ff == 0))
			{
				subdiv(tmp_n, 5, tmp_n);
				ff = remain(tmp_n, 5);
				tmp_p5++;
			}

			if (compare(pre_n, tmp_n) == 1)
			{
				pre_p2 = tmp_p2;
				pre_p3 = tmp_p3;
				pre_p5 = tmp_p5;
				flg = i;
				copy(tmp_n, pre_n);
				//break;
			}
		}

		copy(pre_n, n);
		pow2 += pre_p2;
		pow3 += pre_p3;
		pow5 += pre_p5;
		prm[mc] = s[flg];

	}
	//printf("%d\n", pow3);
	//big cert = mirvar(0);
	//big tmpp = mirvar(0);
	//big twop = mirvar(0);
	//int t;
	//for (int i = mc - 1; i > 0; i--) {
		//printf("%d\n", POW2[i]);
	//	expb2(POW2[i], twop);
	//	multiply(pow3n[POW3[i]], twop, tmpp);
	//	multiply(pow5n[POW5[i]], tmpp, twop);
	//	premult(twop, -1 * prm[i], twop);
	//	add(cert, twop, cert);
	//	printf("+ 2^%d*3^%d*5^%d*(%d) ", POW2[i], POW3[i], POW5[i],prm[i]);
	//}

	//expb2(POW2[0], twop);
	//multiply(pow3n[POW3[0]], twop, tmpp);
	//multiply(pow5n[POW5[0]], tmpp, twop);
	//premult(twop, -prm[0], twop);
	//add(cert, twop, cert);
	//printf("+ 2^%d*3^%d*5^%d*(%d)\n", POW2[0], POW3[0], POW5[0], prm[0]);

	//cotnum(cert, stdout);
	//cotnum(origin, stdout);

	* let = mc-1;
}

double cp2_3(int x, int y)
{
	double k = log2(3.0);
	return x + k * y;
}

void span_dec_23_double(big n, short sPOW2[], short sPOW3[], short sISM[], short sprm[], int* let) {
	//miracl* mip = mirsys(256, 2);
	//big ans = mirvar(0);
	big origin = mirvar(0);
	//big tmp = mirvar(0);
	copy(n, origin);
	big pr = mirvar(0);
	big ori_n[2] = { mirvar(0),mirvar(0) };
	big tmp_n = mirvar(0);
	big tmpl[2][6] = { 
		{mirvar(0),mirvar(0), mirvar(0),
		mirvar(0), mirvar(0), mirvar(0)},
		mirvar(0),mirvar(0), mirvar(0),
		mirvar(0), mirvar(0), mirvar(0) };

	int s[30] = { -1,+1,-5,+5,-7,+7,-11,+11 ,-13,+13,-17,+17,-19,+19,-23,23,-25,25,-29,29,-31,31,-35,35,-37,37,-41,41 };
	int fl = 0;
	int flg = 0;
	

	int POW2[2][256] = { 0 };
	int POW3[2][256] = { 0 };
	int ISM[2][256] = { 0 };
	int prm[2][256] = { 0 };
	int father[2][256] = { 0 };
	
	int mc = -1;
	int pow2 = 0;
	int pow3 = 0;
	fl = remain(n, 3);
	heap H[2];
	H[0] = (heap)malloc(sizeof(Myheap));
	H[1] = (heap)malloc(sizeof(Myheap));
	heap_init(H[0]);
	heap_init(H[1]);


	//printf("%d\n",fl);
	

	while (n->len && !mr_testbit(_MIPP_ n, 0))
	{
		sftbit(n, -1, n);
		fl = fl + (3 - fl * 2);
		fl %= 3;
		pow2 += 1;
	}

	while (n->len && (fl == 0))
	{
		subdiv(n, 3, n);
		fl = remain(n, 3);

		//cout << "pow " << powm << endl;

		pow3 += 1;
	}
	++mc;
	POW2[0][mc] = pow2;
	POW2[1][mc] = pow2;
	POW3[0][mc] = pow3;
	POW3[1][mc] = pow3;
	
	int pre_p2 = 0;
	int pre_p3 = 0;
	int tmp_p3 = 0;
	int tmp_p2 = 0;
	double val;
	Etag e;
	for (int i = 0; i < 6; i++)
	{
		pre_p2 = pre_p3 = tmp_p3 = tmp_p2 = 0;
		incr(n, s[i], tmpl[0][i]);
		if (tmpl[0][i]->len == 0)
		{
			e.t = i;
			e.father = 0;
			e.pow2 = 0;
			e.pow3 = 0;
			heap_push(H[0], e, 2000);
			break;
		}

		while (!mr_testbit(tmpl[0][i], 0) && tmpl[0][i]->len)
		{
			sftbit(tmpl[0][i], -1, tmpl[0][i]);
			tmp_p2++;
		}
		fl = remain(tmpl[0][i], 3);
		while (tmpl[0][i]->len && (fl == 0))
		{
			subdiv(tmpl[0][i], 3, tmpl[0][i]);
			fl = remain(tmpl[0][i], 3);
			//cout << "pow " << powm << endl;
			tmp_p3++;
		}
		e.t = i;
		e.father = 0;
		e.pow2 = tmp_p2;
		e.pow3 = tmp_p3;
		val=cp2_3(tmp_p2, tmp_p3);
		heap_push(H[0],e, val);
	}
	
	//heap_print(H);
	Node tg = heap_pop(H[0]);
	if (tg.val == 2000)
	{
		++mc;
		sPOW2[mc] = pow2;
		sPOW3[mc] = pow3;
		sprm[mc] = s[tg.tag.t];
		return;
	}
	else
	{
		++mc;
		copy(tmpl[0][tg.tag.t], ori_n[0]);
		POW2[0][mc] = tg.tag.pow2;
		POW3[0][mc] = tg.tag.pow3;
		prm[0][mc] = s[tg.tag.t];
		father[0][mc] = 0;
		tg = heap_pop(H[0]);
		copy(tmpl[0][tg.tag.t], ori_n[1]);
		POW2[1][mc] = tg.tag.pow2;
		POW3[1][mc] = tg.tag.pow3;
		prm[1][mc] = s[tg.tag.t];
		father[1][mc] = 1;
	}

	//cout << "2^" << pow2 << "*" << "3" << "^" << pow3 << "+";

	//cotnum(n, stdout);
	int flgg = 0;
	while (1)
	{
		//cotnum(ori_n[0], stdout);
		//cotnum(ori_n[1], stdout);
		//printf("\n");
		if (ori_n[0]->len == 0) {
			flgg = 0;
			break;
		}
		else if (ori_n[1]->len == 0) {
			flgg = 1;
			break;
		}
		heap_clear(H[0]);
		heap_clear(H[1]);
		for (int sk = 0; sk < 2; sk++) {
			for (int i = 0; i < 2; i++)
			{
				pre_p2 = pre_p3 = tmp_p3 = tmp_p2 = 0;
				incr(ori_n[sk], s[i], tmpl[sk][i]);
				if (tmpl[sk][i]->len == 0)
				{
					e.t = i;
					e.father = sk;
					e.pow2 = 0;
					e.pow3 = 0;
					heap_push(H[sk], e, 2000.0);
					break;
				}
				while (!mr_testbit(tmpl[sk][i], 0) && tmpl[sk][i]->len)
				{
					sftbit(tmpl[sk][i], -1, tmpl[sk][i]);
					tmp_p2++;
				}
				fl = remain(tmpl[sk][i], 3);
				while (tmpl[sk][i]->len && (fl == 0))
				{
					subdiv(tmpl[sk][i], 3, tmpl[sk][i]);
					fl = remain(tmpl[sk][i], 3);
					tmp_p3++;
				}
				e.t = i;
				e.father = sk;
				e.pow2 = tmp_p2;
				e.pow3 = tmp_p3;
				val = cp2_3(tmp_p2, tmp_p3);
				heap_push(H[sk], e, val);
			}
		}
		//heap_print(H);
		++mc;
		Node tg1, tg2,tp;
		//printf("%d %d\n", H[0]->len, H[1]->len);
		tg1 = heap_pop(H[0]);
		tg2 = heap_pop(H[1]);
		
		if (tg2.val < 2000 && tg1.val < 2000) {
			if (compare(tmpl[tg1.tag.father][tg1.tag.t], tmpl[tg2.tag.father][tg2.tag.t]) == 1)
			{
				tp = heap_pop(H[1]);
				if (compare(tmpl[tg1.tag.father][tg1.tag.t], tmpl[tp.tag.father][tp.tag.t]) == 1)
				{
					tg1 = tp;
				}
			}
			else if (compare(tmpl[tg1.tag.father][tg1.tag.t], tmpl[tg2.tag.father][tg2.tag.t]) == -1)
			{
				tp = heap_pop(H[0]);
				if (compare(tmpl[tg2.tag.father][tg2.tag.t], tmpl[tp.tag.father][tp.tag.t]) == 1)
				{
					tg2 = tp;
				}

			}
			else {
				tp = heap_pop(H[0]);
				tg2 = heap_pop(H[1]);
				if (compare(tmpl[tg2.tag.father][tg2.tag.t], tmpl[tp.tag.father][tp.tag.t]) == 1)
				{
					tg2 = tp;
				}
			}
		}

		copy(tmpl[tg1.tag.father][tg1.tag.t], ori_n[0]);
		POW2[0][mc] = tg1.tag.pow2;
		POW3[0][mc] = tg1.tag.pow3;
		prm[0][mc] = s[tg1.tag.t];
		father[0][mc] = tg1.tag.father;
	
		copy(tmpl[tg2.tag.father][tg2.tag.t], ori_n[1]);
		POW2[1][mc] = tg2.tag.pow2;
		POW3[1][mc] = tg2.tag.pow3;
		prm[1][mc] = s[tg2.tag.t];
		father[1][mc] = tg2.tag.father;

		

		//cout << "2^" << pow2 << "*" << "3" << "^" << pow3 << "+";

	}

	int pre = flgg;
	flgg = father[flgg][mc];
	int ll = mc-1;
	pow2 = pow3 = 0;
	while (ll >= 0)
	{
		sPOW2[ll] = POW2[flgg][ll];
		sPOW3[ll] = POW3[flgg][ll];
		sprm[ll] = prm[pre][ll+1];
		pre = flgg;
		flgg = father[flgg][ll];
		//printf("%d : %d  %d  %d\n", ll, sPOW2[ll], sPOW3[ll], -sprm[ll]);
		ll--;
	}
	ll = 0;
	while (ll < mc)
	{
		pow2 += sPOW2[ll];
		pow3 += sPOW3[ll];
		sPOW2[ll] = pow2;
		sPOW3[ll] = pow3;
		//printf("%d : %d  %d  %d\n", ll, sPOW2[ll], sPOW3[ll], -sprm[ll]);
		ll++;
	}

	//printf("%d\n", pow3);
	/*big cert = mirvar(0);
	//big tmpp = mirvar(0);
	//big twop = mirvar(0);
	//int t;
	//for (int i = mc - 1; i > 0; i--) {
		//printf("%d\n", POW2[i]);
		//expb2(sPOW2[i], twop);

		//multiply(pow3n[sPOW3[i]], twop, tmpp);
		//premult(tmpp, -sprm[i], tmpp);
		//cotnum(tmpp, stdout);
		//cotnum(tmpp, stdout);
		//add(cert, tmpp, cert);
		//printf("+ 2^%d*3^%d*(%d) ", sPOW2[i], sPOW3[i], -sprm[i]);

		//cotnum(cert, stdout);
	//}

	//expb2(sPOW2[0], twop);
	//multiply(pow3n[sPOW3[0]], twop, tmpp);

	//premult(tmpp, -sprm[0], tmpp);


	//add(cert, tmpp, cert);
	//printf("+ 2^%d*3^%d*(%d)\n", sPOW2[0], sPOW3[0], -sprm[0]);

	//cotnum(cert, stdout);
	//cotnum(origin, stdout);
	//let[0] = mc;
	//let[1] = POW2[mc - 1];
	//let[2] = POW3[mc - 1];
	*let = mc;
}*/
