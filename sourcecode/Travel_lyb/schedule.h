#pragma once
#include<iostream>
#include<QString>
#include<QDateTime>
#include<QDebug>
using namespace std;

class Schedule
{
public:
	QString dep;//������
	QString des;//Ŀ�ĵ�
	QString vehicle;//��ͨ����
	QString id;//���
	QDateTime start_time;//����ʱ��
	QDateTime arrival_time;//����ʱ��

	//���캯��
	Schedule();
	Schedule(QString dep, QString des, QString vehicle, QString id, QString start_time, QString arrival_time);

	//��������
	~Schedule();
};
