#include<time.h>
#include<stdlib.h>
#include "miracl.h"
#include <math.h>
#include<stdio.h>



//ÉèÖÃËæ»úbitÓÃ
void set16(big* t, big* p)
{
	big k = mirvar(0xffff);
	big tmp = mirvar(0);
	sftbit(k, -1, k);

	big s = mirvar(1);
	sftbit(s, 15, s);
	copy(k, t);
	copy(s, p);
}
void set32(big* t, big* p)
{
	big k = mirvar(0xffff);
	big tmp = mirvar(0);
	sftbit(k, 16, tmp);
	add(k, tmp, k);
	sftbit(k, -1, k);

	big s = mirvar(1);
	sftbit(s, 31, s);
	copy(k, t);
	copy(s, p);
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
	copy(s, p);
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

void set200(big* t, big* p)
{
	big k = mirvar(0xffff);
	big tmp = mirvar(0);
	big tp1 = mirvar(0);
	sftbit(k, 16, tmp);
	add(k, tmp, k);
	sftbit(k, 32, tmp);
	add(k, tmp, k);
	copy(tmp, tp1);

	sftbit(k, 64, tmp);
	add(k, tmp, k);

	sftbit(k, 72, tmp);
	sftbit(k, -1, k);
	sftbit(tp1, 8, tp1);
	incr(tp1, 127, tp1);
	add(k, tp1, k);

	big s = mirvar(1);
	sftbit(s, 199, s);
	copy(k, t);
	copy(s, p);
}


void set320(big* t, big* p)
{
	big k = mirvar(0xffff);
	big t64 = mirvar(0);
	big tmp = mirvar(0);
	sftbit(k, 16, tmp);
	add(k, tmp, k);
	sftbit(k, 32, tmp);
	add(k, tmp, k);
	copy(k, t64);


	sftbit(k, 64, tmp);
	add(k, tmp, k);
	

	sftbit(k, 128, tmp);
	add(k, tmp, k);


	sftbit(k, 64, k);
	add(t64, k, k);
	


	sftbit(k, -1, k);

	big s = mirvar(1);
	sftbit(s, 319, s);
	copy(k, t);
	copy(s, p);
}
void set384(big* t, big* p)
{
	big k = mirvar(0xffff);
	big t64 = mirvar(0);
	big tmp = mirvar(0);
	sftbit(k, 16, tmp);
	add(k, tmp, k);
	sftbit(k, 32, tmp);
	add(k, tmp, k);
	copy(k, t64);


	sftbit(k, 64, tmp);
	add(k, tmp, k);


	sftbit(k, 128, tmp);
	add(k, tmp, k);


	sftbit(k, 64, k);
	add(t64, k, k);
	sftbit(k, 64, k);
	add(t64, k, k);


	sftbit(k, -1, k);

	big s = mirvar(1);
	sftbit(s, 383, s);
	copy(k, t);
	copy(s, p);
}
void set448(big* t, big* p)
{
	big k = mirvar(0xffff);
	big t64 = mirvar(0);
	big tmp = mirvar(0);
	sftbit(k, 16, tmp);
	add(k, tmp, k);
	sftbit(k, 32, tmp);
	add(k, tmp, k);
	copy(k, t64);


	sftbit(k, 64, tmp);
	add(k, tmp, k);


	sftbit(k, 128, tmp);
	add(k, tmp, k);


	sftbit(k, 64, k);
	add(t64, k, k);
	sftbit(k, 64, k);
	add(t64, k, k);
	sftbit(k, 64, k);
	add(t64, k, k);


	sftbit(k, -1, k);

	big s = mirvar(1);
	sftbit(s, 447, s);
	copy(k, t);
	copy(s, p);
}
void set512(big* t, big* p)
{
	big k = mirvar(0xffff);
	big t64 = mirvar(0);
	big tmp = mirvar(0);
	sftbit(k, 16, tmp);
	add(k, tmp, k);
	sftbit(k, 32, tmp);
	add(k, tmp, k);
	copy(k, t64);


	sftbit(k, 64, tmp);
	add(k, tmp, k);


	sftbit(k, 128, tmp);
	add(k, tmp, k);


	sftbit(k, 64, k);
	add(t64, k, k);
	sftbit(k, 64, k);
	add(t64, k, k);
	sftbit(k, 64, k);
	add(t64, k, k);
	sftbit(k, 64, k);
	add(t64, k, k);


	sftbit(k, -1, k);

	big s = mirvar(1);
	sftbit(s, 511, s);
	copy(k, t);
	copy(s, p);
}
