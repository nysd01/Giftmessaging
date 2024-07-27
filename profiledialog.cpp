#include "profiledialog.h"
#include <QFileDialog>
#include <QHBoxLayout>

ProfileDialog::ProfileDialog(QWidget *parent)
    : QDialog(parent), profilePicturePath("")
{
    QVBoxLayout *layout = new QVBoxLayout(this);

    nameLineEdit = new QLineEdit(this);
    nameLineEdit->setPlaceholderText("Enter your name");

    QPushButton *browseButton = new QPushButton("Browse...", this);
    pictureLabel = new QLabel("No picture selected", this);

    QHBoxLayout *pictureLayout = new QHBoxLayout;
    pictureLayout->addWidget(pictureLabel);
    pictureLayout->addWidget(browseButton);

    QPushButton *okButton = new QPushButton("OK", this);
    QPushButton *cancelButton = new QPushButton("Cancel", this);

    QHBoxLayout *buttonsLayout = new QHBoxLayout;
    buttonsLayout->addWidget(okButton);
    buttonsLayout->addWidget(cancelButton);

    layout->addWidget(new QLabel("Profile Name:", this));
    layout->addWidget(nameLineEdit);
    layout->addLayout(pictureLayout);
    layout->addLayout(buttonsLayout);

    connect(browseButton, &QPushButton::clicked, this, &ProfileDialog::on_browseButton_clicked);
    connect(okButton, &QPushButton::clicked, this, &QDialog::accept);
    connect(cancelButton, &QPushButton::clicked, this, &QDialog::reject);
}

QString ProfileDialog::getProfileName() const
{
    return nameLineEdit->text();
}

QString ProfileDialog::getProfilePicturePath() const
{
    return profilePicturePath;
}

void ProfileDialog::on_browseButton_clicked()
{
    profilePicturePath = QFileDialog::getOpenFileName(this, "Select Profile Picture", "", "Images (*.png *.xpm *.jpg)");
    if (!profilePicturePath.isEmpty()) {
        pictureLabel->setText(profilePicturePath);
    } else {
        pictureLabel->setText("No picture selected");
    }
}


