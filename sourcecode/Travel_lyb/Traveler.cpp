#include "Traveler.h"
//��֤����������ַ�
#if _MSC_VER >= 1600	// MSVC2015 > 1899,	MSVC_VER = 14.0
#pragma execution_character_set("utf-8")
#endif

#include"manager.h"

extern Manager ma;

//���캯��

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

//��ʾ�ÿ���Ϣ
void Traveler::show_info()
{
	qDebug() << "�����أ�" << departure << endl;
	qDebug() << "Ŀ�ĵأ�" << destination << endl;
	qDebug() << "����ʱ�䣺" << start_time.toString("MM.dd hh:mm") << endl;
}

void Traveler::showRoute()
{
	qDebug() << "�ÿ�·�����£�" << endl;
	int num = route.size();
	for (int i = 0; i < num; i++)
	{
		qDebug() << route[i].start_time.toString("M.d hh:mm") << "��" << route[i].arrival_time.toString("M.d hh:mm") << ":" << endl;
		qDebug() << "����" << route[i].vehicle << "��" << route[i].dep << "��" << route[i].des << endl;
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
	int i = ma.getIndex(route[rou_ID].dep);//�ҵ��������±�
	int j = ma.getIndex(route[rou_ID].des);//�ҵ�Ŀ�ĵ��±�
	
	//��ʱ�䵽���ٳ���
	if (ma.current_time < route[rou_ID].start_time)
	{
		qDebug() << "ʱ�仹û��" << endl;
		return;
	}
	qDebug() << "�ÿ��ƶ�" << endl;
	
	state = "��" + route[rou_ID].vehicle + "��" + route[rou_ID].dep + "��" + route[rou_ID].des;
	//���㵱ǰ·��ʣ����ʱ
	int t = ma.current_time.secsTo(route[rou_ID].arrival_time);
	//����·�̲� Ŀ�ĵ�-�ÿ�λ��
	float ax = (ma.city_list[j].x - m_x);
	float ay = (ma.city_list[j].y - m_y);
	
	qDebug() << "ax:" << ax << "ay:" << ay << endl;
	//�������������ٶ�,����/s
	float sx = (float)ax / t;
	float sy = (float)ay / t;
	qDebug() << "sx:" << sx << "sy:" << sy << endl;
	//�ƶ�
	m_x += (float)sx * 36 * ma.move_speed;
	m_y += (float)sy * 36 * ma.move_speed;
	//���糬��ȥ��
	if ((ma.city_list[j].x - m_x)*ax < 0)
	{
		QString str = name + "��" + ma.current_time.toString("MM-dd HH:mm") + "����" + ma.city_list[j].name;
		qDebug() << "������" << endl;
		if (rou_ID < route.size() - 1)
		{
			rou_ID++;
		}
		else//���һ��·��������
		{
			str = name + "��" + ma.current_time.toString("MM-dd HH:mm") + "����" + ma.city_list[j].name + ", �����յ㣡\n";
			moving = 0;
		}
		m_x = ma.city_list[j].x;
		m_y = ma.city_list[j].y;
		state = "ͣ��" + ma.city_list[j].name;
		ma.log(str);
		return;
	}
	qDebug()<< "m_x:" << m_x << "m_y:" << m_y << endl;
}

//��������
Traveler::~Traveler()
{

}