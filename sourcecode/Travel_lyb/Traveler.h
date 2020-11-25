#pragma once
#include<iostream>
#include<ctime>
#include<QString>
#include<QPixmap>
#include<QDateTime>
#include<QRect>
#include"config.h"
#include"schedule.h"
#include"city.h"
#include<qDebug>

using namespace std;
class Traveler
{
public:
	int id;//�ÿͱ��
	QString name;//�ÿ�����
	QString departure;//������
	QString destination;//Ŀ�ĵ�
	//QString location;//�ÿ͵�ǰ��λ��
	int strategy;//ѡ����� (��ʱΪ1������ʱΪ2)
	QDateTime start_time;//��ʼʱ��
	QDateTime deadline;//��ֹʱ��
	QString state;//�ÿ�״̬
	float m_x;
	float m_y;//�ÿ�����

	int moving;//�ÿ��Ƿ����˶��У�����Ϊ1������Ϊ0

	QVector<Schedule> route;//�ÿ�·��
	int rou_ID;//��ǰ�ߵ�·��

	//���캯��
	Traveler();

	//��ʾ�ÿ���Ϣ
	void show_info();

	//�����ÿ�λ��
	void setPosition(int x, int y);

	//��ʾ�ÿ�·�߹滮
	void showRoute();

	//�ÿ��ƶ�
	void move();

	//��������
	~Traveler();
};

