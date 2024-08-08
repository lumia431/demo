/********************************************************************************
** Form generated from reading UI file 'TrendDBConfClass.ui'
**
** Created by: Qt User Interface Compiler version 5.14.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TRENDDBCONFCLASS_H
#define UI_TRENDDBCONFCLASS_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_TrendDBConfClass
{
public:
    QGridLayout *gridLayout_2;
    QWidget *widget;
    QPushButton *pushButton_cancel;
    QLabel *label_5;
    QPushButton *pushButton_ok;
    QLabel *label_2;
    QLabel *label_4;
    QLineEdit *lineEdit_usr;
    QLineEdit *lineEdit_addr;
    QLineEdit *lineEdit_passw;
    QLineEdit *lineEdit_port;
    QLabel *label;
    QPushButton *pushButton_test;

    void setupUi(QWidget *TrendDBConfClass)
    {
        if (TrendDBConfClass->objectName().isEmpty())
            TrendDBConfClass->setObjectName(QString::fromUtf8("TrendDBConfClass"));
        TrendDBConfClass->resize(675, 550);
        QIcon icon;
        icon.addFile(QString::fromUtf8("myapp.ico"), QSize(), QIcon::Normal, QIcon::Off);
        TrendDBConfClass->setWindowIcon(icon);
        gridLayout_2 = new QGridLayout(TrendDBConfClass);
        gridLayout_2->setSpacing(6);
        gridLayout_2->setContentsMargins(11, 11, 11, 11);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        widget = new QWidget(TrendDBConfClass);
        widget->setObjectName(QString::fromUtf8("widget"));
        pushButton_cancel = new QPushButton(widget);
        pushButton_cancel->setObjectName(QString::fromUtf8("pushButton_cancel"));
        pushButton_cancel->setGeometry(QRect(549, 428, 93, 28));
        label_5 = new QLabel(widget);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setGeometry(QRect(111, 339, 30, 16));
        pushButton_ok = new QPushButton(widget);
        pushButton_ok->setObjectName(QString::fromUtf8("pushButton_ok"));
        pushButton_ok->setGeometry(QRect(11, 428, 93, 28));
        label_2 = new QLabel(widget);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(111, 161, 75, 16));
        label_4 = new QLabel(widget);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setGeometry(QRect(111, 250, 45, 16));
        lineEdit_usr = new QLineEdit(widget);
        lineEdit_usr->setObjectName(QString::fromUtf8("lineEdit_usr"));
        lineEdit_usr->setGeometry(QRect(193, 250, 281, 21));
        lineEdit_addr = new QLineEdit(widget);
        lineEdit_addr->setObjectName(QString::fromUtf8("lineEdit_addr"));
        lineEdit_addr->setGeometry(QRect(193, 72, 281, 21));
        lineEdit_addr->setMaxLength(20);
        lineEdit_passw = new QLineEdit(widget);
        lineEdit_passw->setObjectName(QString::fromUtf8("lineEdit_passw"));
        lineEdit_passw->setGeometry(QRect(193, 339, 281, 21));
        lineEdit_port = new QLineEdit(widget);
        lineEdit_port->setObjectName(QString::fromUtf8("lineEdit_port"));
        lineEdit_port->setGeometry(QRect(193, 161, 281, 21));
        lineEdit_port->setFrame(true);
        lineEdit_port->setDragEnabled(false);
        label = new QLabel(widget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(111, 72, 75, 16));
        pushButton_test = new QPushButton(widget);
        pushButton_test->setObjectName(QString::fromUtf8("pushButton_test"));
        pushButton_test->setGeometry(QRect(270, 428, 93, 28));
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(pushButton_test->sizePolicy().hasHeightForWidth());
        pushButton_test->setSizePolicy(sizePolicy);

        gridLayout_2->addWidget(widget, 0, 0, 1, 1);


        retranslateUi(TrendDBConfClass);

        QMetaObject::connectSlotsByName(TrendDBConfClass);
    } // setupUi

    void retranslateUi(QWidget *TrendDBConfClass)
    {
        TrendDBConfClass->setWindowTitle(QCoreApplication::translate("TrendDBConfClass", "\345\256\236\346\227\266\345\272\223\351\205\215\347\275\256", nullptr));
        pushButton_cancel->setText(QCoreApplication::translate("TrendDBConfClass", "\345\217\226\346\266\210", nullptr));
        label_5->setText(QCoreApplication::translate("TrendDBConfClass", "\345\257\206\347\240\201", nullptr));
        pushButton_ok->setText(QCoreApplication::translate("TrendDBConfClass", "\347\241\256\345\256\232", nullptr));
        label_2->setText(QCoreApplication::translate("TrendDBConfClass", "\345\256\236\346\227\266\345\272\223\347\253\257\345\217\243", nullptr));
        label_4->setText(QCoreApplication::translate("TrendDBConfClass", "\347\224\250\346\210\267\345\220\215", nullptr));
        label->setText(QCoreApplication::translate("TrendDBConfClass", "\345\256\236\346\227\266\345\272\223\345\234\260\345\235\200", nullptr));
        pushButton_test->setText(QCoreApplication::translate("TrendDBConfClass", "\350\277\236\346\216\245\346\265\213\350\257\225", nullptr));
    } // retranslateUi

};

namespace Ui {
    class TrendDBConfClass: public Ui_TrendDBConfClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TRENDDBCONFCLASS_H
