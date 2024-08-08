#include "AddGroupClass.h"

AddGroupClass::AddGroupClass(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
}

AddGroupClass::~AddGroupClass()
{
}

void AddGroupClass::on_pushButton_cancel_clicked()
{
	this->close();
}

void AddGroupClass::on_pushButton_ok_clicked()
{
	auto qStr = ui.lineEdit->text();
	emit OkSignal(qStr);
}
