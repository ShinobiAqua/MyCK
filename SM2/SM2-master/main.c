#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include "miracl.h"
#include "ConstValue.h"
#include "Sm2Util.h"
#include<time.h>


miracl* mip;
int maxLen = 8192;			//全局字符串最大长度
int v = 64;					//哈希的16进制串长，即256位

extern big pow3n[256];
extern int lsp[1000] = { 0 };
extern int W2BT3[500] = { 0 };
extern int W3BT2[500] = { 0 };

void init() {
	int num = 1;
	big two = mirvar(1);
	big three = mirvar(3);
	for (int i = 0; i < 256; i++)
	{
		if (mr_compare(two,three))
		{
			W2BT3[num++] = i;
			premult(three, 3, three);
		}
		sftbit(two, 1, two);
	}
	two = mirvar(2);
	three = mirvar(1);
	num = 1;
	for (int i = 0; i < 162; i++)
	{
		if (mr_compare(three , two))
		{
			W3BT2[num++] = i;
			sftbit(two, 1, two);
		}
		premult(three, 3, three);
	}

	pow3n[0] = mirvar(1);

	for (int i = 1; i < 256; i++)
		pow3n[i] = mirvar(0);

	for (int i = 1; i < 256; i++)
		premult(pow3n[i - 1], 3, pow3n[i]);
}




void set64(big* t, big* p)
{
	big k = mirvar(0xffff);
	big tmp = mirvar(0);
	sftbit(k, 16, tmp);
	add(k, tmp, k);
	sftbit(k, 32, tmp);
	add(k, tmp, k);
	sftbit(k, -1, k);

	big s = mirvar(1);
	sftbit(s, 63, s);
	copy(k, t);
}

void set128(big* t, big* p)
{
	big k = mirvar(0xffff);
	big tmp = mirvar(0);
	sftbit(k, 16, tmp);
	add(k, tmp, k);
	sftbit(k, 32, tmp);
	add(k, tmp, k);

	sftbit(k, 64, tmp);
	add(k, tmp, k);

	sftbit(k, -1, k);

	big s = mirvar(1);
	sftbit(s, 127, s);
	copy(k, t);
	copy(s, p);
}

void set256(big* t, big* p)
{
	big k = mirvar(0xffff);
	big tmp = mirvar(0);
	sftbit(k, 16, tmp);
	add(k, tmp, k);
	sftbit(k, 32, tmp);
	add(k, tmp, k);

	sftbit(k, 64, tmp);
	add(k, tmp, k);

	sftbit(k, 128, tmp);
	add(k, tmp, k);
	sftbit(k, -1, k);

	big s = mirvar(1);
	sftbit(s, 255, s);
	copy(k, t);
	copy(s, p);
}


int main() {
	mip = mirsys(500, 0);

	init();
	//初始化椭圆曲线
	ecurve_init(HexCharsToBig(a), HexCharsToBig(b), HexCharsToBig(p), MR_PROJECTIVE);
	//计算公钥和私钥
	//CalculateKeys();
	//加密
	/*Encryption();
	//解密
	Decryption();
	system("pause");*/

	/*big k = mirvar(0);
	copy(GetBigRandom(mirvar(1), Sub2(HexCharsToBig(n), mirvar(1))), k);
	*/
	
	epoint* a = epoint_init();
	epoint* b = epoint_init();
	/*big u = mirvar(1024*81);
	multiply(u, u, u);
	multiply(u, u, u);
	multiply(u, u, u);
	big s = mirvar(4358379);
	big s2 = mirvar(4358379);
	copy(u, s);
	copy(u, s2);*/


	big k = mirvar(0xffff);
	big b1 = mirvar(0);
	big tmp = mirvar(0);
	big s = mirvar(1);
	big n = mirvar(0);
	//sftbit(s, 255, s);
	set256(k, s);

	
	big x = mirvar(0);
	big y = mirvar(0);
	big z = mirvar(0);
	irand(time(NULL));

	epoint* g = CalculateG();
	setpt(g);
	int iteration = 70000;
	clock_t start, finish;
	double totaltime;
	int i = 0;
	start = clock();
	while (i < iteration) {
		//int t = rand() % 256;
		//bigbits(t, n);
		//bigrand(k, n);
		//add(n, s, n);
		//n = mirvar(12345);
		//CalculateKeys();
		//incr(n, iteration, b1);
		//if (i == 0)
		//	setpt(g);
		ecurve_add(g,g);
		//a = MultiplyEpoint(n, g);
		//Encryption();
		//epoint_norm(a);
		//cotnum(a->X, stdout);
		i++;
	}
	finish = clock();
	totaltime = (double)(finish - start) / CLOCKS_PER_SEC;
	printf("time: %lf\n", totaltime);

	irand(time(NULL));
	clock_t start1, finish1;
	double totaltime1;
	int j = 0;
	start1 = clock();
	while (j < iteration) {
		//int t = rand() % 256;
		//bigbits(t, n);
		//bigrand(k, n);
		//add(n, s, n);
		//n = mirvar(12345);
		//incr(n, iteration, b1);
		ecurve_double(g);
		//b = MultiplyEpoint2(n, g);
		j++;
		//epoint_norm(b);
		//cotnum(b->X, stdout);
	}
	finish1 = clock();
	totaltime1 = (double)(finish1 - start1) / CLOCKS_PER_SEC;
	printf("time: %lf\n", totaltime1);
	
	printf("xxx : %lf \n", (totaltime1 - totaltime) *100/ totaltime1);
	printf("xxx : %lf \n", (totaltime1)  / totaltime);
	mirkill(mip);
	system("pause");
	return 0;
}