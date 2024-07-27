#include "mainwindow.h"
#include "chatwindow.h"
#include "profiledialog.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QMessageBox>
#include <QSqlQuery>
#include <QSqlError>
#include <QFileDialog>
#include <QListWidgetItem>
#include <QIcon>
#include <QPixmap>
#include <QUuid>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
    recentChatsList(new QListWidget(this)),
    addGroupChatLineEdit(new QLineEdit(this)),
    addContactLineEdit(new QLineEdit(this)),
    searchContactLineEdit(new QLineEdit(this)), // Initialize search line edit
    createGroupChatButton(new QPushButton("Create Group Chat", this)),
    addContactButton(new QPushButton("Add Contact", this)),
    searchContactButton(new QPushButton("Search Contact", this)), // Initialize search button
    profileButton(new QPushButton("Setup Profile", this))
{
    QVBoxLayout *mainLayout = new QVBoxLayout;
    QHBoxLayout *topLayout = new QHBoxLayout;

    topLayout->addStretch();
    topLayout->addWidget(profileButton);

    mainLayout->addLayout(topLayout);
    mainLayout->addWidget(recentChatsList);
    mainLayout->addWidget(addGroupChatLineEdit);
    mainLayout->addWidget(createGroupChatButton);
    mainLayout->addWidget(addContactLineEdit);
    mainLayout->addWidget(addContactButton);
    mainLayout->addWidget(searchContactLineEdit); // Add search line edit to layout
    mainLayout->addWidget(searchContactButton); // Add search button to layout

    QWidget *centralWidget = new QWidget(this);
    centralWidget->setLayout(mainLayout);
    setCentralWidget(centralWidget);

    connect(createGroupChatButton, &QPushButton::clicked, this, &MainWindow::on_createGroupChatButton_clicked);
    connect(addContactButton, &QPushButton::clicked, this, &MainWindow::on_addContactButton_clicked);
    connect(searchContactButton, &QPushButton::clicked, this, &MainWindow::on_searchContactButton_clicked); // Connect search button
    connect(recentChatsList, &QListWidget::itemDoubleClicked, this, &MainWindow::on_recentChatsList_itemDoubleClicked);
    connect(profileButton, &QPushButton::clicked, this, &MainWindow::on_profileButton_clicked);

    database = QSqlDatabase::addDatabase("QSQLITE");
    database.setDatabaseName("mydatabase.db");

    if (!database.open()) {
        QMessageBox::critical(this, "Database Error", database.lastError().text());
    } else {
        createRecentChatsTable();
        loadRecentChats();
    }
}

MainWindow::~MainWindow()
{
    database.close();
}

void MainWindow::createRecentChatsTable()
{
    QSqlQuery query;
    QString createTableQuery = R"(
        CREATE TABLE IF NOT EXISTS recent_chats (
            id INTEGER PRIMARY KEY AUTOINCREMENT,
            chat_name TEXT NOT NULL,
            profile_picture_path TEXT,
            unique_id TEXT UNIQUE NOT NULL
        )
    )";

    if (!query.exec(createTableQuery)) {
        QMessageBox::critical(this, "Database Error", query.lastError().text());
    }
}

void MainWindow::loadRecentChats()
{
    QSqlQuery query("SELECT chat_name, profile_picture_path FROM recent_chats");
    while (query.next()) {
        QString chatName = query.value(0).toString();
        QString profilePicturePath = query.value(1).toString();

        QListWidgetItem *item = new QListWidgetItem(chatName);
        if (!profilePicturePath.isEmpty()) {
            QPixmap pixmap(profilePicturePath);
            QIcon icon(pixmap);
            item->setIcon(icon);
        }
        recentChatsList->addItem(item);
    }
}

void MainWindow::on_createGroupChatButton_clicked()
{
    QString groupName = addGroupChatLineEdit->text();
    if (groupName.isEmpty()) {
        QMessageBox::warning(this, "Input Error", "Group name cannot be empty.");
        return;
    }

    QSqlQuery query;
    query.prepare("INSERT INTO recent_chats (chat_name, unique_id) VALUES (:chat_name, :unique_id)");
    query.bindValue(":chat_name", groupName);
    query.bindValue(":unique_id", QUuid::createUuid().toString()); // Generate a unique ID for the group

    if (!query.exec()) {
        QMessageBox::critical(this, "Database Error", query.lastError().text());
    } else {
        QListWidgetItem *item = new QListWidgetItem(groupName);
        recentChatsList->addItem(item);
        addGroupChatLineEdit->clear();

        ChatWindow *chatWindow = new ChatWindow(groupName, true, this); // Open group chat window
        chatWindow->show();
        this->hide();
    }
}

void MainWindow::on_addContactButton_clicked()
{
    QString contactName = addContactLineEdit->text();
    if (contactName.isEmpty()) {
        QMessageBox::warning(this, "Input Error", "Contact name cannot be empty.");
        return;
    }

    QString profilePicturePath = QFileDialog::getOpenFileName(this, "Select Profile Picture", "", "Images (*.png *.xpm *.jpg)");
    QString uniqueId = QUuid::createUuid().toString(); // Generate a unique ID for the contact

    QSqlQuery query;
    query.prepare("INSERT INTO recent_chats (chat_name, profile_picture_path, unique_id) VALUES (:chat_name, :profile_picture_path, :unique_id)");
    query.bindValue(":chat_name", contactName);
    query.bindValue(":profile_picture_path", profilePicturePath);
    query.bindValue(":unique_id", uniqueId);

    if (!query.exec()) {
        QMessageBox::critical(this, "Database Error", query.lastError().text());
    } else {
        QListWidgetItem *item = new QListWidgetItem(contactName);
        if (!profilePicturePath.isEmpty()) {
            QPixmap pixmap(profilePicturePath);
            QIcon icon(pixmap);
            item->setIcon(icon);
        }
        recentChatsList->addItem(item);
        addContactLineEdit->clear();
    }
}

void MainWindow::on_searchContactButton_clicked()
{
    QString contactId = searchContactLineEdit->text();
    if (contactId.isEmpty()) {
        QMessageBox::warning(this, "Input Error", "Contact ID cannot be empty.");
        return;
    }

    QSqlQuery query;
    query.prepare("SELECT chat_name, profile_picture_path FROM recent_chats WHERE unique_id = :unique_id");
    query.bindValue(":unique_id", contactId);

    if (!query.exec()) {
        QMessageBox::critical(this, "Database Error", query.lastError().text());
    } else if (query.next()) {
        QString contactName = query.value(0).toString();
        QString profilePicturePath = query.value(1).toString();

        QListWidgetItem *item = new QListWidgetItem(contactName);
        if (!profilePicturePath.isEmpty()) {
            QPixmap pixmap(profilePicturePath);
            QIcon icon(pixmap);
            item->setIcon(icon);
        }
        recentChatsList->addItem(item);
        searchContactLineEdit->clear();
    } else {
        QMessageBox::information(this, "Search Result", "No contact found with the given ID.");
    }
}

void MainWindow::on_recentChatsList_itemDoubleClicked(QListWidgetItem *item)
{
    QString chatName = item->text();
    ChatWindow *chatWindow = new ChatWindow(chatName);
    chatWindow->show();
    this->hide();
}

void MainWindow::on_profileButton_clicked()
{
    ProfileDialog profileDialog(this);
    if (profileDialog.exec() == QDialog::Accepted) {
        QString profileName = profileDialog.getProfileName();
        QString profilePicturePath = profileDialog.getProfilePicturePath();

        // Update the profile information in the database if needed
        QSqlQuery query;
        query.prepare("UPDATE profile SET profile_name = :profile_name, profile_picture_path = :profile_picture_path");
        query.bindValue(":profile_name", profileName);
        query.bindValue(":profile_picture_path", profilePicturePath);

        if (!query.exec()) {
            QMessageBox::critical(this, "Database Error", query.lastError().text());
        } else {
            // Update UI or notify user of successful update
            QMessageBox::information(this, "Profile Updated", "Profile information updated successfully.");
        }
    }
}


