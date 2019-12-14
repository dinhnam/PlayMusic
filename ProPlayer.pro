QT += quick
QT += multimedia
QT += core
QT += widgets
CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Refer to the documentation for the
# deprecated API to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        appengine.cpp \
        controller/hmicontroller.cpp \
        controller/musiccontroller.cpp \
        main.cpp \
        model/album.cpp \
        model/artist.cpp \
        model/folder.cpp \
        model/hmimodel.cpp \
        model/jsonmanager.cpp \
        model/loadfolder.cpp \
        model/loadmetadata.cpp \
        model/music.cpp \
        model/musicmanager.cpp \
        model/musicmodel.cpp \
        model/mytrans.cpp \
        model/playlistmodel.cpp \
        model/randommusic.cpp \
        model/searchmodel.cpp

RESOURCES += qml.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Additional import path used to resolve QML modules just for Qt Quick Designer
QML_DESIGNER_IMPORT_PATH =

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

HEADERS += \
    appengine.h \
    commondefine.h \
    controller/hmicontroller.h \
    controller/musiccontroller.h \
    model/Mylang.h \
    model/album.h \
    model/artist.h \
    model/folder.h \
    model/hmimodel.h \
    model/jsonmanager.h \
    model/loadfolder.h \
    model/loadmetadata.h \
    model/music.h \
    model/musicmanager.h \
    model/musicmodel.h \
    model/mytrans.h \
    model/playlistmodel.h \
    model/randommusic.h \
    model/searchmodel.h
TRANSLATIONS = translator/Trans_VI.ts \
               translator/Trans_EN.ts
