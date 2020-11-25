#include "paintTraveler.h"
extern Manager ma;
void paintTraveler::drawTraveler()
{
	int num = ma.tra_list.size();
	for (int i = 0; i < num; i++)
	{
		ma.tra_list[i].move();//旅客移动
		//绘制旅客
	}
	emit isDone();
}