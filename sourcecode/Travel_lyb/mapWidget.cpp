#include "mapWidget.h"
#include <QPainter>
extern Manager ma;

MapWidget::MapWidget(QWidget *parent):QWidget(parent)
{
	
}

void MapWidget::paintEvent(QPaintEvent *)
{
	qDebug() << "mapWidget��ͼ" << endl;
	QPainter painter(this);

	//����QPixmap����
	QPixmap pix;
	//����ͼƬ
	pix.load(MAP_PATH);
	//����
	pix = pix.scaledToHeight(MAP_HEIGHT,Qt::FastTransformation);
	//���Ʊ���ͼ
	painter.drawPixmap(0, 0, pix.width(), pix.height(), pix);

	//��ʼ������λ��
	QPen myPen;
	//myPen.setColor(QColor(CITY_COLOR));
	//painter.setPen(myPen);
	//painter.setBrush(QColor(CITY_COLOR));
	for (int i = 0; i < ma.city_num; i++)
	{
		myPen.setColor(QColor(CITY_COLOR));
		painter.setPen(myPen);
		painter.setBrush(QColor(CITY_COLOR));
		painter.drawEllipse(ma.city_list[i].x - CITY_WIDTH / 2, ma.city_list[i].y - CITY_WIDTH / 2, CITY_WIDTH, CITY_WIDTH);
		//painter.drawPixmap(city_list[i].x - CITY_WIDTH/2, city_list[i].y - CITY_WIDTH/2, city);
		myPen.setColor(QColor(FONTCOLOR));
		painter.setPen(myPen);
		painter.drawText(ma.city_list[i].x - CITY_WIDTH , ma.city_list[i].y - CITY_WIDTH / 2, ma.city_list[i].name);
	}	

	////���Ʋ���ͼƬ
	//static float m = 20;
	//static float n = 20;
	//painter.drawEllipse(m, n, 10, 10);
	//m+=0.1;
	//n+=0.1;

	int num = ma.tra_list.size();
	QPixmap traveler;
	for (int i = 0; i < num; i++)
	{
		qDebug() << "�����ÿ�" << i << endl;
		//����·��
		int x = ma.tra_list[i].route.size();
		if (i % 5 == 0)
		{
			painter.setPen(QPen(QColor(ROUTE_COLOR1), 4, Qt::DashDotDotLine, Qt::RoundCap));
		}
		else if (i % 5 == 1)
		{
			painter.setPen(QPen(QColor(ROUTE_COLOR2), 4, Qt::DashDotDotLine, Qt::RoundCap));
		}
		else if (i % 5 == 2)
		{
			painter.setPen(QPen(QColor(ROUTE_COLOR3), 4, Qt::DashDotDotLine, Qt::RoundCap));
		}
		else if (i % 5 == 3)
		{
			painter.setPen(QPen(QColor(ROUTE_COLOR4), 4, Qt::DashDotDotLine, Qt::RoundCap));
		}
		else 
		{
			painter.setPen(QPen(QColor(ROUTE_COLOR5), 4, Qt::DashDotDotLine, Qt::RoundCap));
		}
		for (int s = 0; s < x; s++)
		{
			int m = ma.getIndex(ma.tra_list[i].route[s].dep);
			int n= ma.getIndex(ma.tra_list[i].route[s].des);
			painter.drawLine(ma.city_list[m].x, ma.city_list[m].y, ma.city_list[n].x, ma.city_list[n].y);
		}

		//���ƽ�ͨ����
		int j = ma.tra_list[i].rou_ID;
		if (ma.tra_list[i].route[j].vehicle == "��")
		{
			traveler.load(TRAIN_PATH);
		}
		else if (ma.tra_list[i].route[j].vehicle == "����")
		{
			traveler.load(CAR_PATH);
		}
		else
		{
			traveler.load(AIRPLANE_PATH);
		}
		//traveler.load(TRAVELER_PATH);
		//����
		//traveler = traveler.scaledToHeight(20);
		traveler = traveler.scaledToHeight(40);
		painter.drawPixmap(ma.tra_list[i].m_x - traveler.width() / 2, ma.tra_list[i].m_y - traveler.height(), traveler.width(), traveler.height(), traveler);
		//painter.setPen(QPen(QColor(0,0,0), 4, Qt::SolidLine, Qt::FlatCap));
		QFont f("����", FONTSIZE, QFont::Bold);
		painter.setPen(Qt::black);
		painter.setFont(f);
		painter.drawText(ma.tra_list[i].m_x - traveler.width() / 2, ma.tra_list[i].m_y - traveler.height(), ma.tra_list[i].name);
		qDebug() << ma.tra_list[i].m_x << endl;
	}
	painter.end();
	
}

