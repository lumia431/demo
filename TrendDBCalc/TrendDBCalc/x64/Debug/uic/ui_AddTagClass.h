/********************************************************************************
** Form generated from reading UI file 'AddTagClass.ui'
**
** Created by: Qt User Interface Compiler version 5.9.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ADDTAGCLASS_H
#define UI_ADDTAGCLASS_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTextEdit>
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

    void setupUi(QWidget *AddTagClass)
    {
        if (AddTagClass->objectName().isEmpty())
            AddTagClass->setObjectName(QStringLiteral("AddTagClass"));
        AddTagClass->resize(1050, 728);
        QIcon icon;
        icon.addFile(QStringLiteral("myapp.ico"), QSize(), QIcon::Normal, QIcon::Off);
        AddTagClass->setWindowIcon(icon);
        widget = new QWidget(AddTagClass);
        widget->setObjectName(QStringLiteral("widget"));
        widget->setGeometry(QRect(40, 20, 953, 662));
        label = new QLabel(widget);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(11, 11, 60, 16));
        label_3 = new QLabel(widget);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(220, 10, 60, 16));
        lineEdit_index = new QLineEdit(widget);
        lineEdit_index->setObjectName(QStringLiteral("lineEdit_index"));
        lineEdit_index->setGeometry(QRect(11, 33, 171, 21));
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(lineEdit_index->sizePolicy().hasHeightForWidth());
        lineEdit_index->setSizePolicy(sizePolicy);
        lineEdit_index->setMaxLength(100);
        textEdit = new QTextEdit(widget);
        textEdit->setObjectName(QStringLiteral("textEdit"));
        textEdit->setGeometry(QRect(219, 33, 611, 561));
        label_2 = new QLabel(widget);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(11, 61, 60, 16));
        lineEdit_name = new QLineEdit(widget);
        lineEdit_name->setObjectName(QStringLiteral("lineEdit_name"));
        lineEdit_name->setGeometry(QRect(11, 83, 171, 21));
        sizePolicy.setHeightForWidth(lineEdit_name->sizePolicy().hasHeightForWidth());
        lineEdit_name->setSizePolicy(sizePolicy);
        lineEdit_name->setFrame(true);
        lineEdit_name->setDragEnabled(false);
        label_4 = new QLabel(widget);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setGeometry(QRect(10, 160, 60, 16));
        lineEdit_interval = new QLineEdit(widget);
        lineEdit_interval->setObjectName(QStringLiteral("lineEdit_interval"));
        lineEdit_interval->setGeometry(QRect(10, 190, 171, 21));
        sizePolicy.setHeightForWidth(lineEdit_interval->sizePolicy().hasHeightForWidth());
        lineEdit_interval->setSizePolicy(sizePolicy);
        pushButton_ok = new QPushButton(widget);
        pushButton_ok->setObjectName(QStringLiteral("pushButton_ok"));
        pushButton_ok->setGeometry(QRect(10, 620, 93, 28));
        pushButton_cancel = new QPushButton(widget);
        pushButton_cancel->setObjectName(QStringLiteral("pushButton_cancel"));
        pushButton_cancel->setGeometry(QRect(740, 620, 93, 28));
        label_5 = new QLabel(widget);
        label_5->setObjectName(QStringLiteral("label_5"));
        label_5->setGeometry(QRect(10, 220, 60, 16));
        lineEdit_test = new QLineEdit(widget);
        lineEdit_test->setObjectName(QStringLiteral("lineEdit_test"));
        lineEdit_test->setGeometry(QRect(10, 240, 171, 21));
        sizePolicy.setHeightForWidth(lineEdit_test->sizePolicy().hasHeightForWidth());
        lineEdit_test->setSizePolicy(sizePolicy);
        pushButton_test = new QPushButton(widget);
        pushButton_test->setObjectName(QStringLiteral("pushButton_test"));
        pushButton_test->setGeometry(QRect(570, 620, 141, 28));
        label_6 = new QLabel(widget);
        label_6->setObjectName(QStringLiteral("label_6"));
        label_6->setGeometry(QRect(10, 110, 60, 16));
        lineEdit_describe = new QLineEdit(widget);
        lineEdit_describe->setObjectName(QStringLiteral("lineEdit_describe"));
        lineEdit_describe->setGeometry(QRect(10, 130, 171, 21));
        sizePolicy.setHeightForWidth(lineEdit_describe->sizePolicy().hasHeightForWidth());
        lineEdit_describe->setSizePolicy(sizePolicy);

        retranslateUi(AddTagClass);

        QMetaObject::connectSlotsByName(AddTagClass);
    } // setupUi

    void retranslateUi(QWidget *AddTagClass)
    {
        AddTagClass->setWindowTitle(QApplication::translate("AddTagClass", "\345\242\236\345\212\240\346\265\213\347\202\271", Q_NULLPTR));
        label->setText(QApplication::translate("AddTagClass", "\346\265\213\347\202\271\345\272\217\345\217\267", Q_NULLPTR));
        label_3->setText(QApplication::translate("AddTagClass", "\350\256\241\347\256\227\350\204\232\346\234\254", Q_NULLPTR));
        label_2->setText(QApplication::translate("AddTagClass", "\346\265\213\347\202\271\345\220\215\347\247\260", Q_NULLPTR));
        label_4->setText(QApplication::translate("AddTagClass", "\350\256\241\347\256\227\351\227\264\351\232\224", Q_NULLPTR));
        pushButton_ok->setText(QApplication::translate("AddTagClass", "\347\241\256\345\256\232", Q_NULLPTR));
        pushButton_cancel->setText(QApplication::translate("AddTagClass", "\345\217\226\346\266\210", Q_NULLPTR));
        label_5->setText(QApplication::translate("AddTagClass", "\346\265\213\350\257\225\347\273\223\346\236\234", Q_NULLPTR));
        pushButton_test->setText(QApplication::translate("AddTagClass", "\346\265\213\350\257\225\350\204\232\346\234\254", Q_NULLPTR));
        label_6->setText(QApplication::translate("AddTagClass", "\346\265\213\347\202\271\346\217\217\350\277\260", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class AddTagClass: public Ui_AddTagClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ADDTAGCLASS_H
