#ifndef LOADFOLDER_H
#define LOADFOLDER_H
#include <QThread>
#include <QDir>
#include <QSharedPointer>
#include <QMutex>
#include <QElapsedTimer>
#include "commondefine.h"
#include "model/musicmanager.h"
#include "model/loadmetadata.h"
class LoadingFolder: public QObject
{
    Q_OBJECT
public:
    LoadingFolder();
    void setManager(MusicManager* manager);
    QString folder() const;
    void setFolder(const QString &folder);
    QSharedPointer<Music> addMusic(QString path_music);
    QSharedPointer<Folder> addFolder(QString path_folder);
    void loadFolder(QString pathFolder);
    void readDir(QString pathFolder);
signals:
    void finishLoadFolder(QSharedPointer<Folder> folder);
    void startLoadData(QSharedPointer<Music> music);
    void completeLoadFolder();
private:
    MusicManager* m_manager;
    QString m_folder;
    static QMutex mutex;
};

#endif // LOADFOLDER_H
