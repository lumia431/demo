/********************************************************************************
** Form generated from reading UI file 'TrendDBCalc.ui'
**
** Created by: Qt User Interface Compiler version 5.9.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TRENDDBCALC_H
#define UI_TRENDDBCALC_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_TrendDBCalcClass
{
public:
	QAction *actionstart;
	QAction *actionend;
	QAction *actionconf;
	QAction *actionadd;
	QAction *actionedit;
	QAction *actiondelete;
	QAction *actionexit;
	QWidget *centralWidget;
	QGridLayout *gridLayout_2;
	QTableWidget *tableWidget;
	QMenuBar *menuBar;
	QMenu *menu;
	QMenu *menu_2;
	QMenu *menu_3;
	QMenu *menu_4;
	QMenu *menu_5;

	void setupUi(QMainWindow *TrendDBCalcClass)
	{
		if (TrendDBCalcClass->objectName().isEmpty())
			TrendDBCalcClass->setObjectName(QStringLiteral("TrendDBCalcClass"));
		TrendDBCalcClass->resize(1098, 873);
		QIcon icon;
		icon.addFile(QStringLiteral("myapp.ico"), QSize(), QIcon::Normal, QIcon::Off);
		TrendDBCalcClass->setWindowIcon(icon);
		actionstart = new QAction(TrendDBCalcClass);
		actionstart->setObjectName(QStringLiteral("actionstart"));
		actionend = new QAction(TrendDBCalcClass);
		actionend->setObjectName(QStringLiteral("actionend"));
		actionconf = new QAction(TrendDBCalcClass);
		actionconf->setObjectName(QStringLiteral("actionconf"));
		actionadd = new QAction(TrendDBCalcClass);
		actionadd->setObjectName(QStringLiteral("actionadd"));
		actionedit = new QAction(TrendDBCalcClass);
		actionedit->setObjectName(QStringLiteral("actionedit"));
		actiondelete = new QAction(TrendDBCalcClass);
		actiondelete->setObjectName(QStringLiteral("actiondelete"));
		actionexit = new QAction(TrendDBCalcClass);
		actionexit->setObjectName(QStringLiteral("actionexit"));
		centralWidget = new QWidget(TrendDBCalcClass);
		centralWidget->setObjectName(QStringLiteral("centralWidget"));
		gridLayout_2 = new QGridLayout(centralWidget);
		gridLayout_2->setSpacing(6);
		gridLayout_2->setContentsMargins(11, 11, 11, 11);
		gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
		tableWidget = new QTableWidget(centralWidget);
		if (tableWidget->columnCount() < 3)
			tableWidget->setColumnCount(3);
		QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
		tableWidget->setHorizontalHeaderItem(0, __qtablewidgetitem);
		QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
		tableWidget->setHorizontalHeaderItem(1, __qtablewidgetitem1);
		QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
		tableWidget->setHorizontalHeaderItem(2, __qtablewidgetitem2);
		if (tableWidget->rowCount() < 1)
			tableWidget->setRowCount(0);
		tableWidget->setObjectName(QStringLiteral("tableWidget"));
		tableWidget->setMaximumSize(QSize(1900, 1200));
		tableWidget->setContextMenuPolicy(Qt::CustomContextMenu);
		tableWidget->setRowCount(0);
		tableWidget->setColumnCount(3);
		tableWidget->horizontalHeader()->setDefaultSectionSize(325);
		tableWidget->horizontalHeader()->setHighlightSections(true);
		tableWidget->horizontalHeader()->setMinimumSectionSize(31);
		tableWidget->horizontalHeader()->setProperty("showSortIndicator", QVariant(false));
		tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
		gridLayout_2->addWidget(tableWidget, 0, 0, 1, 1);

		TrendDBCalcClass->setCentralWidget(centralWidget);
		menuBar = new QMenuBar(TrendDBCalcClass);
		menuBar->setObjectName(QStringLiteral("menuBar"));
		menuBar->setGeometry(QRect(0, 0, 1098, 26));
		menu = new QMenu(menuBar);
		menu->setObjectName(QStringLiteral("menu"));
		menu_2 = new QMenu(menuBar);
		menu_2->setObjectName(QStringLiteral("menu_2"));
		menu_3 = new QMenu(menuBar);
		menu_3->setObjectName(QStringLiteral("menu_3"));
		menu_4 = new QMenu(menuBar);
		menu_4->setObjectName(QStringLiteral("menu_4"));
		menu_5 = new QMenu(menuBar);
		menu_5->setObjectName(QStringLiteral("menu_5"));
		TrendDBCalcClass->setMenuBar(menuBar);

		menuBar->addAction(menu->menuAction());
		menuBar->addAction(menu_2->menuAction());
		menuBar->addAction(menu_3->menuAction());
		menuBar->addAction(menu_4->menuAction());
		menuBar->addAction(menu_5->menuAction());
		menu->addAction(actionexit);
		menu_2->addAction(actionstart);
		menu_2->addAction(actionend);
		menu_3->addAction(actionconf);
		menu_4->addAction(actionadd);
		menu_4->addAction(actionedit);
		menu_4->addAction(actiondelete);

		retranslateUi(TrendDBCalcClass);

		QMetaObject::connectSlotsByName(TrendDBCalcClass);
	} // setupUi

	void retranslateUi(QMainWindow *TrendDBCalcClass)
	{
		TrendDBCalcClass->setWindowTitle(QApplication::translate("TrendDBCalcClass", "\345\256\236\346\227\266\345\272\223\350\256\241\347\256\227\345\267\245\345\205\267", Q_NULLPTR));
		actionstart->setText(QApplication::translate("TrendDBCalcClass", "\345\274\200\345\247\213", Q_NULLPTR));
		actionend->setText(QApplication::translate("TrendDBCalcClass", "\347\273\223\346\235\237", Q_NULLPTR));
		actionconf->setText(QApplication::translate("TrendDBCalcClass", "\351\205\215\347\275\256\345\256\236\346\227\266\345\272\223", Q_NULLPTR));
		actionadd->setText(QApplication::translate("TrendDBCalcClass", "\345\242\236\345\212\240\346\265\213\347\202\271", Q_NULLPTR));
		actionedit->setText(QApplication::translate("TrendDBCalcClass", "\344\277\256\346\224\271\346\265\213\347\202\271", Q_NULLPTR));
		actiondelete->setText(QApplication::translate("TrendDBCalcClass", "\345\210\240\351\231\244\346\265\213\347\202\271", Q_NULLPTR));
		actionexit->setText(QApplication::translate("TrendDBCalcClass", "\351\200\200\345\207\272", Q_NULLPTR));
		QTableWidgetItem *___qtablewidgetitem = tableWidget->horizontalHeaderItem(0);
		___qtablewidgetitem->setText(QApplication::translate("TrendDBCalcClass", "\346\265\213\347\202\271\345\220\215", Q_NULLPTR));
		QTableWidgetItem *___qtablewidgetitem1 = tableWidget->horizontalHeaderItem(1);
		___qtablewidgetitem1->setText(QApplication::translate("TrendDBCalcClass", "\350\256\241\347\256\227\350\204\232\346\234\254", Q_NULLPTR));
		QTableWidgetItem *___qtablewidgetitem2 = tableWidget->horizontalHeaderItem(2);
		___qtablewidgetitem2->setText(QApplication::translate("TrendDBCalcClass", "\350\256\241\347\256\227\351\227\264\351\232\224", Q_NULLPTR));
		menu->setTitle(QApplication::translate("TrendDBCalcClass", "\346\226\207\344\273\266", Q_NULLPTR));
		menu_2->setTitle(QApplication::translate("TrendDBCalcClass", "\350\277\220\350\241\214", Q_NULLPTR));
		menu_3->setTitle(QApplication::translate("TrendDBCalcClass", "\351\205\215\347\275\256", Q_NULLPTR));
		menu_4->setTitle(QApplication::translate("TrendDBCalcClass", "\347\274\226\350\276\221", Q_NULLPTR));
		menu_5->setTitle(QApplication::translate("TrendDBCalcClass", "\345\257\274\345\207\272\347\202\271\350\241\250", Q_NULLPTR));
	} // retranslateUi

};

namespace Ui {
	class TrendDBCalcClass : public Ui_TrendDBCalcClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TRENDDBCALC_H
