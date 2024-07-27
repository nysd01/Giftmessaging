#ifndef PROFILEDIALOG_H
#define PROFILEDIALOG_H

#include <QDialog>
#include <QLineEdit>
#include <QPushButton>
#include <QLabel>
#include <QVBoxLayout>

class ProfileDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ProfileDialog(QWidget *parent = nullptr);
    QString getProfileName() const;
    QString getProfilePicturePath() const;

private slots:
    void on_browseButton_clicked();

private:
    QLineEdit *nameLineEdit;
    QLabel *pictureLabel;
    QString profilePicturePath;
};

#endif // PROFILEDIALOG_H


