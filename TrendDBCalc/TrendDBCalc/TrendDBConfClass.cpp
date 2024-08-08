#include "TrendDBConfClass.h"

TrendDBConfClass::TrendDBConfClass(MyInfo &info, QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	ui.lineEdit_port->setText(QString("7000"));
	ui.lineEdit_addr->setText(QString::fromStdWString(info.addr));
	m_info = info;
	m_logger = info.logger;
}

TrendDBConfClass::~TrendDBConfClass()
{
}

void TrendDBConfClass::SetAddr(QString & addr)
{
	ui.lineEdit_addr->setText(addr);
}

void TrendDBConfClass::on_pushButton_ok_clicked()
{
	emit OkSignal(ui.lineEdit_addr->text(),ui.lineEdit_port->text());
	this->close();
}

void TrendDBConfClass::on_pushButton_cancel_clicked()
{
	this->close();
}

void TrendDBConfClass::on_pushButton_test_clicked()
{
	MyInfo info;
	info.addr = ui.lineEdit_addr->text().toStdWString();
	info.port = ui.lineEdit_port->text().toInt();
	info.logger = m_info.logger;
	auto m_cal = std::make_shared<LuaCal>();
	if (m_cal->ConnectTest(info) < 0)
	{
		QMessageBox::warning(NULL, "info", "connect fail", "ok");
	}
	else
	{
		QMessageBox::warning(NULL, "info", "connect success", "ok");
	}
}

