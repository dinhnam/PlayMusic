#ifndef LOADMETADATA_H
#define LOADMETADATA_H

#include <QObject>
#include <QMediaPlayer>
#include <QMediaMetaData>
#include <QThread>
#include <QDir>
#include <QQueue>
#include <QObject>
#include <QTimer>
#include "commondefine.h"
#include "model/musicmanager.h"
class LoadMetaData : public QObject
{
    Q_OBJECT
public:
    explicit LoadMetaData();
    void loadMusic();
    void setManager(MusicManager* manager);
signals:
    void finishGetMetaData();
public slots:
    void onMediaStatusChanged(QMediaPlayer::MediaStatus status);
    void onStartLoadData(QSharedPointer<Music> music);
private:
    bool isloading;
    QQueue<QSharedPointer<Music>> m_musicQueue;
    QMediaPlayer *m_media;
    MusicManager* m_manager;
    QSharedPointer<Music> m_music;
};


#endif // LOADMETADATA_H
