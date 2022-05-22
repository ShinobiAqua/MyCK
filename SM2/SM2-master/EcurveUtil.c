#include <stdio.h>
#include <stdlib.h>
#include "miracl.h"

#define  uint unsigned int

big pow3n[256];
int lsp[1000] ;
int W2BT3[500] ;
int W3BT2[500] ;

void ttd10(_MIPD_ big n, short POW2[], short POW3[], short ISM[], int* let) {
	//miracl* mip = mirsys(256, 2);
	//big ans = mirvar(0);
	//big origin = mirvar(0);
	//big tmp = mirvar(0);
	//copy(n, origin);
	//big origin = n;
	/*big mp = mirvar(0);
	big ap = mirvar(0);
	big mn = mirvar(0);
	big an = mirvar(0);*/
	int fl = 0;
	/*int POW2[256] = { 0 };
	int POW3[256] = { 0 };
	int ISM[256] = { 0 };*/
	int mc = -1;
	int pow2 = 0;
	int pow3 = 0;
	//fl = remain(n, 3);
	//printf("%d\n",fl);
	//int fl2;



	while (1)
	{
		//cotnum(n, stdout);

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
		++mc;
		POW2[mc] = pow2;
		POW3[mc] = pow3;
		if (n->len == 0)
			break;
		/*if (mr_testbit(_MIPP_ n, 1) == 0)
		{
			if (mr_testbit(_MIPP_ n, 2) == 0)
			{
				decr(n, 1, n);
			}
			else if (fl == 2) {
				fl2 = remain(n, 9);
				if (fl2 == 20) {
					incr(n, 1, n);
					ISM[mc] = 1;
				}
				else
					decr(n, 1, n);
			}
			else {
				decr(n, 1, n);
			}
		}
		else {
			if (mr_testbit(_MIPP_ n, 2) == 1)
			{
				incr(n, 1, n);
				ISM[mc] = 1;
			}
			else if (fl == 2) {
				incr(n, 1, n);
				ISM[mc] = 1;
			}
			else {
				fl2 = remain(n, 9);
				if(fl2==1)
					decr(n, 1, n);
				else {
					incr(n, 1, n);
					ISM[mc] = 1;
				}
			}
		}
		*/
		
		if (fl == 2)
		{
			if (mr_testbit(_MIPP_ n, 1) == 0 && mr_testbit(_MIPP_ n, 2) == 0 && mr_testbit(_MIPP_ n, 3) == 0)
			{
				decr(n, 1, n);
				sftbit(n, -4, n);
				pow2 += 4;
			}
			else
			{
				incr(n, 1, n);
				ISM[mc] = 1;
			}
		}
		else
		{

			if (mr_testbit(_MIPP_ n, 1) == 1 && mr_testbit(_MIPP_ n, 2) == 1 && mr_testbit(_MIPP_ n, 3) == 1)
			{
				incr(n, 1, n);
				ISM[mc] = 1;
				sftbit(n, -4, n);
				pow2 += 4;
			}
			else
			{
				decr(n, 1, n);
			}
		}




		//cout << "2^" << pow2 << "*" << "3" << "^" << pow3 << "+";

	}
	*let = mc-1;
	//printf("%d\n", pow3);
	/*big cert = mirvar(0);
	big tmpp = mirvar(0);
	big twop = mirvar(0);
	for (int i = mc-1; i > 0; i--) {

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
	}


	expb2(POW2[0], twop);
	multiply(pow3n[POW3[0]], twop, tmpp);
	if (ISM[0]) {
		subtract(cert, tmpp, cert);
		printf("- 2^%d*3^%d\n ", POW2[0], POW3[0]);
	}
	else {
		add(cert, tmpp, cert);
		printf("+ 2^%d*3^%d\n", POW2[0], POW3[0]);
	}
	cotnum(cert, stdout);
	cotnum(origin, stdout);*/

	//printf("10:  %d\n", mc);


}

void brandnew_Joker(big n, short POW2[], short POW3[], short ISM[], int* let) {
	//miracl* mip = mirsys(256, 2);
	//big ans = mirvar(0);
	big origin = mirvar(0);
	//big tmp = mirvar(0);
	copy(n, origin);
	//big origin = n;
	/*big mp = mirvar(0);
	big ap = mirvar(0);
	big mn = mirvar(0);
	big an = mirvar(0);*/
	int fl = 0;
	/*int POW2[256] = { 0 };
	int POW3[256] = { 0 };
	int ISM[256] = { 0 };*/
	int mc = -1;
	int pow2 = 0;
	int pow3 = 0;
	//fl = remain(n, 3);
	big tmp = mirvar(0);
	//printf("%d\n",fl);




	while (1)
	{
		//cotnum(n, stdout);

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
	tag1:
		++mc;
		POW2[mc] = pow2;
		POW3[mc] = pow3;
		if (n->len == 0)
			break;

		if (fl == 2)
		{
			if (mr_testbit(_MIPP_ n, 1) == 0 && mr_testbit(_MIPP_ n, 2) == 0)
			{
				int k;
				k = remain(n, 9);
				if (k != 8)
				{
					decr(n, 1, n);
				}
				else
				{
					int tp2, tp3;
					tp2 = tp3 = 0;
					incr(n, 1, tmp);
					decr(n, 1, n);
					sftbit(n, -3, n);
					sftbit(tmp, -1, tmp);
					tp2 += 2;
					while (!mr_testbit(n, 0))
					{
						sftbit(n, -1, n);
						tp2++;
					}
					tp3 = W3BT2[tp2];
					for (int i = 0; i < tp3; i++)
					{
						fl = subdiv(tmp, 3, tmp);
						if (fl != 0)
							break;
						tp3--;
					}
					if (tp3 != 0)
					{
						pow2 = pow2 + tp2 + 1;
						fl = 1;
						goto tag1;
					}
					else {
						ISM[mc] = 1;
						tp3 = W3BT2[tp2];
						fl = remain(tmp, 3);
						while (fl == 0)
						{
							subdiv(tmp, 3, tmp);
							fl = remain(tmp, 3);
							tp3++;
						}
						copy(tmp, n);
						pow3 += tp3;
						pow2 += 1;
						goto tag1;
					}

				}
			}
			else
			{
				incr(n, 1, n);
				ISM[mc] = 1;
			}
		}
		else
		{

			if (mr_testbit(_MIPP_ n, 1) == 1 && mr_testbit(_MIPP_ n, 2) == 1)
			{
				int k;
				k = remain(n, 9);
				if (k != 1)
				{
					incr(n, 1, n);
					ISM[mc] = 1;
				}
				else
				{
					int tp2, tp3;
					tp2 = tp3 = 0;
					decr(n, 1, tmp);
					incr(n, 1, n);
					sftbit(n, -3, n);
					sftbit(tmp, -1, tmp);
					tp2 += 2;
					while (!mr_testbit(n, 0))
					{
						sftbit(n, -1, n);
						tp2++;
					}
					tp3 = W3BT2[tp2];
					for (int i = 0; i < tp3; i++)
					{
						fl = subdiv(tmp, 3, tmp);
						if (fl != 0)
							break;
						tp3--;
					}
					if (tp3 != 0)
					{
						pow2 = pow2 + tp2 + 1;
						fl = 2;
						ISM[mc] = 1;
						goto tag1;
					}
					else {
						tp3 = W3BT2[tp2];
						fl = remain(tmp, 3);
						while (fl == 0)
						{
							subdiv(tmp, 3, tmp);
							fl = remain(tmp, 3);
							tp3++;
						}
						copy(tmp, n);
						pow3 += tp3;
						pow2 += 1;
						goto tag1;
					}
				}
			}
			else
			{
				decr(n, 1, n);
			}
		}



		//cout << "2^" << pow2 << "*" << "3" << "^" << pow3 << "+";

	}
	//printf("%d\n", pow3);
	/*big cert = mirvar(0);
	big tmpp = mirvar(0);
	big twop = mirvar(0);
	for (int i = mc-1; i > 0; i--) {

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
	}


	expb2(POW2[0], twop);
	multiply(pow3n[POW3[0]], twop, tmpp);
	if (ISM[0]) {
		subtract(cert, tmpp, cert);
		printf("- 2^%d*3^%d\n ", POW2[0], POW3[0]);
	}
	else {
		add(cert, tmpp, cert);
		printf("+ 2^%d*3^%d\n", POW2[0], POW3[0]);
	}
	cotnum(cert, stdout);
	cotnum(origin, stdout);*/
	mirkill(tmp);
	* let = mc-1;
	//printf("10:  %d\n", mc);


}

void ttd6(big n, short POW2[], short POW3[], short ISM[], int* let) {
	//miracl* mip = mirsys(256, 2);
	//big ans = mirvar(0);
	big origin = mirvar(0);
	//big tmp = mirvar(0);
	copy(n, origin);
	//big origin = n;
	big mp = mirvar(0);
	big ap = mirvar(0);
	big mn = mirvar(0);
	big an = mirvar(0);
	int fl = 0;
	/*int POW2[256] = { 0 };
	int POW3[256] = { 0 };
	int ISM[256] = { 0 };*/
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

	while (n->len == 1 && (fl == 0))
	{
		subdiv(n, 3, n);
		fl = remain(n, 3);

		//cout << "pow " << powm << endl;

		pow3 += 1;
	}

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
		if (mr_compare(mn, an) == 1)
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
		cotnum(cert, stdout);
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

	* let = mc-1;
}
void ttd6_plus_plus(big n, short POW2[], short POW3[], short ISM[], short prm[] ,int* let) {
	//miracl* mip = mirsys(256, 2);
	//big ans = mirvar(0);
	//big origin = mirvar(0);
	//big tmp = mirvar(0);
	//copy(n, origin);
	//big origin = n;
	/*big pre_mn = mirvar(0);
	big pre_an = mirvar(0);
	big mn = mirvar(0);
	big an = mirvar(0);*/
	big pre_n = mirvar(0);
	big tmp_n = mirvar(0);

	int s[10] = { -1,+1,-5 ,+5,-7,+7,-11,+11 ,-13,+13 };
	//int s[10] = { -1,+1,-13,+13,-11,+11,-7,+7 ,-5,+5 };
	int fl = 0;
	int flg = 0;
	
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

			/*if (mr_compare(tmp_n, mirvar(0)) == -1)
				continue;*/

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
			if (mr_compare(pre_n, tmp_n) == 1)
			{
				//printf("%d\n", s[i]);
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
	/*big cert = mirvar(0);
	big tmpp = mirvar(0);
	big twop = mirvar(0);
	int t;
	for (int i = mc-1; i > 0; i--) {
		//printf("%d\n", POW2[i]);
		expb2(POW2[i],twop);

		multiply(pow3n[POW3[i]], twop, tmpp);
		premult(tmpp, -1 * prm[i], tmpp);
		//cotnum(tmpp, stdout);
		//cotnum(tmpp, stdout);
		add(cert, tmpp, cert);
		printf("+ 2^%d*3^%d*(%d) ", POW2[i], POW3[i],prm[i]);

		//cotnum(cert, stdout);
	}

	expb2(POW2[0], twop);
	multiply(pow3n[POW3[0]], twop, tmpp);

	premult(tmpp, -prm[0], tmpp);


	add(cert, tmpp, cert);
	printf("+ 2^%d*3^%d*(%d)\n", POW2[0], POW3[0], prm[0]);

	cotnum(cert, stdout);
	cotnum(origin, stdout);
	*/
	* let = mc - 1;
}

void new_ttd6_plus(big n, short POW2[], short POW3[], short ISM[], short prm[], int* let) {
	//miracl* mip = mirsys(256, 2);
	//big ans = mirvar(0);
	//big origin = mirvar(0);
	//big tmp = mirvar(0);
	//copy(n, origin);
	//big origin = n;
	/*big pre_mn = mirvar(0);
	big pre_an = mirvar(0);
	big mn = mirvar(0);
	big an = mirvar(0);*/
	big tmp1 = mirvar(0);
	big tmp2 = mirvar(0);

	int s[7] = { 0,-1,+1,-5 ,+5,-7,+7 };
	int sp2[6] = { 0 };
	int sp3[6] = { 0 };
	int ss16[16][7] = { 0 };
	int ss9[9][7] = { 0 };
	double lg23 = log2(3.0);
	for (int i = 0; i < 16; i++)
	{
		int k = 32;
		k = k + i;
		//ss16[i][0] = i;
		int mx = 0;
		int tg = 0;
		for (int j = 1; j < 7; j++)
		{
			int t = k + s[j];
			while (t % 2 == 0) {
				ss16[i][j]++;
				t /= 2;
			}
			if (ss16[i][j] > mx)
			{
				mx = ss16[i][j];
				tg = j;
			}
		}
		ss16[i][0] = tg;
	}
	for (int i = 0; i < 9; i++)
	{
		int k = 27;
		k += i;
		int mx = 0;
		int tg = 0;
		for (int j = 1; j < 7; j++)
		{
			int t = k + s[j];
			while (t % 3 == 0) {
				ss9[i][j]++;
				t /= 3;
			}
			if (ss9[i][j] > mx)
			{
				mx = ss9[i][j];
				tg = j;
			}
		}
		ss9[i][0] = tg;

	}
	/*for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 7; j++)
			printf("%d ", ss9[i][j]);
		printf("\n");
	}*/
	//int s[10] = { -1,+1,-13,+13,-11,+11,-7,+7 ,-5,+5 };

	int fl = 0;
	int fk = 0;
	int fs = 0;
	//int flg = 0;
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

		fs = remain(n, 9);
		fk = remain(n, 16);
		int t2 = ss16[fk][0];
		int t3 = ss9[fs][0];
		if (t2 == t3)
		{
			incr(n, s[t3], n);
			subdiv(n, 3, n);
			subdiv(n, 3, n);
			pow3 += 2;
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
			prm[mc] = s[t3];
			continue;
		}

		incr(n, s[t3], tmp1);
		incr(n, s[t2], tmp2);
		int tp2 = 0;
		int tp3 = 2;
		while (tmp2->len && !mr_testbit(_MIPP_ tmp2, 0))
		{
			sftbit(tmp2, -1, tmp2);
			tp2 += 1;
		}
		ss16[fk][t2] = tp2;
		subdiv(tmp1, 3, tmp1);
		subdiv(tmp1, 3, tmp1);
		fl = remain(tmp1, 3);
		while (tmp1->len && (fl == 0))
		{
			subdiv(tmp1, 3, tmp1);
			fl = remain(tmp1, 3);
			tp3 += 1;
		}
		ss9[fs][t3] = tp3;
		int flg = 0;
		double mx = 0;
		for (int i = 1; i < 7; i++)
		{
			double ttp = ss16[fk][i] + ss9[fs][i] * lg23;
			if (ttp > mx)
			{
				mx = ttp;
				flg = i;
			}
		}
		if (s[flg] == t3)
		{
			copy(tmp1, n);
			prm[mc] = s[t3];
			pow3 += tp3;
		}
		else {
			incr(n, s[flg], n);
			prm[mc] = s[flg];
			fl = remain(n, 3);
		}
		while (n->len && !mr_testbit(_MIPP_ n, 0))
		{
			sftbit(n, -1, n);
			pow2 += 1;
		}

		while (n->len && (fl == 0))
		{
			subdiv(n, 3, n);
			fl = remain(n, 3);
			pow3 += 1;
		}


	}
	//printf("%d\n", pow3);
	/*big cert = mirvar(0);
	big tmpp = mirvar(0);
	big twop = mirvar(0);
	int t;
	for (int i = mc-1; i > 0; i--) {
		//printf("%d\n", POW2[i]);
		expb2(POW2[i],twop);

		multiply(pow3n[POW3[i]], twop, tmpp);
		premult(tmpp, -1 * prm[i], tmpp);
		//cotnum(tmpp, stdout);
		//cotnum(tmpp, stdout);
		add(cert, tmpp, cert);
		printf("+ 2^%d*3^%d ", POW2[i], POW3[i]);

		//cotnum(cert, stdout);
	}

	expb2(POW2[0], twop);
	multiply(pow3n[POW3[0]], twop, tmpp);

	premult(tmpp, -prm[0], tmpp);


	add(cert, tmpp, cert);
	printf("+ 2^%d*3^%d\n", POW2[0], POW3[0]);

	cotnum(cert, stdout);
	cotnum(origin, stdout);*/

	* let = mc - 1;
}
void ttd6_plus(big n, short POW2[], short POW3[], short ISM[], short prm[],int* let) {
	//miracl* mip = mirsys(256, 2);
	//big ans = mirvar(0);
	big origin = mirvar(0);
	//big tmp = mirvar(0);
	copy(n, origin);
	//big origin = n;
	big mp = mirvar(0);
	big ap = mirvar(0);
	big mn = mirvar(0);
	big an = mirvar(0);

	//	big mp_5 = mirvar(0);
	//	big ap_5 = mirvar(0);
	big mn_5 = mirvar(0);
	big an_5 = mirvar(0);

	int fl = 0;
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

	while (n->len == 1 && (fl == 0))
	{
		subdiv(n, 3, n);
		fl = remain(n, 3);

		//cout << "pow " << powm << endl;

		pow3 += 1;
	}

	while (1)
	{
		//cotnum(n, stdout);
		++mc;
		POW2[mc] = pow2;
		POW3[mc] = pow3;
		if (n->len == 0)
			break;
		/*if (compare(n, mirvar(5)) == 0||compare(n,mirvar(1))==0)
		{

			mc++;
			break;
		}*/

		/*mp = mirvar(1);
		ap = mirvar(1);*/
		int mpow2, mpow3, apow2, apow3;
		int mf, af;

		int mpow2_5, mpow3_5, apow2_5, apow3_5;
		int mf_5, af_5;

		mf = (fl + 2) % 3;
		af = (fl + 1) % 3;
		mf_5 = (fl + 1) % 3;
		af_5 = (fl + 2) % 3;
		mpow2 = mpow3 = apow2 = apow3 = 0;
		mpow2_5 = mpow3_5 = apow2_5 = apow3_5 = 0;
		decr(n, 1, mn);
		incr(n, 1, an);
		if (mr_compare(n, mirvar(5)) == 1) {
			decr(n, 5, mn_5);
			incr(n, 5, an_5);
		}

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


		if (mr_compare(n, mirvar(6)) == -1)
			goto tag3;

		while (mn_5->len && !mr_testbit(_MIPP_ mn_5, 0))
		{
			sftbit(mn_5, -1, mn_5);
			mf_5 = mf_5 + (3 - mf_5 * 2);
			mf_5 %= 3;
			mpow2_5 += 1;
			//sftbit(mp, 1, mp);
		}

		while (mn_5->len && (mf_5 == 0))
		{
			subdiv(mn_5, 3, mn_5);
			mf_5 = remain(mn_5, 3);
			mpow3_5 += 1;
			//premult(mp, 3, mp);
		}


		while (an_5->len && !mr_testbit(_MIPP_ an_5, 0))
		{
			sftbit(an_5, -1, an_5);
			af_5 = af_5 + (3 - af_5 * 2);
			af_5 %= 3;
			apow2_5 += 1;
			//sftbit(ap, 1, ap);
		}

		while (an_5->len && (af_5 == 0))
		{
			subdiv(an_5, 3, an_5);
			af_5 = remain(an_5, 3);
			apow3_5 += 1;
			//premult(ap, 3, ap);
		}


		/*if (compare(mn, an) == 1)
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
		}*/
	tag3:
		if (mr_compare(mn, an) == 1)
		{
			if (mr_compare(an, an_5) == 1)
			{
				copy(an_5, n);
				fl = af_5;
				pow2 += apow2_5;
				pow3 += apow3_5;
				ISM[mc] = 1;
				prm[mc] = 5;
			}
			else
			{
				copy(an, n);
				fl = af;
				pow2 += apow2;
				pow3 += apow3;
				ISM[mc] = 1;
			}
		}
		else
		{
			if (mr_compare(mn, mn_5) == 1)
			{
				copy(mn_5, n);
				fl = mf_5;
				pow2 += mpow2_5;
				pow3 += mpow3_5;
				prm[mc] = 5;
			}
			else {
				copy(mn, n);
				fl = mf;
				pow2 += mpow2;
				pow3 += mpow3;
			}
		}

		//cout << "2^" << pow2 << "*" << "3" << "^" << pow3 << "+";

	}
	//printf("%d\n", pow3);
	/*big cert = mirvar(0);
	big tmpp = mirvar(0);
	big twop = mirvar(0);
	for (int i = mc - 1; i > 1; i--) {

		expb2(POW2[i], twop);
		multiply(pow3n[POW3[i]], twop, tmpp);
		if (prm[i] == 5)
			premult(tmpp, 5, tmpp);
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
	if (prm[1] == 5)
		premult(tmpp, 5, tmpp);
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
	
	*let = mc - 1;
}


void Decompose(_MIPD_ big n, short POW2[], short POW3[], short ISM[], int* let) {
	
	big myb[3];//用来储存+1后的大数临时值  -1后的大数临时值  和处理时中间结果
	//W2B3 意思是witch 2 is bigger than 3 就是2的几次大于当前的3幂次数  这个值通过W2B3[]这个数组取得，比如W2B3[3]的意思是 2的最小几次能大于3的3次
	int W2B3, W3B2;
	int npow2 = 1;
	int npow3 = 1;
	uint flg = 0;
	myb[0] = mirvar(0);
	myb[1] = mirvar(0);
	myb[2] = mirvar(0);
	copy(n, myb[0]);

	int fl = 0;//fl是模3后的余数
	int mc = -1;
	int pow2 = 0;
	int pow3 = 0;
	int id = 0;
	// myb[lid]是-1后的大数临时值   myb[rid]是+1后的临时大数值   myb[id]是当前处理的中间结果 myb[lid]=myb[id]-1,myb[rid]=myb[id]+1
	// 之所以用这种复杂的写法是为了减少过多的复制。  
	int lid, rid;

	int m4;
	fl = remain(myb[id], 3);
	while ((myb[id]->len) && !mr_testbit(_MIPP_ myb[id], 0))//一直除2除到不能除
	{
		sftbit(myb[id], -1, myb[id]);
		//一个数除2后模3余多少可以通过fl直接算出
		fl = fl + (3 - fl * 2);
		fl %= 3;
		pow2 += 1;
	}
	while ((myb[id]->len) && (fl == 0))//一直除3除到不能除
	{
		subdiv(myb[id], 3, myb[id]);
		fl = remain(myb[id], 3);
		pow3 += 1;
	}

	while (1)
	{
		m4 = mr_testbit(_MIPP_ myb[id], 1);
		++mc;
		POW2[mc] = pow2;
		POW3[mc] = pow3;
		lid = (id + 2) % 3;
		rid = (id + 1) % 3;
		/*if (mr_compare(n, mirvar(1)) == 0)
			break;*/
		if (fl == 1)
		{
			if (!m4)//3进制-1 好  2进制-1 好
			{
				decr(myb[id], 1, myb[id]);
				fl = (fl - 1) % 3;
				if (!myb[id]->len)   //这里是判断-1后是否为0  为0就退出循环了
					break;
				while ((myb[id]->len) && !mr_testbit(_MIPP_ myb[id], 0))
				{
					sftbit(myb[id], -1, myb[id]);
					fl = fl + (3 - fl * 2);
					fl %= 3;
					pow2 += 1;
				}

				while ((myb[id]->len) && (fl == 0))
				{
					subdiv(myb[id], 3, myb[id]);
					fl = remain(myb[id], 3);
					pow3 += 1;
				}
			}
			else//3进制-1 好 2进制+1 好
			{
				//本来应该是+1后最少被2的2次除    -1后最少被2*3除
				//为了可以让+1后只除2与-1后只除3比较
				//这里同时除以了2
				//所以是比较+1后除以2的数 与 -1后除以2的数  哪个能够除的数大
				//这时候变成一方至少被一个2除，另一方至少被一个3除
				//所以这里npow2=1,npow3=1。
				npow2 = 1;
				npow3 = 1;
				flg = 0;
				decr(myb[id], 1, myb[lid]);
				incr(myb[id], 1, myb[rid]);
				sftbit(myb[rid], -2, myb[rid]);
				sftbit(myb[lid], -1, myb[lid]);
				subdiv(myb[lid], 3, myb[lid]);
				W2B3 = W2BT3[1];
				W3B2 = W3BT2[1];
				while (1) {
					//flg用于判断当前是在除2还是除3
					if (!flg) {
						if (!mr_testbit(_MIPP_ myb[rid], 0))//试着除一个2
						{
							sftbit(myb[rid], -1, myb[rid]);
							npow2++;
							if (npow2 >= W2B3)//如果这时候比除3的那边除的要多了
							{
								flg = !flg;//就反转flg  转到除3的那边
								W3B2 = W3BT2[npow2];
							}
						}
						else {// 否则，也就是说不能再通过除以2使得被除的数大于除3的那一边了，这时候直接选择除3的那一边对应的-1
							
							id = (id + 2) % 3;//这里是因为lid在id的逆时针边，rid在id的顺时针边   即可能是 lid=0 id=1 rid=2| id=0 rid=1 lid=2 |  rid=0 lid=1 id=2
							pow2 += 1;
							pow3 += npow3;
							fl = remain(myb[id], 3);
							while ((myb[id]->len) && (fl == 0))
							{
								subdiv(myb[id], 3, myb[id]);
								fl = remain(myb[id], 3);
								pow3 += 1;
							}
							break;
						}

					}
					else {
						if (subdivisible(myb[lid], 3))
						{
							subdiv(myb[lid], 3, myb[lid]);
							npow3++;
							if (npow3 >= W3B2)
							{
								flg = !flg;
								W2B3 = W2BT3[npow3];
							}
						}
						else {
							//copy(myb[rid], myb[id]);
							id = (id + 1) % 3;
							pow2 += npow2 + 1;
							fl = remain(myb[id], 3);
							while ((myb[id]->len) && !mr_testbit(_MIPP_ myb[id], 0))
							{
								sftbit(myb[id], -1, myb[id]);
								fl = fl + (3 - fl * 2);
								fl %= 3;
								pow2 += 1;
							}
							ISM[mc] = 1;
							break;
						}
					}
				}
			}
		}
		else
		{
			if (m4)//3进制+1 好  2进制+1 好
			{
				incr(myb[id], 1, myb[id]);
				ISM[mc] = 1;
				fl = (fl + 1) % 3;
				while ((myb[id]->len) && !mr_testbit(_MIPP_ myb[id], 0))
				{
					sftbit(myb[id], -1, myb[id]);
					fl = fl + (3 - fl * 2);
					fl %= 3;
					pow2 += 1;
				}

				while ((myb[id]->len) && (fl == 0))
				{
					subdiv(myb[id], 3, myb[id]);
					fl = remain(myb[id], 3);
					pow3 += 1;
				}
			}
			else//3进制+1 好  2进制-1 好
			{
				npow2 = 1;
				npow3 = 1;
				flg = 0;
				decr(myb[id], 1, myb[lid]);
				incr(myb[id], 1, myb[rid]);
				sftbit(myb[lid], -2, myb[lid]);
				sftbit(myb[rid], -1, myb[rid]);
				subdiv(myb[rid], 3, myb[rid]);
				W2B3 = W2BT3[1];
				W3B2 = W3BT2[1];
				while (1) {
					if (!flg) {
						if (!mr_testbit(_MIPP_ myb[lid], 0))
						{
							sftbit(myb[lid], -1, myb[lid]);
							npow2++;
							if (npow2 >= W2B3)
							{
								flg = !flg;
								W3B2 = W3BT2[npow2];
							}
						}
						else {
							//copy(myb[rid], myb[id]);
							id = (id + 1) % 3;
							pow2 += 1;
							pow3 += npow3;
							fl = remain(myb[id], 3);
							while ((myb[id]->len) && (fl == 0))
							{
								subdiv(myb[id], 3, myb[id]);
								fl = remain(myb[id], 3);
								pow3 += 1;
							}
							ISM[mc] = 1;
							break;
						}

					}
					else {
						if (subdivisible(myb[rid], 3))
						{
							subdiv(myb[rid], 3, myb[rid]);
							npow3++;
							if (npow3 >= W3B2)
							{
								flg = !flg;
								W2B3 = W2BT3[npow3];
							}
						}
						else {
							//copy(myb[lid], myb[id]);
							id = (id + 2) % 3;
							pow2 += npow2 + 1;
							fl = remain(myb[id], 3);
							while ((myb[id]->len) && !mr_testbit(_MIPP_ myb[id], 0))
							{
								sftbit(myb[id], -1, myb[id]);
								fl = fl + (3 - fl * 2);
								fl %= 3;
								pow2 += 1;
							}
							break;
						}
					}
				}
			}

		}



	}
	*let = mc;
	mirkill(myb[0]);
	mirkill(myb[1]);
	mirkill(myb[2]);
	//printf("%d\n", pow3);
	big cert = mirvar(0);
	big tmpp = mirvar(0);
	big twop = mirvar(0);
	for (int i = mc; i > 0; i--) {

		expb2(POW2[i], twop);
		multiply(pow3n[POW3[i]], twop, tmpp);
		if (ISM[i]) {
			subtract(cert, tmpp, cert);
			printf("- 2^%d*3^%d ", POW2[i], POW3[i]);
		}
		else {
			add(cert, tmpp, cert);
			printf("+ 2^%d*3^%d ", POW2[i], POW3[i]);
		}
	}

	expb2(POW2[0], twop);
	multiply(pow3n[POW3[0]], twop, tmpp);
	if (ISM[0]) {
		subtract(cert, tmpp, cert);
		printf("- 2^%d*3^%d\n ", POW2[0], POW3[0]);
	}
	else {
		add(cert, tmpp, cert);
		printf("+ 2^%d*3^%d\n", POW2[0], POW3[0]);
	}
	cotnum(cert, stdout);
	//cotnum(origin, stdout);
	
}


void ecurve_triple(_MIPD_ epoint* p)
{ /* double epoint on active ecurve */

#ifdef MR_OS_THREADS
	miracl* mr_mip = get_mip();
#endif
	if (mr_mip->ERNUM) return;

	if (p->marker == MR_EPOINT_INFINITY)
	{ /* 2 times infinity == infinity ! */
		return;
	}

#ifndef MR_AFFINE_ONLY
	if (mr_mip->coord == MR_AFFINE)
	{ /* 2 sqrs, 1 mul, 1 div */
#endif
		if (size(p->Y) == 0)
		{ /* set to point at infinity */
			epoint_set(_MIPP_ NULL, NULL, 0, p);
			return;
		}

		nres_modmult(_MIPP_ p->X, p->X, mr_mip->w8);    /* w8=x^2   */
		nres_premult(_MIPP_ mr_mip->w8, 3, mr_mip->w8); /* w8=3*x^2 */
		if (mr_abs(mr_mip->Asize) == MR_TOOBIG)
			nres_modadd(_MIPP_ mr_mip->w8, mr_mip->A, mr_mip->w8);
		else
		{
			convert(_MIPP_ mr_mip->Asize, mr_mip->w2);
			nres(_MIPP_ mr_mip->w2, mr_mip->w2);
			nres_modadd(_MIPP_ mr_mip->w8, mr_mip->w2, mr_mip->w8);
		}                                     /* w8=3*x^2+A */
		nres_premult(_MIPP_ p->Y, 2, mr_mip->w6);      /* w6=2y */
		if (nres_moddiv(_MIPP_ mr_mip->w8, mr_mip->w6, mr_mip->w8) > 1)
		{
			epoint_set(_MIPP_ NULL, NULL, 0, p);
			mr_berror(_MIPP_ MR_ERR_COMPOSITE_MODULUS);
			return;
		}

		/* w8 is slope m on exit */

		nres_modmult(_MIPP_ mr_mip->w8, mr_mip->w8, mr_mip->w2); /* w2=m^2 */
		nres_premult(_MIPP_ p->X, 2, mr_mip->w1);
		nres_modsub(_MIPP_ mr_mip->w2, mr_mip->w1, mr_mip->w1); /* w1=m^2-2x */

		nres_modsub(_MIPP_ p->X, mr_mip->w1, mr_mip->w2);
		nres_modmult(_MIPP_ mr_mip->w2, mr_mip->w8, mr_mip->w2);
		nres_modsub(_MIPP_ mr_mip->w2, p->Y, p->Y);
		copy(mr_mip->w1, p->X);

		return;
#ifndef MR_AFFINE_ONLY
	}

	if (size(p->Y) == 0)
	{ /* set to point at infinity */
		epoint_set(_MIPP_ NULL, NULL, 0, p);
		return;
	}

	convert(_MIPP_ 1, mr_mip->w1);
	if (mr_abs(mr_mip->Asize) < MR_TOOBIG)
	{
		if (mr_mip->Asize != 0)
		{
			if (p->marker == MR_EPOINT_NORMALIZED)
				nres(_MIPP_ mr_mip->w1, mr_mip->w6);  //如果已经标准化  则w6=1
			else nres_modmult(_MIPP_ p->Z, p->Z, mr_mip->w6);//如果未标准化  则w6=Z^2
		}

		if (mr_mip->Asize == (-3))
		{ /* a is -3. Goody. 4 sqrs, 4 muls */
			nres_modsub(_MIPP_ p->X, mr_mip->w6, mr_mip->w3);//w3=X-Z^2
			nres_modadd(_MIPP_ p->X, mr_mip->w6, mr_mip->w8);//w8=X+Z^2
			nres_modmult(_MIPP_ mr_mip->w3, mr_mip->w8, mr_mip->w3);
			nres_modadd(_MIPP_ mr_mip->w3, mr_mip->w3, mr_mip->w8);
			nres_modadd(_MIPP_ mr_mip->w8, mr_mip->w3, mr_mip->w8);//W8=A
		}
		else
		{ /* a is small */
			if (mr_mip->Asize != 0)
			{ /* a is non zero! */
				nres_modmult(_MIPP_ mr_mip->w6, mr_mip->w6, mr_mip->w3);
				nres_premult(_MIPP_ mr_mip->w3, mr_mip->Asize, mr_mip->w3);
			}
			nres_modmult(_MIPP_ p->X, p->X, mr_mip->w1);
			nres_modadd(_MIPP_ mr_mip->w1, mr_mip->w1, mr_mip->w8);
			nres_modadd(_MIPP_ mr_mip->w8, mr_mip->w1, mr_mip->w8);
			if (mr_mip->Asize != 0) nres_modadd(_MIPP_ mr_mip->w8, mr_mip->w3, mr_mip->w8);
		}
	}
	else
	{ /* a is not special */
		
		if (p->marker == MR_EPOINT_NORMALIZED) nres(_MIPP_ mr_mip->w1, mr_mip->w6);//如果已经标准化  则w6=1
		else nres_modmult(_MIPP_ p->Z, p->Z, mr_mip->w6);//如果未标准化  则w6=Z^2

		nres_modmult(_MIPP_ mr_mip->w6, mr_mip->w6, mr_mip->w3);//w3=w6^2=z^4
		nres_modmult(_MIPP_ mr_mip->w3, mr_mip->A, mr_mip->w3);//w3=w3*a=z^4*a
		nres_modmult(_MIPP_ p->X, p->X, mr_mip->w1);//w1=x^2
		nres_modadd(_MIPP_ mr_mip->w1, mr_mip->w1, mr_mip->w8);//w8=2*w1=2x^2
		nres_modadd(_MIPP_ mr_mip->w8, mr_mip->w1, mr_mip->w8);//w8=3*w1=3*x^2
		nres_modadd(_MIPP_ mr_mip->w8, mr_mip->w3, mr_mip->w8);//w8=w8+w3=3*x^2+z^4*a  A
	}

	// w8=A


	nres_modmult(_MIPP_ p->Y, p->Y, mr_mip->w2);//w2=Y^2
	nres_modadd(_MIPP_ mr_mip->w2, mr_mip->w2, mr_mip->w2);//w2=2*Y^2
	nres_modmult(_MIPP_ mr_mip->w2, mr_mip->w2, mr_mip->w5);//w5=4*Y^4
	nres_modadd(_MIPP_ mr_mip->w5, mr_mip->w5, mr_mip->w5);//w5=8*Y^4

	nres_modadd(_MIPP_ mr_mip->w2, mr_mip->w2, mr_mip->w2);//w2=4*Y^2
	nres_modmult(_MIPP_ mr_mip->w2, p->X, mr_mip->w3);//w3=4*Y^2*X
	nres_modadd(_MIPP_ mr_mip->w3, mr_mip->w3, mr_mip->w4);//w4=8X*Y^2
	nres_modadd(_MIPP_ mr_mip->w4, mr_mip->w3, mr_mip->w3);//w3=12X*Y^2
	nres_modmult(_MIPP_ mr_mip->w8, mr_mip->w8, mr_mip->w4); //w4=A^2
	nres_modsub(_MIPP_ mr_mip->w3, mr_mip->w4, mr_mip->w3); //w3=12X*Y^2-A^2
	nres_modmult(_MIPP_ mr_mip->w8, mr_mip->w3, mr_mip->w1);//w1=A*B


	// w1=C   w2=4*Y^2  w3=B  w4=A^2   w5=D  W8=A



	if (p->marker == MR_EPOINT_NORMALIZED)
		copy(mr_mip->w3, p->Z);//如果Z是1  则Z=B
	else nres_modmult(_MIPP_ p->Z, mr_mip->w3, p->Z);//如果Z不是1  则Z=Z*B


	nres_modmult(_MIPP_ mr_mip->w3, mr_mip->w3, mr_mip->w6);//w6=B^2
	nres_modmult(_MIPP_ mr_mip->w6, p->X, p->X);//X3= X*B^2
	nres_modmult(_MIPP_ mr_mip->w6, mr_mip->w3, mr_mip->w3);//w3=B^3
	nres_modsub(_MIPP_ mr_mip->w1, mr_mip->w5, mr_mip->w1);//w1=C-D
	nres_modmult(_MIPP_ mr_mip->w1, mr_mip->w2, mr_mip->w6);//w6=(C-D)*4*Y^2
	nres_modadd(_MIPP_ mr_mip->w6, mr_mip->w6, mr_mip->w6);//w6=8*Y^2*(C-D)
	nres_modsub(_MIPP_ p->X, mr_mip->w6, p->X);//X3=8*Y^2*(D-C)+X*B^2

	// w1=C-D  w2=4*Y^2  w3=B^3 w4=A^2 w5=D  W8=A
	nres_modsub(_MIPP_ mr_mip->w5, mr_mip->w1, mr_mip->w5);//w5=D-(C-D)=2D-C
	nres_modmult(_MIPP_ mr_mip->w5, mr_mip->w1, mr_mip->w5);//w5=(C-D)*(2D-C)
	nres_modadd(_MIPP_ mr_mip->w5, mr_mip->w5, mr_mip->w5);//w5=2*(C-D)*(2D-C)
	nres_modadd(_MIPP_ mr_mip->w5, mr_mip->w5, mr_mip->w5);//w5=4*(C-D)*(2D-C)
	nres_modsub(_MIPP_ mr_mip->w5, mr_mip->w3, mr_mip->w5);//w5=4*(C-D)*(2D-C)-B^3
	nres_modmult(_MIPP_ p->Y, mr_mip->w5, p->Y);

	/*nres_modadd(_MIPP_ mr_mip->w2, mr_mip->w2, mr_mip->w7);// w7=2*Y^2
	nres_modmult(_MIPP_ mr_mip->w7, mr_mip->w7, mr_mip->w2);// w2=4Y^4
	nres_modadd(_MIPP_ mr_mip->w2, mr_mip->w2, mr_mip->w2); // w2=8Y^4
	nres_modsub(_MIPP_ mr_mip->w3, p->X, mr_mip->w3);//
	nres_modmult(_MIPP_ mr_mip->w8, mr_mip->w3, p->Y);
	nres_modsub(_MIPP_ p->Y, mr_mip->w2, p->Y);*/

	/* alternative method
		nres_modadd(_MIPP_ p->Y,p->Y,mr_mip->w2);

		if (p->marker==MR_EPOINT_NORMALIZED)
			copy(mr_mip->w2,p->Z);

		else nres_modmult(_MIPP_ mr_mip->w2,p->Z,p->Z);

		nres_modmult(_MIPP_ mr_mip->w2,mr_mip->w2,mr_mip->w2);
		nres_modmult(_MIPP_ p->X,mr_mip->w2,mr_mip->w3);
		nres_modadd(_MIPP_ mr_mip->w3,mr_mip->w3,p->X);
		nres_modmult(_MIPP_ mr_mip->w8,mr_mip->w8,mr_mip->w1);
		nres_modsub(_MIPP_ mr_mip->w1,p->X,p->X);
		nres_modmult(_MIPP_ mr_mip->w2,mr_mip->w2,mr_mip->w2);

		if (remain(_MIPP_ mr_mip->w2,2)!=0)
			mr_padd(_MIPP_ mr_mip->w2,mr_mip->modulus,mr_mip->w2);
		subdiv(_MIPP_ mr_mip->w2,2,mr_mip->w2);

		nres_modsub(_MIPP_ mr_mip->w3,p->X,mr_mip->w3);
		nres_modmult(_MIPP_ mr_mip->w3,mr_mip->w8,mr_mip->w3);
		nres_modsub(_MIPP_ mr_mip->w3,mr_mip->w2,p->Y);
	*/

	/*

	Observe that when finished w8 contains the line slope, w7 has 2y^2 and w6 has z^2
	This is useful for calculating line functions in pairings

	*/

	p->marker = MR_EPOINT_GENERAL;
	return;
#endif
}


int my_ecurve_mult(_MIPD_ big e, epoint* pa, epoint* pt)
{ /* pt=e*pa; */
	int i, j;
#ifndef MR_AFFINE_ONLY
	big work[MR_ECC_STORE_N];
#endif

#ifdef MR_STATIC
	char mem[MR_ECP_RESERVE(MR_ECC_STORE_N)];
#ifndef MR_AFFINE_ONLY
	char mem1[MR_BIG_RESERVE(MR_ECC_STORE_N)];
#endif
#else
	char* mem;
#ifndef MR_AFFINE_ONLY
	char* mem1;
#endif
#endif

#ifndef MR_ALWAYS_BINARY
	epoint* p;
	int ce, ch;
#endif
#ifdef MR_OS_THREADS
	miracl* mr_mip = get_mip();
#endif
	if (mr_mip->ERNUM) return 0;

	MR_IN(95)
		if (size(e) == 0)
		{ /* multiplied by 0 */
			epoint_set(_MIPP_ NULL, NULL, 0, pt);
			MR_OUT
				return 0;
		}
	copy(e, mr_mip->w9);
	/*    epoint_norm(_MIPP_ pa); */

	if (size(mr_mip->w9) < 0)
	{ /* pt = -pt */
		negify(mr_mip->w9, mr_mip->w9);
		epoint_negate(_MIPP_ pa);
	}

	if (size(mr_mip->w9) == 1)
	{
		MR_OUT
			return 0;
	}

	//premult(_MIPP_ mr_mip->w9, 3, mr_mip->w10);      /* h=3*e */

#ifndef MR_STATIC
#ifndef MR_ALWAYS_BINARY
	if (mr_mip->base == mr_mip->base2)
	{
#endif
#endif

#ifdef  MR_STATIC
		memset(mem, 0, MR_ECP_RESERVE(MR_ECC_STORE_N));
#ifndef MR_AFFINE_ONLY
		memset(mem1, 0, MR_BIG_RESERVE(MR_ECC_STORE_N));
#endif
#else
		mem = (char*)ecp_memalloc(_MIPP_ MR_ECC_STORE_N);
#ifndef MR_AFFINE_ONLY
		mem1 = (char*)memalloc(_MIPP_ MR_ECC_STORE_N);
#endif
#endif

		
#ifndef MR_AFFINE_ONLY
			
#endif
		

		

#ifndef MR_AFFINE_ONLY
		
#endif
		epoint_set(_MIPP_ NULL, NULL, 0, pt);
		short pow2[100] = { 0 };
		short pow3[100] = { 0 };
		short ISM[100] = { 0 };
		int len = 0;
		//Decompose(_MIPP_ mr_mip->w9,pow2,pow3,ISM,&len);
		//ttd6(_MIPP_ mr_mip->w9, pow2, pow3, ISM, &len);
		brandnew_Joker(_MIPP_ mr_mip->w9, pow2, pow3, ISM, &len);
		int b, t;
		i = len;
		if (mr_mip->user != NULL) (*mr_mip->user)();
		while (i > 0)
		{
			if (ISM[i])
				ecurve_sub(_MIPP_ pa, pt);//Q=Q-P
			else
				ecurve_add(_MIPP_ pa, pt);//Q=Q+P
			b = pow2[i] - pow2[i - 1];
			t = pow3[i] - pow3[i - 1];
			
			while (t > 0)
			{
				ecurve_triple(_MIPP_ pt);		
				t--;
			}
			while (b > 0)
			{
				ecurve_double(_MIPP_ pt);
				b--;
			}

			i--;
		}
		
		if (ISM[0])
			ecurve_sub(_MIPP_ pa, pt);//Q=Q-P
		else
			ecurve_add(_MIPP_ pa, pt);//Q=Q+P
		b = pow2[0];
		t = pow3[0];
		while (t > 0)
		{
			ecurve_triple(_MIPP_ pt);
			t--;
		}
		while (b > 0)
		{
			ecurve_double(_MIPP_ pt);
			b--;
		}
		
		
		
		/*nb = logb2(_MIPP_ mr_mip->w10);
		nadds = 0;
		epoint_set(_MIPP_ NULL, NULL, 0, pt);
		for (i = nb - 1; i >= 1;)
		{ // add/subtract 
			if (mr_mip->user != NULL) (*mr_mip->user)();
			n = mr_naf_window(_MIPP_ mr_mip->w9, mr_mip->w10, i, &nbs, &nzs, MR_ECC_STORE_N);
			for (j = 0; j < nbs; j++)
				ecurve_double(_MIPP_ pt);
			if (n > 0) { ecurve_add(_MIPP_ table[n / 2], pt); nadds++; }
			if (n < 0) { ecurve_sub(_MIPP_ table[(-n) / 2], pt); nadds++; }
			i -= nbs;
			if (nzs)
			{
				for (j = 0; j < nzs; j++) ecurve_double(_MIPP_ pt);
				i -= nzs;
			}
		}
		*/

		ecp_memkill(_MIPP_ mem, MR_ECC_STORE_N);
#ifndef MR_AFFINE_ONLY
		memkill(_MIPP_ mem1, MR_ECC_STORE_N);
#endif

#ifndef MR_STATIC
#ifndef MR_ALWAYS_BINARY
	}
	else
	{
		mem = (char*)ecp_memalloc(_MIPP_ 1);
		p = epoint_init_mem(_MIPP_ mem, 0);
		epoint_norm(_MIPP_ pt);
		epoint_copy(pt, p);

		nadds = 0;
		expb2(_MIPP_ logb2(_MIPP_ mr_mip->w10) - 1, mr_mip->w11);
		mr_psub(_MIPP_ mr_mip->w10, mr_mip->w11, mr_mip->w10);
		subdiv(_MIPP_ mr_mip->w11, 2, mr_mip->w11);
		while (size(mr_mip->w11) > 1)
		{ // add/subtract method 
			if (mr_mip->user != NULL) (*mr_mip->user)();

			ecurve_double(_MIPP_ pt);
			ce = mr_compare(mr_mip->w9, mr_mip->w11); /* e(i)=1? */
			ch = mr_compare(mr_mip->w10, mr_mip->w11); /* h(i)=1? */
			if (ch >= 0)
			{  /* h(i)=1 */
				if (ce < 0) { ecurve_add(_MIPP_ p, pt); nadds++; }
				mr_psub(_MIPP_ mr_mip->w10, mr_mip->w11, mr_mip->w10);
			}
			if (ce >= 0)
			{  /* e(i)=1 */
				if (ch < 0) { ecurve_sub(_MIPP_ p, pt); nadds++; }
				mr_psub(_MIPP_ mr_mip->w9, mr_mip->w11, mr_mip->w9);
			}
			subdiv(_MIPP_ mr_mip->w11, 2, mr_mip->w11);
		}
		ecp_memkill(_MIPP_ mem, 1);
	}
#endif
#endif
	MR_OUT
		return 1;
		//return nadds;
}


int my_ecurve_mult2(_MIPD_ big e, epoint* pa, epoint* pt)
{ /* pt=e*pa; */
	int i, j;
#ifndef MR_AFFINE_ONLY
	big work[MR_ECC_STORE_N];
#endif

#ifdef MR_STATIC
	char mem[MR_ECP_RESERVE(MR_ECC_STORE_N)];
#ifndef MR_AFFINE_ONLY
	char mem1[MR_BIG_RESERVE(MR_ECC_STORE_N)];
#endif
#else
	char* mem;
#ifndef MR_AFFINE_ONLY
	char* mem1;
#endif
#endif

#ifndef MR_ALWAYS_BINARY
	epoint* p;
	int ce, ch;
#endif
#ifdef MR_OS_THREADS
	miracl* mr_mip = get_mip();
#endif
	if (mr_mip->ERNUM) return 0;

	MR_IN(95)
		if (size(e) == 0)
		{ /* multiplied by 0 */
			epoint_set(_MIPP_ NULL, NULL, 0, pt);
			MR_OUT
				return 0;
		}
	copy(e, mr_mip->w9);
	/*    epoint_norm(_MIPP_ pa); */

	if (size(mr_mip->w9) < 0)
	{ /* pt = -pt */
		negify(mr_mip->w9, mr_mip->w9);
		epoint_negate(_MIPP_ pa);
	}

	if (size(mr_mip->w9) == 1)
	{
		MR_OUT
			return 0;
	}

	//premult(_MIPP_ mr_mip->w9, 3, mr_mip->w10);      /* h=3*e */

#ifndef MR_STATIC
#ifndef MR_ALWAYS_BINARY
	if (mr_mip->base == mr_mip->base2)
	{
#endif
#endif

#ifdef  MR_STATIC
		memset(mem, 0, MR_ECP_RESERVE(MR_ECC_STORE_N));
#ifndef MR_AFFINE_ONLY
		memset(mem1, 0, MR_BIG_RESERVE(MR_ECC_STORE_N));
#endif
#else
		mem = (char*)ecp_memalloc(_MIPP_ MR_ECC_STORE_N);
#ifndef MR_AFFINE_ONLY
		mem1 = (char*)memalloc(_MIPP_ MR_ECC_STORE_N);
#endif
#endif


#ifndef MR_AFFINE_ONLY

#endif




#ifndef MR_AFFINE_ONLY

#endif
		epoint_set(_MIPP_ NULL, NULL, 0, pt);
		short pow2[100] = { 0 };
		short pow3[100] = { 0 };
		short ISM[100] = { 0 };
		int len = 0;
		//Decompose(_MIPP_ mr_mip->w9,pow2,pow3,ISM,&len);
		//ttd6(_MIPP_ mr_mip->w9, pow2, pow3, ISM, &len);
		brandnew_Joker(_MIPP_ mr_mip->w9, pow2, pow3, ISM, &len);
		//printf("%d\n", len);
		int b, t;
		i = len;
		if (mr_mip->user != NULL) (*mr_mip->user)();
		while (i > 0)
		{
			if (ISM[i])
				ecurve_sub(_MIPP_ pa, pt);//Q=Q-P
			else
				ecurve_add(_MIPP_ pa, pt);//Q=Q+P
			b = pow2[i] - pow2[i - 1];
			t = pow3[i] - pow3[i - 1];

			while (t > 0)
			{
				ecurve_triple(_MIPP_ pt);
				t--;
			}
			while (b > 0)
			{
				ecurve_double(_MIPP_ pt);
				b--;
			}

			i--;
		}

		if (ISM[0])
			ecurve_sub(_MIPP_ pa, pt);//Q=Q-P
		else
			ecurve_add(_MIPP_ pa, pt);//Q=Q+P
		b = pow2[0];
		t = pow3[0];
		while (t > 0)
		{
			ecurve_triple(_MIPP_ pt);
			t--;
		}
		while (b > 0)
		{
			ecurve_double(_MIPP_ pt);
			b--;
		}



		/*nb = logb2(_MIPP_ mr_mip->w10);
		nadds = 0;
		epoint_set(_MIPP_ NULL, NULL, 0, pt);
		for (i = nb - 1; i >= 1;)
		{ // add/subtract
			if (mr_mip->user != NULL) (*mr_mip->user)();
			n = mr_naf_window(_MIPP_ mr_mip->w9, mr_mip->w10, i, &nbs, &nzs, MR_ECC_STORE_N);
			for (j = 0; j < nbs; j++)
				ecurve_double(_MIPP_ pt);
			if (n > 0) { ecurve_add(_MIPP_ table[n / 2], pt); nadds++; }
			if (n < 0) { ecurve_sub(_MIPP_ table[(-n) / 2], pt); nadds++; }
			i -= nbs;
			if (nzs)
			{
				for (j = 0; j < nzs; j++) ecurve_double(_MIPP_ pt);
				i -= nzs;
			}
		}
		*/

		ecp_memkill(_MIPP_ mem, MR_ECC_STORE_N);
#ifndef MR_AFFINE_ONLY
		memkill(_MIPP_ mem1, MR_ECC_STORE_N);
#endif

#ifndef MR_STATIC
#ifndef MR_ALWAYS_BINARY
	}
	else
	{
		mem = (char*)ecp_memalloc(_MIPP_ 1);
		p = epoint_init_mem(_MIPP_ mem, 0);
		epoint_norm(_MIPP_ pt);
		epoint_copy(pt, p);

		nadds = 0;
		expb2(_MIPP_ logb2(_MIPP_ mr_mip->w10) - 1, mr_mip->w11);
		mr_psub(_MIPP_ mr_mip->w10, mr_mip->w11, mr_mip->w10);
		subdiv(_MIPP_ mr_mip->w11, 2, mr_mip->w11);
		while (size(mr_mip->w11) > 1)
		{ // add/subtract method 
			if (mr_mip->user != NULL) (*mr_mip->user)();

			ecurve_double(_MIPP_ pt);
			ce = mr_compare(mr_mip->w9, mr_mip->w11); /* e(i)=1? */
			ch = mr_compare(mr_mip->w10, mr_mip->w11); /* h(i)=1? */
			if (ch >= 0)
			{  /* h(i)=1 */
				if (ce < 0) { ecurve_add(_MIPP_ p, pt); nadds++; }
				mr_psub(_MIPP_ mr_mip->w10, mr_mip->w11, mr_mip->w10);
			}
			if (ce >= 0)
			{  /* e(i)=1 */
				if (ch < 0) { ecurve_sub(_MIPP_ p, pt); nadds++; }
				mr_psub(_MIPP_ mr_mip->w9, mr_mip->w11, mr_mip->w9);
			}
			subdiv(_MIPP_ mr_mip->w11, 2, mr_mip->w11);
		}
		ecp_memkill(_MIPP_ mem, 1);
	}
#endif
#endif
	MR_OUT
		return 1;
	//return nadds;
}

epoint* MultiplyEpoint2(big a, epoint* b);

epoint* tmp5 ;
epoint* tmp7 ;
epoint* tmp11 ;
epoint* tmp ;
void setpt(epoint *pa)
{
	tmp5 = epoint_init();
	tmp7 = epoint_init();
	tmp11 = epoint_init();
	tmp = epoint_init();
	epoint_copy(pa, tmp);
	ecurve_double(tmp);
	ecurve_triple(tmp);
	epoint_copy(tmp, tmp5);
	epoint_copy(tmp, tmp7);
	ecurve_double(tmp);
	epoint_copy(tmp, tmp11);
	ecurve_sub(pa, tmp5);
	ecurve_add(pa, tmp7);
	ecurve_sub(pa, tmp11);
}
int my_ecurve_mult3(_MIPD_ big e, epoint* pa, epoint* pt)
{ /* pt=e*pa; */
	int i, j;
#ifndef MR_AFFINE_ONLY
	big work[MR_ECC_STORE_N];
#endif

#ifdef MR_STATIC
	char mem[MR_ECP_RESERVE(MR_ECC_STORE_N)];
#ifndef MR_AFFINE_ONLY
	char mem1[MR_BIG_RESERVE(MR_ECC_STORE_N)];
#endif
#else
	char* mem;
#ifndef MR_AFFINE_ONLY
	char* mem1;
#endif
#endif

#ifndef MR_ALWAYS_BINARY
	epoint* p;
	int ce, ch;
#endif
#ifdef MR_OS_THREADS
	miracl* mr_mip = get_mip();
#endif
	if (mr_mip->ERNUM) return 0;

	MR_IN(95)
		if (size(e) == 0)
		{ /* multiplied by 0 */
			epoint_set(_MIPP_ NULL, NULL, 0, pt);
			MR_OUT
				return 0;
		}
	copy(e, mr_mip->w9);
	/*    epoint_norm(_MIPP_ pa); */

	if (size(mr_mip->w9) < 0)
	{ /* pt = -pt */
		negify(mr_mip->w9, mr_mip->w9);
		epoint_negate(_MIPP_ pa);
	}

	if (size(mr_mip->w9) == 1)
	{
		MR_OUT
			return 0;
	}

	//premult(_MIPP_ mr_mip->w9, 3, mr_mip->w10);      /* h=3*e */

#ifndef MR_STATIC
#ifndef MR_ALWAYS_BINARY
	if (mr_mip->base == mr_mip->base2)
	{
#endif
#endif

#ifdef  MR_STATIC
		memset(mem, 0, MR_ECP_RESERVE(MR_ECC_STORE_N));
#ifndef MR_AFFINE_ONLY
		memset(mem1, 0, MR_BIG_RESERVE(MR_ECC_STORE_N));
#endif
#else
		mem = (char*)ecp_memalloc(_MIPP_ MR_ECC_STORE_N);
#ifndef MR_AFFINE_ONLY
		mem1 = (char*)memalloc(_MIPP_ MR_ECC_STORE_N);
#endif
#endif


#ifndef MR_AFFINE_ONLY

#endif




#ifndef MR_AFFINE_ONLY

#endif
		epoint_set(_MIPP_ NULL, NULL, 0, pt);
		/*tmp5= epoint_init();
		tmp7 = epoint_init();
		tmp11 = epoint_init();
		tmp = epoint_init();
		epoint_copy(pa, tmp);
		ecurve_double(tmp);
		ecurve_triple(tmp);
		epoint_copy(tmp, tmp5);
		epoint_copy(tmp, tmp7);
		ecurve_double(tmp);
		epoint_copy(tmp, tmp11);
		ecurve_sub(pa,tmp5);
		ecurve_add(pa,tmp7);
		ecurve_sub(pa,tmp11);*/
		//big aa = mirvar(5);
		//cotnum(pa->X, stdout);
		//tmp = MultiplyEpoint2(aa, pa);
		//cotnum(pa->X, stdout);
		/*epoint_copy(pa, tmp);
		ecurve_double(_MIPP_ tmp);
		ecurve_double(_MIPP_ tmp);
		ecurve_add(_MIPP_ pa, tmp);*/
		//cotnum(pa->X, stdout);
		//cotnum(tmp->X, stdout);
		

		short pow2[100] = { 0 };
		short pow3[100] = { 0 };
		short ISM[100] = { 0 };
		short isp[100] = { 0 };
		int len = 0;
		//Decompose(_MIPP_ mr_mip->w9,pow2,pow3,ISM,&len);
		//ttd6(_MIPP_ mr_mip->w9, pow2, pow3, ISM, &len);
		new_ttd6_plus(_MIPP_ mr_mip->w9, pow2, pow3, ISM,isp, &len);
		//ttd6_plus_plus(_MIPP_ mr_mip->w9, pow2, pow3, ISM, isp, &len);
		//printf("%d\n", len);
		//brandnew_Joker(_MIPP_ mr_mip->w9, pow2, pow3, ISM, &len);
		int b, t;
		i = len;
		if (mr_mip->user != NULL) (*mr_mip->user)();
		while (i > 0)
		{
			if (isp[i]>0)
			{
				if (isp[i]==5)
					ecurve_sub(_MIPP_ tmp5, pt);
				else if(isp[i]==7)
					ecurve_sub(_MIPP_ tmp7, pt);//Q=Q-P
				else if(isp[i]==11)
					ecurve_sub(_MIPP_ tmp11, pt);
				else
					ecurve_sub(_MIPP_ pa, pt);
			}
			else
			{
				isp[i] = -isp[i];
				if (isp[i] == 5)
					ecurve_add(_MIPP_ tmp5, pt);
				else if (isp[i] == 7)
					ecurve_add(_MIPP_ tmp7, pt);//Q=Q-P
				else if (isp[i] == 11)
					ecurve_add(_MIPP_ tmp11, pt);
				else
					ecurve_add(_MIPP_ pa, pt);
			}
			b = pow2[i] - pow2[i - 1];
			t = pow3[i] - pow3[i - 1];

			while (t > 0)
			{
				ecurve_triple(_MIPP_ pt);
				t--;
			}
			while (b > 0)
			{
				ecurve_double(_MIPP_ pt);
				b--;
			}

			i--;
		}

		if (isp[0]>0)
		{
			if (isp[0] == 5)
				ecurve_sub(_MIPP_ tmp5, pt);
			else if (isp[0] == 7)
				ecurve_sub(_MIPP_ tmp7, pt);//Q=Q-P
			else if (isp[0] == 11)
				ecurve_sub(_MIPP_ tmp11, pt);
			else
				ecurve_sub(_MIPP_ pa, pt);
		}
		else
		{
			isp[0] = -isp[0];
			if (isp[0] == 5)
				ecurve_add(_MIPP_ tmp5, pt);
			else if (isp[0] == 7)
				ecurve_add(_MIPP_ tmp7, pt);//Q=Q-P
			else if (isp[0] == 11)
				ecurve_add(_MIPP_ tmp11, pt);
			else
				ecurve_add(_MIPP_ pa, pt);
		}
		b = pow2[0];
		t = pow3[0];
		while (t > 0)
		{
			ecurve_triple(_MIPP_ pt);
			t--;
		}
		while (b > 0)
		{
			ecurve_double(_MIPP_ pt);
			b--;
		}



		/*nb = logb2(_MIPP_ mr_mip->w10);
		nadds = 0;
		epoint_set(_MIPP_ NULL, NULL, 0, pt);
		for (i = nb - 1; i >= 1;)
		{ // add/subtract
			if (mr_mip->user != NULL) (*mr_mip->user)();
			n = mr_naf_window(_MIPP_ mr_mip->w9, mr_mip->w10, i, &nbs, &nzs, MR_ECC_STORE_N);
			for (j = 0; j < nbs; j++)
				ecurve_double(_MIPP_ pt);
			if (n > 0) { ecurve_add(_MIPP_ table[n / 2], pt); nadds++; }
			if (n < 0) { ecurve_sub(_MIPP_ table[(-n) / 2], pt); nadds++; }
			i -= nbs;
			if (nzs)
			{
				for (j = 0; j < nzs; j++) ecurve_double(_MIPP_ pt);
				i -= nzs;
			}
		}
		*/

		ecp_memkill(_MIPP_ mem, MR_ECC_STORE_N);
#ifndef MR_AFFINE_ONLY
		memkill(_MIPP_ mem1, MR_ECC_STORE_N);
#endif

#ifndef MR_STATIC
#ifndef MR_ALWAYS_BINARY
	}
	else
	{
		mem = (char*)ecp_memalloc(_MIPP_ 1);
		p = epoint_init_mem(_MIPP_ mem, 0);
		epoint_norm(_MIPP_ pt);
		epoint_copy(pt, p);

		nadds = 0;
		expb2(_MIPP_ logb2(_MIPP_ mr_mip->w10) - 1, mr_mip->w11);
		mr_psub(_MIPP_ mr_mip->w10, mr_mip->w11, mr_mip->w10);
		subdiv(_MIPP_ mr_mip->w11, 2, mr_mip->w11);
		while (size(mr_mip->w11) > 1)
		{ // add/subtract method 
			if (mr_mip->user != NULL) (*mr_mip->user)();

			ecurve_double(_MIPP_ pt);
			ce = mr_compare(mr_mip->w9, mr_mip->w11); /* e(i)=1? */
			ch = mr_compare(mr_mip->w10, mr_mip->w11); /* h(i)=1? */
			if (ch >= 0)
			{  /* h(i)=1 */
				if (ce < 0) { ecurve_add(_MIPP_ p, pt); nadds++; }
				mr_psub(_MIPP_ mr_mip->w10, mr_mip->w11, mr_mip->w10);
			}
			if (ce >= 0)
			{  /* e(i)=1 */
				if (ch < 0) { ecurve_sub(_MIPP_ p, pt); nadds++; }
				mr_psub(_MIPP_ mr_mip->w9, mr_mip->w11, mr_mip->w9);
			}
			subdiv(_MIPP_ mr_mip->w11, 2, mr_mip->w11);
		}
		ecp_memkill(_MIPP_ mem, 1);
	}
#endif
#endif
	MR_OUT
		return 1;
	//return nadds;
}

//新建一个椭圆曲线上的点
epoint* NewPoint(big x, big y) {
	epoint* result = epoint_init();
	epoint_set(x, y, 0, result);
	return result;
}

int my_ecurve_mult4(_MIPD_ big e, epoint* pa, epoint* pt)
{ /* pt=e*pa; */
	int i, j;
#ifndef MR_AFFINE_ONLY
	big work[MR_ECC_STORE_N];
#endif

#ifdef MR_STATIC
	char mem[MR_ECP_RESERVE(MR_ECC_STORE_N)];
#ifndef MR_AFFINE_ONLY
	char mem1[MR_BIG_RESERVE(MR_ECC_STORE_N)];
#endif
#else
	char* mem;
#ifndef MR_AFFINE_ONLY
	char* mem1;
#endif
#endif

#ifndef MR_ALWAYS_BINARY
	epoint* p;
	int ce, ch;
#endif
#ifdef MR_OS_THREADS
	miracl* mr_mip = get_mip();
#endif
	if (mr_mip->ERNUM) return 0;

	MR_IN(95)
		if (size(e) == 0)
		{ /* multiplied by 0 */
			epoint_set(_MIPP_ NULL, NULL, 0, pt);
			MR_OUT
				return 0;
		}
	copy(e, mr_mip->w9);
	/*    epoint_norm(_MIPP_ pa); */

	if (size(mr_mip->w9) < 0)
	{ /* pt = -pt */
		negify(mr_mip->w9, mr_mip->w9);
		epoint_negate(_MIPP_ pa);
	}

	if (size(mr_mip->w9) == 1)
	{
		MR_OUT
			return 0;
	}

	//premult(_MIPP_ mr_mip->w9, 3, mr_mip->w10);      /* h=3*e */

#ifndef MR_STATIC
#ifndef MR_ALWAYS_BINARY
	if (mr_mip->base == mr_mip->base2)
	{
#endif
#endif

#ifdef  MR_STATIC
		memset(mem, 0, MR_ECP_RESERVE(MR_ECC_STORE_N));
#ifndef MR_AFFINE_ONLY
		memset(mem1, 0, MR_BIG_RESERVE(MR_ECC_STORE_N));
#endif
#else
		mem = (char*)ecp_memalloc(_MIPP_ MR_ECC_STORE_N);
#ifndef MR_AFFINE_ONLY
		mem1 = (char*)memalloc(_MIPP_ MR_ECC_STORE_N);
#endif
#endif


#ifndef MR_AFFINE_ONLY

#endif




#ifndef MR_AFFINE_ONLY

#endif
		epoint_set(_MIPP_ NULL, NULL, 0, pt);
		/*tmp5= epoint_init();
		tmp7 = epoint_init();
		tmp11 = epoint_init();
		tmp = epoint_init();
		epoint_copy(pa, tmp);
		ecurve_double(tmp);
		ecurve_triple(tmp);
		epoint_copy(tmp, tmp5);
		epoint_copy(tmp, tmp7);
		ecurve_double(tmp);
		epoint_copy(tmp, tmp11);
		ecurve_sub(pa,tmp5);
		ecurve_add(pa,tmp7);
		ecurve_sub(pa,tmp11);*/
		//big aa = mirvar(5);
		//cotnum(pa->X, stdout);
		//tmp = MultiplyEpoint2(aa, pa);
		//cotnum(pa->X, stdout);
		/*epoint_copy(pa, tmp);
		ecurve_double(_MIPP_ tmp);
		ecurve_double(_MIPP_ tmp);
		ecurve_add(_MIPP_ pa, tmp);*/
		//cotnum(pa->X, stdout);
		//cotnum(tmp->X, stdout);


		short pow2[100] = { 0 };
		short pow3[100] = { 0 };
		short ISM[100] = { 0 };
		short isp[100] = { 0 };
		int len = 0;
		//Decompose(_MIPP_ mr_mip->w9,pow2,pow3,ISM,&len);
		//ttd6(_MIPP_ mr_mip->w9, pow2, pow3, ISM, &len);
		//new_ttd6_plus(_MIPP_ mr_mip->w9, pow2, pow3, ISM, isp, &len);
		ttd6_plus_plus(_MIPP_ mr_mip->w9, pow2, pow3, ISM, isp, &len);
		//printf("%d\n", len);
		//brandnew_Joker(_MIPP_ mr_mip->w9, pow2, pow3, ISM, &len);
		int b, t;
		i = len;
		if (mr_mip->user != NULL) (*mr_mip->user)();
		while (i > 0)
		{
			if (isp[i] > 0)
			{
				if (isp[i] == 5)
					ecurve_sub(_MIPP_ tmp5, pt);
				else if (isp[i] == 7)
					ecurve_sub(_MIPP_ tmp7, pt);//Q=Q-P
				else if (isp[i] == 11)
					ecurve_sub(_MIPP_ tmp11, pt);
				else
					ecurve_sub(_MIPP_ pa, pt);
			}
			else
			{
				isp[i] = -isp[i];
				if (isp[i] == 5)
					ecurve_add(_MIPP_ tmp5, pt);
				else if (isp[i] == 7)
					ecurve_add(_MIPP_ tmp7, pt);//Q=Q-P
				else if (isp[i] == 11)
					ecurve_add(_MIPP_ tmp11, pt);
				else
					ecurve_add(_MIPP_ pa, pt);
			}
			b = pow2[i] - pow2[i - 1];
			t = pow3[i] - pow3[i - 1];

			while (t > 0)
			{
				ecurve_triple(_MIPP_ pt);
				t--;
			}
			while (b > 0)
			{
				ecurve_double(_MIPP_ pt);
				b--;
			}

			i--;
		}

		if (isp[0] > 0)
		{
			if (isp[0] == 5)
				ecurve_sub(_MIPP_ tmp5, pt);
			else if (isp[0] == 7)
				ecurve_sub(_MIPP_ tmp7, pt);//Q=Q-P
			else if (isp[0] == 11)
				ecurve_sub(_MIPP_ tmp11, pt);
			else
				ecurve_sub(_MIPP_ pa, pt);
		}
		else
		{
			isp[0] = -isp[0];
			if (isp[0] == 5)
				ecurve_add(_MIPP_ tmp5, pt);
			else if (isp[0] == 7)
				ecurve_add(_MIPP_ tmp7, pt);//Q=Q-P
			else if (isp[0] == 11)
				ecurve_add(_MIPP_ tmp11, pt);
			else
				ecurve_add(_MIPP_ pa, pt);
		}
		b = pow2[0];
		t = pow3[0];
		while (t > 0)
		{
			ecurve_triple(_MIPP_ pt);
			t--;
		}
		while (b > 0)
		{
			ecurve_double(_MIPP_ pt);
			b--;
		}



		/*nb = logb2(_MIPP_ mr_mip->w10);
		nadds = 0;
		epoint_set(_MIPP_ NULL, NULL, 0, pt);
		for (i = nb - 1; i >= 1;)
		{ // add/subtract
			if (mr_mip->user != NULL) (*mr_mip->user)();
			n = mr_naf_window(_MIPP_ mr_mip->w9, mr_mip->w10, i, &nbs, &nzs, MR_ECC_STORE_N);
			for (j = 0; j < nbs; j++)
				ecurve_double(_MIPP_ pt);
			if (n > 0) { ecurve_add(_MIPP_ table[n / 2], pt); nadds++; }
			if (n < 0) { ecurve_sub(_MIPP_ table[(-n) / 2], pt); nadds++; }
			i -= nbs;
			if (nzs)
			{
				for (j = 0; j < nzs; j++) ecurve_double(_MIPP_ pt);
				i -= nzs;
			}
		}
		*/

		ecp_memkill(_MIPP_ mem, MR_ECC_STORE_N);
#ifndef MR_AFFINE_ONLY
		memkill(_MIPP_ mem1, MR_ECC_STORE_N);
#endif

#ifndef MR_STATIC
#ifndef MR_ALWAYS_BINARY
	}
	else
	{
		mem = (char*)ecp_memalloc(_MIPP_ 1);
		p = epoint_init_mem(_MIPP_ mem, 0);
		epoint_norm(_MIPP_ pt);
		epoint_copy(pt, p);

		nadds = 0;
		expb2(_MIPP_ logb2(_MIPP_ mr_mip->w10) - 1, mr_mip->w11);
		mr_psub(_MIPP_ mr_mip->w10, mr_mip->w11, mr_mip->w10);
		subdiv(_MIPP_ mr_mip->w11, 2, mr_mip->w11);
		while (size(mr_mip->w11) > 1)
		{ // add/subtract method 
			if (mr_mip->user != NULL) (*mr_mip->user)();

			ecurve_double(_MIPP_ pt);
			ce = mr_compare(mr_mip->w9, mr_mip->w11); /* e(i)=1? */
			ch = mr_compare(mr_mip->w10, mr_mip->w11); /* h(i)=1? */
			if (ch >= 0)
			{  /* h(i)=1 */
				if (ce < 0) { ecurve_add(_MIPP_ p, pt); nadds++; }
				mr_psub(_MIPP_ mr_mip->w10, mr_mip->w11, mr_mip->w10);
			}
			if (ce >= 0)
			{  /* e(i)=1 */
				if (ch < 0) { ecurve_sub(_MIPP_ p, pt); nadds++; }
				mr_psub(_MIPP_ mr_mip->w9, mr_mip->w11, mr_mip->w9);
			}
			subdiv(_MIPP_ mr_mip->w11, 2, mr_mip->w11);
		}
		ecp_memkill(_MIPP_ mem, 1);
	}
#endif
#endif
	MR_OUT
		return 1;
	//return nadds;
}



//椭圆曲线上的点相加
epoint* AddEpoint(epoint* a, epoint* b) {
	epoint* result = epoint_init();
	epoint_copy(b, result);
	ecurve_add(a, result);
	return result;
}


//椭圆曲线上的点多倍点运算
epoint* MultiplyEpoint(big a, epoint* b) {
	epoint* result = epoint_init();
	my_ecurve_mult3(a, b, result);
	return result;
	
}




epoint* MultiplyEpoint2(big a, epoint* b) {
	epoint* result = epoint_init();
	my_ecurve_mult4(a, b, result);
	return result;
}


//获得椭圆曲线上点的横坐标
big PointX(epoint* point) {
	big x = mirvar(0);
	big y = mirvar(0);
	epoint_get(point, x, y);
	mirkill(y);
	return x;
}

//获得椭圆曲线上点的纵坐标
big PointY(epoint* point) {
	big x = mirvar(0);
	big y = mirvar(0);
	epoint_get(point, x, y);
	mirkill(x);
	return y;
}