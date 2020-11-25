#include "MainWindow.h"
#include"manager.h"
#include"Traveler.h"
#include"strategy.h"
#include<iostream>
#include <QtWidgets/QApplication>
using namespace std;


Manager ma;//管理者
Strategy way;//策略对象

int main(int argc, char *argv[])
{
	
	ma.init_schedule();//初始化manager
	QApplication a(argc, argv);
	QFont UIFont( "SimSun" );
	UIFont.setPixelSize(15);
	a.setFont(UIFont);
	MainWindow w;
	way.init_node();//初始化节点
	//way.show_nodes();//显示节点
	
	w.show();
	return a.exec();
}
