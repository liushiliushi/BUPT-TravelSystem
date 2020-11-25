#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_Travel_lyb.h"
#include"Traveler.h"
#include"manager.h"
#include"city.h"
#include<QPainter>
#include<QMouseEvent>
#include<QTimer>
#include<QVector>
#include<QDateTime>
#include<QString>
#include<QPushButton>
#include<QLineEdit>
#include<QRadioButton>
#include<QDebug>
#include<QThread>
#include<QMenuBar>
#include<QMessageBox>
#include"Traveler.h"
#include"city.h"
#include"strategy.h"
#include"config.h"
#include "paintTraveler.h"
#include"mapWidget.h"
#include"query.h"


extern Manager ma;

class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	MainWindow(QWidget *parent = Q_NULLPTR);

	////城市数组
	//City city_list[20];

	//重新paintEvent事件，画背景图
	void paintEvent(QPaintEvent *);
	
	//初始化场景
	void initScene();
	//初始化城市
	void initCity();	

	//int getIndex(QString);
	
	


private:
	Ui::Travel_lybClass ui;

	paintTraveler *paint;
	QTimer *myTimer;

private slots:	
	//添加旅客
	void addTraveler();
	//修改旅客信息
	void modiTraveler();
	//显示旅客信息
	void showTraveler(const QString& str);
	//删除旅客信息
	void deleteTraveler();
	//时间到了该做什么
	void dealTimeOut();

	void start_stimulation();

	void stop_stimulation();

	void end_stimulation();

	void accelerate_stimulation();

	void slow_down_stimulation();

	void dealDone();//线程结束槽函数
	
	QString show_route(Traveler tra);//在textbrowser中显示旅客路线

signals:

	void speed_changed();//速度变化了

	

};
