#pragma once
#include <QObject>
#include"manager.h"
#include <QDebug>
#include<QPainter>
#include<QMouseEvent>
#include<QTimer>
#include<QVector>
#include<QDateTime>
#include<QString>
#include<QDebug>
#include<QThread>
class paintTraveler :
	public QObject
{
	Q_OBJECT
public:
	

signals:
	void update();
	void isDone();

public slots:
	void drawTraveler();//ªÊ÷∆∆Ô ÷
};

