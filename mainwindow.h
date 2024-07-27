#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QListWidget>
#include <QLineEdit>
#include <QPushButton>
#include <QSqlDatabase>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_createGroupChatButton_clicked();
    void on_addContactButton_clicked();
    void on_recentChatsList_itemDoubleClicked(QListWidgetItem *item);
    void on_profileButton_clicked();
    void on_searchContactButton_clicked(); // Slot for searching contact by ID

private:
    void createRecentChatsTable();
    void loadRecentChats();

    QListWidget *recentChatsList;
    QLineEdit *addGroupChatLineEdit;
    QLineEdit *addContactLineEdit;
    QLineEdit *searchContactLineEdit; // Line edit for search
    QPushButton *createGroupChatButton;
    QPushButton *addContactButton;
    QPushButton *searchContactButton; // Button for search
    QPushButton *profileButton;
    QSqlDatabase database;
};

#endif // MAINWINDOW_H



