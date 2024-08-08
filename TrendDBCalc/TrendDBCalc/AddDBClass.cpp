#include "AddDBClass.h"

AddDBClass::AddDBClass(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
}

AddDBClass::~AddDBClass()
{
}

void AddDBClass::on_pushButton_cancel_clicked()
{
	this->close();
}

void AddDBClass::on_pushButton_ok_clicked()
{
	QString qsStr = ui.lineEdit->text();
	emit OkSignal(qsStr);
}
