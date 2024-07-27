#include "chatwindow.h"
#include <QHBoxLayout>
#include <QMessageBox>
#include <QFileDialog>
#include <QListWidgetItem>
#include <QLabel>
#include <QPixmap>
#include <QSqlQuery>
#include <QSqlError>
#include <QDateTime>

ChatWindow::ChatWindow(const QString &chatName, bool isGroupChat, QWidget *parent)
    : QWidget(parent),
    chatDisplay(new QListWidget(this)),
    messageInput(new QTextEdit(this)),
    sendButton(new QPushButton("Send", this)),
    attachButton(new QPushButton("Attach Image", this)),
    isGroupChat(isGroupChat),
    chatName(chatName)
{
    mainLayout = new QVBoxLayout;
    QHBoxLayout *inputLayout = new QHBoxLayout;

    inputLayout->addWidget(messageInput);
    inputLayout->addWidget(sendButton);
    inputLayout->addWidget(attachButton);

    mainLayout->addWidget(chatDisplay);
    mainLayout->addLayout(inputLayout);

    setLayout(mainLayout);

    connect(sendButton, &QPushButton::clicked, this, &ChatWindow::on_sendButton_clicked);
    connect(attachButton, &QPushButton::clicked, this, &ChatWindow::on_attachButton_clicked);

    if (isGroupChat) {
        QLabel *label = new QLabel("Group Members:");
        mainLayout->insertWidget(0, label);
    }

    database = QSqlDatabase::addDatabase("QSQLITE");
    database.setDatabaseName("mydatabase.db");

    if (!database.open()) {
        QMessageBox::critical(this, "Database Error", database.lastError().text());
    } else {
        createMessagesTable();
        loadMessages();
    }
}

ChatWindow::~ChatWindow()
{
    database.close();
}

void ChatWindow::createMessagesTable()
{
    QSqlQuery query;
    if (!query.exec("CREATE TABLE IF NOT EXISTS messages ("
                    "id INTEGER PRIMARY KEY AUTOINCREMENT, "
                    "chat_name TEXT, "
                    "sender TEXT, "
                    "message TEXT, "
                    "timestamp DATETIME DEFAULT CURRENT_TIMESTAMP)")) {
        QMessageBox::critical(this, "Database Error", query.lastError().text());
    }
}

void ChatWindow::loadMessages()
{
    QSqlQuery query;
    query.prepare("SELECT sender, message, timestamp FROM messages WHERE chat_name = :chat_name ORDER BY timestamp ASC");
    query.bindValue(":chat_name", chatName);
    if (!query.exec()) {
        QMessageBox::critical(this, "Database Error", query.lastError().text());
        return;
    }

    while (query.next()) {
        QString sender = query.value(0).toString();
        QString message = query.value(1).toString();
        QString timestamp = query.value(2).toString();

        QListWidgetItem *item = new QListWidgetItem("[" + timestamp + "] " + sender + ": " + message);
        chatDisplay->addItem(item);
    }
}

void ChatWindow::on_sendButton_clicked()
{
    QString message = messageInput->toPlainText();
    if (message.isEmpty()) {
        QMessageBox::warning(this, "Input Error", "Message cannot be empty.");
        return;
    }

    QListWidgetItem *item = new QListWidgetItem(message);
    chatDisplay->addItem(item);

    QSqlQuery query;
    query.prepare("INSERT INTO messages (chat_name, sender, message) VALUES (:chat_name, :sender, :message)");
    query.bindValue(":chat_name", chatName);
    query.bindValue(":sender", "me"); // Replace with actual sender if applicable
    query.bindValue(":message", message);
    if (!query.exec()) {
        QMessageBox::critical(this, "Database Error", query.lastError().text());
    }

    messageInput->clear();
}

void ChatWindow::on_attachButton_clicked()
{
    QString imagePath = QFileDialog::getOpenFileName(this, "Select Image", "", "Images (*.png *.xpm *.jpg *.jpeg)");
    if (!imagePath.isEmpty()) {
        addImageToChat(imagePath);
    }
}

void ChatWindow::addImageToChat(const QString &imagePath)
{
    QListWidgetItem *item = new QListWidgetItem;
    QPixmap pixmap(imagePath);
    QLabel *label = new QLabel;
    label->setPixmap(pixmap.scaled(100, 100, Qt::KeepAspectRatio));
    chatDisplay->addItem(item);
    chatDisplay->setItemWidget(item, label);
}

void ChatWindow::addMember(const QString &memberName)
{
    if (isGroupChat) {
        QListWidgetItem *item = new QListWidgetItem("New member: " + memberName);
        chatDisplay->addItem(item);
    }
}
