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
	/*big cert = mirvar(0);
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
	cotnum(origin, stdout);*/

}