#include "paintTraveler.h"
extern Manager ma;
void paintTraveler::drawTraveler()
{
	int num = ma.tra_list.size();
	for (int i = 0; i < num; i++)
	{
		ma.tra_list[i].move();//�ÿ��ƶ�
		//�����ÿ�
	}
	emit isDone();
}