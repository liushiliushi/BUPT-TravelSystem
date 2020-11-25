//保证能输出中文字符
#if _MSC_VER >= 1600	// MSVC2015 > 1899,	MSVC_VER = 14.0
#pragma execution_character_set("utf-8")
#endif
#include"manager.h"

using namespace std;

extern Strategy way;//策略


Manager::Manager()
{
	move_speed = 1;
	QString min = "12-31 23:59";
	current_time = QDateTime::fromString(min, "MM-dd HH:mm");

	//读取城市文件
	QFile csvFile(CITY_FILE);
	QStringList CSVList;
	CSVList.clear();
	if (csvFile.open(QIODevice::ReadWrite))
	{
		QTextStream stream(&csvFile);
		QStringList tem;
		tem = stream.readLine().split(",");
		for (int i = 0; (tem[0] != ""); i++)
		{
			city_num++;
			city_list[i] = City(tem[0], tem[1].toInt(), tem[2].toInt(), tem[3].toFloat());
			tem = stream.readLine().split(",");
		}
		csvFile.close();
	}
	else
	{
		qDebug() << "读取城市文件错误" << endl;
		open = 0;
	}
	
}

void Manager::init_schedule()
{
	qDebug() << "初始化列车时刻表" << endl;
	//读文件初始化列车时刻表
	QFile csvFile(SCHEDULEFILE);
	QStringList CSVList;
	CSVList.clear();
	if (csvFile.open(QIODevice::ReadWrite))
	{
		QTextStream stream(&csvFile);
		QStringList tem;
		while (!stream.atEnd())
		{
			tem = stream.readLine().split(",");
			if (tem[0] == "")
			{
				return;
			}
			time_table[time_table_size] = Schedule(tem[0], tem[1], tem[2], tem[3], tem[4], tem[5]);
			time_table_size++;
		}
		csvFile.close();
	}
	else
	{
		qDebug() << "读取文件错误" << endl;
		open = 0;
	}
	
}

void Manager::ExitSystem()
{
	system("pause");
	exit(0);//退出程序
}

void Manager::show_tra_set()
{
	int num = tra_list.size();
	for (int i = 0; i < num; i++)
	{
		qDebug() << tra_list[i].name << "	" << tra_list[i].deadline.toString("hh:mm") << endl;
	}
}

void Manager::get_currentTime()
{
	int num = tra_list.size();
	current_time = tra_list[0].start_time;
	for (int i = 0; i < num; i++)
	{
		if (tra_list[i].start_time < current_time)
		{
			current_time = tra_list[i].start_time;
		}
	}
	qDebug() << "currentTime：" << current_time << endl;
}

void Manager::show_schedule()
{
	for (int i = 0; i < time_table_size; i++)
	{
		qDebug() << time_table[i].dep << "	" << time_table[i].des << "	" << time_table[i].start_time.toString("hh:mm") << "	" << time_table[i].arrival_time.toString("hh:mm") << endl;
	}
}

void Manager::stringToHtmlFilter(QString &str)
{
	//注意这几行代码的顺序不能乱，否则会造成多次替换
	str.replace("&", "&amp;");
	str.replace(">", "&gt;");
	str.replace("<", "&lt;");
	str.replace("\"", "&quot;");
	str.replace("\'", "&#39;");
	str.replace(" ", "&nbsp;");
	str.replace("\n", "<br>");
	str.replace("\r", "<br>");
}

void Manager::stringToHtml(QString &str, QColor crl)
{
	QByteArray array;
	array.append(crl.red());
	array.append(crl.green());
	array.append(crl.blue());
	QString strC(array.toHex());
	str = QString("<span style=\" color:#%1;\">%2</span>").arg(strC).arg(str);
}


int Manager::log(QString str)
{
	QFile logfile(LOGFILE);
	QDateTime current_date_time = QDateTime::currentDateTime();
	QString current_date = current_date_time.toString("【MM.dd hh:mm】：");
	if (!logfile.open(QIODevice::Append)) {
		return -1;
	}
	QTextStream out(&logfile);
	out << current_date << str << endl;
	out.flush();
	logfile.close();
	return 0;
}

int Manager::getIndex(QString city)
{
	for (int i = 0; i < city_num; i++)
	{
		if (city_list[i].name == city)
		{
			return i;
		}
	}
	return -1;//如果没找到返回-1
}


Manager::~Manager()
{

}