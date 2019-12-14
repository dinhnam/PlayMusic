#ifndef MUSICSTORE_H
#define MUSICSTORE_H
#include <QObject>
#include <QSharedPointer>
#include <QDir>
#include <QFile>
#include <QFileInfo>
#include <QMediaPlayer>
#include <QMediaMetaData>
#include <QMediaContent>
#include <QTimer>
#include <QMutex>
#include <QThread>
#include <QFileDialog>
#include <QCoreApplication>
#include "commondefine.h"
#include "model/music.h"
#include "model/folder.h"
#include "model/album.h"
#include "model/artist.h"
#include "model/searchmodel.h"
class LoadMetaData;
class LoadingFolder;
class MusicManager : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int currentTab READ currentTab WRITE setCurrentTab NOTIFY currentTabChanged)
    Q_PROPERTY(bool isloading READ isloading NOTIFY isloadingChanged)
    Q_PROPERTY(int musicTotal READ musicTotal NOTIFY musicUpdate)
    Q_PROPERTY(int folderTotal READ folderTotal NOTIFY folderUpdate)
    Q_PROPERTY(int albumTotal READ albumTotal NOTIFY albumUpdate)
    Q_PROPERTY(int artistTotal READ artistTotal NOTIFY artistUpdate)
    Q_ENUMS(TabRoles)
public:
    enum TabRoles{
        MUSICTAB = 0,
        FOLDERTAB,
        ALBUMTAB,
        ARTISTTAB
    };
    MusicManager();
    QSharedPointer<Music> addMusic(QString path_music);
    void removeMusic(QString path);
    void setFolders(QList<QSharedPointer<Folder>> folders);
    QSharedPointer<Folder> addFolder(QString path_folder);
    QSharedPointer<Artist> addArtist(QString name_artist);
    QSharedPointer<Album> addAlbum(QString name_album);
    QList<QSharedPointer<Music> > &musics();
    QList<QSharedPointer<Folder>> &folders();
    QList<QSharedPointer<Album>> &albums();
    QList<QSharedPointer<Artist>> &artists();
    int currentTab() const;
    void setCurrentTab(int currentTab);
    void openFolder();
    void selectFiles();
    bool isloading() const;
    void setIsloading(bool isloading);
    int musicTotal();
    int folderTotal();
    int albumTotal();
    int artistTotal();
signals:
    void currentTabChanged();
    void listItemUpdate();
    void isloadingChanged();
    void startLoadFolder(QString path_folder);
    void startLoadData(QSharedPointer<Music> music);
    void musicUpdate();
    void albumUpdate();
    void artistUpdate();
    void folderUpdate();
public slots:
     void onFinishLoadFolder(QSharedPointer<Folder> folder);
     void onFinishLoadMusic(QSharedPointer<Music> music);
     void onCompleteLoadFolder();
private:
    QList<QSharedPointer<Music>> m_musics;
    QList<QSharedPointer<Folder>> m_folders;
    QList<QSharedPointer<Album>> m_albums;
    QList<QSharedPointer<Artist>> m_artists;
    static QMutex mutex;
    int m_currentTab;
    QFileDialog m_qfile;
    bool m_isloading;
    QThread getFolderThread;
    QThread getDataThread;
    LoadMetaData *m_loadMetaData;
    LoadingFolder *m_loadingFolder;
};

#endif // MUSICSTORE_H
