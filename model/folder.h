#ifndef FOLDER_H
#define FOLDER_H
#include <QObject>
#include <QSharedPointer>
#include <QMutex>
#include <QDir>
#include "model/music.h"
#include "model/item.h"
class Folder : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged)
    Q_PROPERTY(QString cover READ cover WRITE setCover NOTIFY coverChanged)
    Q_PROPERTY(QString path READ getPath WRITE setPath NOTIFY pathChanged)
public:
    Folder();
    QString name() const;
    void setName(const QString &name);
    QString cover() const;
    void setCover(const QString &cover);
    QString getPath() const;
    void setPath(const QString &path);
    void addMusic(QSharedPointer<Music> music);
    QList<QSharedPointer<Music> > musics();
    void setMusics(const QList<QSharedPointer<Music> > &value);
public slots:
    void removeMusic(QString path);
signals:
    void pathChanged();
    void nameChanged();
    void coverChanged();
private:
    QString m_name;
    QString m_cover;
    QString m_path;
    QList<QSharedPointer<Music>> m_musics;
    static QMutex mutex;
};

#endif // FOLDER_H
