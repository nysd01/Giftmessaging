/********************************************************************************
** Form generated from reading UI file 'signup.ui'
**
** Created by: Qt User Interface Compiler version 6.7.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SIGNUP_H
#define UI_SIGNUP_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_signup
{
public:
    QLineEdit *lineEdit;
    QLabel *label;
    QLabel *label_2;
    QLineEdit *lineEdit_2;
    QLineEdit *lineEdit_3;
    QLabel *label_3;
    QLabel *label_4;
    QLabel *pic2;
    QPushButton *pushButton;
    QLabel *label_5;

    void setupUi(QWidget *signup)
    {
        if (signup->objectName().isEmpty())
            signup->setObjectName("signup");
        signup->resize(1329, 729);
        lineEdit = new QLineEdit(signup);
        lineEdit->setObjectName("lineEdit");
        lineEdit->setGeometry(QRect(500, 210, 191, 20));
        label = new QLabel(signup);
        label->setObjectName("label");
        label->setGeometry(QRect(410, 210, 49, 16));
        QFont font;
        font.setPointSize(12);
        label->setFont(font);
        label_2 = new QLabel(signup);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(350, 260, 121, 20));
        label_2->setFont(font);
        lineEdit_2 = new QLineEdit(signup);
        lineEdit_2->setObjectName("lineEdit_2");
        lineEdit_2->setGeometry(QRect(500, 260, 191, 20));
        lineEdit_3 = new QLineEdit(signup);
        lineEdit_3->setObjectName("lineEdit_3");
        lineEdit_3->setGeometry(QRect(500, 310, 191, 20));
        label_3 = new QLabel(signup);
        label_3->setObjectName("label_3");
        label_3->setGeometry(QRect(390, 310, 91, 20));
        label_3->setFont(font);
        label_4 = new QLabel(signup);
        label_4->setObjectName("label_4");
        label_4->setGeometry(QRect(440, 100, 421, 41));
        QFont font1;
        font1.setPointSize(28);
        label_4->setFont(font1);
        pic2 = new QLabel(signup);
        pic2->setObjectName("pic2");
        pic2->setGeometry(QRect(890, 30, 391, 401));
        pushButton = new QPushButton(signup);
        pushButton->setObjectName("pushButton");
        pushButton->setGeometry(QRect(550, 430, 121, 24));
        pushButton->setFont(font);
        label_5 = new QLabel(signup);
        label_5->setObjectName("label_5");
        label_5->setGeometry(QRect(860, 400, 181, 16));

        retranslateUi(signup);

        QMetaObject::connectSlotsByName(signup);
    } // setupUi

    void retranslateUi(QWidget *signup)
    {
        signup->setWindowTitle(QCoreApplication::translate("signup", "Form", nullptr));
        lineEdit->setText(QString());
        label->setText(QCoreApplication::translate("signup", "EMAIL", nullptr));
        label_2->setText(QCoreApplication::translate("signup", "NEW USERNAME", nullptr));
        label_3->setText(QCoreApplication::translate("signup", "PASSWORD", nullptr));
        label_4->setText(QCoreApplication::translate("signup", "WELCOME, SIGNUP!", nullptr));
        pic2->setText(QCoreApplication::translate("signup", "TextLabel", nullptr));
        pushButton->setText(QCoreApplication::translate("signup", "Create account", nullptr));
        label_5->setText(QCoreApplication::translate("signup", "BY BRITNEY BERINYU MOUKOKO", nullptr));
    } // retranslateUi

};

namespace Ui {
    class signup: public Ui_signup {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SIGNUP_H
