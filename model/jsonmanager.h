#ifndef JSONMANAGER_H
#define JSONMANAGER_H
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QObject>
#include <QFile>
#include <QSharedPointer>
#include "model/folder.h"
class JsonManager: public QObject
{
    Q_OBJECT
public:
    JsonManager();
    void wirteFile(QList<QSharedPointer<Folder>> &folders);
    QList<QSharedPointer<Folder>> readFile();
    QSharedPointer<Folder> getFolder(QJsonObject jsonFolder);
    QSharedPointer<Music> getMusic(QJsonObject jsonMusic);
signals:
    void wirteComplete();
};

#endif // JSONMANAGER_H
