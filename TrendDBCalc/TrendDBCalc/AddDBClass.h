#pragma once

#include <QWidget>
#include "ui_AddDBClass.h"

class AddDBClass : public QWidget
{
	Q_OBJECT

public:
	AddDBClass(QWidget *parent = Q_NULLPTR);
	~AddDBClass();

signals:
	void OkSignal(QString &groupName);

private slots:
	void on_pushButton_ok_clicked();
	void on_pushButton_cancel_clicked();

private:
	Ui::AddDBClass ui;
};
