#include "AddTagClass.h"
using namespace tinyxml2;

AddTagClass::AddTagClass(MyInfo &info, QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	m_info = info;
	m_logger = info.logger;
	connect(ui.treeWidget, &QTreeWidget::doubleClicked,
		this, &AddTagClass::ChangeScript);
	ui.textEdit->setContentsMargins(20,0,20,0);
	if (ReadScript() < 0)
	{
		LOGINFO("Read script file fail");
	}
	m_cal = std::make_shared<LuaCal>();
	auto ret = m_cal->ConnectTest(m_info);
	if (ret < 0)
	{
		LOGINFO("Connect RTDB fail");
		return;
	}
	m_iniFlg = true;
}
AddTagClass::~AddTagClass()
{
}

int AddTagClass::ReConnect(MyInfo & info)
{
	m_info.addr = info.addr;
	m_info.port = info.port;
	auto ret = m_cal->ConnectTest(m_info);
	if (ret < 0)
	{
		m_iniFlg = false;
		LOGINFO("Connect RTDB fail");
		return -1;
	}
	m_iniFlg = true;
	return 0;
}

void AddTagClass::on_pushButton_cancel_clicked()
{
	this->close();
}

void AddTagClass::on_pushButton_test_clicked()
{
	QString addName = ui.lineEdit_name->text();
	QString addscript = ui.textEdit->toPlainText();
	auto tableData = std::make_shared<std::map<QString, std::tuple<QString, QString, QString>>>();
	tableData->insert({ m_dbName + "." + addName,std::make_tuple("",addscript,"") });
	if (addscript.toStdString().find("GetValue") != std::string::npos || addscript.toStdString().find("CheckValue") != std::string::npos)
	{
		if (!m_iniFlg)
		{
			ui.lineEdit_test->setText(QString("Connect error"));
			return;
		}
		m_cal->PackTask(tableData);
	}
	float ret = m_cal->CalcTest(addscript.toStdString());
	if (ret < 0)
	{
		ui.lineEdit_test->setText(QString("script error"));
		return;
	}
	QString result = QString::number(ret);
	ui.lineEdit_test->setText(result);
}

void AddTagClass::ChangeScript(const QModelIndex & index)
{
	auto nowIndex = index;
	auto chooseName = nowIndex.data().toString();
	if (nowIndex.parent().isValid())
	{
		auto parentName = nowIndex.parent().data().toString();
		ui.textEdit->setText(m_script[parentName][chooseName]);
	}
}

int AddTagClass::ReadScript()
{
	tinyxml2::XMLDocument doc;
	auto res = doc.LoadFile("./script.xml");
	if (XML_SUCCESS != res)
	{
		LOGINFO("script file is not exist ,res = {}" , res);
		return -1;
	}
	XMLElement *Config = doc.RootElement();
	XMLElement *confChild = Config->FirstChildElement();
	while (confChild)
	{
		auto keyStr = confChild->Name();
		auto itemParent = new QTreeWidgetItem(ui.treeWidget, QStringList(QString(keyStr)));
		itemParent->setIcon(0, QIcon("./res/a.png"));
		XMLElement *child = confChild->FirstChildElement();
		while (child)
		{
			auto childStr = child->Name();
			QTreeWidgetItem *item = new QTreeWidgetItem(itemParent, QStringList(QString(childStr))); //子节点1
			itemParent->addChild(item); //添加子节点
			item->setIcon(0, QIcon("./res/b.png"));
			m_script[keyStr].insert({ QString(childStr),QString(child->GetText()) });
			child = child->NextSiblingElement();
		}
		confChild = confChild->NextSiblingElement();
	}
	return 0;
}

void AddTagClass::on_pushButton_ok_clicked()
{
	emit OkSignal(ui.lineEdit_name->text(),ui.lineEdit_describe->text(),ui.textEdit->toPlainText(),ui.lineEdit_interval->text());
}
