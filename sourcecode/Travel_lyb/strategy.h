#pragma once
//保证能输出中文字符
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
	//属性
	//Node cities[CITY_NUM];//城市 节点
	

	//方法
	Strategy();//构造函数
	void init_node();//初始化顶点
	void show_nodes();//显示顶点
	int getIndex(QString city);//找到城市节点
	int getRiskValue(QString vehicle);//获得交通工具的风险值
	int dij1(Traveler &tra);//限时
	int dij2(Traveler &tra);//不限时
	~Strategy();//析构函数
};

