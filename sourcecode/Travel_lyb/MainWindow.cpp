//��֤����������ַ�
#if _MSC_VER >= 1600	// MSVC2015 > 1899,	MSVC_VER = 14.0
#pragma execution_character_set("utf-8")
#endif
#include "MainWindow.h"
extern Strategy way;//����

MainWindow::MainWindow(QWidget *parent)
	: QMainWindow(parent)
{

	ui.setupUi(this);

	myTimer = new QTimer(this);

	Query *qu = new Query;
	//qu->show();

	//��ʼ��������
	initScene();
	//��ʼ������
	initCity();
	//��������
	QFont font;
	QFont font2;
	font.setFamily("����");
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
		QMessageBox::critical(this, "����", "�޷���ȷ���ļ�����ر��ļ�city.csv,schedule.csv.");
	}
	//����ÿ�
	connect(ui.toolButton, SIGNAL(clicked()), this, SLOT(addTraveler()));
	//�޸��ÿ�
	connect(ui.toolButton_6, SIGNAL(clicked()), this, SLOT(modiTraveler()));
	//��ѯ�ÿ���Ϣ
	//connect(ui.comboBox_5, SIGNAL(currentTextChanged(const QString& )), this, SLOT(showTraveler(const QString& )));
	connect(ui.comboBox_5, SIGNAL(activated(const QString &)), this, SLOT(showTraveler(const QString&)));
	//ɾ���ÿ�
	connect(ui.toolButton_7, SIGNAL(clicked()), this, SLOT(deleteTraveler()));


	connect(myTimer, SIGNAL(timeout()), this, SLOT(dealTimeOut()));//����������ʾ���ÿ�λ��
	connect(myTimer, SIGNAL(timeout()), ui.widget_2, SLOT(update()));//��ͼ
	//connect(myTimer, SIGNAL(timeout()), this, SLOT(ceshi()));//��ͼ

	//�����ʼģ�ⰴť֮��
	connect(ui.toolButton_2, SIGNAL(clicked()), this, SLOT(start_stimulation()));
	connect(ui.toolButton_4, SIGNAL(clicked()), this, SLOT(start_stimulation()));
	//�����ͣ��ť֮��
	connect(ui.toolButton_3, SIGNAL(clicked()), this, SLOT(stop_stimulation()));
	connect(ui.toolButton_9, SIGNAL(clicked()), this, SLOT(stop_stimulation()));
	//�����ֹ��ť֮��
	connect(ui.toolButton_8, SIGNAL(clicked()), this, SLOT(end_stimulation()));
	connect(ui.toolButton_10, SIGNAL(clicked()), this, SLOT(end_stimulation()));
	//������ٰ�ť֮��
	connect(ui.toolButton_5, SIGNAL(clicked()), this, SLOT(accelerate_stimulation()));
	connect(ui.toolButton_11, SIGNAL(clicked()), this, SLOT(accelerate_stimulation()));
	//������ٰ�ť֮��
	connect(ui.toolButton_12, SIGNAL(clicked()), this, SLOT(slow_down_stimulation()));
	connect(ui.toolButton_13, SIGNAL(clicked()), this, SLOT(slow_down_stimulation()));
	//��ѯʱ�̱�
	connect(ui.actionshike, SIGNAL(triggered()), qu, SLOT(show()));
}

void MainWindow::paintEvent(QPaintEvent *)
{
	//cout << "��ͼ" << endl;
	QPainter p(this);
	p.setPen(Qt::NoPen);
	p.setBrush(QColor(BACKGROUNDCOLOR));
	p.drawRect(rect());
}

void MainWindow::initScene()
{
	//���ô��ڹ̶��ߴ�
	setFixedSize(WIDTH, HEIGHT);
	//����ͼ��
	setWindowIcon(QIcon(":/ziyuan/icon.PNG"));

	//���ñ���
	setWindowTitle(TITLE);

	//�������ڱ༭��ʽ
	ui.dateTimeEdit_5->setDisplayFormat("MM-dd HH:mm");
	ui.dateTimeEdit_6->setDisplayFormat("MM-dd HH:mm");
	ui.dateTimeEdit_7->setDisplayFormat("MM-dd HH:mm");
	ui.dateTimeEdit_8->setDisplayFormat("MM-dd HH:mm");
	
}

void MainWindow::initCity()
{
	//��ʼ��combobox
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
		QMessageBox::information(this, "��ʾ", "����ֹģ���������ÿ�");
		return;
	}
	//��������Чʱ,�������ַ���Ϊ�գ���δѡ�����
	if (ui.lineEdit->text().isEmpty() | (!ui.radioButton_5->isChecked() && !ui.radioButton_6->isChecked()))
	{
		QMessageBox::critical(this, "����", "�������ÿ�������Ϣ");
		qDebug() << "����������" << endl;
		return;
	}
	Traveler tra;
	tra.name = ui.lineEdit->text();//����
	//��������
	int num = ma.tra_list.size();
	//���Ƿ�����
	for (int i = 0; i < num; i++)
	{
		if (ma.tra_list[i].name == tra.name)
		{
			QMessageBox::critical(this, "����", "�����벻ͬ���ÿ�����");
			return;
		}
	}
	tra.moving = 1;
	tra.departure = ui.comboBox_6->currentText().trimmed();
	tra.destination = ui.comboBox_7->currentText().trimmed();
	tra.strategy = ui.radioButton_5->isChecked() ? 1 : 2;
	tra.start_time = ui.dateTimeEdit_7->dateTime();
	tra.deadline = ui.dateTimeEdit_8->dateTime();
	tra.show_info();//��ʾ�ÿ���Ϣ
	tra.state = "ͣ��" + tra.departure;
	int j = ma.getIndex(tra.departure);//��ó������е��±�
	tra.setPosition(ma.city_list[j].x, ma.city_list[j].y);

	int r;

	if (tra.strategy == 1)//��ʱ
	{
		r = way.dij1(tra);

	}
	else//����ʱ
	{
		r = way.dij2(tra);//Ϊ�ÿ͹滮·��
	}
	if (r == -1)
	{
		QMessageBox::information(this, "��ʾ", "û�к��ʵ�·��");
		return;
	}

	ma.tra_list.push_back(tra);//����ÿ�

	//�����ÿͳ���������ʱ��
	int i = tra.start_time.secsTo(ma.current_time);

	if (i > 0)
	{
		qDebug() << "����" << endl;
		ma.current_time = tra.start_time;
	}
	ui.textBrowser_2->clear();
	
	//��textbrowser����ʾ�ÿ�·��
	QString str = show_route(tra);//�ÿ�����·��
	QString route = str;

	QColor  clrR(FONTCOLOR);
    ma.stringToHtmlFilter(str);
	ma.stringToHtml(str, clrR);
	ui.textBrowser_2->insertHtml(str);

	ui.comboBox_5->addItem(tra.name);

	QString celue = (tra.strategy == 1) ? (QString)"��ʱ" : "����ʱ";
	QString jiezhi = (tra.strategy == 1) ? (QString)tra.deadline.toString("MM-dd HH:mm") : "��";

	QString str1= (QString)"����ÿ�\n"
		+"�ÿ�������"+tra.name+"\n"
		+ "�����أ�"+tra.departure+"	Ŀ�ĵأ�"+tra.destination+"\n"
		+"���ԣ�"+celue+"\n"
		+"����ʱ�䣺"+tra.start_time.toString("MM-dd HH:mm")+"	  ��ֹʱ�䣺"+jiezhi+"\n"
		+"�滮·�ߣ�\n";
	ma.log(str1+route);
	//ma.log(route);
	ui.widget_2->update();
}

void MainWindow::deleteTraveler()
{
	if (ma.stimulation == true)
	{
		QMessageBox::information(this, "��ʾ", "����ֹģ�����ɾ���ÿ�");
		return;
	}
	qDebug() << "ɾ���ÿ�" << endl;
	QString str = ui.comboBox_5->currentText();
	int num = ma.tra_list.size();
	int j = -1;
	//�ҵ��ÿ����j
	for (int i = 0; i < num; i++)
	{
		if (ma.tra_list[i].name == str)
		{
			j = i;
		}
	}
	if (j == -1)
	{
		QMessageBox::critical(this, "����", "��ѡ��Ҫɾ�����ÿ�");
		return;
	}
	qDebug() << "j:" << j << endl;
	//�����־
	str = (QString)"ɾ���ÿ�\n"
		+ "�ÿ�������" + ma.tra_list[j].name + "\n";
	ma.log(str);
	qDebug() << ma.tra_list[j].name << endl;
	QString name = ma.tra_list[j].name;
	ma.tra_list.erase(ma.tra_list.begin() + j);//ɾ���ÿ���Ϣ
	qDebug() << "ɾ���ÿ���Ϣ" << endl;
	ui.comboBox_5->removeItem(ui.comboBox_5->findText(name));//��ѡ����Ϣ�����仯ʱ����������ʾ��Ϣ�����Ǵ�ʱ�Ѿ������ÿ���ϢĨ��
	ui.widget_2->update();
}

void MainWindow::dealTimeOut()
{
	//1.����ʱ��  2.����λ��
	QString str = ma.current_time.toString("MM-dd HH:mm");
	//���µ�ǰʱ��
	qDebug() << "ma.move_speed=" << ma.move_speed;
	ma.current_time = ma.current_time.addSecs(36 * ma.move_speed);
	qDebug() << "��ǰʱ�����Ϊ��" << ma.current_time.toString("MM-dd HH:mm");
	ui.timedisplay1->setText(str);
	ui.timedisplay2->setText(str);

	int num = ma.tra_list.size();
	for (int i = 0; i < num; i++)
	{
		ma.tra_list[i].move();//�ÿ��ƶ�
	}
}

void MainWindow::modiTraveler()
{
	if (ma.stimulation == true)
	{
		QMessageBox::information(this, "��ʾ", "����ֹģ������޸��ÿ�");
		return;
	}
	QString str2 = ui.comboBox_5->currentText();
	int num = ma.tra_list.size();
	qDebug() << "�ÿ͹���" << num << "��" << endl;
	int j = -1;
	//�ҵ��ÿ����j
	for (int i = 0; i < num; i++)
	{
		if (ma.tra_list[i].name == str2)
		{
			j = i;
		}
	}
	if (j == -1)
	{
		QMessageBox::critical(this, "����", "��ѡ��Ҫ�޸ĵ��ÿ�");
		return;
	}
	qDebug() << "�ÿ����Ϊ" << j << endl;
	//�޸��ÿ���Ϣ
	ma.tra_list[j].departure = ui.comboBox_3->currentText().trimmed();
	ma.tra_list[j].destination = ui.comboBox_4->currentText().trimmed();
	ma.tra_list[j].strategy = ui.radioButton_3->isChecked() ? 1 : 2;
	ma.tra_list[j].start_time = ui.dateTimeEdit_5->dateTime();
	ma.tra_list[j].state = "ͣ��" + ma.tra_list[j].departure;
	ma.tra_list[j].deadline = ui.dateTimeEdit_6->dateTime();
	ma.tra_list[j].route.clear();
	int r;

	int k = ma.getIndex(ma.tra_list[j].departure);//��ó������е��±�
	qDebug() << "k:" << k << endl;
	ma.tra_list[j].setPosition(ma.city_list[k].x, ma.city_list[k].y);

	if (ma.tra_list[j].strategy == 1)//��ʱ
	{
		r = way.dij1(ma.tra_list[j]);

	}
	else//����ʱ
	{
		r = way.dij2(ma.tra_list[j]);//Ϊ�ÿ͹滮·��
	}
	if (r == -1)
	{

		QMessageBox::information(this, "QAQ", "��·�߿ɵ���");
		qDebug() << "��·�߿ɵ�����������" << endl;
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
	qDebug() << "�޸ĳɹ�" << endl;

	QString celue = (ma.tra_list[j].strategy == 1) ? (QString)"��ʱ" : "����ʱ";
	QString jiezhi = (ma.tra_list[j].strategy == 1) ? (QString)ma.tra_list[j].deadline.toString("MM-dd HH:mm") : "��";

	QString str1 = (QString)"�޸��ÿ�\n"
		+ "�ÿ�������" + ma.tra_list[j].name + "\n"
		+ "�����أ�" + ma.tra_list[j].departure + "	Ŀ�ĵأ�" + ma.tra_list[j].destination + "\n"
		+ "���ԣ�" + celue + "\n"
		+ "����ʱ�䣺" + ma.tra_list[j].start_time.toString("MM-dd HH:mm") + "	  ��ֹʱ�䣺" + jiezhi + "\n";
	ma.log(str1 + route);
	ui.widget_2->update();
}

void MainWindow::showTraveler(const QString& str)
{
	//����Ҫ��ʾû���ÿ���Ϣ
	if (str == "")
	{
		ui.comboBox_3->setCurrentIndex(0);//������
		ui.comboBox_4->setCurrentIndex(0);//Ŀ�ĵ�
		QDateTime time = QDateTime::fromString("01-01 00:00", "MM-dd HH:mm");
		ui.dateTimeEdit_5->setDateTime(time);//����ʱ��
		ui.dateTimeEdit_6->setDateTime(time);//ddl
		ui.textBrowser->clear();
		ui.label_6->clear();
		return;
	}
	qDebug() << "��ʾ�ÿ���Ϣ" << endl;
	int num = ma.tra_list.size();
	int j;
	//�ҵ��ÿ����j
	for (int i = 0; i < num; i++)
	{
		if (ma.tra_list[i].name == str)
		{
			j = i;
		}
	}
	//��ʾ�ÿ���Ϣ
	ui.comboBox_3->setCurrentIndex(ui.comboBox_3->findText(ma.tra_list[j].departure));//������
	ui.comboBox_4->setCurrentIndex(ui.comboBox_4->findText(ma.tra_list[j].destination));//Ŀ�ĵ�
	ui.label_6->setText(ma.tra_list[j].state);
	if (ma.tra_list[j].strategy == 1)//������ʱ
	{
		ui.radioButton_3->setChecked(true);
	}
	else
	{
		ui.radioButton_4->setChecked(true);
	}
	ui.dateTimeEdit_5->setDateTime(ma.tra_list[j].start_time);//����ʱ��
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
		QMessageBox::critical(this, "����", "������ÿ�");
		qDebug() << "������ÿ�" << endl;
		return;
	}
	//��ʼ��ʱ��
	qDebug() << ma.current_time.toString("MM-dd HH:mm") << endl;
	if (myTimer->isActive() == false)
	{
		myTimer->start(TIMER_INTVL);
		//ma.move_speed = ui.horizontalSlider->value();
	}
	ma.stimulation = true;
	ma.log("-----------��ʼģ��----------\n");
}

void MainWindow::stop_stimulation()
{
	qDebug() << "��ͣ" << endl;
	if (myTimer->isActive() == true)
	{
		myTimer->stop();
	}
	ma.log("-----------��ͣģ��----------\n");
}

void MainWindow::end_stimulation()
{
	if (ma.stimulation == true)
	{
		qDebug() << "��ֹģ��" << endl;
		myTimer->stop();
		//��ֹģ�⣬����ȫ������
		int num = ma.tra_list.size();
		ma.current_time = ma.tra_list[0].start_time;
		ma.move_speed = 1;//����ģ���ٶ�
		//����ÿһλ�ÿ͵Ĳ���
		for (int i = 0; i < num; i++)
		{
			int j = ma.getIndex(ma.tra_list[i].departure);//��ó������е��±�
			ma.tra_list[i].setPosition(ma.city_list[j].x, ma.city_list[j].y);
			ma.tra_list[i].moving = 1;
			ma.tra_list[i].rou_ID = 0;
			ma.tra_list[i].state = "ͣ��" + ma.tra_list[i].departure;
			qDebug() << "������������" << endl;
			if (ma.current_time > ma.tra_list[i].start_time)
			{
				ma.current_time = ma.tra_list[i].start_time;
				qDebug() << ma.current_time.toString("MM-dd HH:mm");
			}
		}
		QString str = ma.current_time.toString("MM-dd HH:mm");
		qDebug() << "��ǰʱ�����Ϊ��" << ma.current_time.toString("MM-dd HH:mm");
		ui.timedisplay1->setText(str);
		ui.timedisplay2->setText(str);
	}
	ma.stimulation = false;
	ma.log("-----------��ֹģ��----------\n");
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
	qDebug() << "���·��" << endl;
	QString str;
	int num = tra.route.size();
	for (int i = 0; i < num; i++)
	{
		QString start_time = tra.route[i].start_time.toString("MM-dd HH:mm");
		QString arrive_time= tra.route[i].arrival_time.toString("MM-dd HH:mm");
		
		QString str1 = start_time + " ---> " + arrive_time + "\n" + "����:" + tra.route[i].vehicle +tra.route[i].id + " �� " + tra.route[i].dep + " �� " + tra.route[i].des + "\n";
		
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
	myTimer->stop();//�رն�ʱ��
}

