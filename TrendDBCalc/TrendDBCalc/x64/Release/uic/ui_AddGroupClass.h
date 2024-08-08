/********************************************************************************
** Form generated from reading UI file 'AddGroupClass.ui'
**
** Created by: Qt User Interface Compiler version 5.14.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ADDGROUPCLASS_H
#define UI_ADDGROUPCLASS_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_AddGroupClass
{
public:
    QLabel *label;
    QLineEdit *lineEdit;
    QPushButton *pushButton_ok;
    QPushButton *pushButton_cancel;

    void setupUi(QWidget *AddGroupClass)
    {
        if (AddGroupClass->objectName().isEmpty())
            AddGroupClass->setObjectName(QString::fromUtf8("AddGroupClass"));
        AddGroupClass->resize(400, 126);
        QIcon icon;
        icon.addFile(QString::fromUtf8("myapp.ico"), QSize(), QIcon::Normal, QIcon::Off);
        AddGroupClass->setWindowIcon(icon);
        label = new QLabel(AddGroupClass);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(11, 30, 45, 16));
        lineEdit = new QLineEdit(AddGroupClass);
        lineEdit->setObjectName(QString::fromUtf8("lineEdit"));
        lineEdit->setGeometry(QRect(70, 30, 311, 21));
        pushButton_ok = new QPushButton(AddGroupClass);
        pushButton_ok->setObjectName(QString::fromUtf8("pushButton_ok"));
        pushButton_ok->setGeometry(QRect(11, 71, 93, 28));
        pushButton_cancel = new QPushButton(AddGroupClass);
        pushButton_cancel->setObjectName(QString::fromUtf8("pushButton_cancel"));
        pushButton_cancel->setGeometry(QRect(296, 71, 93, 28));

        retranslateUi(AddGroupClass);

        QMetaObject::connectSlotsByName(AddGroupClass);
    } // setupUi

    void retranslateUi(QWidget *AddGroupClass)
    {
        AddGroupClass->setWindowTitle(QCoreApplication::translate("AddGroupClass", "\345\242\236\345\212\240\347\202\271\347\273\204", nullptr));
        label->setText(QCoreApplication::translate("AddGroupClass", "\347\202\271\347\273\204\345\220\215", nullptr));
        pushButton_ok->setText(QCoreApplication::translate("AddGroupClass", "\347\241\256\345\256\232", nullptr));
        pushButton_cancel->setText(QCoreApplication::translate("AddGroupClass", "\345\217\226\346\266\210", nullptr));
    } // retranslateUi

};

namespace Ui {
    class AddGroupClass: public Ui_AddGroupClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ADDGROUPCLASS_H
