#include "Traveler.h"
//保证能输出中文字符
#if _MSC_VER >= 1600	// MSVC2015 > 1899,	MSVC_VER = 14.0
#pragma execution_character_set("utf-8")
#endif

#include"manager.h"

extern Manager ma;

//构造函数

Traveler::Traveler()
{
	this->m_x = 100;
	this->m_y = 100;
	rou_ID = 0;
}

void Traveler::setPosition(int x, int y)
{
	m_x = x;
	m_y = y;
	//m_rect.moveTo(m_x, m_y);
}

//显示旅客信息
void Traveler::show_info()
{
	qDebug() << "出发地：" << departure << endl;
	qDebug() << "目的地：" << destination << endl;
	qDebug() << "出发时间：" << start_time.toString("MM.dd hh:mm") << endl;
}

void Traveler::showRoute()
{
	qDebug() << "旅客路线如下：" << endl;
	int num = route.size();
	for (int i = 0; i < num; i++)
	{
		qDebug() << route[i].start_time.toString("M.d hh:mm") << "到" << route[i].arrival_time.toString("M.d hh:mm") << ":" << endl;
		qDebug() << "乘坐" << route[i].vehicle << "从" << route[i].dep << "到" << route[i].des << endl;
	}

}

void Traveler::move()
{
	if (moving == 0)
	{
		return;
	}
	if (route[rou_ID].arrival_time < ma.current_time)
	{
		return;
	}
	qDebug() << "rou_ID" << rou_ID << endl;
	int i = ma.getIndex(route[rou_ID].dep);//找到出发地下标
	int j = ma.getIndex(route[rou_ID].des);//找到目的地下标
	
	//当时间到了再出发
	if (ma.current_time < route[rou_ID].start_time)
	{
		qDebug() << "时间还没到" << endl;
		return;
	}
	qDebug() << "旅客移动" << endl;
	
	state = "乘" + route[rou_ID].vehicle + "从" + route[rou_ID].dep + "到" + route[rou_ID].des;
	//计算当前路线剩余用时
	int t = ma.current_time.secsTo(route[rou_ID].arrival_time);
	//计算路程差 目的地-旅客位置
	float ax = (ma.city_list[j].x - m_x);
	float ay = (ma.city_list[j].y - m_y);
	
	qDebug() << "ax:" << ax << "ay:" << ay << endl;
	//计算各个方向的速度,像素/s
	float sx = (float)ax / t;
	float sy = (float)ay / t;
	qDebug() << "sx:" << sx << "sy:" << sy << endl;
	//移动
	m_x += (float)sx * 36 * ma.move_speed;
	m_y += (float)sy * 36 * ma.move_speed;
	//假如超过去了
	if ((ma.city_list[j].x - m_x)*ax < 0)
	{
		QString str = name + "于" + ma.current_time.toString("MM-dd HH:mm") + "到达" + ma.city_list[j].name;
		qDebug() << "超过了" << endl;
		if (rou_ID < route.size() - 1)
		{
			rou_ID++;
		}
		else//最后一条路线已走完
		{
			str = name + "于" + ma.current_time.toString("MM-dd HH:mm") + "到达" + ma.city_list[j].name + ", 到达终点！\n";
			moving = 0;
		}
		m_x = ma.city_list[j].x;
		m_y = ma.city_list[j].y;
		state = "停留" + ma.city_list[j].name;
		ma.log(str);
		return;
	}
	qDebug()<< "m_x:" << m_x << "m_y:" << m_y << endl;
}

//析构函数
Traveler::~Traveler()
{

}