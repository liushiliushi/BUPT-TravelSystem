#include "query.h"
//��֤����������ַ�
#if _MSC_VER >= 1600	// MSVC2015 > 1899,	MSVC_VER = 14.0
#endif
#pragma execution_character_se
extern Manager ma;
Query::Query(QWidget *parent) :QWidget(parent)
{
	ui.setupUi(this);
	//��ӱ�ͷ

	QStandardItemModel *model = new QStandardItemModel();

	model->setColumnCount(6);
	model->setRowCount(ma.time_table_size);

	model->setHorizontalHeaderItem(0, new QStandardItem("������"));
	model->setHorizontalHeaderItem(1, new QStandardItem("Ŀ�ĵ�"));
	model->setHorizontalHeaderItem(2, new QStandardItem("��ͨ����"));
	model->setHorizontalHeaderItem(3, new QStandardItem("����"));
	model->setHorizontalHeaderItem(4, new QStandardItem("����ʱ��"));
	model->setHorizontalHeaderItem(5, new QStandardItem("����ʱ��"));

	//���ñ�����ԣ�
	ui.tableView->setModel(model);
	ui.tableView->setColumnWidth(0, 80);
	ui.tableView->setColumnWidth(1, 80);
	ui.tableView->setColumnWidth(2, 80);
	ui.tableView->setColumnWidth(3, 80);
	ui.tableView->setColumnWidth(4, 80);
	ui.tableView->setColumnWidth(5, 80);
	//�����
	for (int i = 0; i < ma.time_table_size; i++)
	{
		model->setHeaderData(i, Qt::Vertical, i + 1);

		model->setItem(i, 0, new QStandardItem(ma.time_table[i].dep));
		model->setItem(i, 1, new QStandardItem(ma.time_table[i].des));
		model->setItem(i, 2, new QStandardItem(ma.time_table[i].vehicle));
		model->setItem(i, 3, new QStandardItem(ma.time_table[i].id));
		model->setItem(i, 4, new QStandardItem(ma.time_table[i].start_time.toString("HH:mm")));
		model->setItem(i, 5, new QStandardItem(ma.time_table[i].arrival_time.toString("HH:mm")));
	}
}
