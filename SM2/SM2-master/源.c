void Decompose(_MIPD_ big n, short POW2[], short POW3[], short ISM[], int* let) {

	big myb[3];//��������+1��Ĵ�����ʱֵ  -1��Ĵ�����ʱֵ  �ʹ���ʱ�м���
	//W2B3 ��˼��witch 2 is bigger than 3 ����2�ļ��δ��ڵ�ǰ��3�ݴ���  ���ֵͨ��W2B3[]�������ȡ�ã�����W2B3[3]����˼�� 2����С�����ܴ���3��3��
	int W2B3, W3B2;
	int npow2 = 1;
	int npow3 = 1;
	uint flg = 0;
	myb[0] = mirvar(0);
	myb[1] = mirvar(0);
	myb[2] = mirvar(0);
	copy(n, myb[0]);

	int fl = 0;//fl��ģ3�������
	int mc = -1;
	int pow2 = 0;
	int pow3 = 0;
	int id = 0;
	// myb[lid]��-1��Ĵ�����ʱֵ   myb[rid]��+1�����ʱ����ֵ   myb[id]�ǵ�ǰ������м��� myb[lid]=myb[id]-1,myb[rid]=myb[id]+1
	// ֮���������ָ��ӵ�д����Ϊ�˼��ٹ���ĸ��ơ�  
	int lid, rid;

	int m4;
	fl = remain(myb[id], 3);
	while ((myb[id]->len) && !mr_testbit(_MIPP_ myb[id], 0))//һֱ��2�������ܳ�
	{
		sftbit(myb[id], -1, myb[id]);
		//һ������2��ģ3����ٿ���ͨ��flֱ�����
		fl = fl + (3 - fl * 2);
		fl %= 3;
		pow2 += 1;
	}
	while ((myb[id]->len) && (fl == 0))//һֱ��3�������ܳ�
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
			if (!m4)//3����-1 ��  2����-1 ��
			{
				decr(myb[id], 1, myb[id]);
				fl = (fl - 1) % 3;
				if (!myb[id]->len)   //�������ж�-1���Ƿ�Ϊ0  Ϊ0���˳�ѭ����
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
			else//3����-1 �� 2����+1 ��
			{
				//����Ӧ����+1�����ٱ�2��2�γ�    -1�����ٱ�2*3��
				//Ϊ�˿�����+1��ֻ��2��-1��ֻ��3�Ƚ�
				//����ͬʱ������2
				//�����ǱȽ�+1�����2���� �� -1�����2����  �ĸ��ܹ���������
				//��ʱ����һ�����ٱ�һ��2������һ�����ٱ�һ��3��
				//��������npow2=1,npow3=1��
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
					//flg�����жϵ�ǰ���ڳ�2���ǳ�3
					if (!flg) {
						if (!mr_testbit(_MIPP_ myb[rid], 0))//���ų�һ��2
						{
							sftbit(myb[rid], -1, myb[rid]);
							npow2++;
							if (npow2 >= W2B3)//�����ʱ��ȳ�3���Ǳ߳���Ҫ����
							{
								flg = !flg;//�ͷ�תflg  ת����3���Ǳ�
								W3B2 = W3BT2[npow2];
							}
						}
						else {// ����Ҳ����˵������ͨ������2ʹ�ñ����������ڳ�3����һ���ˣ���ʱ��ֱ��ѡ���3����һ�߶�Ӧ��-1

							id = (id + 2) % 3;//��������Ϊlid��id����ʱ��ߣ�rid��id��˳ʱ���   �������� lid=0 id=1 rid=2| id=0 rid=1 lid=2 |  rid=0 lid=1 id=2
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
			if (m4)//3����+1 ��  2����+1 ��
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
			else//3����+1 ��  2����-1 ��
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