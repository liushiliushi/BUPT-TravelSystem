#pragma once
#include <QDate>
#include <QTime>
#include <QDateTimeEdit>
#include <QTimer>
#include <QThread>
#include <QKeyEvent>
#include <QEvent>
#include <QWidget>
#include <QStringList>
#include <QPixmap>
#include <QScrollArea>
#include <QPalette>
#include <QLayout>
#include <QPalette>
#include <QStandardItemModel>
#include <QTableWidgetItem>
#include"config.h"
#include"city.h"
#include "manager.h"
#include <QtWidgets/QMainWindow>
#include "ui_Widget.h"
class Query :
	public QWidget
{
	Q_OBJECT
public:

	Query(QWidget *parent = 0);//构造函数

	//void paintEvent(QPaintEvent *);//重写paintEvent
private:
	Ui::Form ui;
};

