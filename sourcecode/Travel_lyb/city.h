#pragma once
#include<QString>
#include<QPixmap>
#include<QRect>
#include"config.h"
#include"Traveler.h"

using namespace std;

class City
{
public:
	//����
	QString name;//������
	int x;//����
	int y;
	int risk;  //����ֵ
	QVector<Schedule> sche;//���ڱ�(ʱ�̱���)
	//���캯��
	City();
	City(QString name, int x, int y, int risk);

	//��������
	~City();
};


