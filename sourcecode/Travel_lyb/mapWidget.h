#pragma once
#include <QDate>
#include <QTime>
#include <QDateTimeEdit>
#include <QTimer>
#include <QThread>
#include <QKeyEvent>
#include <QEvent>
#include <QWidget>

#include <QPixmap>
#include <QScrollArea>
#include <QPalette>
#include <QLayout>
#include <QPalette>
#include"config.h"
#include"city.h"
#include"paintTraveler.h"
#include "manager.h"
class MapWidget :
	public QWidget
{
	Q_OBJECT
public:
	//City city_list[20];

	MapWidget(QWidget *parent = 0);//构造函数

	void paintEvent(QPaintEvent *);//重写paintEvent
	

};
