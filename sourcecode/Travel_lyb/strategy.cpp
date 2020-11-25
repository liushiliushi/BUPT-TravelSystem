#include "strategy.h"
extern Manager ma;
Strategy::Strategy()
{

}

void Strategy::init_node()
{
	QString tem;
	for (int i = 0; i < CITY_NUM; i++)//���γ�ʼ��ÿ���ڵ�
	{
		tem = ma.city_list[i].name;
		/*tem = cities[i].name;*/
		for (int j = 0; j < ma.time_table_size; j++)//������ÿ��ʱ�̱������ʼ��=�ڵ����ӽ�������
		{
			if (ma.time_table[j].dep == tem)
			{
				ma.city_list[i].sche.push_back(ma.time_table[j]);
			}
		}
	}
}

void Strategy::show_nodes()
{
	qDebug() << "��ʾ�ڵ�" << endl;
	for (int i = 0; i < ma.city_num; i++)
	{
		int num = ma.city_list[i].sche.size();//�ߵ�����
		qDebug() << "�ߵ�����Ϊ" << num << endl;
		for (int j = 0; j < num; j++)//������ÿ��ʱ�̱������ʼ��=�ڵ����ӽ�������
		{
			qDebug() << ma.city_list[i].sche[j].des << "	";
		}
		qDebug() << endl;
	}
}

int Strategy::getIndex(QString city)
{
	for (int i = 0; i < ma.city_num; i++)
	{
		if (ma.city_list[i].name == city)
		{
			return i;
		}
	}
	return -1;//���û�ҵ�����-1
}

int Strategy::getRiskValue(QString vehicle)
{
	if (vehicle == "�ɻ�")
	{
		return 9;
	}
	else if (vehicle == "��")
	{
		return 5;
	}
	else
	{
		return 2;
	}
}

int Strategy::dij1(Traveler &tra)
{
	if (tra.departure == tra.destination)
	{
		return -1;
	}
	QString dep = tra.departure;
	QString des = tra.destination;
	QDateTime start = tra.start_time;
	QDateTime ddl = tra.deadline;
	int S[CITY_NUM];//�жϸõ��Ƿ��Ѵ��뵽S�����е����飬��û���룬ֵΪ-1�������룬��Ϊ1
	int P[CITY_NUM];//�ڵ��ǰ���ڵ�
	float U[CITY_NUM];//�õ㵽Դ��ľ���
	QDateTime T[CITY_NUM];//�Ӹó��г���������ʱ��         T[a]=b��ʾ����a��ʱ��Ϊb
	int A[CITY_NUM];//��ǰ��ѡ��ıߵ����                  A[a]=b��ʾ����aѡ���˵�b��ʱ�̱�
	float minRisk = 10000;//������Сֵ
	//�ҵ������±�
	int depIndex = getIndex(dep);//�ҵ��������е��±�
	qDebug() << "������" << depIndex << endl;
	int desIndex = getIndex(des);//�ҵ�Ŀ�ĳ��е��±�
	//��ʼ��S����
	for (int i = 0; i < ma.city_num; i++)
	{
		S[i] = -1;
	}
	//��ʼ��U����
	for (int i = 0; i < ma.city_num; i++)
	{
		U[i] = 10000;
	}
	//��ʼ��A����
	for (int i = 0; i < ma.city_num; i++)
	{
		A[i] = -1;
	}
	//��ʼ��P����
	for (int i = 0; i < ma.city_num; i++)
	{
		P[i] = -1;
	}
	U[depIndex] = 0;//��ʼ�㵽��ʼ��ľ���Ϊ0
	//��ʼ��T����
	T[depIndex] = start;//�������ʱ��=��ʼʱ��
	int cur = depIndex;//��ǰ�ڵ��±�
	P[depIndex] = depIndex;
	qDebug() << "ddl:" << ddl.toString("MM-dd HH:mm");
	while (1)
	{
		qDebug() << "��ʼ��ѯ·��" << endl;
		int min = 0;//���������С�ĵ��±�Ϊ0
		//����һ����Ϊ������С��ĵ�,ȡһ����û�м���S�����
		for (int i = 0; i < ma.city_num; i++)
		{
			if (S[i] == -1)
			{
				min = i;
			}
		}

		//��U��������С��һ�������
		for (int i = 0; i < ma.city_num; i++)
		{
			//�ҵ�U����С�������±�
			if ((S[i] == -1) && (U[i] < U[min]))
			{
				min = i;
			}
		}
		if (U[min] != 10000)
		{
			S[min] = 1;//���±�Ϊmin�ĵ����S���飬������һ����Ϊcur
			cur = min;//���µ�ǰ���±�
			qDebug() << "--------------------------------��" << min << "�Žڵ����S����" << endl;
			qDebug() << "���S����" << endl;
			for (int i = 0; i < ma.city_num; i++)
			{
				qDebug() << S[i] << "	";
			}
			qDebug() << endl;
		}
		else
		{
			qDebug() << "û��·�߿��Ե���" << endl;
			return -1;
		}
		//�����������յ㣬��ô�Ѿ��������ѭ��
		if (cur == desIndex)
		{
			qDebug() << "�����յ㣡!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!" << endl;
			//д���ÿ�����·��
			int before;
			while (cur != P[cur])
			{
				qDebug() << "���ʱ�̱�" << endl;
				Schedule fact;
				//�ҵ���һ������±�
				before = P[cur];
				if (before == -1)
				{
					return -1;
				}
				qDebug() << cur << "����һ����Ϊ" << before << endl;
				//�ҵ���һ����ѡ�еıߵ��±�
				int i = A[cur];
				fact = ma.city_list[before].sche[i];
				fact.start_time.setDate(T[cur].date());//�޸Ĵ���һ���㿪ʼ����������
				fact.arrival_time.setDate(T[cur].date());//�޸ĵ��ﵱǰ�������
				tra.route.insert(tra.route.begin(), fact);
				cur = before;
			}
			tra.showRoute();//��ʾ�ÿ�·��
			break;
		}
		//�Ըռ���ĵ�min���в�������������
		//��min��ÿһ���߽��в���
		int arcNum = ma.city_list[cur].sche.size();
		////�����������û�г��Σ����޷������յ�
		//if (arcNum == 0)
		//{
		//	qDebug() << "û��·�߿��Ե���" << endl;
		//	return -1;
		//}
		for (int i = 0; i < arcNum; i++)
		{
			qDebug() << "����ڵ�" << cur << "�ĵ�" << i << "��ʱ�̱�" << endl;
			Schedule tem = ma.city_list[cur].sche[i];//��ǰ����
			qDebug() << "�ó���Ŀ�ĵ�Ϊ" << tem.des << endl;
			int nextIndex = getIndex(tem.des);//��õ������±�
			float risk;//ѡ��ǰ·�ߣ���һ�ε�riskֵ
			if (S[nextIndex] != -1)//����Ҫ�߻�ͷ·
			{
				qDebug() << "�߻�ͷ·" << endl;
				continue;//��һ��
			}
			//��ý�ͨ���߷���ֵ
			float vehicleRisk = getRiskValue(tem.vehicle);
			float cityRisk = ma.city_list[cur].risk;
			if (T[cur].time() < ma.city_list[cur].sche[i].start_time.time())//�������ʱ�����ڵ��쳵����ʼʱ��
			{
				//�������ֵ=����ǰ����ʱ��*���з���+��ͨʱ��*����ʱ��*��ͨ����
				risk = (float)T[cur].time().secsTo(tem.start_time.time()) / 3600 * cityRisk
					+ (float)tem.start_time.time().secsTo(tem.arrival_time.time()) / 3600 * cityRisk * vehicleRisk;
				//������·�߷��ո��ͣ�����U�����T�����A����
				if ((U[cur] + risk) < U[nextIndex])
				{
					qDebug() << "cur:" << cur << endl;
					qDebug() << "U[cur]:" << U[cur] << endl;
					
					T[nextIndex].setDate(T[cur].date());
					T[nextIndex].setTime(tem.arrival_time.time()); //���µ���nextIndex��ʱ��
					int s = T[nextIndex].secsTo(ddl);
					if (s < 0)
					{
						qDebug() << "��ǰ��ʱ" << endl;
						continue;
					}
					U[nextIndex] = U[cur] + risk;
					A[nextIndex] = i;  //����nextIndexѡ���˵�i��ʱ�̱�
					P[nextIndex] = cur;  //ǰ���ڵ�
					qDebug() << "**************************" << endl;
					qDebug() << "U�������Ϊ" << U[nextIndex] << endl;
					qDebug() << "T�������Ϊ" << T[nextIndex].toString("M.d hh:mm");
					qDebug() << "**************************" << endl;
				}
			}
			else//�������ڵ�����ʼʱ�䣬���һ������
			{
				qDebug() << "���ڵ�����ʼʱ��" << endl;
				//�������ֵ
				risk = ((float)T[cur].time().secsTo(tem.start_time.time()) / 3600 + 24)* cityRisk
					+ (float)tem.start_time.time().secsTo(tem.arrival_time.time()) / 3600 * cityRisk * vehicleRisk;
				qDebug() << "ͣ���ڳ��е�ʱ��" << ((float)T[cur].time().secsTo(tem.start_time.time()) / 3600 + 24) << endl;
				//������·�߷��ո��ͣ�����U�����T����
				if ((U[cur] + risk) < U[nextIndex])
				{
					
					//��ʼʱ��+1��
					T[nextIndex].setDate(T[cur].date());
					T[nextIndex] = T[nextIndex].addDays(1);
					T[nextIndex].setTime(tem.arrival_time.time());
					int s = T[nextIndex].secsTo(ddl);
					if (s < 0)
					{
						qDebug() << "��ǰ��ʱ" << endl;
						continue;
					}
					U[nextIndex] = U[cur] + risk;
					A[nextIndex] = i;
					P[nextIndex] = cur;  //ǰ���ڵ�
					qDebug() << "**************************" << endl;
					qDebug() << "U�������Ϊ" << U[nextIndex] << endl;
					qDebug() << "T�������Ϊ" << T[nextIndex].toString("M.d hh:mm");
					qDebug() << "**************************" << endl;
				}
			}

		}
		qDebug() << "���U����" << endl;
		for (int i = 0; i < ma.city_num; i++)
		{
			qDebug() << U[i] << "	";
		}
		qDebug() << endl;
		qDebug() << "���S����" << endl;
		for (int i = 0; i < ma.city_num; i++)
		{
			qDebug() << S[i] << "	";
		}
		qDebug() << endl;
		qDebug() << "���P����" << endl;
		for (int i = 0; i < ma.city_num; i++)
		{
			qDebug() << P[i] << "	";
		}
		qDebug() << endl;
		qDebug() << "���A����" << endl;
		for (int i = 0; i < ma.city_num; i++)
		{
			qDebug() << A[i] << "	";
		}
		qDebug() << endl;
	}
	return 0;
}


int Strategy::dij2(Traveler &tra)//����ʱ
{
	if (tra.departure == tra.destination)
	{
		return -1;
	}
	QString dep = tra.departure;
	QString des = tra.destination;
	QDateTime start = tra.start_time;
	QDateTime ddl = tra.deadline;
	int S[CITY_NUM];//�жϸõ��Ƿ��Ѵ��뵽S�����е����飬��û���룬ֵΪ-1�������룬��Ϊ1
	int P[CITY_NUM];//�ڵ��ǰ���ڵ�
	float U[CITY_NUM];//�õ㵽Դ��ľ���
	QDateTime T[CITY_NUM];//�Ӹó��г���������ʱ��         T[a]=b��ʾ����a��ʱ��Ϊb
	int A[CITY_NUM];//��ǰ��ѡ��ıߵ����                  A[a]=b��ʾ����aѡ���˵�b��ʱ�̱�
	float minRisk = 10000;//������Сֵ
	//�ҵ������±�
	int depIndex = getIndex(dep);//�ҵ��������е��±�
	qDebug() << "������" << depIndex << endl;
	int desIndex = getIndex(des);//�ҵ�Ŀ�ĳ��е��±�
	//��ʼ��S����
	for (int i = 0; i < CITY_NUM; i++)
	{
		S[i] = -1;
	}
	//��ʼ��U����
	for (int i = 0; i < CITY_NUM; i++)
	{
		U[i] = 10000;
	}
	//��ʼ��A����
	for (int i = 0; i < CITY_NUM; i++)
	{
		A[i] = -1;
	}
	//��ʼ��P����
	for (int i = 0; i < CITY_NUM; i++)
	{
		P[i] = -1;
	}
	U[depIndex] = 0;//��ʼ�㵽��ʼ��ľ���Ϊ0
	//��ʼ��T����
	T[depIndex] = start;//�������ʱ��=��ʼʱ��
	int cur = depIndex;//��ǰ�ڵ��±�
	P[depIndex] = depIndex;
	while (1)
	{
		qDebug() << "��ʼ��ѯ·��" << endl;
		int min = 0;//���������С�ĵ��±�Ϊ0
		//����һ����Ϊ������С��ĵ�,ȡһ����û�м���S�����
		for (int i = 0; i < ma.city_num; i++)
		{
			if (S[i] == -1)
			{
				min = i;
			}
		}
		qDebug() << "��min��" << min << endl;
		
		//��U��������С��һ�������
		for (int i = 0; i < ma.city_num; i++)
		{
			//�ҵ�U����С�������±�
			if ((S[i] == -1) && (U[i] < U[min]))
			{
				min = i;
				qDebug() << "min:" << min << endl;
			}
		}
		if (U[min] != 10000)
		{
			S[min] = 1;//���±�Ϊmin�ĵ����S���飬������һ����Ϊcur
			cur = min;//���µ�ǰ���±�
			qDebug() << "--------------------------------��" << min << "�Žڵ����S����" << endl;
			qDebug() << "���S����" << endl;
			for (int i = 0; i < ma.city_num; i++)
			{
				qDebug() << S[i] << "	";
			}
			qDebug() << endl;
		}
		else
		{
			qDebug() << "û��·�߿��Ե���" << endl;
			return -1;
		}
		
		//�����������յ㣬��ô�Ѿ��������ѭ��
		if (cur == desIndex)
		{
			qDebug() << "�����յ㣡!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!" << endl;
			//д���ÿ�����·��
			int before;
			while (cur != P[cur])
			{
				qDebug() << "���ʱ�̱�" << endl;
				Schedule fact;
				//�ҵ���һ������±�
				before = P[cur];
				if (before == -1)
				{
					qDebug() << "û��·�߿��Ե���" << endl;
					return -1;
				}
				qDebug() << cur << "����һ����Ϊ" << before << endl;
				//�ҵ���һ����ѡ�еıߵ��±�
				int i = A[cur];
				fact = ma.city_list[before].sche[i];
				fact.start_time.setDate(T[cur].date());//�޸Ĵ���һ���㿪ʼ����������
				fact.arrival_time.setDate(T[cur].date());//�޸ĵ��ﵱǰ�������
				tra.route.insert(tra.route.begin(), fact);
				cur = before;
			}
			tra.showRoute();//��ʾ�ÿ�·��
			break;
		}
		//�Ըռ���ĵ�min���в�������������
		//��min��ÿһ���߽��в���
		int arcNum = ma.city_list[cur].sche.size();
		//�����������û�г��Σ����޷������յ�
		/*if (arcNum == 0)
		{
			qDebug() << "û��·�߿��Ե���" << endl;
			return -1;
		}*/
		for (int i = 0; i < arcNum; i++)
		{
			qDebug() << "����ڵ�" << cur << "�ĵ�" << i << "��ʱ�̱�" << endl;
			Schedule tem = ma.city_list[cur].sche[i];//��ǰ����
			qDebug() << "�ó���Ŀ�ĵ�Ϊ" << tem.des << endl;
			int nextIndex = getIndex(tem.des);//��õ������±�
			float risk;//ѡ��ǰ·�ߣ���һ�ε�riskֵ
			if (S[nextIndex] != -1)//����Ҫ�߻�ͷ·
			{
				qDebug() << "�߻�ͷ·" << endl;
				continue;//��һ��
			}
			//��ý�ͨ���߷���ֵ
			float vehicleRisk = getRiskValue(tem.vehicle);
			float cityRisk = ma.city_list[cur].risk;
			if (T[cur].time() < ma.city_list[cur].sche[i].start_time.time())//�������ʱ�����ڵ��쳵����ʼʱ��
			{
				qDebug() << "�������ʱ��Ϊ" << T[cur].toString("M.d hh:mm");
				qDebug() << "cityrisk" << cityRisk << endl;
				qDebug() << "vehiclerisk" << vehicleRisk << endl;
				//�������ֵ=����ǰ����ʱ��*���з���+��ͨʱ��*����ʱ��*��ͨ����
				risk = (float)T[cur].time().secsTo(tem.start_time.time()) / 3600 * cityRisk 
					+ (float)tem.start_time.time().secsTo(tem.arrival_time.time()) / 3600 * cityRisk * vehicleRisk;
				qDebug() <<"ͣ���ڳ��е�ʱ��" << (float)T[cur].time().secsTo(tem.start_time.time()) / 3600 << endl;
				//������·�߷��ո��ͣ�����U�����T�����A����
				if ((U[cur] + risk) < U[nextIndex])
				{
					qDebug() << "cur:" << cur << endl;
					qDebug() << "U[cur]:" << U[cur] << endl;
					U[nextIndex] = U[cur] + risk;
					T[nextIndex].setDate(T[cur].date());
					T[nextIndex].setTime(tem.arrival_time.time()); //���µ���nextIndex��ʱ��
					A[nextIndex] = i;  //����nextIndexѡ���˵�i��ʱ�̱�
					P[nextIndex] = cur;  //ǰ���ڵ�
					/*qDebug() << "**************************" << endl;
					qDebug() << "U�������Ϊ" << U[nextIndex] << endl;
					qDebug() << "T�������Ϊ" << T[nextIndex].toString("M.d hh:mm");
					qDebug() << "**************************" << endl;*/
				}
			}
			else//�������ڵ�����ʼʱ�䣬���һ������
			{
				qDebug() << "���ڵ�����ʼʱ��" << endl;
				//�������ֵ
				risk = ((float)T[cur].time().secsTo(tem.start_time.time()) / 3600 + 24)* cityRisk
					+ (float)tem.start_time.time().secsTo(tem.arrival_time.time()) / 3600 * cityRisk * vehicleRisk;
				qDebug() << "ͣ���ڳ��е�ʱ��" << ((float)T[cur].time().secsTo(tem.start_time.time()) / 3600 + 24) << endl;
				//������·�߷��ո��ͣ�����U�����T����
				if ((U[cur] + risk) < U[nextIndex])
				{
					U[nextIndex] = U[cur] + risk;
					//��ʼʱ��+1��
					T[nextIndex].setDate(T[cur].date());
					T[nextIndex] = T[nextIndex].addDays(1);
					T[nextIndex].setTime(tem.arrival_time.time());
					A[nextIndex] = i;
					P[nextIndex] = cur;  //ǰ���ڵ�
					/*qDebug() << "**************************" << endl;
					qDebug() << "U�������Ϊ" << U[nextIndex] << endl;
					qDebug() << "T�������Ϊ" << T[nextIndex].toString("M.d hh:mm");
					qDebug() << "**************************" << endl;*/
				}
			}

		}
		/*qDebug() << "���U����" << endl;
		for (int i = 0; i < CITY_NUM; i++)
		{
			qDebug() << U[i] << "	";
		}
		qDebug() << endl;
		qDebug() << "���S����" << endl;
		for (int i = 0; i < CITY_NUM; i++)
		{
			qDebug() << S[i] << "	";
		}
		qDebug() << endl;
		qDebug() << "���P����" << endl;
		for (int i = 0; i < CITY_NUM; i++)
		{
			qDebug() << P[i] << "	";
		}
		qDebug() << endl;
		qDebug() << "���A����" << endl;
		for (int i = 0; i < CITY_NUM; i++)
		{
			qDebug() << A[i] << "	";
		}
		qDebug() << endl;*/
	}
	return 0;
}

Strategy::~Strategy()
{

}