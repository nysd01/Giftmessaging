#ifndef CHATWINDOW_H
#define CHATWINDOW_H

#include <QWidget>
#include <QListWidget>
#include <QTextEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include <QSqlDatabase>

class ChatWindow : public QWidget
{
    Q_OBJECT

public:
    explicit ChatWindow(const QString &chatName, bool isGroupChat = false, QWidget *parent = nullptr);
    ~ChatWindow();

public slots:
    void on_sendButton_clicked();
    void on_attachButton_clicked();
    void addMember(const QString &memberName);

private:
    void createMessagesTable();
    void loadMessages();
    void addImageToChat(const QString &imagePath);

    QListWidget *chatDisplay;
    QTextEdit *messageInput;
    QPushButton *sendButton;
    QPushButton *attachButton;
    QVBoxLayout *mainLayout;
    QSqlDatabase database;

    bool isGroupChat;
    QString chatName;
};

#endif // CHATWINDOW_H
