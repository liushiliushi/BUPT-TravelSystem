#pragma once
#include"schedule.h"
#include"traveler.h"
#include"city.h"
#include"config.h"
#include<QString>
#include<iostream>
#include<QDateTime>
#include<QFile>
#include<fstream>
#include<QDebug>
#include <QStringList>
#include <QFileDialog>
#include<QVector>
#include"strategy.h"

using namespace std;

class Manager
{
public:
	//����
	Schedule time_table[100];//ʱ�̱�����

	QVector<Traveler> tra_list;//�ÿ�����

	int move_speed;//�ƶ��ٶ�

	int time_table_size = 0;

	int city_num = 0;

	int open = 1;//��ȷ���ļ��������ȷΪ1������Ϊ-1

	bool stimulation = false;//�Ƿ�����ģ��

	QDateTime current_time;//��ǰʱ��

	City city_list[CITY_NUM];//��������

	//��Ϊ

	Manager();//���캯��

	void init_schedule();//��ʼ��ʱ�̱�

	void ExitSystem();//�˳�ϵͳ

	void show_tra_set();//��ʾ�ÿ�

	void show_schedule();//��ʾ�г�ʱ�̱�

	void get_currentTime();//��ȡ����ʱ��

	void stringToHtmlFilter(QString &str);

	void stringToHtml(QString &str, QColor crl);

	int getIndex(QString city);

	int log(QString str);//д��־,���޷�д���򷵻�-1

	~Manager();//��������
};