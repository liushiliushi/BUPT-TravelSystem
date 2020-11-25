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
	//属性
	QString name;//城市名
	int x;//坐标
	int y;
	int risk;  //风险值
	QVector<Schedule> sche;//相邻边(时刻表用)
	//构造函数
	City();
	City(QString name, int x, int y, int risk);

	//析构函数
	~City();
};


