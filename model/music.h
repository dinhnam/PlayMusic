#ifndef MUSIC_H
#define MUSIC_H

#include <QObject>
#include <QImage>
#include "commondefine.h"
class Music: public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged)
    Q_PROPERTY(QString cover READ cover WRITE setCover NOTIFY coverChanged)
    Q_PROPERTY(QImage image READ image WRITE setImage NOTIFY imageChanged)
    Q_PROPERTY(QString title READ title WRITE setTitle NOTIFY titleChanged)
    Q_PROPERTY(QString path READ path WRITE setPath NOTIFY pathChanged)
    Q_PROPERTY(QString album READ album WRITE setAlbum NOTIFY albumChanged)
    Q_PROPERTY(QString artist READ artist WRITE setArtist NOTIFY artistChanged)
    Q_PROPERTY(QString lyric READ lyric WRITE setLyric NOTIFY lyricChanged)
    Q_PROPERTY(QString year READ year WRITE setYear NOTIFY yearChanged)
    Q_PROPERTY(QString size READ size WRITE setSize NOTIFY sizeChanged)
    Q_PROPERTY(qint64 duration  READ duration WRITE setDuration NOTIFY durationChanged)
    Q_PROPERTY(int trackNumber READ trackNumber WRITE setTrackNumber NOTIFY trackNumberChanged)
public:
    Music();
    Music(const Music &muisc);
    QString path();
    void setPath(const QString &path);

    QString album() const;
    void setAlbum(const QString &album);

    QString artist() const;
    void setArtist(const QString &artist);

    QString lyric() const;
    void setLyric(const QString &lyric);

    QString year() const;
    void setYear(const QString &year);

    QString size() const;
    void setSize(const QString &size);

    qint64 duration() const;
    void setDuration(qint64 duration);

    QString title() const;
    void setTitle(const QString &title);

    QImage image() const;
    void setImage(const QImage &image);

    int trackNumber() const;
    void setTrackNumber(int trackNumber);


    QString name() const;
    void setName(const QString &name);

    QString cover() const;
    void setCover(const QString &cover);

signals:
    void pathChanged();
    void albumChanged();
    void artistChanged();
    void lyricChanged();
    void yearChanged();
    void sizeChanged();
    void durationChanged();
    void finishSetMetaData();
    void titleChanged();
    void imageChanged();
    void trackNumberChanged();
    void nameChanged();
    void coverChanged();
    void checkedChanged();
public slots:

private:
    QString m_name;
    QString m_cover;
    QImage m_image;
    QString m_title;
    QString m_path;
    QString m_album;
    QString m_artist;
    QString m_lyric;
    QString m_year;
    QString m_size;
    qint64 m_duration;
    int m_trackNumber;
};

#endif // MUSIC_H
