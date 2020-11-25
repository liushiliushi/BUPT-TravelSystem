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
	int id;//旅客编号
	QString name;//旅客姓名
	QString departure;//出发地
	QString destination;//目的地
	//QString location;//旅客当前的位置
	int strategy;//选择策略 (限时为1，不限时为2)
	QDateTime start_time;//起始时间
	QDateTime deadline;//截止时间
	QString state;//旅客状态
	float m_x;
	float m_y;//旅客坐标

	int moving;//旅客是否在运动中，是则为1，否则为0

	QVector<Schedule> route;//旅客路线
	int rou_ID;//当前走的路线

	//构造函数
	Traveler();

	//显示旅客信息
	void show_info();

	//设置旅客位置
	void setPosition(int x, int y);

	//显示旅客路线规划
	void showRoute();

	//旅客移动
	void move();

	//析构函数
	~Traveler();
};

