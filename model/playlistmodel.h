#ifndef PLAYLISTMODEL_H
#define PLAYLISTMODEL_H
#include <QAbstractListModel>
#include <QObject>
#include <QSharedPointer>
#include <QMediaPlayer>
#include <QMediaContent>
#include <QMediaMetaData>
#include <QThread>
#include "model/randommusic.h"
#include "commondefine.h"
#include "model/music.h"
class PlayListModel : public QObject
{
    Q_OBJECT
    Q_ENUMS(PlayRoles)
    Q_PROPERTY(int mediaStatus READ status WRITE setStatus NOTIFY statusChanged)
    Q_PROPERTY(qint64 position READ position WRITE setPosition NOTIFY positionChanged)
    Q_PROPERTY(int state READ getState WRITE setState NOTIFY stateChanged)
    Q_PROPERTY(qint64 duration READ getDuration WRITE setDuration NOTIFY durationChanged)
    Q_PROPERTY(int currentIndex READ getCurrentIndex WRITE setCurrentIndex NOTIFY currentIndexChanged)
    Q_PROPERTY(float volume READ getVolume WRITE setVolume NOTIFY volumeChanged)
    Q_PROPERTY(unsigned char playRule READ getPlayRule WRITE setPlayRule NOTIFY playRuleChanged)
    Q_PROPERTY(QString musicTitle READ getMusicTitle NOTIFY statusChanged)
public:
    enum PlayRoles{
        normal = 1,
        repeat,
        repeatone,
        shuffle
    };

    PlayListModel();
    virtual ~PlayListModel();
    void init();

private:
    QMediaPlayer* m_mediaplayer;
    QList<QSharedPointer<Music>> m_musics;
    int m_currentIndex;
    int m_status;
    int m_state;
    unsigned char m_playRule;
    qint64 m_position;
    qint64 m_duration;
    int m_volume;
    RandomMusic m_randomMusic;
    QThread thread;
public:
    void removeMusic(int index);
    int status() const;
    qint64 position() const;
    qint64 getDuration() const;
    int getState() const;
    int getCurrentIndex() const;
    void setCurrentIndex(int currentIndex);
    int getVolume() const;
    void setVolume(int volume);
    void setDuration(const qint64 &duration);
    void setStatus(int status);
    void setState(int state);
    void setPosition(const qint64 &position);
    QList<QSharedPointer<Music> > getMusics();
    void setMusics(const QList<QSharedPointer<Music> > &musics);
    unsigned char getPlayRule() const;
    void setPlayRule(unsigned char playRule);
    void autoNextMusic();
    void shuffleMusic();
    void removeSelctMusics(QList<int> selections);
    void addMusic(QSharedPointer<Music> item);
    QString getMusicTitle();
public slots:
    void loadMusic();
    void playMusic();
    void pauseMusic();
    void stopMusic();
    void onDurationChanged(qint64 duration);
    void onPositionChanged(qint64 position);
    void onStateChanged(QMediaPlayer::State state);
    void onMediaStatusChanged(QMediaPlayer::MediaStatus status);
signals:
    void statusChanged();
    void positionChanged();
    void durationChanged();
    void stateChanged();
    void currentIndexChanged();
    void volumeChanged();
    void playRuleChanged();
};

#endif // PLAYLISTMODEL_H
