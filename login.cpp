#include "login.h"
#include "ui_login.h"
#include "signup.h"
#include "mainwindow.h"
#include <QMessageBox>
#include <QSqlDatabase>
#include <QSqlError>
#include <QPixmap>
login::login(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::login)
{
    ui->setupUi(this);
    QPixmap pix("C:/Users/BC/Documents/Giftmessaging/ict.jpg");
    ui->pic->setPixmap(pix);
    connect(ui->pushButton, SIGNAL(clicked()), this, SLOT(LOGIN()));
    connect(ui->pushButton_2, SIGNAL(clicked()), this, SLOT(SIGNUP()));


    setWindowFlag(Qt::FramelessWindowHint);
    setAttribute(Qt:: WA_TintedBackground, true);

    QSqlDatabase mydb = QSqlDatabase:: addDatabase("QSQLITE");
    mydb.setDatabaseName("mydatabase.db");

    if (!mydb.open()) {
        QMessageBox::critical(nullptr, QObject::tr("Database Error"),
                              mydb.lastError().text());
    }
}

login::~login()
{
    delete ui;
}

void login::LOGIN()
{
    QString username = ui->lineEdit->text();
    QString email = ui->lineEdit_2->text();
    QString password = ui->lineEdit_3->text();

    if(username.isEmpty() || email.isEmpty() || password.isEmpty()){
        QMessageBox::information(this, tr("Input Error"), tr("Fill in all fields"));
    }
    else{
        QMessageBox::information(this, tr("Login Successful"), tr("Welcome Back, ") + username + "!");

        MainWindow *mainwindow = new MainWindow;
        mainwindow->show();
        this->close();
    }

}



void login::SIGNUP()
{
    signup *nw = new signup;
    nw->show();
    this->hide();
}
