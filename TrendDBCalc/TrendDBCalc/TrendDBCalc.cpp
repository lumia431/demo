#include "TrendDBCalc.h"
#include <QtWidgets/QMainWindow>
#include "stdafx.h"
#include <fstream>
#include <QDebug>

//#include "CsvCreate.h"
//#include "MakeCSV.h"
#include "sqlite3.h"

//************************************
// Method:    TrendDBCalc
// FullName:  TrendDBCalc::TrendDBCalc
// Access:    public 
// Returns:   
// Qualifier: : QMainWindow(parent)
// Parameter: QWidget * parent
//************************************
TrendDBCalc::TrendDBCalc(QWidget *parent)
	: QMainWindow(parent)
{
	ReadCfg();
	spdlog::set_pattern("%Y-%m-%d %H:%M:%S - [thread %t][%^%l%$][%s][%#]|,%v");
	spdlog::set_level(static_cast<spdlog::level::level_enum>(m_logLevel));
	//设置日志为异步日志，不带滚动，日志文件会一直写入
	//my_logger_ = spdlog::basic_logger_mt(logger_name, file_name);
	m_logger = spdlog::basic_logger_mt<spdlog::async_factory >("m_calc", "./log.txt");
	//当遇到错误级别以上的立刻刷新到日志
	m_logger->flush_on(spdlog::level::err);
	//每三秒刷新一次
	spdlog::flush_every(std::chrono::seconds(3));
	m_info.logger = m_logger;

	m_edit = new EditTagClass();
	m_conf = new TrendDBConfClass(m_info);
	m_add = new AddTagClass(m_info);
	m_addGroup = new AddGroupClass();
	m_addDB = new AddDBClass();
	m_cal = std::make_shared<LuaCal>();
	m_timer = new QTimer;
	m_groupDatas = new std::map<QString, std::map<QString, std::map<QString, std::tuple<QString, QString, QString>>>>;
	m_allDatas = new std::map<QString, std::tuple<QString, QString, QString>>;
	m_dbDatas = new std::map<QString, std::map<QString, std::tuple<QString, QString, QString>>>;
	ui.setupUi(this);
	this->setWindowFlags(Qt::WindowMinimizeButtonHint | Qt::WindowCloseButtonHint);
	ui.actionstart->setDisabled(true);
	ui.actionimport->setDisabled(true);
	ui.tabWidget->clear();
	ui.tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
	ReadSqlite();
	//新建QSystemTrayIcon对象
	m_sysTrayIcon = new QSystemTrayIcon(this);

	//新建托盘要显示的pngn
	QIcon pngn = QIcon("./res/mini.png");
	//将pngn设到QSystemTrayIcon对象中
	m_sysTrayIcon->setIcon(pngn);
	//当鼠标移动到托盘上的图标时，会显示此处设置的内容
	m_sysTrayIcon->setToolTip(QObject::trUtf8("实时库计算点工具"));
	connect(m_sysTrayIcon, &QSystemTrayIcon::activated, this, &TrendDBCalc::on_activatedSysTrayIcon);
	connect(m_add, &AddTagClass::OkSignal,
		this, &TrendDBCalc::Add);
	connect(m_edit, &EditTagClass::OkSignal,
		this, &TrendDBCalc::Edit);
	connect(m_conf, &TrendDBConfClass::OkSignal,
		this, &TrendDBCalc::GetConf);
	connect(m_addGroup, &AddGroupClass::OkSignal,
		this, &TrendDBCalc::AddGroup);
	connect(m_addDB, &AddDBClass::OkSignal,
		this, &TrendDBCalc::AddDB);
	connect(ui.treeWidget, &QTreeWidget::doubleClicked,
		this, &TrendDBCalc::ChangeStatus);
	connect(ui.tabWidget, &QTabWidget::tabBarClicked,
		this, &TrendDBCalc::TabClicked);
	connect(ui.tabWidget, &QTabWidget::tabCloseRequested,
		this, &TrendDBCalc::TabClose);
	connect(m_timer, &QTimer::timeout, this, [this]() {
		if (m_saveFlg)
		{
			this->setWindowTitle("实时库计算工具");
			m_timer->stop();
		}
		});
	m_thr = std::thread(&TrendDBCalc::CalcThread, this);
	m_thr.detach();
}

//************************************
// Method:    on_tableWidget_clicked
// FullName:  TrendDBCalc::on_tableWidget_clicked
// Access:    private 
// Returns:   void
// Qualifier:
// Parameter: const QModelIndex & index
//************************************
void TrendDBCalc::on_tableWidget_customContextMenuRequested(const QPoint &pos)
{

	QAction* cc_0 = nullptr;
	cc_0 = new QAction(tr("增加测点"), this);
	QAction* cc_1 = nullptr;
	cc_1 = new QAction(tr("修改测点"), this);
	QAction* cc_2 = nullptr;
	cc_2 = new QAction(tr("删除测点"), this);
	QAction* cc_3 = nullptr;
	cc_3 = new QAction(tr("清空测点"), this);

	QMenu *menu = new QMenu(this);
	menu->addAction(cc_0);
	menu->addAction(cc_1);
	menu->addAction(cc_2);
	menu->addAction(cc_3);

	connect(cc_0, &QAction::triggered, this, [this]() {m_add->m_dbName = m_NowDB; m_add->show(); }); //每个Action信号相应一个槽函数
	connect(cc_1, &QAction::triggered, this, [this]() {
		int row = ui.tableWidget->currentRow();
		if (row >= 0)
		{
			QString tagnameText = ui.tableWidget->item(row, 0)->text();
			QString describeText = ui.tableWidget->item(row, 1)->text();
			QString scriptText = ui.tableWidget->item(row, 2)->text();
			QString intervalText = ui.tableWidget->item(row, 3)->text();
			QString rowStr = QString::number(row+1);
			m_edit->SetEditValue(rowStr, describeText, tagnameText, scriptText, intervalText);
			m_toDeleteTagName = tagnameText;
			m_toDeleteDesc = describeText;
			m_toDeleteScript = scriptText;
			m_toDeleteInter = intervalText;
		}
		else
		{
			QMessageBox::warning(NULL, "warning", "Please choose a tag", "ok");
			return;
		}
		m_edit->show();
		});
	connect(cc_2, &QAction::triggered, this, &TrendDBCalc::DeleteTag);
	connect(cc_3, &QAction::triggered, this, [this]() {

		int rowCount = ui.tableWidget->rowCount();

		for (int index = 0; index < rowCount; ++index)
		{
			QString tagnameText = ui.tableWidget->item(0, 0)->text();
			MyErase(tagnameText);
			ui.tableWidget->removeRow(0);
		}
		});
	menu->setStyleSheet("QMenu{background-color:rgb(255,255,255);color:rgb(0,0,0);font:10pt ""Microsoft YaHei"";}"
		"QMenu::item:selected{background-color:#CCDAE7;}"
		"QMenu::item:disabled{color:#BFBFBF;}");
	if (m_status == Status::DBCHOOSE)
	{
		cc_0->setEnabled(false);
	}
	menu->exec(QCursor::pos());

}

void TrendDBCalc::on_treeWidget_customContextMenuRequested(const QPoint & pos)
{
	if (pos.isNull())
	{
		return;
	}
	QAction* cc_0 = nullptr;
	cc_0 = new QAction(tr("增加数据库"), this);
	QAction* cc_1 = nullptr;
	cc_1 = new QAction(tr("删除数据库"), this);
	QAction* cc_2 = nullptr;
	cc_2 = new QAction(tr("增加点组"), this);
	QAction* cc_3 = nullptr;
	cc_3 = new QAction(tr("删除点组"), this);
	QMenu *menu = new QMenu(this);
	menu->addAction(cc_0);
	menu->addAction(cc_1);
	menu->addAction(cc_2);
	menu->addAction(cc_3);
	connect(cc_0, &QAction::triggered, this, [this]() {m_addDB->show(); });
	connect(cc_1, &QAction::triggered, this, [this]() {
		auto currentItem = ui.treeWidget->currentItem();
		auto dbName = currentItem->data(0, 0).toString();
		if (currentItem->parent())
		{
			return;
		}
		QMessageBox::StandardButton result = QMessageBox::information(NULL, "Confirm delete", "Really Delete? ", QMessageBox::Yes | QMessageBox::No);
		switch (result)
		{
		case QMessageBox::Yes:
			if (m_dbGroup[dbName].empty() && (*m_dbDatas)[dbName].empty())
			{
				ui.treeWidget->takeTopLevelItem(ui.treeWidget->currentIndex().row());
				m_dbGroup.erase(dbName);
				m_dbDatas->erase(dbName);
				m_groupDatas->erase(dbName);
				QMessageBox::information(NULL, "info", "Delete OK", "ok");
			}
			else
			{
				QMessageBox::warning(NULL, "warning", "Please clear the DB", "ok");
			}
			break;
		case QMessageBox::No:
			break;
		default:
			break;
		}
		});
	connect(cc_2, &QAction::triggered, this, [this]() {m_addGroup->show(); });
	connect(cc_3, &QAction::triggered, this, [this]() {
		auto currentItem = ui.treeWidget->currentItem();
		auto groupName = currentItem->data(0, 0).toString();
		if (groupName.isEmpty()) return;
		if (!currentItem->parent()) return;
		auto parentName = currentItem->parent()->data(0, 0).toString();
		if (m_dbGroup.find(parentName) == m_dbGroup.end())
		{
			return;
		}
		QMessageBox::StandardButton result = QMessageBox::information(NULL, "Confirm delete", "Really Delete? ", QMessageBox::Yes | QMessageBox::No);
		switch (result)
		{
		case QMessageBox::Yes:
			if ((*m_groupDatas)[parentName][groupName].empty())
			{
				currentItem->parent()->takeChild(ui.treeWidget->currentIndex().row());
				m_dbGroup[parentName].erase(std::find(m_dbGroup[parentName].begin(), m_dbGroup[parentName].end(), groupName));
				(*m_dbDatas)[parentName].erase(groupName);
				(*m_groupDatas)[parentName].erase(groupName);
				QMessageBox::information(NULL, "info", "Delete OK", "ok");
			}
			else
			{
				QMessageBox::warning(NULL, "warning", "Please clear the group", "ok");
			}
			break;
		case QMessageBox::No:
			break;
		default:
			break;
		}
		});
	menu->exec(QCursor::pos());
}

//************************************
// Method:    on_actionexit_triggered
// FullName:  TrendDBCalc::on_actionexit_triggered
// Access:    private 
// Returns:   void
// Qualifier:
//************************************
void TrendDBCalc::on_actionexit_triggered()
{
	m_sysTrayIcon->hide();
	this->close();
}

//************************************
// Method:    on_actionstart_triggered
// FullName:  TrendDBCalc::on_actionstart_triggered
// Access:    private 
// Returns:   void
// Qualifier:
//************************************
void TrendDBCalc::on_actionstart_triggered()
{
	std::thread thr([this]() {
		m_endFlg = false;
		m_cal->m_cancleFlg = false;
		auto prefDatas = std::make_shared<std::map<QString, std::tuple<QString, QString, QString>>>();
		for (auto &dbData : *m_dbDatas)
		{
			for (auto &data : dbData.second)
			{
				prefDatas->insert({ dbData.first + "." + data.first,data.second });
			}
		}
		int ret = m_cal->Init(m_info, prefDatas);
		if (ret < 0)
		{
			QMessageBox::warning(NULL, "info", "init fail", "ok");
			LOGINFO("Init fail , ret = {}", ret);
			return;
		}
		ui.actionend->setEnabled(true);
		ui.actionstart->setDisabled(true);
		m_cal->Run();
		});
	thr.detach();
}

//************************************
// Method:    on_actionend_triggered
// FullName:  TrendDBCalc::on_actionend_triggered
// Access:    private 
// Returns:   void
// Qualifier:
//************************************
void TrendDBCalc::on_actionend_triggered()
{
	m_endFlg = true;
	m_cal->m_cancleFlg = true;
	ui.actionend->setDisabled(true);
	ui.actionstart->setEnabled(true);
}

//************************************
// Method:    on_actionconf_triggered
// FullName:  TrendDBCalc::on_actionconf_triggered
// Access:    private 
// Returns:   void
// Qualifier:
//************************************
void TrendDBCalc::on_actionconf_triggered()
{
	m_conf->show();
}

//************************************
// Method:    on_actionadd_triggered
// FullName:  TrendDBCalc::on_actionadd_triggered
// Access:    private 
// Returns:   void
// Qualifier:
//************************************
void TrendDBCalc::on_actionadd_triggered()
{
	m_add->show();
}

//************************************
// Method:    on_actionedit_triggered
// FullName:  TrendDBCalc::on_actionedit_triggered
// Access:    private 
// Returns:   void
// Qualifier:
//************************************
void TrendDBCalc::on_actionedit_triggered()
{
	m_edit->show();
}

//************************************
// Method:    on_actiondelete_triggered
// FullName:  TrendDBCalc::on_actiondelete_triggered
// Access:    private 
// Returns:   void
// Qualifier:
//************************************
void TrendDBCalc::on_actiondelete_triggered()
{
	DeleteTag();
}

//************************************
// Method:    on_actionimport_triggered
// FullName:  TrendDBCalc::on_actionimport_triggered
// Access:    private 
// Returns:   void
// Qualifier:
//************************************
void TrendDBCalc::on_actionimport_triggered()
{
	QString filepath = QFileDialog::getOpenFileName(NULL, "请选择数据文件", "", "txt(*.txt)");
	if (filepath.isEmpty())
	{
		return;
	}
	QFile file(filepath);
	if (!file.open(QIODevice::ReadOnly))
	{
		QMessageBox::warning(NULL, "info", "打开文件失败", "ok");
		return;
	}
	QTextStream stream(&file);
	stream.setCodec("GBK");
	int rowIndex = ui.tableWidget->rowCount();
	while (!stream.atEnd())
	{
		auto line = stream.readLine();
		QStringList strList = line.split(",");
		if (strList.size() != 4)
		{
			QMessageBox::warning(NULL, "info", "file format eroor", "ok");
			return;
		}
		AddTag(strList[0], strList[1], strList[2], strList[3],false);
	}
	file.close();

}

//************************************
// Method:    on_actionexport_triggered
// FullName:  TrendDBCalc::on_actionexport_triggered
// Access:    private 
// Returns:   void
// Qualifier:
//************************************
void TrendDBCalc::on_actionexport_triggered()
{
	QString dirpath = QFileDialog::getSaveFileName(this, tr("保存的文件"), tr("."), tr("txt(*.txt)"));
	if (dirpath.isEmpty())
	{
		return;
	}
	QFile file(dirpath);
	if (file.open(QIODevice::ReadWrite | QIODevice::Truncate |QIODevice::Text))
	{
		QTextStream stream(&file);
		stream.seek(file.size());
		For(ui.tableWidget->rowCount())
		{
			QString tagnameText = ui.tableWidget->item(index, 0)->text();
			QString describeText = ui.tableWidget->item(index, 1)->text();
			QString scriptText = ui.tableWidget->item(index, 2)->text();
			std::string scriptStr = scriptText.toStdString();
			scriptStr.erase(std::remove_if(scriptStr.begin(), scriptStr.end(), [](const char& argStr) {
				return (argStr == '\t' || argStr == '\n');
				}), scriptStr.end());
			QString intervalText = ui.tableWidget->item(index, 3)->text();
			QString qs;
			qs.append(tagnameText);
			qs.append(",");
			qs.append(describeText);
			qs.append(",");
			qs.append(QString::fromStdString(scriptStr));
			qs.append(",");
			qs.append(intervalText);
			stream << qs << "\n";
		}
		file.close();
	}

	//QString qs;
	//for (auto& data : m_tableData)
	//{
	//	qs.append(data.first);
	//	qs.append(",");
	//	qs.append(std::get<0>(data.second));
	//	qs.append(",");
	//	qs.append(std::get<1>(data.second));
	//}
	//CreateCsv(qs.toStdString(), dirpath.toStdString());
	QMessageBox::information(NULL, "info", "export success", "ok");
}

//************************************
// Method:    on_actionsave_triggered
// FullName:  TrendDBCalc::on_actionsave_triggered
// Access:    private 
// Returns:   void
// Qualifier:
//************************************
void TrendDBCalc::on_actionsave_triggered()
{
	m_timer->start(1000);
	this->setWindowTitle("实时库计算工具 is saving ,do not exit ");
	std::thread thr([this]() {
		sqlite3 * db;
		char *zErrMsg = 0;
		int res = sqlite3_open("trendDBCalc.db", &db);
		if (res != SQLITE_OK)
		{
			LOGINFO("sqlite open fail! {}", sqlite3_errmsg(db));
			return;
		}
		try
		{
			const char* clearGroup = "DELETE FROM CALCGROUP";
			res = sqlite3_exec(db, clearGroup, NULL, NULL, &zErrMsg);
			const char* clearTag = "DELETE FROM TRENDDBCALC";
			res = sqlite3_exec(db, clearTag, NULL, NULL, &zErrMsg);
			for (auto &dbname : m_dbGroup)
			{
				for (auto &group : dbname.second)
				{
					std::string insertSql = "INSERT INTO CALCGROUP(DBNAME,GROUPNAME) VALUES";
					insertSql += "('" + dbname.first.toStdString() + "','" + group.toStdString() + "');";
					res = sqlite3_exec(db, insertSql.c_str(), NULL, NULL, &zErrMsg);
					if (res != SQLITE_OK)
					{
						LOGINFO("sqlite insert fail! {}", sqlite3_errmsg(db));
					}
				}
			}
			//time_t timeNow = time(NULL);
			//sqlite3_stmt *stmt = NULL;
			//std::string insertSql = "INSERT INTO TRENDDBCALC(TAGNAME,DBNAME,GROUPNAME,DESCRIBE,SCRIPT,INTERVAL) VALUES(?,?,?,?,?,?)";
			//res = sqlite3_prepare_v2(db, insertSql.c_str(), -1, &stmt, NULL);
			//for (auto &dbData : *m_groupDatas)
			//{
			//	for (auto &groupData : dbData.second)
			//	{
			//		for (auto &data : groupData.second)
			//		{
			//			sqlite3_bind_text(stmt, 1, data.first.toStdString().c_str(), data.first.toStdString().size(), NULL);
			//			sqlite3_bind_text(stmt, 2, dbData.first.toStdString().c_str(), dbData.first.toStdString().size(), NULL);
			//			sqlite3_bind_text(stmt, 3, groupData.first.toStdString().c_str(), groupData.first.toStdString().size(), NULL);
			//			sqlite3_bind_text(stmt, 4, std::get<0>(data.second).toStdString().c_str(), std::get<0>(data.second).toStdString().size(), NULL);
			//			sqlite3_bind_text(stmt, 5, std::get<1>(data.second).toStdString().c_str(), std::get<1>(data.second).toStdString().size(), NULL);
			//			sqlite3_bind_text(stmt, 6, std::get<2>(data.second).toStdString().c_str(), std::get<2>(data.second).toStdString().size(), NULL);
			//			res = sqlite3_step(stmt);
			//			if (res != SQLITE_OK && res!= SQLITE_DONE)
			//			{
			//				LOGINFO("sqlite insert fail! tag name = {}{}", data.first.toStdString(), sqlite3_errmsg(db));
			//			}
			//		}
			//	}
			//}
			std::string insertSql = "INSERT INTO TRENDDBCALC(TAGNAME,DBNAME,GROUPNAME,DESCRIBE,SCRIPT,INTERVAL) VALUES";
			for (auto &dbData : *m_groupDatas)
			{
				for (auto &groupData : dbData.second)
				{
					for (auto &data : groupData.second)
					{
						insertSql += "('" + data.first.toStdString() + "','" + dbData.first.toStdString() + "','" + groupData.first.toStdString() + "','" +
							std::get<0>(data.second).toStdString() + "','" + std::get<1>(data.second).toStdString() + "','" + std::get<2>(data.second).toStdString() + "'),";
					}
				}
			}
			insertSql.erase(insertSql.end() - 1);
			res = sqlite3_exec(db, insertSql.c_str(), NULL, NULL, &zErrMsg);
			if (res != SQLITE_OK)
			{
				LOGINFO("sqlite insert fail! error info = {}", sqlite3_errmsg(db));
			}
			/*qDebug() << "time using = " << time(NULL) - timeNow;*/
		}
		catch (const std::exception&)
		{
			return;
		}
		sqlite3_close(db);
		m_saveFlg = true;
		});
	thr.detach();
}

//************************************
// Method:    on_actionclear_triggered
// FullName:  TrendDBCalc::on_actionclear_triggered
// Access:    private 
// Returns:   void
// Qualifier:
//************************************
void TrendDBCalc::on_actionclear_triggered()
{
	sqlite3 * db;
	char *zErrMsg = 0;
	int res = sqlite3_open("trendDBCalc.db", &db);
	if (res != SQLITE_OK)
	{
		LOGINFO("sqlite open fail! {}", sqlite3_errmsg(db));
		return;
	}
	const char* clearGroup = "DELETE FROM CALCGROUP";
	res = sqlite3_exec(db, clearGroup, NULL, NULL, &zErrMsg);
	const char* clearSql = "DELETE FROM TRENDDBCALC";
	res = sqlite3_exec(db, clearSql, NULL, NULL, &zErrMsg);
	if (res != SQLITE_OK)
	{
		QMessageBox::warning(NULL, "info", "clear fail", "ok");
		LOGINFO("sqlite open fail! {}", sqlite3_errmsg(db));
		return;
	}
	else
	{
		QMessageBox::warning(NULL, "info", "clear success!", "ok");
	}
	sqlite3_close(db);
}

void TrendDBCalc::on_pushButton_clicked()
{
	auto queryStr = ui.lineEdit->text();
	For(ui.tableWidget->rowCount())
	{
		if (queryStr == ui.tableWidget->item(index, 0)->text())
		{
			ui.tableWidget->selectRow(index);
			return;
		}
	}
	QMessageBox::warning(NULL, "info", "can not find the tag ", "ok");
}

//************************************
// Method:    AddTag
// FullName:  TrendDBCalc::AddTag
// Access:    private 
// Returns:   void
// Qualifier:
// Parameter: QString addName
// Parameter: QString addscript
// Parameter: QString addinterval
//************************************
void TrendDBCalc::Add(QString addName, QString describe, QString addscript, QString addinterval)
{
	m_add->close();
	AddTag(addName, describe, addscript, addinterval,true);
}

void TrendDBCalc::AddTag(QString & addName, QString & describe, QString & addscript, QString & addinterval, bool messageFlg)
{
	if (addName.isEmpty() || addscript.isEmpty() || addinterval.isEmpty())
	{
		if(messageFlg)
		QMessageBox::warning(NULL, "info", "Add fail !tag info empty", "ok");
		return;
	}
	for (auto data : *m_allDatas)
	{
		if (data.first == addName)
		{
			if (messageFlg)
			QMessageBox::warning(NULL, "info", "Add fail !tagname is exist", "ok");
			return;
		}
	}
	int row = ui.tableWidget->rowCount();
	if (row < 0) row = 0;
	ui.tableWidget->setRowCount(row + 1);
	QTableWidgetItem * itemname = new QTableWidgetItem();
	itemname->setText(addName);
	ui.tableWidget->setItem(row, 0, itemname);
	QTableWidgetItem * itemdesc = new QTableWidgetItem();
	itemdesc->setText(describe);
	ui.tableWidget->setItem(row, 1, itemdesc);
	QTableWidgetItem * itemscript = new QTableWidgetItem();
	itemscript->setText(addscript);
	ui.tableWidget->setItem(row, 2, itemscript);
	QTableWidgetItem * iteminterval = new QTableWidgetItem();
	iteminterval->setText(addinterval);
	ui.tableWidget->setItem(row, 3, iteminterval);
	MyInsert(addName, describe, addscript, addinterval);
}

//************************************
// Method:    Edit
// FullName:  TrendDBCalc::Edit
// Access:    private 
// Returns:   void
// Qualifier:
// Parameter: QString addName
// Parameter: QString addscript
// Parameter: QString addinterval
//************************************
void TrendDBCalc::Edit(QString addName, QString describe, QString addscript, QString addinterval)
{
	m_edit->close();
	MyErase(m_toDeleteTagName);

	if (EditTag(addName, describe, addscript, addinterval) < 0)
	{
		MyInsert(m_toDeleteTagName, m_toDeleteDesc, m_toDeleteScript, m_toDeleteInter);
	}
}

int TrendDBCalc::EditTag(QString & addName, QString & describe, QString & addscript, QString & addinterval)
{
	if (addName.isEmpty() || addscript.isEmpty() || addinterval.isEmpty())
	{
		QMessageBox::warning(NULL, "info", "Add fail! please check empty", "ok");
		return -1;
	}
	for (auto data : *m_allDatas)
	{
		if (data.first == addName)
		{
			QMessageBox::warning(NULL, "info", "Add fail !tagname is exist", "ok");
			return -1;
		}
	}
	int row = ui.tableWidget->currentRow();
	if (row < 0) return -1;
	QTableWidgetItem * itemname = new QTableWidgetItem();
	itemname->setText(addName);
	ui.tableWidget->setItem(row, 0, itemname);
	QTableWidgetItem * itemdesc = new QTableWidgetItem();
	itemdesc->setText(describe);
	ui.tableWidget->setItem(row, 1, itemdesc);
	QTableWidgetItem * itemscript = new QTableWidgetItem();
	itemscript->setText(addscript);
	ui.tableWidget->setItem(row, 2, itemscript);
	QTableWidgetItem * iteminterval = new QTableWidgetItem();
	iteminterval->setText(addinterval);
	ui.tableWidget->setItem(row, 3, iteminterval);
	MyInsert(addName, describe, addscript, addinterval);
}

//************************************
// Method:    DeleteTag
// FullName:  TrendDBCalc::DeleteTag
// Access:    private 
// Returns:   void
// Qualifier:
//************************************
void TrendDBCalc::DeleteTag()
{
	auto range = ui.tableWidget->selectedRanges();
	int rangesize = range.size();
	int deleteNum = 0;
	if (!range.empty())
	{
		int index = 0;
		while (index < rangesize)
		{
			auto ran = ui.tableWidget->selectedRanges();
			int i = 0;
			while (i < ran[0].bottomRow() - ran[0].topRow() + 1)
			{
				QString tagnameText = ui.tableWidget->item(ran[0].topRow(), 0)->text();
				MyErase(tagnameText);
				ui.tableWidget->removeRow(ran[0].topRow());
				i++;
			}
			index++;
		}
	}
}

//************************************
// Method:    GetConf
// FullName:  TrendDBCalc::GetConf
// Access:    private 
// Returns:   void
// Qualifier:
// Parameter: QString dbAddr
// Parameter: QString dbPort
//************************************
void TrendDBCalc::GetConf(QString dbAddr, QString dbPort)
{
	m_info.addr = dbAddr.toStdWString();
	m_info.port = dbPort.toInt();
	m_add->ReConnect(m_info);
	m_conf->m_info = m_info;
}

//************************************
// Method:    resizeEvent
// FullName:  TrendDBCalc::resizeEvent
// Access:    private 
// Returns:   void
// Qualifier:
// Parameter: QResizeEvent * event
//************************************
void TrendDBCalc::resizeEvent(QResizeEvent *event)
{
	//列宽随窗口大小改变而改变，每列平均分配，充满整个表，但是此时列宽不能拖动进行改变
	int widths = event->size().width() / 10;
	ui.tableWidget->setColumnWidth(0, widths * 2);
	ui.tableWidget->setColumnWidth(1, widths * 2);
	ui.tableWidget->setColumnWidth(2, widths * 3.3);
	ui.tableWidget->setColumnWidth(3, widths * 1);
}
void TrendDBCalc::changeEvent(QEvent * event)
{
	if (event->type() != QEvent::WindowStateChange) return;
	if (!this->isMinimized()) return;
	auto type = event->type();
	//隐藏程序主窗口
	this->hide();
	QMenu* mMenu = new QMenu(this);
	QAction* cc_1 = nullptr;
	cc_1 = new QAction(tr("显示主界面"), this);
	QAction* cc_2 = nullptr;
	cc_2 = new QAction(tr("退出"), this);

	//新增菜单项---显示主界面
	mMenu->addAction(cc_1);
	//增加分隔符
	mMenu->addSeparator();
	//新增菜单项---退出程序
	mMenu->addAction(cc_2);
	connect(cc_1, &QAction::triggered, this, &TrendDBCalc::on_showMainAction);
	connect(cc_2, &QAction::triggered, this, &TrendDBCalc::on_exitAppAction);
	//把QMenu赋给QSystemTrayIcon对象
	m_sysTrayIcon->setContextMenu(mMenu);
	//在系统托盘显示此对象
	m_sysTrayIcon->show();
}
void TrendDBCalc::on_activatedSysTrayIcon(QSystemTrayIcon::ActivationReason reason)
{
	switch (reason) {
	case QSystemTrayIcon::Trigger:
		//单击托盘图标
		break;
	case QSystemTrayIcon::DoubleClick:
		//双击托盘图标
		//双击后显示主程序窗口
		m_sysTrayIcon->hide();
		this->showMaximized();
		/*this->show();*/
		break;
	default:
		break;
	}
}
//************************************
// Method:    closeEvent
// FullName:  TrendDBCalc::closeEvent
// Access:    private 
// Returns:   void
// Qualifier:
// Parameter: QCloseEvent * event
//************************************
void TrendDBCalc::closeEvent(QCloseEvent * event)
{
	m_cal->m_cancleFlg = true;
	m_sysTrayIcon->hide();
	delete m_sysTrayIcon;
	delete m_conf;
	delete m_edit;
	delete m_add;
	delete m_addGroup;
	delete m_timer;
	m_logger.reset();
	m_cal.reset();
}
//************************************
// Method:    ReadSqlite
// FullName:  TrendDBCalc::ReadSqlite
// Access:    private 
// Returns:   void
// Qualifier:
//************************************
void TrendDBCalc::ReadSqlite()
{
	sqlite3 * db;
	char *zErrMsg = 0;
	int res = sqlite3_open("trendDBCalc.db", &db);
	if (res != SQLITE_OK)
	{
		LOGINFO("sqlite open fail! {}", sqlite3_errmsg(db));
		return;
	}
	const char * createSql = "CREATE TABLE TRENDDBCALC( TAGNAME CHAR(50) PRIMARY KEY NOT NULL, DBNAME CHAR(50), GROUPNAME CHAR(50), DESCRIBE CHAR(50), SCRIPT CHAR(200), INTERVAL CHAR(50));";
	const char * createSqlGroup = "CREATE TABLE CALCGROUP( DBNAME CHAR(50) NOT NULL, GROUPNAME CHAR(50) );";

	res = sqlite3_exec(db, createSql, NULL, NULL, &zErrMsg);
	res = sqlite3_exec(db, createSqlGroup, NULL, NULL, &zErrMsg);

	const char* querySqlGroup = "SELECT *FROM CALCGROUP";
	sqlite3_stmt *stmtGroup = NULL;
	res = sqlite3_prepare_v2(db, querySqlGroup, -1, &stmtGroup, NULL);
	while (sqlite3_step(stmtGroup) == SQLITE_ROW)
	{
		const char *dbnameStr = (char*)sqlite3_column_text(stmtGroup, 0);
		const char *groupStr = (char*)sqlite3_column_text(stmtGroup, 1);
		DBAdd(QString(dbnameStr));
		GroupAdd(QString(groupStr), QString(dbnameStr));
	}
	const char * querySql = "SELECT *FROM TRENDDBCALC";
	sqlite3_stmt *stmt = NULL;
	res = sqlite3_prepare_v2(db, querySql, -1, &stmt, NULL);
	while (sqlite3_step(stmt) == SQLITE_ROW)
	{
		const char *nameStr = (char*)sqlite3_column_text(stmt, 0);
		const char *dbnameStr = (char*)sqlite3_column_text(stmt, 1);
		const char *groupStr = (char*)sqlite3_column_text(stmt, 2);
		const char *describeStr = (char*)sqlite3_column_text(stmt, 3);
		const char *scriptStr = (char*)sqlite3_column_text(stmt, 4);
		const char *intervalStr = (char*)sqlite3_column_text(stmt, 5);
		std::pair<QString, std::tuple<QString, QString, QString>> tmpMap({ QString(nameStr),std::make_tuple(QString(describeStr),QString(scriptStr),QString(intervalStr)) });
		m_allDatas->insert(tmpMap);
		(*m_dbDatas)[dbnameStr].insert(tmpMap);
		(*m_groupDatas)[dbnameStr][groupStr].insert(tmpMap);
	}
	sqlite3_close(db);
}

//************************************
// Method:    ClearTag
// FullName:  TrendDBCalc::ClearTag
// Access:    private 
// Returns:   void
// Qualifier:
//************************************
void TrendDBCalc::ClearTable()
{
	int rowCount = ui.tableWidget->rowCount();

	for (int index = 0; index < rowCount; ++index)
	{
		ui.tableWidget->removeRow(0);
	}
}

void TrendDBCalc::ShowTag()
{
	if (m_NowDB.isEmpty()) return;

	ClearTable();
	switch (m_status)
	{
	case Status::DBCHOOSE:
	{
		int ReadIndex = 0;
		for (auto &data : (*m_dbDatas)[m_NowDB])
		{
			ui.tableWidget->setRowCount(ReadIndex + 1);
			QTableWidgetItem * itemname = new QTableWidgetItem();
			itemname->setText(data.first);
			ui.tableWidget->setItem(ReadIndex, 0, itemname);
			QTableWidgetItem * itemdescribe = new QTableWidgetItem();
			itemdescribe->setText(std::get<0>(data.second));
			ui.tableWidget->setItem(ReadIndex, 1, itemdescribe);
			QTableWidgetItem * itemscript = new QTableWidgetItem();
			itemscript->setText(std::get<1>(data.second));
			ui.tableWidget->setItem(ReadIndex, 2, itemscript);
			QTableWidgetItem * iteminterval = new QTableWidgetItem();
			iteminterval->setText(std::get<2>(data.second));
			ui.tableWidget->setItem(ReadIndex, 3, iteminterval);
			ReadIndex++;
		}
	}
	break;
	case Status::GROUPCHOOSE:
	{
		if (m_NowGroup.isEmpty()) return;
		ClearTable();
		int Index = 0;
		for (auto &data : (*m_groupDatas)[m_NowDB][m_NowGroup])
		{
			ui.tableWidget->setRowCount(Index + 1);
			QTableWidgetItem * itemname = new QTableWidgetItem();
			itemname->setText(data.first);
			ui.tableWidget->setItem(Index, 0, itemname);
			QTableWidgetItem * itemdescribe = new QTableWidgetItem();
			itemdescribe->setText(std::get<0>(data.second));
			ui.tableWidget->setItem(Index, 1, itemdescribe);
			QTableWidgetItem * itemscript = new QTableWidgetItem();
			itemscript->setText(std::get<1>(data.second));
			ui.tableWidget->setItem(Index, 2, itemscript);
			QTableWidgetItem * iteminterval = new QTableWidgetItem();
			iteminterval->setText(std::get<2>(data.second));
			ui.tableWidget->setItem(Index, 3, iteminterval);
			Index++;
		}
	}
	break;
	case Status::EMPTY:
		break;
	default:
		break;
	}
}

void TrendDBCalc::ReadCfg()
{
	std::ifstream file("./config.ini");
	if (!file)
	{
		std::ofstream ofile("./config.ini");
		ofile << "127.0.0.1" << std::endl;
		ofile << "2" << std::endl;
		ofile.close();
		m_logLevel = 2;
		m_addr = QString("127.0.0.1");
		m_info.addr = QString("127.0.0.1").toStdWString();
		ofile.close();
		return;
	}
	std::string strCfg;
	std::vector<std::string>cfgList;
	For(2)
	{
		std::getline(file, strCfg);
		cfgList.push_back(strCfg);
	}
	m_addr = QString(cfgList[0].c_str());
	m_info.addr = m_addr.toStdWString();
	m_logLevel = std::atoi(cfgList[1].c_str());
	file.close();
}

void TrendDBCalc::WriteCfg()
{
	std::ofstream ofile("./config.ini");
	ofile << m_addr.toStdString() << std::endl;
	ofile << m_logLevel << std::endl;
}

void TrendDBCalc::ChangeStatus(const QModelIndex &index)
{
	auto nowIndex = index;

	auto chooseName = nowIndex.data().toString();
	if (!nowIndex.parent().isValid())
	{
		m_NowDB = chooseName;
		m_status = Status::DBCHOOSE;
		ui.actionimport->setDisabled(true);
		bool existFlg = false;
		int index = 0;
		for (auto &tab : m_runTab)
		{
			if (tab.status == Status::DBCHOOSE && tab.dbName == m_NowDB)
			{
				ui.tabWidget->setCurrentIndex(index);
				existFlg = true;
				break;
			}
			index++;
		}
		if (!existFlg)
		{
			auto tab = new QWidget();
			ui.tabWidget->addTab(tab, QString());
			ui.tabWidget->setCurrentWidget(tab);
			ui.tabWidget->setTabText(ui.tabWidget->count() - 1, QApplication::translate("TrendDBCalcClass", m_NowDB.toStdString().c_str(), Q_NULLPTR));
			TabInfo info(m_status, m_NowDB);
			m_runTab.emplace_back(info);
		}
	}
	else
	{
		m_NowDB = nowIndex.parent().data().toString();
		m_NowGroup = chooseName;
		m_status = Status::GROUPCHOOSE;
		ui.actionimport->setEnabled(true);
		bool existFlg = false;
		int index = 0;
		for (auto &tab : m_runTab)
		{
			if (tab.status == Status::GROUPCHOOSE && tab.dbName == m_NowDB && tab.groupName == m_NowGroup)
			{
				ui.tabWidget->setCurrentIndex(index);
				existFlg = true;
				break;
			}
			index++;
		}
		if (!existFlg)
		{
			auto tab = new QWidget();
			ui.tabWidget->addTab(tab, QString());
			ui.tabWidget->setCurrentWidget(tab);
			ui.tabWidget->setTabText(ui.tabWidget->count() - 1, QApplication::translate("TrendDBCalcClass", m_NowGroup.toStdString().c_str(), Q_NULLPTR));
			TabInfo info(m_status, m_NowDB, m_NowGroup);
			m_runTab.emplace_back(info);
		}
	}
	ShowTag();
}

void TrendDBCalc::AddGroup(QString &groupName)
{
	auto currItem = ui.treeWidget->currentItem();
	QString dbName = currItem->data(0, 0).toString();
	if (!currItem)
	{
		QMessageBox::warning(NULL, "info", "Add faile! Please choose a db", "ok");
		return;
	}
	if (currItem->parent())
	{
		QMessageBox::warning(NULL, "info", "Add faile! Please choose a db", "ok");
		return;
	}
	if (std::find(m_dbGroup[dbName].begin(), m_dbGroup[dbName].end(), groupName) != m_dbGroup[dbName].end())
	{
		QMessageBox::warning(NULL, "info", "Add faile! group name exist", "ok");
		return;
	}

	QTreeWidgetItem *item = new QTreeWidgetItem(currItem, QStringList(QString(groupName))); //子节点1
	currItem->addChild(item); //添加子节点
	item->setIcon(0, QIcon("./res/b.png"));
	m_dbGroup[dbName].emplace_back(groupName);
	m_addGroup->close();
}

void TrendDBCalc::GroupAdd(QString groupName, QString dbName)
{
	auto parentItem = ui.treeWidget->findItems(dbName, Qt::MatchFlag::MatchRecursive);
	if (parentItem.empty()) return;
	if (std::find(m_dbGroup[dbName].begin(), m_dbGroup[dbName].end(), groupName) != m_dbGroup[dbName].end()) return;
	QTreeWidgetItem *item = new QTreeWidgetItem(parentItem.front(), QStringList(QString(groupName))); //子节点1
	parentItem.front()->addChild(item); //添加子节点
	item->setIcon(0, QIcon("./res/b.png"));
	m_dbGroup[dbName].emplace_back(groupName);
}

void TrendDBCalc::AddDB(QString dbName)
{
	if (m_dbGroup.find(dbName) != m_dbGroup.end())
	{
		QMessageBox::warning(NULL, "info", "Add faile! dbName is exist", "ok");
		return;
	}
	auto itemDB = new QTreeWidgetItem(ui.treeWidget, QStringList(QString(dbName)));
	itemDB->setIcon(0, QIcon("./res/a.png"));
	m_addDB->close();
}

void TrendDBCalc::DBAdd(QString dbName)
{
	if (m_dbGroup.find(dbName) != m_dbGroup.end())
	{
		return;
	}
	auto itemDB = new QTreeWidgetItem(ui.treeWidget, QStringList(QString(dbName)));
	itemDB->setIcon(0, QIcon("./res/a.png"));
}

void TrendDBCalc::TabClicked(int index)
{
	auto info = m_runTab[index];
	ui.tabWidget->setCurrentIndex(index);
	m_status = info.status;
	m_NowDB = info.dbName;
	switch (m_status)
	{
	case Status::DBCHOOSE:
		ui.actionimport->setDisabled(true);
		ShowTag();
		break;
	case Status::GROUPCHOOSE:
		m_NowGroup = info.groupName;
		ui.actionimport->setEnabled(true);
		ShowTag();
		break;
	case Status::EMPTY:
		break;
	default:
		break;
	}
}

void TrendDBCalc::TabClose(int index)
{
	auto removeName = ui.tabWidget->tabText(index);
	auto iter = m_runTab.begin();
	m_runTab.erase(iter + index);
	ui.tabWidget->removeTab(index);
	auto nowIndex = ui.tabWidget->currentIndex();
	m_status = m_runTab[nowIndex].status;
	m_NowDB = m_runTab[nowIndex].dbName;
	m_NowGroup = m_runTab[nowIndex].groupName;
	ShowTag();
}

void TrendDBCalc::CalcThread()
{
	while (true)
	{
		if (m_endFlg)
		{
			return;
		}
		auto prefDatas = std::make_shared<std::map<QString, std::tuple<QString, QString, QString>>>();
		for (auto &dbData : *m_dbDatas)
		{
			for (auto &data : dbData.second)
			{
				prefDatas->insert({ dbData.first + "." + data.first,data.second });
			}
		}
		int ret = m_cal->Init(m_info, prefDatas);
		if (ret < 0)
		{
			LOGINFO("Init fail , ret = {}", ret);
			Sleep(30000);
			continue;
		}
		else
		{
			break;
		}
	}
	m_cal->Run();
}

void TrendDBCalc::MyErase(QString & tagName)
{
	if (m_NowDB.isEmpty())
	{
		return;
	}
	switch (m_status)
	{
	case Status::DBCHOOSE:
		(*m_dbDatas)[m_NowDB].erase(tagName);
		m_allDatas->erase(tagName);
		for (auto &data : (*m_groupDatas)[m_NowDB])
		{
			if (data.second.find(tagName) != data.second.end())
			{
				data.second.erase(tagName);
				break;
			}
		}
		break;
	case Status::GROUPCHOOSE:
		if (m_NowGroup.isEmpty()) break;
		(*m_groupDatas)[m_NowDB][m_NowGroup].erase(tagName);
		(*m_dbDatas)[m_NowDB].erase(tagName);
		m_allDatas->erase(tagName);
		break;
	case Status::EMPTY:
		break;
	default:
		break;
	}
}

void TrendDBCalc::MyInsert(QString & tagName, QString & describe, QString & addscript, QString & addinterval)
{
	if (tagName.isEmpty() && addscript.isEmpty() && addinterval.isEmpty())
	{
		return;
	}
	if (m_NowDB.isEmpty())
	{
		return;
	}
	switch (m_status)
	{
	case Status::GROUPCHOOSE:
		(*m_groupDatas)[m_NowDB][m_NowGroup].insert({ tagName,std::make_tuple(describe,addscript, addinterval) });
		(*m_dbDatas)[m_NowDB].insert({ tagName,std::make_tuple(describe,addscript, addinterval) });
		m_allDatas->insert({ tagName,std::make_tuple(describe,addscript, addinterval) });
		break;
	case Status::DBCHOOSE:
		break;
	case Status::EMPTY:
		break;
	default:
		break;
	}
}

/*
* 当在系统托盘点击菜单内的显示主界面操作
*/
void TrendDBCalc::on_showMainAction()
{
	m_sysTrayIcon->hide();
	this->showMaximized();
}

/*
* 当在系统托盘点击菜单内的退出程序操作
*/
void TrendDBCalc::on_exitAppAction()
{
	m_sysTrayIcon->hide();
	exit(0);
}