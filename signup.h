#ifndef SIGNUP_H
#define SIGNUP_H

#include <QGroupBox>
#include <QSqlDatabase>

namespace Ui {
class signup;
}

class signup : public QGroupBox
{
    Q_OBJECT

public:
    explicit signup(QWidget *parent = nullptr);
    ~signup();

private slots:
    void CREATEACCOUNT();


private:
    Ui::signup *ui;
    bool setupDatabase();
    bool insertUser(const QString &username, const QString &email, const QString &password);
    bool sendEmail(const QString &to, const QString &subject, const QString &body);
    QString getUniqueId(const QString &username);

};

#endif // SIGNUP_H
