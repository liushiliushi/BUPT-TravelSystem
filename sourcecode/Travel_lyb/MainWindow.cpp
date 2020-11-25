//保证能输出中文字符
#if _MSC_VER >= 1600	// MSVC2015 > 1899,	MSVC_VER = 14.0
#pragma execution_character_set("utf-8")
#endif
#include "MainWindow.h"
extern Strategy way;//策略

MainWindow::MainWindow(QWidget *parent)
	: QMainWindow(parent)
{

	ui.setupUi(this);

	myTimer = new QTimer(this);

	Query *qu = new Query;
	//qu->show();

	//初始化主场景
	initScene();
	//初始化城市
	initCity();
	//设置字体
	QFont font;
	QFont font2;
	font.setFamily("宋体");
	font.setPixelSize(18);
	font2.setFamily("Simsun");
	font2.setPixelSize(15);
	//font.setBold(true);
	ui.tabWidget_2->setFont(font);
	ui.label_14->setFont(font);
	ui.lineEdit->setFont(font);
	ui.label_15->setFont(font);
	ui.comboBox_6->setFont(font);
	ui.label_16->setFont(font);
	ui.comboBox_7->setFont(font);
	ui.label_17->setFont(font);
	ui.radioButton_5->setFont(font);
	ui.radioButton_6->setFont(font);
	ui.label_18->setFont(font);
	ui.label_19->setFont(font);
	
	ui.toolButton->setFont(font);
	ui.label_4->setFont(font);
	ui.label_13->setFont(font);
	ui.label_8->setFont(font);
	ui.label_9->setFont(font);
	ui.label_10->setFont(font);
	ui.label_11->setFont(font);
	ui.label_12->setFont(font);
	ui.label_5->setFont(font);
	ui.label->setFont(font);
	ui.toolButton_6->setFont(font);
	ui.toolButton_7->setFont(font);
	ui.comboBox_3->setFont(font);
	ui.comboBox_4->setFont(font);
	ui.comboBox_5->setFont(font);
	ui.radioButton_3->setFont(font);
	ui.radioButton_4->setFont(font);
	/*ui.dateTimeEdit_5->setFont(font);
	ui.dateTimeEdit_6->setFont(font);
	ui.dateTimeEdit_7->setFont(font);
	ui.dateTimeEdit_8->setFont(font);*/

	ui.textBrowser->setFont(font2);
	ui.textBrowser_2->setFont(font2);
	ui.label_6->setFont(font2);
	if (ma.open == 0)
	{
		QMessageBox::critical(this, "错误", "无法正确打开文件，请关闭文件city.csv,schedule.csv.");
	}
	//添加旅客
	connect(ui.toolButton, SIGNAL(clicked()), this, SLOT(addTraveler()));
	//修改旅客
	connect(ui.toolButton_6, SIGNAL(clicked()), this, SLOT(modiTraveler()));
	//查询旅客信息
	//connect(ui.comboBox_5, SIGNAL(currentTextChanged(const QString& )), this, SLOT(showTraveler(const QString& )));
	connect(ui.comboBox_5, SIGNAL(activated(const QString &)), this, SLOT(showTraveler(const QString&)));
	//删除旅客
	connect(ui.toolButton_7, SIGNAL(clicked()), this, SLOT(deleteTraveler()));


	connect(myTimer, SIGNAL(timeout()), this, SLOT(dealTimeOut()));//更新日期显示和旅客位置
	connect(myTimer, SIGNAL(timeout()), ui.widget_2, SLOT(update()));//绘图
	//connect(myTimer, SIGNAL(timeout()), this, SLOT(ceshi()));//绘图

	//点击开始模拟按钮之后
	connect(ui.toolButton_2, SIGNAL(clicked()), this, SLOT(start_stimulation()));
	connect(ui.toolButton_4, SIGNAL(clicked()), this, SLOT(start_stimulation()));
	//点击暂停按钮之后
	connect(ui.toolButton_3, SIGNAL(clicked()), this, SLOT(stop_stimulation()));
	connect(ui.toolButton_9, SIGNAL(clicked()), this, SLOT(stop_stimulation()));
	//点击终止按钮之后
	connect(ui.toolButton_8, SIGNAL(clicked()), this, SLOT(end_stimulation()));
	connect(ui.toolButton_10, SIGNAL(clicked()), this, SLOT(end_stimulation()));
	//点击加速按钮之后
	connect(ui.toolButton_5, SIGNAL(clicked()), this, SLOT(accelerate_stimulation()));
	connect(ui.toolButton_11, SIGNAL(clicked()), this, SLOT(accelerate_stimulation()));
	//点击减速按钮之后
	connect(ui.toolButton_12, SIGNAL(clicked()), this, SLOT(slow_down_stimulation()));
	connect(ui.toolButton_13, SIGNAL(clicked()), this, SLOT(slow_down_stimulation()));
	//查询时刻表
	connect(ui.actionshike, SIGNAL(triggered()), qu, SLOT(show()));
}

void MainWindow::paintEvent(QPaintEvent *)
{
	//cout << "画图" << endl;
	QPainter p(this);
	p.setPen(Qt::NoPen);
	p.setBrush(QColor(BACKGROUNDCOLOR));
	p.drawRect(rect());
}

void MainWindow::initScene()
{
	//设置窗口固定尺寸
	setFixedSize(WIDTH, HEIGHT);
	//设置图标
	setWindowIcon(QIcon(":/ziyuan/icon.PNG"));

	//设置标题
	setWindowTitle(TITLE);

	//调整日期编辑格式
	ui.dateTimeEdit_5->setDisplayFormat("MM-dd HH:mm");
	ui.dateTimeEdit_6->setDisplayFormat("MM-dd HH:mm");
	ui.dateTimeEdit_7->setDisplayFormat("MM-dd HH:mm");
	ui.dateTimeEdit_8->setDisplayFormat("MM-dd HH:mm");
	
}

void MainWindow::initCity()
{
	//初始化combobox
	ui.comboBox_3->clear();
	for (int i = 0; i < CITY_NUM; i++)
	{
		ui.comboBox_3->addItem(ma.city_list[i].name);
	}
	ui.comboBox_4->clear();
	for (int i = 0; i < CITY_NUM; i++)
	{
		ui.comboBox_4->addItem(ma.city_list[i].name);
	}
	ui.comboBox_6->clear();
	for (int i = 0; i < CITY_NUM; i++)
	{
		ui.comboBox_6->addItem(ma.city_list[i].name);
	}
	ui.comboBox_7->clear();
	for (int i = 0; i < CITY_NUM; i++)
	{
		ui.comboBox_7->addItem(ma.city_list[i].name);
	}
}

void MainWindow::addTraveler()
{
	if (ma.stimulation == true)
	{
		QMessageBox::information(this, "提示", "请终止模拟后再添加旅客");
		return;
	}
	//当输入无效时,即输入字符串为空，或未选择策略
	if (ui.lineEdit->text().isEmpty() | (!ui.radioButton_5->isChecked() && !ui.radioButton_6->isChecked()))
	{
		QMessageBox::critical(this, "错误", "请输入旅客完整信息");
		qDebug() << "请完整输入" << endl;
		return;
	}
	Traveler tra;
	tra.name = ui.lineEdit->text();//姓名
	//不能重名
	int num = ma.tra_list.size();
	//看是否重名
	for (int i = 0; i < num; i++)
	{
		if (ma.tra_list[i].name == tra.name)
		{
			QMessageBox::critical(this, "错误", "请输入不同的旅客姓名");
			return;
		}
	}
	tra.moving = 1;
	tra.departure = ui.comboBox_6->currentText().trimmed();
	tra.destination = ui.comboBox_7->currentText().trimmed();
	tra.strategy = ui.radioButton_5->isChecked() ? 1 : 2;
	tra.start_time = ui.dateTimeEdit_7->dateTime();
	tra.deadline = ui.dateTimeEdit_8->dateTime();
	tra.show_info();//显示旅客信息
	tra.state = "停留" + tra.departure;
	int j = ma.getIndex(tra.departure);//获得出发城市的下标
	tra.setPosition(ma.city_list[j].x, ma.city_list[j].y);

	int r;

	if (tra.strategy == 1)//限时
	{
		r = way.dij1(tra);

	}
	else//不限时
	{
		r = way.dij2(tra);//为旅客规划路线
	}
	if (r == -1)
	{
		QMessageBox::information(this, "提示", "没有合适的路线");
		return;
	}

	ma.tra_list.push_back(tra);//添加旅客

	//更新旅客出发的最早时间
	int i = tra.start_time.secsTo(ma.current_time);

	if (i > 0)
	{
		qDebug() << "早于" << endl;
		ma.current_time = tra.start_time;
	}
	ui.textBrowser_2->clear();
	
	//在textbrowser中显示旅客路线
	QString str = show_route(tra);//旅客旅行路线
	QString route = str;

	QColor  clrR(FONTCOLOR);
    ma.stringToHtmlFilter(str);
	ma.stringToHtml(str, clrR);
	ui.textBrowser_2->insertHtml(str);

	ui.comboBox_5->addItem(tra.name);

	QString celue = (tra.strategy == 1) ? (QString)"限时" : "不限时";
	QString jiezhi = (tra.strategy == 1) ? (QString)tra.deadline.toString("MM-dd HH:mm") : "无";

	QString str1= (QString)"添加旅客\n"
		+"旅客姓名："+tra.name+"\n"
		+ "出发地："+tra.departure+"	目的地："+tra.destination+"\n"
		+"策略："+celue+"\n"
		+"出发时间："+tra.start_time.toString("MM-dd HH:mm")+"	  截止时间："+jiezhi+"\n"
		+"规划路线：\n";
	ma.log(str1+route);
	//ma.log(route);
	ui.widget_2->update();
}

void MainWindow::deleteTraveler()
{
	if (ma.stimulation == true)
	{
		QMessageBox::information(this, "提示", "请终止模拟后再删除旅客");
		return;
	}
	qDebug() << "删除旅客" << endl;
	QString str = ui.comboBox_5->currentText();
	int num = ma.tra_list.size();
	int j = -1;
	//找到旅客序号j
	for (int i = 0; i < num; i++)
	{
		if (ma.tra_list[i].name == str)
		{
			j = i;
		}
	}
	if (j == -1)
	{
		QMessageBox::critical(this, "错误", "请选择要删除的旅客");
		return;
	}
	qDebug() << "j:" << j << endl;
	//输出日志
	str = (QString)"删除旅客\n"
		+ "旅客姓名：" + ma.tra_list[j].name + "\n";
	ma.log(str);
	qDebug() << ma.tra_list[j].name << endl;
	QString name = ma.tra_list[j].name;
	ma.tra_list.erase(ma.tra_list.begin() + j);//删除旅客信息
	qDebug() << "删除旅客信息" << endl;
	ui.comboBox_5->removeItem(ui.comboBox_5->findText(name));//当选框信息发生变化时，会重新显示信息，但是此时已经将该旅客信息抹除
	ui.widget_2->update();
}

void MainWindow::dealTimeOut()
{
	//1.更新时间  2.更新位置
	QString str = ma.current_time.toString("MM-dd HH:mm");
	//更新当前时间
	qDebug() << "ma.move_speed=" << ma.move_speed;
	ma.current_time = ma.current_time.addSecs(36 * ma.move_speed);
	qDebug() << "当前时间更新为：" << ma.current_time.toString("MM-dd HH:mm");
	ui.timedisplay1->setText(str);
	ui.timedisplay2->setText(str);

	int num = ma.tra_list.size();
	for (int i = 0; i < num; i++)
	{
		ma.tra_list[i].move();//旅客移动
	}
}

void MainWindow::modiTraveler()
{
	if (ma.stimulation == true)
	{
		QMessageBox::information(this, "提示", "请终止模拟后再修改旅客");
		return;
	}
	QString str2 = ui.comboBox_5->currentText();
	int num = ma.tra_list.size();
	qDebug() << "旅客共有" << num << "人" << endl;
	int j = -1;
	//找到旅客序号j
	for (int i = 0; i < num; i++)
	{
		if (ma.tra_list[i].name == str2)
		{
			j = i;
		}
	}
	if (j == -1)
	{
		QMessageBox::critical(this, "错误", "请选择要修改的旅客");
		return;
	}
	qDebug() << "旅客序号为" << j << endl;
	//修改旅客信息
	ma.tra_list[j].departure = ui.comboBox_3->currentText().trimmed();
	ma.tra_list[j].destination = ui.comboBox_4->currentText().trimmed();
	ma.tra_list[j].strategy = ui.radioButton_3->isChecked() ? 1 : 2;
	ma.tra_list[j].start_time = ui.dateTimeEdit_5->dateTime();
	ma.tra_list[j].state = "停留" + ma.tra_list[j].departure;
	ma.tra_list[j].deadline = ui.dateTimeEdit_6->dateTime();
	ma.tra_list[j].route.clear();
	int r;

	int k = ma.getIndex(ma.tra_list[j].departure);//获得出发城市的下标
	qDebug() << "k:" << k << endl;
	ma.tra_list[j].setPosition(ma.city_list[k].x, ma.city_list[k].y);

	if (ma.tra_list[j].strategy == 1)//限时
	{
		r = way.dij1(ma.tra_list[j]);

	}
	else//不限时
	{
		r = way.dij2(ma.tra_list[j]);//为旅客规划路线
	}
	if (r == -1)
	{

		QMessageBox::information(this, "QAQ", "无路线可到达");
		qDebug() << "无路线可到达，请重新添加" << endl;
		return;
	}
	ma.get_currentTime();
	QString str = show_route(ma.tra_list[j]);
	QString route = str;
	QColor  clrR(FONTCOLOR);
	ma.stringToHtmlFilter(str);
	ma.stringToHtml(str, clrR);
	ui.textBrowser->clear();
	ui.textBrowser->insertHtml(str);
	qDebug() << "修改成功" << endl;

	QString celue = (ma.tra_list[j].strategy == 1) ? (QString)"限时" : "不限时";
	QString jiezhi = (ma.tra_list[j].strategy == 1) ? (QString)ma.tra_list[j].deadline.toString("MM-dd HH:mm") : "无";

	QString str1 = (QString)"修改旅客\n"
		+ "旅客姓名：" + ma.tra_list[j].name + "\n"
		+ "出发地：" + ma.tra_list[j].departure + "	目的地：" + ma.tra_list[j].destination + "\n"
		+ "策略：" + celue + "\n"
		+ "出发时间：" + ma.tra_list[j].start_time.toString("MM-dd HH:mm") + "	  截止时间：" + jiezhi + "\n";
	ma.log(str1 + route);
	ui.widget_2->update();
}

void MainWindow::showTraveler(const QString& str)
{
	//假如要显示没有旅客信息
	if (str == "")
	{
		ui.comboBox_3->setCurrentIndex(0);//出发地
		ui.comboBox_4->setCurrentIndex(0);//目的地
		QDateTime time = QDateTime::fromString("01-01 00:00", "MM-dd HH:mm");
		ui.dateTimeEdit_5->setDateTime(time);//出发时间
		ui.dateTimeEdit_6->setDateTime(time);//ddl
		ui.textBrowser->clear();
		ui.label_6->clear();
		return;
	}
	qDebug() << "显示旅客信息" << endl;
	int num = ma.tra_list.size();
	int j;
	//找到旅客序号j
	for (int i = 0; i < num; i++)
	{
		if (ma.tra_list[i].name == str)
		{
			j = i;
		}
	}
	//显示旅客信息
	ui.comboBox_3->setCurrentIndex(ui.comboBox_3->findText(ma.tra_list[j].departure));//出发地
	ui.comboBox_4->setCurrentIndex(ui.comboBox_4->findText(ma.tra_list[j].destination));//目的地
	ui.label_6->setText(ma.tra_list[j].state);
	if (ma.tra_list[j].strategy == 1)//假如限时
	{
		ui.radioButton_3->setChecked(true);
	}
	else
	{
		ui.radioButton_4->setChecked(true);
	}
	ui.dateTimeEdit_5->setDateTime(ma.tra_list[j].start_time);//出发时间
	ui.dateTimeEdit_6->setDateTime(ma.tra_list[j].deadline);//ddl
	ui.textBrowser->clear();
	QString str1 = show_route(ma.tra_list[j]);
	QString route = str1;
	QColor  clrR(FONTCOLOR);
	ma.stringToHtmlFilter(str1);
	ma.stringToHtml(str1, clrR);
	ui.textBrowser->insertHtml(str1);
}

void MainWindow::start_stimulation()
{
	if (ma.tra_list.size() == 0)
	{
		QMessageBox::critical(this, "错误", "请添加旅客");
		qDebug() << "请添加旅客" << endl;
		return;
	}
	//开始计时咯
	qDebug() << ma.current_time.toString("MM-dd HH:mm") << endl;
	if (myTimer->isActive() == false)
	{
		myTimer->start(TIMER_INTVL);
		//ma.move_speed = ui.horizontalSlider->value();
	}
	ma.stimulation = true;
	ma.log("-----------开始模拟----------\n");
}

void MainWindow::stop_stimulation()
{
	qDebug() << "暂停" << endl;
	if (myTimer->isActive() == true)
	{
		myTimer->stop();
	}
	ma.log("-----------暂停模拟----------\n");
}

void MainWindow::end_stimulation()
{
	if (ma.stimulation == true)
	{
		qDebug() << "终止模拟" << endl;
		myTimer->stop();
		//终止模拟，重置全部参数
		int num = ma.tra_list.size();
		ma.current_time = ma.tra_list[0].start_time;
		ma.move_speed = 1;//重置模拟速度
		//重置每一位旅客的参数
		for (int i = 0; i < num; i++)
		{
			int j = ma.getIndex(ma.tra_list[i].departure);//获得出发城市的下标
			ma.tra_list[i].setPosition(ma.city_list[j].x, ma.city_list[j].y);
			ma.tra_list[i].moving = 1;
			ma.tra_list[i].rou_ID = 0;
			ma.tra_list[i].state = "停留" + ma.tra_list[i].departure;
			qDebug() << "出发城市重置" << endl;
			if (ma.current_time > ma.tra_list[i].start_time)
			{
				ma.current_time = ma.tra_list[i].start_time;
				qDebug() << ma.current_time.toString("MM-dd HH:mm");
			}
		}
		QString str = ma.current_time.toString("MM-dd HH:mm");
		qDebug() << "当前时间更新为：" << ma.current_time.toString("MM-dd HH:mm");
		ui.timedisplay1->setText(str);
		ui.timedisplay2->setText(str);
	}
	ma.stimulation = false;
	ma.log("-----------终止模拟----------\n");
	ui.widget_2->update();
}

void MainWindow::accelerate_stimulation()
{
	if (myTimer->isActive() == true)
	{
		ma.move_speed += 10;
	}
}

void MainWindow::slow_down_stimulation()
{
	if ((myTimer->isActive() == true) && ma.move_speed > 5)
	{
		ma.move_speed = 5;
	}
	else if ((myTimer->isActive() == true) && ma.move_speed > 1)
	{
		ma.move_speed -= 1;
	}
}

QString MainWindow::show_route(Traveler tra)
{
	qDebug() << "输出路线" << endl;
	QString str;
	int num = tra.route.size();
	for (int i = 0; i < num; i++)
	{
		QString start_time = tra.route[i].start_time.toString("MM-dd HH:mm");
		QString arrive_time= tra.route[i].arrival_time.toString("MM-dd HH:mm");
		
		QString str1 = start_time + " ---> " + arrive_time + "\n" + "乘坐:" + tra.route[i].vehicle +tra.route[i].id + " 从 " + tra.route[i].dep + " 到 " + tra.route[i].des + "\n";
		
		str += str1;
		
	}
	qDebug() << "str:" << str << endl;
	/*QColor  clrR(67,65,141);
	ma.stringToHtmlFilter(str);
	ma.stringToHtml(str, clrR);*/
	return str;
}

void MainWindow::dealDone()
{
	myTimer->stop();//关闭定时器
}

