#include"schedule.h"

//构造函数
Schedule::Schedule()
{

}

Schedule::Schedule(QString dep, QString des, QString vehicle, QString id, QString start_time, QString arrival_time)
{
	static int i = 1;
	this->dep = dep;
	this->des = des;
	this->vehicle = vehicle;
	this->id = id;
	this->start_time = QDateTime::fromString(start_time, "h:mm");
	this->arrival_time = QDateTime::fromString(arrival_time, "h:mm");
	i++;
}

//析构函数
Schedule::~Schedule()
{

}