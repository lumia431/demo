#pragma once

#include <QWidget>
#include "ui_TrendDBConfClass.h"
#include <QMessageBox>
#include <LuaCal.h>
class TrendDBConfClass : public QWidget
{
	Q_OBJECT

public:
	TrendDBConfClass(MyInfo &info,QWidget *parent = Q_NULLPTR);
	~TrendDBConfClass();
	MyInfo m_info;
	void SetAddr(QString &addr);

signals:
	void OkSignal(QString dbAddr, QString dbPort);


private slots:
	void on_pushButton_ok_clicked();
	void on_pushButton_cancel_clicked();
	void on_pushButton_test_clicked();

private:
	Ui::TrendDBConfClass ui;
	std::shared_ptr<spdlog::logger>m_logger;
};
