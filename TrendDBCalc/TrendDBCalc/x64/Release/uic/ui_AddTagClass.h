/********************************************************************************
** Form generated from reading UI file 'AddTagClass.ui'
**
** Created by: Qt User Interface Compiler version 5.14.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ADDTAGCLASS_H
#define UI_ADDTAGCLASS_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QTreeWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_AddTagClass
{
public:
    QWidget *widget;
    QLabel *label;
    QLabel *label_3;
    QLineEdit *lineEdit_index;
    QTextEdit *textEdit;
    QLabel *label_2;
    QLineEdit *lineEdit_name;
    QLabel *label_4;
    QLineEdit *lineEdit_interval;
    QPushButton *pushButton_ok;
    QPushButton *pushButton_cancel;
    QLabel *label_5;
    QLineEdit *lineEdit_test;
    QPushButton *pushButton_test;
    QLabel *label_6;
    QLineEdit *lineEdit_describe;
    QTreeWidget *treeWidget;

    void setupUi(QWidget *AddTagClass)
    {
        if (AddTagClass->objectName().isEmpty())
            AddTagClass->setObjectName(QString::fromUtf8("AddTagClass"));
        AddTagClass->resize(1050, 728);
        QIcon icon;
        icon.addFile(QString::fromUtf8("myapp.ico"), QSize(), QIcon::Normal, QIcon::Off);
        AddTagClass->setWindowIcon(icon);
        widget = new QWidget(AddTagClass);
        widget->setObjectName(QString::fromUtf8("widget"));
        widget->setGeometry(QRect(40, 20, 953, 662));
        label = new QLabel(widget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(11, 11, 60, 16));
        label_3 = new QLabel(widget);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(220, 10, 60, 16));
        lineEdit_index = new QLineEdit(widget);
        lineEdit_index->setObjectName(QString::fromUtf8("lineEdit_index"));
        lineEdit_index->setGeometry(QRect(11, 33, 171, 21));
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(lineEdit_index->sizePolicy().hasHeightForWidth());
        lineEdit_index->setSizePolicy(sizePolicy);
        lineEdit_index->setMaxLength(100);
        textEdit = new QTextEdit(widget);
        textEdit->setObjectName(QString::fromUtf8("textEdit"));
        textEdit->setGeometry(QRect(219, 33, 611, 561));
        label_2 = new QLabel(widget);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(11, 61, 60, 16));
        lineEdit_name = new QLineEdit(widget);
        lineEdit_name->setObjectName(QString::fromUtf8("lineEdit_name"));
        lineEdit_name->setGeometry(QRect(11, 83, 171, 21));
        sizePolicy.setHeightForWidth(lineEdit_name->sizePolicy().hasHeightForWidth());
        lineEdit_name->setSizePolicy(sizePolicy);
        lineEdit_name->setFrame(true);
        lineEdit_name->setDragEnabled(false);
        label_4 = new QLabel(widget);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setGeometry(QRect(10, 160, 60, 16));
        lineEdit_interval = new QLineEdit(widget);
        lineEdit_interval->setObjectName(QString::fromUtf8("lineEdit_interval"));
        lineEdit_interval->setGeometry(QRect(10, 190, 171, 21));
        sizePolicy.setHeightForWidth(lineEdit_interval->sizePolicy().hasHeightForWidth());
        lineEdit_interval->setSizePolicy(sizePolicy);
        pushButton_ok = new QPushButton(widget);
        pushButton_ok->setObjectName(QString::fromUtf8("pushButton_ok"));
        pushButton_ok->setGeometry(QRect(10, 620, 93, 28));
        pushButton_cancel = new QPushButton(widget);
        pushButton_cancel->setObjectName(QString::fromUtf8("pushButton_cancel"));
        pushButton_cancel->setGeometry(QRect(740, 620, 93, 28));
        label_5 = new QLabel(widget);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setGeometry(QRect(10, 220, 60, 16));
        lineEdit_test = new QLineEdit(widget);
        lineEdit_test->setObjectName(QString::fromUtf8("lineEdit_test"));
        lineEdit_test->setGeometry(QRect(10, 240, 171, 21));
        sizePolicy.setHeightForWidth(lineEdit_test->sizePolicy().hasHeightForWidth());
        lineEdit_test->setSizePolicy(sizePolicy);
        pushButton_test = new QPushButton(widget);
        pushButton_test->setObjectName(QString::fromUtf8("pushButton_test"));
        pushButton_test->setGeometry(QRect(570, 620, 141, 28));
        label_6 = new QLabel(widget);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        label_6->setGeometry(QRect(10, 110, 60, 16));
        lineEdit_describe = new QLineEdit(widget);
        lineEdit_describe->setObjectName(QString::fromUtf8("lineEdit_describe"));
        lineEdit_describe->setGeometry(QRect(10, 130, 171, 21));
        sizePolicy.setHeightForWidth(lineEdit_describe->sizePolicy().hasHeightForWidth());
        lineEdit_describe->setSizePolicy(sizePolicy);
        treeWidget = new QTreeWidget(widget);
        QTreeWidgetItem *__qtreewidgetitem = new QTreeWidgetItem();
        __qtreewidgetitem->setText(0, QString::fromUtf8("\350\204\232\346\234\254\346\241\210\344\276\213"));
        treeWidget->setHeaderItem(__qtreewidgetitem);
        treeWidget->setObjectName(QString::fromUtf8("treeWidget"));
        treeWidget->setGeometry(QRect(10, 290, 181, 301));
        treeWidget->setColumnCount(1);

        retranslateUi(AddTagClass);

        QMetaObject::connectSlotsByName(AddTagClass);
    } // setupUi

    void retranslateUi(QWidget *AddTagClass)
    {
        AddTagClass->setWindowTitle(QCoreApplication::translate("AddTagClass", "\345\242\236\345\212\240\346\265\213\347\202\271", nullptr));
        label->setText(QCoreApplication::translate("AddTagClass", "\346\265\213\347\202\271\345\272\217\345\217\267", nullptr));
        label_3->setText(QCoreApplication::translate("AddTagClass", "\350\256\241\347\256\227\350\204\232\346\234\254", nullptr));
        label_2->setText(QCoreApplication::translate("AddTagClass", "\346\265\213\347\202\271\345\220\215\347\247\260", nullptr));
        label_4->setText(QCoreApplication::translate("AddTagClass", "\350\256\241\347\256\227\351\227\264\351\232\224", nullptr));
        pushButton_ok->setText(QCoreApplication::translate("AddTagClass", "\347\241\256\345\256\232", nullptr));
        pushButton_cancel->setText(QCoreApplication::translate("AddTagClass", "\345\217\226\346\266\210", nullptr));
        label_5->setText(QCoreApplication::translate("AddTagClass", "\346\265\213\350\257\225\347\273\223\346\236\234", nullptr));
        pushButton_test->setText(QCoreApplication::translate("AddTagClass", "\346\265\213\350\257\225\350\204\232\346\234\254", nullptr));
        label_6->setText(QCoreApplication::translate("AddTagClass", "\346\265\213\347\202\271\346\217\217\350\277\260", nullptr));
    } // retranslateUi

};

namespace Ui {
    class AddTagClass: public Ui_AddTagClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ADDTAGCLASS_H
