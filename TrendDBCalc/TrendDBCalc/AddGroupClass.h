#pragma once

#include <QWidget>
#include "ui_AddGroupClass.h"

class AddGroupClass : public QWidget
{
	Q_OBJECT

public:
	AddGroupClass(QWidget *parent = Q_NULLPTR);
	~AddGroupClass();

signals:
	void OkSignal(QString &groupName);

private slots:
	void on_pushButton_ok_clicked();
	void on_pushButton_cancel_clicked();

private:
	Ui::AddGroupClass ui;
};
