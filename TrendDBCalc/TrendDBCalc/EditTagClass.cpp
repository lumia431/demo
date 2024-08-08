#include "EditTagClass.h"

EditTagClass::EditTagClass(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
}

EditTagClass::~EditTagClass()
{
}
void EditTagClass::SetEditValue(QString &index , QString describe, QString &tagName, QString &script, QString &interval)
{
	ui.lineEdit_index->setText(index);
	ui.lineEdit_name->setText(tagName);
	ui.lineEdit_interval->setText(interval);
	ui.textEdit->setText(script);
	ui.lineEdit_describe->setText(describe);
}

void EditTagClass::on_pushButton_cancel_clicked()
{
	this->close();
}

void EditTagClass::on_pushButton_ok_clicked()
{
	emit OkSignal(ui.lineEdit_name->text(), ui.lineEdit_describe->text(),ui.textEdit->toPlainText(), ui.lineEdit_interval->text());
}