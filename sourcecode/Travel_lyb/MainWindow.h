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

	////��������
	//City city_list[20];

	//����paintEvent�¼���������ͼ
	void paintEvent(QPaintEvent *);
	
	//��ʼ������
	void initScene();
	//��ʼ������
	void initCity();	

	//int getIndex(QString);
	
	


private:
	Ui::Travel_lybClass ui;

	paintTraveler *paint;
	QTimer *myTimer;

private slots:	
	//����ÿ�
	void addTraveler();
	//�޸��ÿ���Ϣ
	void modiTraveler();
	//��ʾ�ÿ���Ϣ
	void showTraveler(const QString& str);
	//ɾ���ÿ���Ϣ
	void deleteTraveler();
	//ʱ�䵽�˸���ʲô
	void dealTimeOut();

	void start_stimulation();

	void stop_stimulation();

	void end_stimulation();

	void accelerate_stimulation();

	void slow_down_stimulation();

	void dealDone();//�߳̽����ۺ���
	
	QString show_route(Traveler tra);//��textbrowser����ʾ�ÿ�·��

signals:

	void speed_changed();//�ٶȱ仯��

	

};
