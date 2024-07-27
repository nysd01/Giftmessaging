#include "signup.h"
#include "ui_signup.h"
#include "mainwindow.h"
#include <QMessageBox>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include <QProcess>
#include <QUuid>
#include <QPixmap>

signup::signup(QWidget *parent) :
    QGroupBox(parent),
    ui(new Ui::signup)
{
    ui->setupUi(this);
    connect(ui->pushButton, SIGNAL(clicked()), this, SLOT(CREATEACCOUNT()));

    QPixmap pix("C:/Users/BC/Documents/Giftmessaging/ict.jpg");
    ui->pic2->setPixmap(pix);

    setWindowFlag(Qt::FramelessWindowHint);

    QSqlDatabase mydb = QSqlDatabase::addDatabase("QSQLITE");
    mydb.setDatabaseName("mydatabase.db");

    if (!mydb.open()) {
        QMessageBox::critical(nullptr, QObject::tr("Database Error"),
                              mydb.lastError().text());
    } else {
        setupDatabase();
    }
}

signup::~signup()
{
    delete ui;
}

bool signup::setupDatabase() {
    QSqlQuery query;
    if (!query.exec("CREATE TABLE IF NOT EXISTS users ("
                    "id INTEGER PRIMARY KEY AUTOINCREMENT, "
                    "username TEXT UNIQUE, "
                    "email TEXT, "
                    "password TEXT, "
                    "unique_id TEXT)")) { // Added column for unique ID
        QMessageBox::critical(nullptr, QObject::tr("Database Error"),
                              query.lastError().text());
        return false;
    }
    return true;
}

bool signup::insertUser(const QString &username, const QString &email, const QString &password) {
    QSqlQuery query;
    QString uniqueId = QUuid::createUuid().toString(); // Generate a unique ID

    query.prepare("INSERT INTO users (username, email, password, unique_id) VALUES (?, ?, ?, ?)");
    query.addBindValue(username);
    query.addBindValue(email);
    query.addBindValue(password); // Ideally, hash the password
    query.addBindValue(uniqueId);

    if (!query.exec()) {
        qDebug() << "Error executing SQL query:" << query.lastError().text();
        qDebug() << "Query:" << query.lastQuery();
        return false;
    }
    qDebug() << "User inserted successfully with unique ID:" << uniqueId;
    return true;
}

void signup::CREATEACCOUNT() {
    QString username = ui->lineEdit->text();
    QString email = ui->lineEdit_2->text();
    QString password = ui->lineEdit_3->text();

    if (username.isEmpty() || email.isEmpty() || password.isEmpty()) {
        QMessageBox::information(this, tr("Input Error"), tr("Fill in all fields"));
    } else {
        if (insertUser(username, email, password)) {
            QString uniqueId = getUniqueId(username); // Get unique ID from the database
            if (!uniqueId.isEmpty()) {
                QString message = "Your unique ID is: " + uniqueId;
                if (sendEmail(email, "Welcome to Our Platform", message)) {
                    QMessageBox::information(this, tr("Registration Successful"), tr("Welcome, ") + username + "!");

                    MainWindow *mainwindow = new MainWindow;
                    mainwindow->show();
                    this->close();
                } else {
                    QMessageBox::critical(this, tr("Email Error"), tr("Failed to send email."));
                }
            } else {
                QMessageBox::critical(this, tr("Database Error"), tr("Failed to retrieve unique ID."));
            }
        } else {
            QMessageBox::critical(this, tr("Database Error"), tr("Failed to insert user into database."));
        }
    }
}

QString signup::getUniqueId(const QString &username) {
    QSqlQuery query;
    query.prepare("SELECT unique_id FROM users WHERE username = ?");
    query.addBindValue(username);

    if (query.exec() && query.next()) {
        QString uniqueId = query.value(0).toString();
        qDebug() << "Retrieved unique ID:" << uniqueId << "for username:" << username;
        return uniqueId;
    } else {
        qDebug() << "Failed to retrieve unique ID for username:" << username << "Error:" << query.lastError().text();
        return QString();
    }
}

bool signup::sendEmail(const QString &to, const QString &subject, const QString &body) {
    // Placeholder implementation for sending an email using the system's email client
    QString command = "echo \"" + body + "\" | mail -s \"" + subject + "\" " + to;
    return QProcess::execute(command) == 0;
}
