#pragma once
//��֤����������ַ�
#if _MSC_VER >= 1600	// MSVC2015 > 1899,	MSVC_VER = 14.0
#pragma execution_character_set("utf-8")
#endif
#include"config.h"
#include"Traveler.h"
#include"manager.h"
#include"schedule.h"
#include"city.h"
#include<QString>
#include<QDateTime>
#include<QVector>
#include<queue>

typedef struct item {
	int index;
	float value;
}Item;
class Strategy
{
public:
	//����
	//Node cities[CITY_NUM];//���� �ڵ�
	

	//����
	Strategy();//���캯��
	void init_node();//��ʼ������
	void show_nodes();//��ʾ����
	int getIndex(QString city);//�ҵ����нڵ�
	int getRiskValue(QString vehicle);//��ý�ͨ���ߵķ���ֵ
	int dij1(Traveler &tra);//��ʱ
	int dij2(Traveler &tra);//����ʱ
	~Strategy();//��������
};

