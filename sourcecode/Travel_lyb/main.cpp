#include "MainWindow.h"
#include"manager.h"
#include"Traveler.h"
#include"strategy.h"
#include<iostream>
#include <QtWidgets/QApplication>
using namespace std;


Manager ma;//������
Strategy way;//���Զ���

int main(int argc, char *argv[])
{
	
	ma.init_schedule();//��ʼ��manager
	QApplication a(argc, argv);
	QFont UIFont( "SimSun" );
	UIFont.setPixelSize(15);
	a.setFont(UIFont);
	MainWindow w;
	way.init_node();//��ʼ���ڵ�
	//way.show_nodes();//��ʾ�ڵ�
	
	w.show();
	return a.exec();
}
