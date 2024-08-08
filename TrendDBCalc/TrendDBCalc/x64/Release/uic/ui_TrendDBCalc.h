/********************************************************************************
** Form generated from reading UI file 'TrendDBCalc.ui'
**
** Created by: Qt User Interface Compiler version 5.14.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TRENDDBCALC_H
#define UI_TRENDDBCALC_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QTreeWidget>
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
    QAction *actionclear;
    QAction *actionimport;
    QAction *actionexport;
    QAction *actionsave;
    QAction *actionexit;
    QWidget *centralWidget;
    QTableWidget *tableWidget;
    QTreeWidget *treeWidget;
    QPushButton *pushButton;
    QLineEdit *lineEdit;
    QTabWidget *tabWidget;
    QWidget *tab;
    QWidget *tab_2;
    QMenuBar *menuBar;
    QMenu *menu;
    QMenu *menu_2;
    QMenu *menu_3;
    QMenu *menu_4;
    QMenu *menu_5;

    void setupUi(QMainWindow *TrendDBCalcClass)
    {
        if (TrendDBCalcClass->objectName().isEmpty())
            TrendDBCalcClass->setObjectName(QString::fromUtf8("TrendDBCalcClass"));
        TrendDBCalcClass->resize(1444, 873);
        TrendDBCalcClass->setMaximumSize(QSize(1444, 873));
        QIcon icon;
        icon.addFile(QString::fromUtf8("myapp.ico"), QSize(), QIcon::Normal, QIcon::Off);
        TrendDBCalcClass->setWindowIcon(icon);
        actionstart = new QAction(TrendDBCalcClass);
        actionstart->setObjectName(QString::fromUtf8("actionstart"));
        actionend = new QAction(TrendDBCalcClass);
        actionend->setObjectName(QString::fromUtf8("actionend"));
        actionconf = new QAction(TrendDBCalcClass);
        actionconf->setObjectName(QString::fromUtf8("actionconf"));
        actionadd = new QAction(TrendDBCalcClass);
        actionadd->setObjectName(QString::fromUtf8("actionadd"));
        actionedit = new QAction(TrendDBCalcClass);
        actionedit->setObjectName(QString::fromUtf8("actionedit"));
        actiondelete = new QAction(TrendDBCalcClass);
        actiondelete->setObjectName(QString::fromUtf8("actiondelete"));
        actionclear = new QAction(TrendDBCalcClass);
        actionclear->setObjectName(QString::fromUtf8("actionclear"));
        actionimport = new QAction(TrendDBCalcClass);
        actionimport->setObjectName(QString::fromUtf8("actionimport"));
        actionexport = new QAction(TrendDBCalcClass);
        actionexport->setObjectName(QString::fromUtf8("actionexport"));
        actionsave = new QAction(TrendDBCalcClass);
        actionsave->setObjectName(QString::fromUtf8("actionsave"));
        actionexit = new QAction(TrendDBCalcClass);
        actionexit->setObjectName(QString::fromUtf8("actionexit"));
        centralWidget = new QWidget(TrendDBCalcClass);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        tableWidget = new QTableWidget(centralWidget);
        if (tableWidget->columnCount() < 4)
            tableWidget->setColumnCount(4);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(3, __qtablewidgetitem3);
        tableWidget->setObjectName(QString::fromUtf8("tableWidget"));
        tableWidget->setGeometry(QRect(199, 30, 1250, 811));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(tableWidget->sizePolicy().hasHeightForWidth());
        tableWidget->setSizePolicy(sizePolicy);
        tableWidget->setContextMenuPolicy(Qt::CustomContextMenu);
        tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
        tableWidget->setRowCount(0);
        tableWidget->setColumnCount(4);
        tableWidget->horizontalHeader()->setMinimumSectionSize(31);
        tableWidget->horizontalHeader()->setDefaultSectionSize(300);
        tableWidget->horizontalHeader()->setHighlightSections(true);
        tableWidget->horizontalHeader()->setProperty("showSortIndicator", QVariant(false));
        treeWidget = new QTreeWidget(centralWidget);
        QTreeWidgetItem *__qtreewidgetitem = new QTreeWidgetItem();
        __qtreewidgetitem->setText(0, QString::fromUtf8("1"));
        treeWidget->setHeaderItem(__qtreewidgetitem);
        treeWidget->setObjectName(QString::fromUtf8("treeWidget"));
        treeWidget->setGeometry(QRect(11, 1, 191, 831));
        QSizePolicy sizePolicy1(QSizePolicy::Minimum, QSizePolicy::Expanding);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(treeWidget->sizePolicy().hasHeightForWidth());
        treeWidget->setSizePolicy(sizePolicy1);
        treeWidget->setContextMenuPolicy(Qt::CustomContextMenu);
        treeWidget->header()->setVisible(false);
        pushButton = new QPushButton(centralWidget);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setGeometry(QRect(1320, 0, 121, 31));
        lineEdit = new QLineEdit(centralWidget);
        lineEdit->setObjectName(QString::fromUtf8("lineEdit"));
        lineEdit->setGeometry(QRect(1080, 0, 241, 31));
        tabWidget = new QTabWidget(centralWidget);
        tabWidget->setObjectName(QString::fromUtf8("tabWidget"));
        tabWidget->setGeometry(QRect(200, 0, 881, 31));
        tabWidget->setIconSize(QSize(40, 20));
        tabWidget->setTabsClosable(true);
        tabWidget->setMovable(true);
        tab = new QWidget();
        tab->setObjectName(QString::fromUtf8("tab"));
        tabWidget->addTab(tab, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName(QString::fromUtf8("tab_2"));
        tabWidget->addTab(tab_2, QString());
        TrendDBCalcClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(TrendDBCalcClass);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1444, 26));
        menu = new QMenu(menuBar);
        menu->setObjectName(QString::fromUtf8("menu"));
        menu_2 = new QMenu(menuBar);
        menu_2->setObjectName(QString::fromUtf8("menu_2"));
        menu_3 = new QMenu(menuBar);
        menu_3->setObjectName(QString::fromUtf8("menu_3"));
        menu_4 = new QMenu(menuBar);
        menu_4->setObjectName(QString::fromUtf8("menu_4"));
        menu_5 = new QMenu(menuBar);
        menu_5->setObjectName(QString::fromUtf8("menu_5"));
        TrendDBCalcClass->setMenuBar(menuBar);

        menuBar->addAction(menu->menuAction());
        menuBar->addAction(menu_2->menuAction());
        menuBar->addAction(menu_3->menuAction());
        menuBar->addAction(menu_4->menuAction());
        menuBar->addAction(menu_5->menuAction());
        menu->addAction(actionclear);
        menu->addAction(actionsave);
        menu->addAction(actionexit);
        menu_2->addAction(actionstart);
        menu_2->addAction(actionend);
        menu_3->addAction(actionconf);
        menu_4->addAction(actionadd);
        menu_4->addAction(actionedit);
        menu_4->addAction(actiondelete);
        menu_5->addAction(actionimport);
        menu_5->addAction(actionexport);

        retranslateUi(TrendDBCalcClass);

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(TrendDBCalcClass);
    } // setupUi

    void retranslateUi(QMainWindow *TrendDBCalcClass)
    {
        TrendDBCalcClass->setWindowTitle(QCoreApplication::translate("TrendDBCalcClass", "\345\256\236\346\227\266\345\272\223\350\256\241\347\256\227\345\267\245\345\205\267", nullptr));
        actionstart->setText(QCoreApplication::translate("TrendDBCalcClass", "\345\274\200\345\247\213", nullptr));
        actionend->setText(QCoreApplication::translate("TrendDBCalcClass", "\347\273\223\346\235\237", nullptr));
        actionconf->setText(QCoreApplication::translate("TrendDBCalcClass", "\351\205\215\347\275\256\345\256\236\346\227\266\345\272\223", nullptr));
        actionadd->setText(QCoreApplication::translate("TrendDBCalcClass", "\345\242\236\345\212\240\346\265\213\347\202\271", nullptr));
        actionedit->setText(QCoreApplication::translate("TrendDBCalcClass", "\344\277\256\346\224\271\346\265\213\347\202\271", nullptr));
        actiondelete->setText(QCoreApplication::translate("TrendDBCalcClass", "\345\210\240\351\231\244\346\265\213\347\202\271", nullptr));
        actionclear->setText(QCoreApplication::translate("TrendDBCalcClass", "\346\270\205\347\251\272\347\202\271\350\241\250\344\277\241\346\201\257", nullptr));
        actionimport->setText(QCoreApplication::translate("TrendDBCalcClass", "\345\257\274\345\205\245\347\202\271\350\241\250", nullptr));
        actionexport->setText(QCoreApplication::translate("TrendDBCalcClass", "\345\257\274\345\207\272\347\202\271\350\241\250", nullptr));
        actionsave->setText(QCoreApplication::translate("TrendDBCalcClass", "\344\277\235\345\255\230\347\202\271\350\241\250\344\277\241\346\201\257", nullptr));
        actionexit->setText(QCoreApplication::translate("TrendDBCalcClass", "\351\200\200\345\207\272\347\250\213\345\272\217", nullptr));
        QTableWidgetItem *___qtablewidgetitem = tableWidget->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("TrendDBCalcClass", "\346\265\213\347\202\271\345\220\215", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidget->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("TrendDBCalcClass", "\346\265\213\347\202\271\346\217\217\350\277\260", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = tableWidget->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QCoreApplication::translate("TrendDBCalcClass", "\350\256\241\347\256\227\350\204\232\346\234\254", nullptr));
        QTableWidgetItem *___qtablewidgetitem3 = tableWidget->horizontalHeaderItem(3);
        ___qtablewidgetitem3->setText(QCoreApplication::translate("TrendDBCalcClass", "\350\256\241\347\256\227\351\227\264\351\232\224", nullptr));
        pushButton->setText(QCoreApplication::translate("TrendDBCalcClass", "\346\237\245\350\257\242\346\265\213\347\202\271", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab), QCoreApplication::translate("TrendDBCalcClass", "Tab 1", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_2), QCoreApplication::translate("TrendDBCalcClass", "Tab 2", nullptr));
        menu->setTitle(QCoreApplication::translate("TrendDBCalcClass", "\346\226\207\344\273\266", nullptr));
        menu_2->setTitle(QCoreApplication::translate("TrendDBCalcClass", "\350\277\220\350\241\214", nullptr));
        menu_3->setTitle(QCoreApplication::translate("TrendDBCalcClass", "\351\205\215\347\275\256", nullptr));
        menu_4->setTitle(QCoreApplication::translate("TrendDBCalcClass", "\347\274\226\350\276\221", nullptr));
        menu_5->setTitle(QCoreApplication::translate("TrendDBCalcClass", "\347\202\271\350\241\250", nullptr));
    } // retranslateUi

};

namespace Ui {
    class TrendDBCalcClass: public Ui_TrendDBCalcClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TRENDDBCALC_H
