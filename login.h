#ifndef LOGIN_H
#define LOGIN_H
#include <QMainWindow>
#include <QSql>
#include <QtDebug>
#include <QFileInfo>

QT_BEGIN_NAMESPACE
namespace Ui {
class login;
}
QT_END_NAMESPACE

class login : public QMainWindow
{
    Q_OBJECT

public:
    login(QWidget *parent = nullptr);
    ~login();

private slots:
    void LOGIN();

    void SIGNUP();

private:
    Ui::login *ui;
};
#endif // LOGIN_H
