#include "model/album.h"
#include "model/searchmodel.h"
QMutex Album::mutex;
Album::Album()
{

}

void Album::removeMusic(QString path)
{
    SearchModel search;
    int index =  search.find_music_at(m_musics,path);
    if(index!=-1){
        m_musics.removeAt(index);
    }
}
QString Album::name() const
{
    return m_name;
}

void Album::setName(const QString &name)
{
    if(m_name!=name){
        m_name = name;
        emit nameChanged();
    }
}

QString Album::cover() const
{
    return m_cover;
}

void Album::setCover(const QString &cover)
{
    if(m_cover!=cover){
        m_cover = cover;
        emit coverChanged();
    }
}

QList<QSharedPointer<Music> > Album::musics()
{
    return m_musics;
}

void Album::setMusics(const QList<QSharedPointer<Music> > &value)
{
    m_musics = value;
}


void Album::addMusic(QSharedPointer<Music> music)
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

