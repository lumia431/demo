/********************************************************************************
** Form generated from reading UI file 'AddDBClass.ui'
**
** Created by: Qt User Interface Compiler version 5.9.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ADDDBCLASS_H
#define UI_ADDDBCLASS_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
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
            AddDBClass->setObjectName(QStringLiteral("AddDBClass"));
        AddDBClass->resize(400, 183);
        QIcon icon;
        icon.addFile(QStringLiteral("myapp.ico"), QSize(), QIcon::Normal, QIcon::Off);
        AddDBClass->setWindowIcon(icon);
        label = new QLabel(AddDBClass);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(20, 50, 91, 16));
        lineEdit = new QLineEdit(AddDBClass);
        lineEdit->setObjectName(QStringLiteral("lineEdit"));
        lineEdit->setGeometry(QRect(130, 50, 251, 21));
        pushButton_ok = new QPushButton(AddDBClass);
        pushButton_ok->setObjectName(QStringLiteral("pushButton_ok"));
        pushButton_ok->setGeometry(QRect(20, 130, 93, 28));
        pushButton_cancel = new QPushButton(AddDBClass);
        pushButton_cancel->setObjectName(QStringLiteral("pushButton_cancel"));
        pushButton_cancel->setGeometry(QRect(280, 130, 93, 28));

        retranslateUi(AddDBClass);

        QMetaObject::connectSlotsByName(AddDBClass);
    } // setupUi

    void retranslateUi(QWidget *AddDBClass)
    {
        AddDBClass->setWindowTitle(QApplication::translate("AddDBClass", "\346\226\260\345\242\236\346\225\260\346\215\256\345\272\223", Q_NULLPTR));
        label->setText(QApplication::translate("AddDBClass", "\346\226\260\345\242\236\346\225\260\346\215\256\345\272\223\345\220\215", Q_NULLPTR));
        pushButton_ok->setText(QApplication::translate("AddDBClass", "\347\241\256\350\256\244", Q_NULLPTR));
        pushButton_cancel->setText(QApplication::translate("AddDBClass", "\345\217\226\346\266\210", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class AddDBClass: public Ui_AddDBClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ADDDBCLASS_H
