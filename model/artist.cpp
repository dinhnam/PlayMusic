#include "artist.h"
#include "model/searchmodel.h"
QMutex Artist::mutex;
Artist::Artist()
{
}
void Artist::removeMusic(QString path)
{
    SearchModel search;
    int index =  search.find_music_at(m_musics,path);
    if(index!=-1){
        m_musics.removeAt(index);
    }

}
QString Artist::name() const
{
    return m_name;
}

void Artist::setName(const QString &name)
{
    if(m_name!=name){
        m_name = name;
        emit nameChanged();
    }
}

QString Artist::cover() const
{
    return m_cover;
}

void Artist::setCover(const QString &cover)
{
    if(m_cover!=cover){
        m_cover = cover;
        emit coverChanged();
    }
}

QList<QSharedPointer<Music> > Artist::musics()
{
    return m_musics;
}

void Artist::setMusics(const QList<QSharedPointer<Music> > &value)
{
    m_musics = value;
}

void Artist::addMusic(QSharedPointer<Music> music)
{
    QString path_music = music->path();
    QList<QSharedPointer<Music>>::iterator pos;
    pos = std::find_if(m_musics.begin(),m_musics.end(),
                       [&](QSharedPointer<Music> &music){
            return music->path() == path_music;
    });
    if(pos == m_musics.end()){
        QDB<<music->name();
        m_musics << music;
    }
}
