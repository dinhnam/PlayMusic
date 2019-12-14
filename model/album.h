#ifndef ALBUM_H
#define ALBUM_H

#include <QSharedPointer>
#include <QObject>
#include <QMutex>
#include "model/item.h"
#include "music.h"
class Album : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged)
    Q_PROPERTY(QString cover READ cover WRITE setCover NOTIFY coverChanged)
public:
    Album();
    QString name() const;
    void setName(const QString &name);
    QString cover() const;
    void setCover(const QString &cover);
    void addMusic(QSharedPointer<Music> music);
    QList<QSharedPointer<Music> > musics();
    void setMusics(const QList<QSharedPointer<Music> > &value);
public slots:
    void removeMusic(QString path);
signals:
    void nameChanged();
    void coverChanged();
private:
    QString m_name;
    QString m_cover;
    QList<QSharedPointer<Music>> m_musics;
    static QMutex mutex;
};

#endif // ALBUM_H
