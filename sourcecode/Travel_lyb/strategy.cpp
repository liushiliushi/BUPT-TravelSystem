#include "strategy.h"
extern Manager ma;
Strategy::Strategy()
{

}

void Strategy::init_node()
{
	QString tem;
	for (int i = 0; i < CITY_NUM; i++)//依次初始化每个节点
	{
		tem = ma.city_list[i].name;
		/*tem = cities[i].name;*/
		for (int j = 0; j < ma.time_table_size; j++)//依次找每个时刻表项，把起始地=节点的添加进边组中
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
	qDebug() << "显示节点" << endl;
	for (int i = 0; i < ma.city_num; i++)
	{
		int num = ma.city_list[i].sche.size();//边的数量
		qDebug() << "边的数量为" << num << endl;
		for (int j = 0; j < num; j++)//依次找每个时刻表项，把起始地=节点的添加进边组中
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
	return -1;//如果没找到返回-1
}

int Strategy::getRiskValue(QString vehicle)
{
	if (vehicle == "飞机")
	{
		return 9;
	}
	else if (vehicle == "火车")
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
	int S[CITY_NUM];//判断该点是否已存入到S集合中的数组，若没加入，值为-1，若加入，则为1
	int P[CITY_NUM];//节点的前驱节点
	float U[CITY_NUM];//该点到源点的距离
	QDateTime T[CITY_NUM];//从该城市出发的最早时间         T[a]=b表示到达a的时间为b
	int A[CITY_NUM];//当前点选择的边的序号                  A[a]=b表示到达a选择了第b个时刻表
	float minRisk = 10000;//风险最小值
	//找到城市下标
	int depIndex = getIndex(dep);//找到出发城市的下标
	qDebug() << "出发地" << depIndex << endl;
	int desIndex = getIndex(des);//找到目的城市的下标
	//初始化S数组
	for (int i = 0; i < ma.city_num; i++)
	{
		S[i] = -1;
	}
	//初始化U数组
	for (int i = 0; i < ma.city_num; i++)
	{
		U[i] = 10000;
	}
	//初始化A数组
	for (int i = 0; i < ma.city_num; i++)
	{
		A[i] = -1;
	}
	//初始化P数组
	for (int i = 0; i < ma.city_num; i++)
	{
		P[i] = -1;
	}
	U[depIndex] = 0;//起始点到起始点的距离为0
	//初始化T数组
	T[depIndex] = start;//最早出发时间=起始时间
	int cur = depIndex;//当前节点下标
	P[depIndex] = depIndex;
	qDebug() << "ddl:" << ddl.toString("MM-dd HH:mm");
	while (1)
	{
		qDebug() << "开始查询路线" << endl;
		int min = 0;//假设距离最小的点下标为0
		//先找一个作为距离最小点的点,取一个还没有加入S数组的
		for (int i = 0; i < ma.city_num; i++)
		{
			if (S[i] == -1)
			{
				min = i;
			}
		}

		//把U数组中最小的一个点加入
		for (int i = 0; i < ma.city_num; i++)
		{
			//找到U中最小距离点的下标
			if ((S[i] == -1) && (U[i] < U[min]))
			{
				min = i;
			}
		}
		if (U[min] != 10000)
		{
			S[min] = 1;//把下标为min的点加入S数组，它的上一个点为cur
			cur = min;//更新当前点下标
			qDebug() << "--------------------------------把" << min << "号节点加入S数组" << endl;
			qDebug() << "输出S数组" << endl;
			for (int i = 0; i < ma.city_num; i++)
			{
				qDebug() << S[i] << "	";
			}
			qDebug() << endl;
		}
		else
		{
			qDebug() << "没有路线可以到达" << endl;
			return -1;
		}
		//假如加入的是终点，那么已经到达，跳出循环
		if (cur == desIndex)
		{
			qDebug() << "到达终点！!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!" << endl;
			//写入旅客最优路线
			int before;
			while (cur != P[cur])
			{
				qDebug() << "添加时刻表" << endl;
				Schedule fact;
				//找到上一个点的下标
				before = P[cur];
				if (before == -1)
				{
					return -1;
				}
				qDebug() << cur << "的上一个点为" << before << endl;
				//找到上一个点选中的边的下标
				int i = A[cur];
				fact = ma.city_list[before].sche[i];
				fact.start_time.setDate(T[cur].date());//修改从上一个点开始出发的日期
				fact.arrival_time.setDate(T[cur].date());//修改到达当前点的日期
				tra.route.insert(tra.route.begin(), fact);
				cur = before;
			}
			tra.showRoute();//显示旅客路线
			break;
		}
		//对刚加入的点min进行操作，更新数组
		//对min的每一条边进行操作
		int arcNum = ma.city_list[cur].sche.size();
		////假如这个城市没有车次，则无法到达终点
		//if (arcNum == 0)
		//{
		//	qDebug() << "没有路线可以到达" << endl;
		//	return -1;
		//}
		for (int i = 0; i < arcNum; i++)
		{
			qDebug() << "考察节点" << cur << "的第" << i << "个时刻表" << endl;
			Schedule tem = ma.city_list[cur].sche[i];//当前车次
			qDebug() << "该车次目的地为" << tem.des << endl;
			int nextIndex = getIndex(tem.des);//获得到达点的下标
			float risk;//选择当前路线，这一段的risk值
			if (S[nextIndex] != -1)//假如要走回头路
			{
				qDebug() << "走回头路" << endl;
				continue;//下一轮
			}
			//获得交通工具风险值
			float vehicleRisk = getRiskValue(tem.vehicle);
			float cityRisk = ma.city_list[cur].risk;
			if (T[cur].time() < ma.city_list[cur].sche[i].start_time.time())//假如出发时间早于当天车的起始时间
			{
				//计算风险值=出发前滞留时间*城市风险+交通时间*城市时间*交通风险
				risk = (float)T[cur].time().secsTo(tem.start_time.time()) / 3600 * cityRisk
					+ (float)tem.start_time.time().secsTo(tem.arrival_time.time()) / 3600 * cityRisk * vehicleRisk;
				//假如新路线风险更低，更新U数组和T数组和A数组
				if ((U[cur] + risk) < U[nextIndex])
				{
					qDebug() << "cur:" << cur << endl;
					qDebug() << "U[cur]:" << U[cur] << endl;
					
					T[nextIndex].setDate(T[cur].date());
					T[nextIndex].setTime(tem.arrival_time.time()); //更新到达nextIndex的时间
					int s = T[nextIndex].secsTo(ddl);
					if (s < 0)
					{
						qDebug() << "当前超时" << endl;
						continue;
					}
					U[nextIndex] = U[cur] + risk;
					A[nextIndex] = i;  //到达nextIndex选择了第i个时刻表
					P[nextIndex] = cur;  //前驱节点
					qDebug() << "**************************" << endl;
					qDebug() << "U数组更新为" << U[nextIndex] << endl;
					qDebug() << "T数组更新为" << T[nextIndex].toString("M.d hh:mm");
					qDebug() << "**************************" << endl;
				}
			}
			else//假如晚于当天起始时间，则隔一天再坐
			{
				qDebug() << "晚于当天起始时间" << endl;
				//计算风险值
				risk = ((float)T[cur].time().secsTo(tem.start_time.time()) / 3600 + 24)* cityRisk
					+ (float)tem.start_time.time().secsTo(tem.arrival_time.time()) / 3600 * cityRisk * vehicleRisk;
				qDebug() << "停留在城市的时间" << ((float)T[cur].time().secsTo(tem.start_time.time()) / 3600 + 24) << endl;
				//假如新路线风险更低，更新U数组和T数组
				if ((U[cur] + risk) < U[nextIndex])
				{
					
					//起始时间+1天
					T[nextIndex].setDate(T[cur].date());
					T[nextIndex] = T[nextIndex].addDays(1);
					T[nextIndex].setTime(tem.arrival_time.time());
					int s = T[nextIndex].secsTo(ddl);
					if (s < 0)
					{
						qDebug() << "当前超时" << endl;
						continue;
					}
					U[nextIndex] = U[cur] + risk;
					A[nextIndex] = i;
					P[nextIndex] = cur;  //前驱节点
					qDebug() << "**************************" << endl;
					qDebug() << "U数组更新为" << U[nextIndex] << endl;
					qDebug() << "T数组更新为" << T[nextIndex].toString("M.d hh:mm");
					qDebug() << "**************************" << endl;
				}
			}

		}
		qDebug() << "输出U数组" << endl;
		for (int i = 0; i < ma.city_num; i++)
		{
			qDebug() << U[i] << "	";
		}
		qDebug() << endl;
		qDebug() << "输出S数组" << endl;
		for (int i = 0; i < ma.city_num; i++)
		{
			qDebug() << S[i] << "	";
		}
		qDebug() << endl;
		qDebug() << "输出P数组" << endl;
		for (int i = 0; i < ma.city_num; i++)
		{
			qDebug() << P[i] << "	";
		}
		qDebug() << endl;
		qDebug() << "输出A数组" << endl;
		for (int i = 0; i < ma.city_num; i++)
		{
			qDebug() << A[i] << "	";
		}
		qDebug() << endl;
	}
	return 0;
}


int Strategy::dij2(Traveler &tra)//不限时
{
	if (tra.departure == tra.destination)
	{
		return -1;
	}
	QString dep = tra.departure;
	QString des = tra.destination;
	QDateTime start = tra.start_time;
	QDateTime ddl = tra.deadline;
	int S[CITY_NUM];//判断该点是否已存入到S集合中的数组，若没加入，值为-1，若加入，则为1
	int P[CITY_NUM];//节点的前驱节点
	float U[CITY_NUM];//该点到源点的距离
	QDateTime T[CITY_NUM];//从该城市出发的最早时间         T[a]=b表示到达a的时间为b
	int A[CITY_NUM];//当前点选择的边的序号                  A[a]=b表示到达a选择了第b个时刻表
	float minRisk = 10000;//风险最小值
	//找到城市下标
	int depIndex = getIndex(dep);//找到出发城市的下标
	qDebug() << "出发地" << depIndex << endl;
	int desIndex = getIndex(des);//找到目的城市的下标
	//初始化S数组
	for (int i = 0; i < CITY_NUM; i++)
	{
		S[i] = -1;
	}
	//初始化U数组
	for (int i = 0; i < CITY_NUM; i++)
	{
		U[i] = 10000;
	}
	//初始化A数组
	for (int i = 0; i < CITY_NUM; i++)
	{
		A[i] = -1;
	}
	//初始化P数组
	for (int i = 0; i < CITY_NUM; i++)
	{
		P[i] = -1;
	}
	U[depIndex] = 0;//起始点到起始点的距离为0
	//初始化T数组
	T[depIndex] = start;//最早出发时间=起始时间
	int cur = depIndex;//当前节点下标
	P[depIndex] = depIndex;
	while (1)
	{
		qDebug() << "开始查询路线" << endl;
		int min = 0;//假设距离最小的点下标为0
		//先找一个作为距离最小点的点,取一个还没有加入S数组的
		for (int i = 0; i < ma.city_num; i++)
		{
			if (S[i] == -1)
			{
				min = i;
			}
		}
		qDebug() << "初min：" << min << endl;
		
		//把U数组中最小的一个点加入
		for (int i = 0; i < ma.city_num; i++)
		{
			//找到U中最小距离点的下标
			if ((S[i] == -1) && (U[i] < U[min]))
			{
				min = i;
				qDebug() << "min:" << min << endl;
			}
		}
		if (U[min] != 10000)
		{
			S[min] = 1;//把下标为min的点加入S数组，它的上一个点为cur
			cur = min;//更新当前点下标
			qDebug() << "--------------------------------把" << min << "号节点加入S数组" << endl;
			qDebug() << "输出S数组" << endl;
			for (int i = 0; i < ma.city_num; i++)
			{
				qDebug() << S[i] << "	";
			}
			qDebug() << endl;
		}
		else
		{
			qDebug() << "没有路线可以到达" << endl;
			return -1;
		}
		
		//假如加入的是终点，那么已经到达，跳出循环
		if (cur == desIndex)
		{
			qDebug() << "到达终点！!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!" << endl;
			//写入旅客最优路线
			int before;
			while (cur != P[cur])
			{
				qDebug() << "添加时刻表" << endl;
				Schedule fact;
				//找到上一个点的下标
				before = P[cur];
				if (before == -1)
				{
					qDebug() << "没有路线可以到达" << endl;
					return -1;
				}
				qDebug() << cur << "的上一个点为" << before << endl;
				//找到上一个点选中的边的下标
				int i = A[cur];
				fact = ma.city_list[before].sche[i];
				fact.start_time.setDate(T[cur].date());//修改从上一个点开始出发的日期
				fact.arrival_time.setDate(T[cur].date());//修改到达当前点的日期
				tra.route.insert(tra.route.begin(), fact);
				cur = before;
			}
			tra.showRoute();//显示旅客路线
			break;
		}
		//对刚加入的点min进行操作，更新数组
		//对min的每一条边进行操作
		int arcNum = ma.city_list[cur].sche.size();
		//假如这个城市没有车次，则无法到达终点
		/*if (arcNum == 0)
		{
			qDebug() << "没有路线可以到达" << endl;
			return -1;
		}*/
		for (int i = 0; i < arcNum; i++)
		{
			qDebug() << "考察节点" << cur << "的第" << i << "个时刻表" << endl;
			Schedule tem = ma.city_list[cur].sche[i];//当前车次
			qDebug() << "该车次目的地为" << tem.des << endl;
			int nextIndex = getIndex(tem.des);//获得到达点的下标
			float risk;//选择当前路线，这一段的risk值
			if (S[nextIndex] != -1)//假如要走回头路
			{
				qDebug() << "走回头路" << endl;
				continue;//下一轮
			}
			//获得交通工具风险值
			float vehicleRisk = getRiskValue(tem.vehicle);
			float cityRisk = ma.city_list[cur].risk;
			if (T[cur].time() < ma.city_list[cur].sche[i].start_time.time())//假如出发时间早于当天车的起始时间
			{
				qDebug() << "最早出发时间为" << T[cur].toString("M.d hh:mm");
				qDebug() << "cityrisk" << cityRisk << endl;
				qDebug() << "vehiclerisk" << vehicleRisk << endl;
				//计算风险值=出发前滞留时间*城市风险+交通时间*城市时间*交通风险
				risk = (float)T[cur].time().secsTo(tem.start_time.time()) / 3600 * cityRisk 
					+ (float)tem.start_time.time().secsTo(tem.arrival_time.time()) / 3600 * cityRisk * vehicleRisk;
				qDebug() <<"停留在城市的时间" << (float)T[cur].time().secsTo(tem.start_time.time()) / 3600 << endl;
				//假如新路线风险更低，更新U数组和T数组和A数组
				if ((U[cur] + risk) < U[nextIndex])
				{
					qDebug() << "cur:" << cur << endl;
					qDebug() << "U[cur]:" << U[cur] << endl;
					U[nextIndex] = U[cur] + risk;
					T[nextIndex].setDate(T[cur].date());
					T[nextIndex].setTime(tem.arrival_time.time()); //更新到达nextIndex的时间
					A[nextIndex] = i;  //到达nextIndex选择了第i个时刻表
					P[nextIndex] = cur;  //前驱节点
					/*qDebug() << "**************************" << endl;
					qDebug() << "U数组更新为" << U[nextIndex] << endl;
					qDebug() << "T数组更新为" << T[nextIndex].toString("M.d hh:mm");
					qDebug() << "**************************" << endl;*/
				}
			}
			else//假如晚于当天起始时间，则隔一天再坐
			{
				qDebug() << "晚于当天起始时间" << endl;
				//计算风险值
				risk = ((float)T[cur].time().secsTo(tem.start_time.time()) / 3600 + 24)* cityRisk
					+ (float)tem.start_time.time().secsTo(tem.arrival_time.time()) / 3600 * cityRisk * vehicleRisk;
				qDebug() << "停留在城市的时间" << ((float)T[cur].time().secsTo(tem.start_time.time()) / 3600 + 24) << endl;
				//假如新路线风险更低，更新U数组和T数组
				if ((U[cur] + risk) < U[nextIndex])
				{
					U[nextIndex] = U[cur] + risk;
					//起始时间+1天
					T[nextIndex].setDate(T[cur].date());
					T[nextIndex] = T[nextIndex].addDays(1);
					T[nextIndex].setTime(tem.arrival_time.time());
					A[nextIndex] = i;
					P[nextIndex] = cur;  //前驱节点
					/*qDebug() << "**************************" << endl;
					qDebug() << "U数组更新为" << U[nextIndex] << endl;
					qDebug() << "T数组更新为" << T[nextIndex].toString("M.d hh:mm");
					qDebug() << "**************************" << endl;*/
				}
			}

		}
		/*qDebug() << "输出U数组" << endl;
		for (int i = 0; i < CITY_NUM; i++)
		{
			qDebug() << U[i] << "	";
		}
		qDebug() << endl;
		qDebug() << "输出S数组" << endl;
		for (int i = 0; i < CITY_NUM; i++)
		{
			qDebug() << S[i] << "	";
		}
		qDebug() << endl;
		qDebug() << "输出P数组" << endl;
		for (int i = 0; i < CITY_NUM; i++)
		{
			qDebug() << P[i] << "	";
		}
		qDebug() << endl;
		qDebug() << "输出A数组" << endl;
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