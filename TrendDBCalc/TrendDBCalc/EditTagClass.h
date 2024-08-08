#pragma once

#include <QWidget>
#include "ui_EditTagClass.h"
#include <LuaCal.h>
class EditTagClass : public QWidget
{
	Q_OBJECT

public:
	EditTagClass(QWidget *parent = Q_NULLPTR);
	~EditTagClass();
	void SetEditValue(QString &index, QString describe, QString &tagName,QString &script,QString &interval);
	MyInfo m_info;

signals:
	void OkSignal(QString addName, QString describe ,QString addscript, QString addinterval);

private slots:
	void on_pushButton_ok_clicked();
	void on_pushButton_cancel_clicked();
private:
	Ui::EditTagClass ui;

};
