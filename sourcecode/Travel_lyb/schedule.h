#pragma once
#include<iostream>
#include<QString>
#include<QDateTime>
#include<QDebug>
using namespace std;

class Schedule
{
public:
	QString dep;//出发地
	QString des;//目的地
	QString vehicle;//交通工具
	QString id;//编号
	QDateTime start_time;//发车时间
	QDateTime arrival_time;//到达时间

	//构造函数
	Schedule();
	Schedule(QString dep, QString des, QString vehicle, QString id, QString start_time, QString arrival_time);

	//析构函数
	~Schedule();
};
