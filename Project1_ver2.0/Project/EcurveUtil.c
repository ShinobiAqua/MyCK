#include <stdio.h>
#include <stdlib.h>
#include "miracl.h"
#include"resolve.h"

#define  uint unsigned int
#define MR_ECC_STORE_N  4



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


void ecurve_fif(_MIPD_ epoint* p)
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
			else 
				nres_modmult(_MIPP_ p->Z, p->Z, mr_mip->w6);//如果未标准化  则w6=Z^2
	
			
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

	

	// w8=T
	//step1--------------------
	nres_modmult(_MIPP_ p->Y, p->Y, mr_mip->w2);//w2=Y2
	nres_modmult(_MIPP_ mr_mip->w2, mr_mip->w2, mr_mip->w3);//w3=Y4
	nres_modadd(_MIPP_ p->X, mr_mip->w2, mr_mip->w4);//w4=X+Y2
	nres_modmult(_MIPP_ mr_mip->w4, mr_mip->w4, mr_mip->w4);//W4=(X+Y2)2
	nres_modmult(_MIPP_ p->X, p->X, mr_mip->w1);//W1=X^2
	nres_modsub(_MIPP_ mr_mip->w4, mr_mip->w1, mr_mip->w4);//W4=(X+Y2)2-X2
	nres_modsub(_MIPP_ mr_mip->w4, mr_mip->w3, mr_mip->w4);//W4=(X+Y2)2-X2-Y4
	nres_premult(_MIPP_ mr_mip->w4, 6, mr_mip->w4);
	//nres_modadd(_MIPP_ mr_mip->w4, mr_mip->w4, mr_mip->w4);//w4=2[(X+Y2)2-X2-Y4]
	//nres_modadd(_MIPP_ mr_mip->w4, mr_mip->w4, mr_mip->w5);//w5=4[(X+Y2)2-X2-Y4]
	//nres_modadd(_MIPP_ mr_mip->w4, mr_mip->w5, mr_mip->w4);//w4=12XY2
	//**************************
	//W1=X2 W2=Y2 W3=Y4 W4=12XY2 W8=T

	//step2--------------------
	nres_modmult(_MIPP_ mr_mip->w8, mr_mip->w8, mr_mip->w7);//W7=T2
	nres_modsub(_MIPP_ mr_mip->w7, mr_mip->w4, mr_mip->w1);//W1=A
	//**************************
	//W1=A W2=Y2 W3=Y4 W4=12XY2 W7=T2 W8=T

	//step3---------------------
	nres_premult(_MIPP_ mr_mip->w3, 16, mr_mip->w5);
	//nres_modadd(_MIPP_ mr_mip->w3, mr_mip->w3, mr_mip->w5);//W5=2Y4
	//nres_modadd(_MIPP_ mr_mip->w5, mr_mip->w5, mr_mip->w5);//W5=4Y4
	//nres_modadd(_MIPP_ mr_mip->w5, mr_mip->w5, mr_mip->w5);//W5=8Y4
	//nres_modadd(_MIPP_ mr_mip->w5, mr_mip->w5, mr_mip->w5);//W5=16Y4

	nres_modmult(_MIPP_ mr_mip->w1, mr_mip->w1, mr_mip->w11);//W11=A2
	nres_modadd(_MIPP_ mr_mip->w8, mr_mip->w1, mr_mip->w8);//W8=A+T
	nres_modmult(_MIPP_ mr_mip->w8, mr_mip->w8, mr_mip->w8);//W8=(A+T)2
	nres_modsub(_MIPP_ mr_mip->w8, mr_mip->w7, mr_mip->w8);//W8=(A+T)2-T2	
	nres_modsub(_MIPP_ mr_mip->w8, mr_mip->w11, mr_mip->w8);//W8=(A+T)2-T2-A2
	nres_modadd(_MIPP_ mr_mip->w8, mr_mip->w5, mr_mip->w8);//W8=B
	//**************************
	//W1=A W2=Y2 W3=Y4 W4=12XY2 W5=16Y4 W11=A2 W7=T2 W8=B


	//step4---------------------
	nres_modmult(_MIPP_ mr_mip->w1, mr_mip->w11, mr_mip->w4);//W4=A3
	nres_modmult(_MIPP_ mr_mip->w5, mr_mip->w8, mr_mip->w9);//W9=16BY4
	nres_modsub(_MIPP_ mr_mip->w4, mr_mip->w9, mr_mip->w5);//W5=C
	//**************************
	//W1=A W2=Y2 W3=Y4 W4=A3 W5=C W11=A2 W7=T2 W8=B W9=16BY4

	//step5---------------------
	nres_modadd(_MIPP_ mr_mip->w8, mr_mip->w2, mr_mip->w7);//W7=B+Y2
	nres_modmult(_MIPP_ mr_mip->w7, mr_mip->w7, mr_mip->w7);//W7=(B+Y2)2
	nres_modmult(_MIPP_ mr_mip->w8, mr_mip->w8, mr_mip->w8); //W8=B2
	nres_modsub(_MIPP_ mr_mip->w7, mr_mip->w8, mr_mip->w2); //W2=(B+Y2)2-B2
	nres_modsub(_MIPP_ mr_mip->w2, mr_mip->w3, mr_mip->w2); //W2=2BY2
	//**************************
	//W1=A W2=2BY2 W3=Y4 W4=A3 W5=C W6=A2 W7=(B+Y2)2 W8=B2 W9=16BY4
	
	//step6---------------------
	nres_modsub(_MIPP_ mr_mip->w5, mr_mip->w8, mr_mip->w7);//W7=C-B2
	nres_modadd(_MIPP_ mr_mip->w1, mr_mip->w7, mr_mip->w1);//W1=A+C-B2
	nres_modmult(_MIPP_ mr_mip->w1, mr_mip->w1, mr_mip->w1);//W1=(A+C-B2)2
	nres_modmult(_MIPP_ mr_mip->w7, mr_mip->w7, mr_mip->w7);//W7=(C-B2)2
	nres_modsub(_MIPP_ mr_mip->w1, mr_mip->w11, mr_mip->w1);//W1=(A+C-B2)2-A2
	nres_modsub(_MIPP_ mr_mip->w1, mr_mip->w7, mr_mip->w1);//W1=2A(C-B2)
	//**************************
	//W1=2A(C-B2) W2=2BY2 W3=Y4 W4=A3 W5=C W11=A2 W7=(C-B2)2 W8=B2 W9=16BY4

	//step7---------------------
	nres_modmult(_MIPP_ mr_mip->w5, mr_mip->w5, mr_mip->w10);//W10=C2
	nres_modmult(_MIPP_ p->X, mr_mip->w10, p->X);//X=X*C2
	nres_modmult(_MIPP_ mr_mip->w2, mr_mip->w1, mr_mip->w1);//W1=2BY2*(2A(C-B2))
	nres_modsub(_MIPP_ p->X, mr_mip->w1, p->X);//X=X*C2-2BY2*(2A(C-B2))
	nres_modadd(_MIPP_ p->X, p->X, p->X);//X=2*[X*C2-2BY2*(2A(C-B2))]
	nres_modadd(_MIPP_ p->X, p->X, p->X);//X=4*[X*C2-2BY2*(2A(C-B2))]
	//**************************
	//W1=2BY2*(2A(C-B2)) W2=2BY2 W3=Y4 W4=A3 W5=C W6=A2 W7=(C-B2)2 W8=B2 W9=16BY4 W10=C2


	//step8---------------------
	nres_modmult(_MIPP_ mr_mip->w8, mr_mip->w8, mr_mip->w8);//W8=B4
	nres_modadd(_MIPP_ mr_mip->w7, mr_mip->w7, mr_mip->w1);//W1=2*(C-B2)2
	nres_modadd(_MIPP_ mr_mip->w7, mr_mip->w1, mr_mip->w1);//W1=3*(C-B2)2
	nres_modadd(_MIPP_ mr_mip->w10, mr_mip->w8, mr_mip->w2);//W2=C2+B4
	nres_modsub(_MIPP_ mr_mip->w2, mr_mip->w1, mr_mip->w2);//W2=C2+B4-3*(C-B2)2
	nres_modmult(_MIPP_ mr_mip->w2, mr_mip->w4, mr_mip->w2);//W2=A3*[C2+B4-3*(C-B2)2]
	nres_modadd(_MIPP_ mr_mip->w9, mr_mip->w9, mr_mip->w9);//W9=32BY4
	nres_modmult(_MIPP_ mr_mip->w9, mr_mip->w8, mr_mip->w9);//W9=32BY4*B4
	nres_modsub(_MIPP_ mr_mip->w9, mr_mip->w2, mr_mip->w9);//W9=32BY4*B4-A3*[C2+B4-3*(C-B2)2]
	nres_modmult(_MIPP_ p->Y, mr_mip->w9, p->Y);
	nres_modadd(_MIPP_ p->Y, p->Y, p->Y);
	nres_modadd(_MIPP_ p->Y, p->Y, p->Y);
	//**************************
	//W1=3*(C-B2)2 W2=C2+B4 W3=Y4 W4=A3 W5=C W6=A2 W7=(C-B2)2 W8=B4 W9=32BY4*B4-A3*[C2+B4-3*(C-B2)2] W10=C2



	//W6=Z2
	//step9---------------------
	if (p->marker == MR_EPOINT_NORMALIZED)
		nres_modadd(_MIPP_ mr_mip->w6, mr_mip->w5, p->Z);
	else
		nres_modadd(_MIPP_ p->Z, mr_mip->w5, p->Z);//Z=Z+C
	nres_modmult(_MIPP_ p->Z, p->Z, p->Z);//Z=(Z+C)2
	nres_modsub(_MIPP_ p->Z, mr_mip->w10, p->Z);
	nres_modsub(_MIPP_ p->Z, mr_mip->w6, p->Z);
	
	//**************************

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


epoint* tmp5;
epoint* tmp7;
epoint* tmp11;
epoint* tmp13;
epoint* tmp17;
epoint* tmp;

void setpt(epoint* pa)
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

int my_ecurve_mult(_MIPD_ big e, epoint* pa, epoint* pt)
{ /* pt=e*pa; */
	int i, j;

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

		epoint_set(_MIPP_ NULL, NULL, 0, pt);
		tmp5= epoint_init();
		tmp7 = epoint_init();
		tmp11 = epoint_init();
		//tmp13 = epoint_init();
		//tmp17 = epoint_init();
		tmp = epoint_init();
		epoint_copy(pa, tmp);
		ecurve_double(tmp);
		ecurve_triple(tmp);
		epoint_copy(tmp, tmp5);
		epoint_copy(tmp, tmp7);
		ecurve_double(tmp);
		epoint_copy(tmp, tmp11);
		//epoint_copy(tmp, tmp13);
		//epoint_copy(tmp, tmp17);
		ecurve_sub(pa,tmp5);
		ecurve_add(pa,tmp7);
		ecurve_sub(pa,tmp11);
		//ecurve_add(pa, tmp13);
		//ecurve_add(tmp5, tmp17);
		


		short pow2[100] = { 0 };
		short pow3[100] = { 0 };
		short ISM[100] = { 0 };
		short isp[100] = { 0 };
		int len = 0;
		
		//span_dec_23(_MIPP_ mr_mip->w9, pow2, pow3, ISM, isp, &len);
		span_dec_23_mod(_MIPP_ mr_mip->w9, pow2, pow3, ISM, isp, &len);
		
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
				else if (isp[i] == 13)
					ecurve_sub(_MIPP_ tmp13, pt);
				else if (isp[i] == 17)
					ecurve_sub(_MIPP_ tmp17, pt);
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
				else if (isp[i] == 13)
					ecurve_add(_MIPP_ tmp13, pt);
				else if (isp[i] == 17)
					ecurve_add(_MIPP_ tmp17, pt);
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
			else if (isp[i] == 13)
				ecurve_sub(_MIPP_ tmp13, pt);
			else if (isp[i] == 17)
				ecurve_sub(_MIPP_ tmp17, pt);
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
			else if (isp[i] == 13)
				ecurve_add(_MIPP_ tmp13, pt);
			else if (isp[i] == 17)
				ecurve_add(_MIPP_ tmp17, pt);
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

	MR_OUT
		return 1;
	//return nadds;
}

int Tree_ecurve_mult(_MIPD_ big e, epoint* pa, epoint* pt)
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

		int ad = 0;
		int db = 0;
		int tp = 0;
		epoint_set(_MIPP_ NULL, NULL, 0, pt);
		tmp5 = epoint_init();
		tmp7 = epoint_init();
		tmp11 = epoint_init();
		//tmp13 = epoint_init();
		//tmp17 = epoint_init();
		tmp = epoint_init();
		epoint_copy(pa, tmp);
		ecurve_double(tmp);
		ecurve_triple(tmp);
		epoint_copy(tmp, tmp5);
		epoint_copy(tmp, tmp7);
		ecurve_double(tmp);
		epoint_copy(tmp, tmp11);
		//epoint_copy(tmp, tmp13);
		//epoint_copy(tmp, tmp17);
		ecurve_sub(pa, tmp5);
		ecurve_add(pa, tmp7);
		ecurve_sub(pa, tmp11);
		//ecurve_add(pa, tmp13);
		//ecurve_add(tmp5, tmp17);

		ad = 2;
		db = 1;
		tp = 1;


		short pow2[100] = { 0 };
		short pow3[100] = { 0 };
		short ISM[100] = { 0 };
		short isp[100] = { 0 };
		int len = 0;

		span_dec_23(_MIPP_ mr_mip->w9, pow2, pow3, ISM, isp, &len);
		//span_dec_23_mod(_MIPP_ mr_mip->w9, pow2, pow3, ISM, isp, &len);

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
				else if (isp[i] == 13)
					ecurve_sub(_MIPP_ tmp13, pt);
				else if (isp[i] == 17)
					ecurve_sub(_MIPP_ tmp17, pt);
				else
					ecurve_sub(_MIPP_ pa, pt);
				ad++;
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
				else if (isp[i] == 13)
					ecurve_add(_MIPP_ tmp13, pt);
				else if (isp[i] == 17)
					ecurve_add(_MIPP_ tmp17, pt);
				else
					ecurve_add(_MIPP_ pa, pt);
				ad++;
			}
			b = pow2[i] - pow2[i - 1];
			t = pow3[i] - pow3[i - 1];

			while (t > 0)
			{
				ecurve_triple(_MIPP_ pt);
				tp++;
				t--;
			}
			while (b > 0)
			{
				ecurve_double(_MIPP_ pt);
				db++;
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
			else if (isp[i] == 13)
				ecurve_sub(_MIPP_ tmp13, pt);
			else if (isp[i] == 17)
				ecurve_sub(_MIPP_ tmp17, pt);
			else
				ecurve_sub(_MIPP_ pa, pt);
			ad++;
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
			else if (isp[i] == 13)
				ecurve_add(_MIPP_ tmp13, pt);
			else if (isp[i] == 17)
				ecurve_add(_MIPP_ tmp17, pt);
			else
				ecurve_add(_MIPP_ pa, pt);
			ad++;
		}
		b = pow2[0];
		t = pow3[0];
		while (t > 0)
		{
			ecurve_triple(_MIPP_ pt);
			tp++;
			t--;
		}
		while (b > 0)
		{
			ecurve_double(_MIPP_ pt);
			db++;
			b--;
		}
		double tot;
		tot = 9.8 * ad + 6.2 * db + 12.2 * tp;
		//*s = tot;
		/*printf("ad:%d  db:%d  tp:%d\n", ad, db, tp);
		printf("tot:%lf\n", tot);*/

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

int his_ecurve_mult(_MIPD_ big e, epoint* pa, epoint* pt)
{ /* pt=e*pa; */
	int i, j, n, nb, nbs, nzs, nadds;
	epoint* table[MR_ECC_STORE_N];
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
	epoint_copy(pa, pt);

	if (size(mr_mip->w9) < 0)
	{ /* pt = -pt */
		negify(mr_mip->w9, mr_mip->w9);
		epoint_negate(_MIPP_ pt);
	}

	if (size(mr_mip->w9) == 1)
	{
		MR_OUT
			return 0;
	}

	premult(_MIPP_ mr_mip->w9, 3, mr_mip->w10);      /* h=3*e */

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

		for (i = 0; i <= MR_ECC_STORE_N - 1; i++)
		{
			table[i] = epoint_init_mem(_MIPP_ mem, i);
#ifndef MR_AFFINE_ONLY
			work[i] = mirvar_mem(_MIPP_ mem1, i);
#endif
		}

		int ad = 0;
		int db = 0;

		epoint_copy(pt, table[0]);
		epoint_copy(table[0], table[MR_ECC_STORE_N - 1]);
		ecurve_double(_MIPP_ table[MR_ECC_STORE_N - 1]);
		/*   epoint_norm(_MIPP_ table[MR_ECC_STORE_N-1]); */

		for (i = 1; i < MR_ECC_STORE_N - 1; i++)
		{ /* precomputation */
			epoint_copy(table[i - 1], table[i]);
			ecurve_add(_MIPP_ table[MR_ECC_STORE_N - 1], table[i]);
			ad++;
		}
		ecurve_add(_MIPP_ table[MR_ECC_STORE_N - 2], table[MR_ECC_STORE_N - 1]);
		ad++;

#ifndef MR_AFFINE_ONLY
		epoint_multi_norm(_MIPP_ MR_ECC_STORE_N, work, table);
#endif

		nb = logb2(_MIPP_ mr_mip->w10);
		nadds = 0;
		epoint_set(_MIPP_ NULL, NULL, 0, pt);
		for (i = nb - 1; i >= 1;)
		{ /* add/subtract */
			if (mr_mip->user != NULL) (*mr_mip->user)();
			n = mr_naf_window(_MIPP_ mr_mip->w9, mr_mip->w10, i, &nbs, &nzs, MR_ECC_STORE_N);
			for (j = 0; j < nbs; j++)
			{
				ecurve_double(_MIPP_ pt);
				db++;
			}
			if (n > 0) { ecurve_add(_MIPP_ table[n / 2], pt); nadds++;  ad++; }
			if (n < 0) { ecurve_sub(_MIPP_ table[(-n) / 2], pt); nadds++;  ad++; }
			i -= nbs;
			if (nzs)
			{
				for (j = 0; j < nzs; j++) {
					ecurve_double(_MIPP_ pt);
					db++;
				}
				i -= nzs;
			}
		}

		double tot;
		tot = 9.8 * ad + 6.2 * db;
		/*printf("ad:%d db:%d\n", ad, db);
		printf("tot:%lf\n", tot);*/

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
		{ /* add/subtract method */
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
		return nadds;
}

int naf_window(_MIPD_ big e)
{ /* pt=e*pa; */
	int i, j, n, nb, nbs, nzs, nadds;
	copy(e, mr_mip->w9);
	premult(_MIPP_ mr_mip->w9, 3, mr_mip->w10);      /* h=3*e */
	nb = logb2(_MIPP_ mr_mip->w10);
	nadds = 0;
	for (i = nb - 1; i >= 1;)
		{ /* add/subtract */
			if (mr_mip->user != NULL) (*mr_mip->user)();
			n = mr_naf_window(_MIPP_ mr_mip->w9, mr_mip->w10, i, &nbs, &nzs, MR_ECC_STORE_N);
			for (j = 0; j < nbs; j++)
			{
			}
			if (n > 0) {  nadds++;  }
			if (n < 0) {  nadds++;  }
			i -= nbs;
			if (nzs)
			{
				for (j = 0; j < nzs; j++) {
					
				}
				i -= nzs;
			}
		}
		return nadds;
}

//新建一个椭圆曲线上的点
epoint* NewPoint(big x, big y) {
	epoint* result = epoint_init();
	epoint_set(x, y, 0, result);
	return result;
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
	my_ecurve_mult(a, b, result);
	return result;
}

epoint* his_MultiplyEpoint(big a, epoint* b) {
	epoint* result = epoint_init();
	his_ecurve_mult(a, b, result);
	return result;
}

epoint* T_MultiplyEpoint(big a, epoint* b) {
	epoint* result = epoint_init();
	Tree_ecurve_mult(a, b, result);
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