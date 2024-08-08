#pragma once
#pragma execution_character_set("utf-8")
#include <QWidget>
#include "ui_AddTagClass.h"
#include <LuaCal.h>
#include <tinyxml2.h>

class AddTagClass : public QWidget
{
	Q_OBJECT

public:
	AddTagClass(MyInfo &info, QWidget *parent = Q_NULLPTR);
	~AddTagClass();
	int ReConnect(MyInfo &info);
	QString m_dbName;

signals:
	void OkSignal(QString addName, QString describe, QString addscript,QString addinterval);

private slots:
	void on_pushButton_ok_clicked();
	void on_pushButton_cancel_clicked();
	void on_pushButton_test_clicked();
	void ChangeScript(const QModelIndex &index);
private:
	Ui::AddTagClass ui;
	std::shared_ptr<spdlog::logger>m_logger;
	std::map<QString, std::map<QString, QString>> m_script;
	std::shared_ptr<LuaCal> m_cal;
	MyInfo m_info;
	bool m_iniFlg = false;
	int ReadScript();
};
