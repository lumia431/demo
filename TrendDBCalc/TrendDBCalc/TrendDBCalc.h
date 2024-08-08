#pragma once
#pragma execution_character_set("utf-8")//让能够正常显示中文字符串

#include <QtWidgets/QMainWindow>
#include "ui_TrendDBCalc.h"
#include "EditTagClass.h"
#include "AddTagClass.h"
#include "TrendDBConfClass.h"
#include "Log.h"
#include "LuaCal.h"
#include "AddGroupClass.h"
#include "AddDBClass.h"
#include <QSystemTrayIcon>
#include <set>

class TrendDBCalc : public QMainWindow
{
    Q_OBJECT

public:
    TrendDBCalc(QWidget *parent = Q_NULLPTR);

private slots:
	void on_tableWidget_customContextMenuRequested(const QPoint &pos);
	void on_treeWidget_customContextMenuRequested(const QPoint &pos);
	void on_actionexit_triggered();
	void on_actionstart_triggered();
	void on_actionend_triggered();
	void on_actionconf_triggered();
	void on_actionadd_triggered();
	void on_actionedit_triggered();
	void on_actiondelete_triggered();
	void on_actionimport_triggered();
	void on_actionexport_triggered();
	void on_actionsave_triggered();
	void on_actionclear_triggered();
	void on_pushButton_clicked();
	void closeEvent(QCloseEvent *event);
	void resizeEvent(QResizeEvent *event);
	void changeEvent(QEvent *event);
	void on_activatedSysTrayIcon(QSystemTrayIcon::ActivationReason reason);

private:
    Ui::TrendDBCalcClass ui;
	EditTagClass *m_edit;
	AddTagClass *m_add;
	TrendDBConfClass *m_conf;
	AddGroupClass *m_addGroup;
	AddDBClass *m_addDB;
	std::shared_ptr<LuaCal> m_cal;
	std::shared_ptr<spdlog::logger>m_logger;
	std::map<QString,std::map<QString,std::map<QString,std::tuple< QString,QString, QString>>>> *m_groupDatas;
	std::map<QString,std::tuple<QString, QString, QString>> *m_allDatas;
	std::map<QString, std::map<QString, std::tuple< QString, QString, QString>>>*m_dbDatas;
	std::map<QString, std::vector<QString>> m_dbGroup;
	void Add(QString addName, QString describe ,QString addscript, QString addinterval);
	void AddTag(QString &addName, QString &describe ,QString &addscript, QString &addinterval,bool messageFlg);
	void Edit(QString addName, QString describe, QString addscript, QString addinterval);
	int  EditTag(QString &addName, QString &describe, QString &addscript, QString &addinterval);
	void DeleteTag();
	void GetConf(QString dbAddr, QString dbPort);
	void ReadSqlite();
	void ClearTable();
	void ShowTag();
	void ReadCfg();
	void WriteCfg();
	void ChangeStatus(const QModelIndex &index);
	void AddGroup(QString &groupName);
	void GroupAdd(QString groupName , QString dbName);
	void AddDB(QString dbName);
	void DBAdd(QString dbName);
	void TabClicked(int index);
	void TabClose(int index);
	void CalcThread();
	void MyErase(QString &tagName);
	void MyInsert(QString &tagName,QString &describe, QString &addscript, QString &addinterval);
	void on_showMainAction();
	void on_exitAppAction();
	QString m_NowGroup;
	QString m_NowDB;
	QString m_addr;
	MyInfo m_info;
	Status m_status = Status::EMPTY;
	std::vector<TabInfo> m_runTab;
	std::thread m_thr;
	int m_logLevel = 1;
	bool m_endFlg = false;
	bool m_saveFlg = false;
	QSystemTrayIcon *m_sysTrayIcon;
	QTimer *m_timer;
	QString m_toDeleteTagName;
	QString m_toDeleteDesc;
	QString m_toDeleteScript;
	QString m_toDeleteInter;
};
