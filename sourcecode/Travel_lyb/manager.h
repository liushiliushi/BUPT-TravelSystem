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
	//属性
	Schedule time_table[100];//时刻表数组

	QVector<Traveler> tra_list;//旅客数组

	int move_speed;//移动速度

	int time_table_size = 0;

	int city_num = 0;

	int open = 1;//正确打开文件。如果正确为1，否则为-1

	bool stimulation = false;//是否正在模拟

	QDateTime current_time;//当前时间

	City city_list[CITY_NUM];//城市数组

	//行为

	Manager();//构造函数

	void init_schedule();//初始化时刻表

	void ExitSystem();//退出系统

	void show_tra_set();//显示旅客

	void show_schedule();//显示列车时刻表

	void get_currentTime();//获取出发时间

	void stringToHtmlFilter(QString &str);

	void stringToHtml(QString &str, QColor crl);

	int getIndex(QString city);

	int log(QString str);//写日志,若无法写入则返回-1

	~Manager();//析构函数
};