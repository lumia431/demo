/********************************************************************************
** Form generated from reading UI file 'AddDBClass.ui'
**
** Created by: Qt User Interface Compiler version 5.14.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ADDDBCLASS_H
#define UI_ADDDBCLASS_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_AddDBClass
{
public:
    QLabel *label;
    QLineEdit *lineEdit;
    QPushButton *pushButton_ok;
    QPushButton *pushButton_cancel;

    void setupUi(QWidget *AddDBClass)
    {
        if (AddDBClass->objectName().isEmpty())
            AddDBClass->setObjectName(QString::fromUtf8("AddDBClass"));
        AddDBClass->resize(400, 183);
        QIcon icon;
        icon.addFile(QString::fromUtf8("myapp.ico"), QSize(), QIcon::Normal, QIcon::Off);
        AddDBClass->setWindowIcon(icon);
        label = new QLabel(AddDBClass);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(20, 50, 91, 16));
        lineEdit = new QLineEdit(AddDBClass);
        lineEdit->setObjectName(QString::fromUtf8("lineEdit"));
        lineEdit->setGeometry(QRect(130, 50, 251, 21));
        pushButton_ok = new QPushButton(AddDBClass);
        pushButton_ok->setObjectName(QString::fromUtf8("pushButton_ok"));
        pushButton_ok->setGeometry(QRect(20, 130, 93, 28));
        pushButton_cancel = new QPushButton(AddDBClass);
        pushButton_cancel->setObjectName(QString::fromUtf8("pushButton_cancel"));
        pushButton_cancel->setGeometry(QRect(280, 130, 93, 28));

        retranslateUi(AddDBClass);

        QMetaObject::connectSlotsByName(AddDBClass);
    } // setupUi

    void retranslateUi(QWidget *AddDBClass)
    {
        AddDBClass->setWindowTitle(QCoreApplication::translate("AddDBClass", "\346\226\260\345\242\236\346\225\260\346\215\256\345\272\223", nullptr));
        label->setText(QCoreApplication::translate("AddDBClass", "\346\226\260\345\242\236\346\225\260\346\215\256\345\272\223\345\220\215", nullptr));
        pushButton_ok->setText(QCoreApplication::translate("AddDBClass", "\347\241\256\350\256\244", nullptr));
        pushButton_cancel->setText(QCoreApplication::translate("AddDBClass", "\345\217\226\346\266\210", nullptr));
    } // retranslateUi

};

namespace Ui {
    class AddDBClass: public Ui_AddDBClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ADDDBCLASS_H
