#include<time.h>
#include<stdlib.h>
#include "miracl.h"
#include <math.h>
#include<stdio.h>
#include"binary_S.h"


#define SSIZE 1
#define BSARRLEN 170*SSIZE
bsa arr[BSARRLEN];
int s[30] = { 1,5,7,11,13,17,19,23,25,29,31,35,37,41,43 };


void windowsize(int x)
{
	int l = s[x - 1] * 2;
	int r = s[x] * 2;
	for (int i = l; i < r; i++)
	{
		int n = i;
		int p2 = 0 , p3 = 0;
		while (n % 2 == 0) { n /= 2; p2++; }
		while (n % 3 == 0) { n /= 3; p3++; }
		if (n == 1)
			printf("%d  %d  %d\n", p2, p3, i);
	}
}


int mycomp(big a, big b)//字典序比较
{
	int n1 = logb2(a), n2 = logb2(b);
	if (n1 == n2)
	{
		return mr_compare(a, b);
	}
	int n = min(n1,n2);
	for (int i = 1; i <= n; i++)
	{
		if (mr_testbit(a, n1 - i) ^ mr_testbit(b, n2 - i))//如果当前位不一样
			return mr_testbit(a, n1 - i) - mr_testbit(b, n2 - i);
	}
	if(n1 > n2)
		return 1;
	else 
		return -1;
	
}


int partition(int l,int r)//快排的partition
{
	int p = l, q = r;
	bsa tmp;
	tmp.a = mirvar(0);
	copy(arr[p].a, tmp.a);
	tmp.b0 = arr[p].b0;
	tmp.s0 = arr[p].s0;
	tmp.len0 = arr[p].len0;
	while (p < q)
	{
		while (p < q && mycomp(arr[q].a, tmp.a) ==  1) --q;
		{
			copy(arr[q].a, arr[p].a);
			arr[p].b0 = arr[q].b0;
			arr[p].s0 = arr[q].s0;
			arr[p].len0 = arr[q].len0;
		}
		while (p < q && mycomp( arr[p].a, tmp.a) == -1) ++p;
		{
			copy(arr[p].a, arr[q].a);
			arr[q].b0 = arr[p].b0;
			arr[q].s0 = arr[p].s0;
			arr[q].len0 = arr[p].len0;
		}
	}
	copy(tmp.a, arr[p].a);
	arr[p].b0 = tmp.b0;
	arr[p].s0 = tmp.s0;
	arr[p].len0 = tmp.len0;
	return p;
}

void q_sort(int l,int r)//快排
{
	if (l < r)
	{
		int pivotpos = partition(l, r);
		q_sort(l, pivotpos - 1);
		q_sort(pivotpos + 1, r);
	}
	return;
}

void binary_init()//初始化
{
	big tmp = mirvar(1);
	big stp = mirvar(1);
	int i = 0;
	int count = 0;
	while(i<BSARRLEN)
	{
		for (int j = 0; j < SSIZE; j++)
		{
			arr[i].a = mirvar(0);
			arr[i].b0 = count;
			arr[i].s0 = s[j];
			premult(tmp, s[j], stp);
			copy(stp, arr[i].a);
			arr[i].len0 = logb2(stp);
			i++;
		}
		premult(tmp, 3, tmp);
		count++;
		
	}
	//int c=mycomp(arr[3].a, arr[1].a);
	
	q_sort(0, BSARRLEN-1);
	/*for (int i = 0; i < BSARRLEN; i++)
	{
		cotnum(arr[i].a, stdout);
		printf("   %d   %d\n", arr[i].b0, arr[i].s0);
	}*/

}


void b_search(big n,int *v1,int *v2)//二分查找
{
	int l = 0, r = BSARRLEN-1;
	int mid;
	int flg;
	while (l < r-1)
	{
		mid = (l + r) / 2;
		flg=mycomp(arr[mid].a, n);
		if (flg == 0)
		{
			*v1 = *v2 = mid;
			return;
		}
		if (flg == 1)
		{
			r = mid;
			continue;
		}
		if (flg == -1)
		{
			l = mid;
			continue;
		}
	}
	
	flg = mycomp(arr[l].a, n);
	if (flg == 0)
	{
		*v1 = *v2 = l;
		return;
	}
	flg = mycomp(arr[r].a, n);
	if (flg == 0)
	{
		*v1 = *v2 = r;
		return;
	}
	*v1 = l;
	*v2 = r;
	return;
}


int judge_p(int n,int a0,int b0,int index)//判断是否符合要求
{
	if (arr[index].b0 > b0)
		return 0;
	int d = n - arr[index].len0;
	if (d >= 0 && d <= a0)
		return 1;

	return 0;
}

void findapprox(big n, int a0, int b0, int* x1, int* x2,int *t1,int* t2)//寻找v1和v2
{
	int v1, v2;
	int len = logb2(n);
	int sr = 0,sl = 0;
	b_search(n, &v1, &v2);
	//printf("\n");
	//cotnum(arr[v1].a, stdout);
	//cotnum(arr[v2].a, stdout);
	if (v2 == BSARRLEN - 1 && mycomp(n, arr[v2].a) == 1)
	{
		v2 = 0;
		sr++;
	}

	while (1) {
		while (!judge_p(len + sr, a0, b0, v2) && v2 < BSARRLEN)
			v2++;
		if (v2 == BSARRLEN)
		{
			sr++;
			v2 = 0;
		}
		else
			break;
	}
	/*if (v2 == BSARRLEN) {
		sr = 1;
		v2 = 0;
		while (!judge_p(len + sr, a0, b0, v2) && v2 < BSARRLEN - 1)
			v2++;
	}*/
	while (1) {
		while (!judge_p(len + sl, a0, b0, v1) && v1 >= 0)
			v1--;
		if (v1 == -1)
		{
			sl -- ;
			v1 = BSARRLEN - 1;
		}
		else break;
	}
	/*if (v1 == -1) {
		sl = -1;
		v1 = BSARRLEN-1;
		while (!judge_p(len + sl, a0, b0, v1) && v1 > 0)
			v1--;
	}*/
	*x1 = v1;
	*x2 = v2;
	*t1 = sl + len - arr[v1].len0;
	*t2 = sr + len - arr[v2].len0;
	

	//printf("%d  %d\n", ct1, ct2);
	
	/*cotnum(arr[v1].a, stdout);
	cotnum(n, stdout);
	cotnum(arr[v2].a, stdout);*/

	return;
}

int bsdecomp(big n)//分解n（测试用，结果未保存）
{
	int v1, v2, t1, t2;
	int a0, b0; 
	big tmp1 = mirvar(0);
	big tmp2 = mirvar(0);
/*#ifndef BINIT
#define BINIT
	binary_init();
#endif*/
	a0 = 173;
	b0 = (int)((logb2(n) - a0) * log(3) + 1);
	//a0 = 100;
	//b0 = 100;
	int numm = 0;

	while (n->len)
	{
		numm++;
		//cotnum(n, stdout);
		if (compare(n, mirvar(1)) == 0)
		{
			findapprox(n, a0, b0, &v1, &v2, &t1, &t2);
		}
		else findapprox(n, a0, b0, &v1, &v2, &t1, &t2);
		sftbit(arr[v1].a, t1, tmp1);
		sftbit(arr[v2].a, t2, tmp2);
		//printf("%d %d    %d %d\n", arr[v1].b0,arr[v1].s0, arr[v2].b0,arr[v2].s0);
		//cotnum(tmp1, stdout);
		//cotnum(tmp2, stdout);
		subtract(n, tmp1, tmp1);
		subtract(tmp2, n, tmp2);
		if (mr_compare(tmp1, tmp2) == 1)
		{
			copy(tmp2, n);
			a0 = t2;
			b0 = arr[v2].b0;
			//printf("tmp2\n");
		}
		else
		{
			copy(tmp1, n);
			a0 = t1;
			b0 = arr[v1].b0;
			//printf("tmp1\n");
		}
	}
	return numm;
	//printf("%d\n", numm);
}
