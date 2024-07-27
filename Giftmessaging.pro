QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    chatwindow.cpp \
    main.cpp \
    login.cpp \
    mainwindow.cpp \
    profiledialog.cpp \
    signup.cpp

HEADERS += \
    chatwindow.h \
    login.h \
    mainwindow.h \
    profiledialog.h \
    signup.h

FORMS += \
    chatwindow.ui \
    login.ui \
    mainwindow.ui \
    profiledialog.ui \
    signup.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    images.qrc
