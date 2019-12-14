#include "folder.h"
#include "model/searchmodel.h"
QMutex Folder::mutex;
Folder::Folder()
{
}


QList<QSharedPointer<Music> > Folder::musics()
{
    for(int i=m_musics.size()-1;i>=0;i--){
        if(m_musics[i].data() == nullptr){
            m_musics.removeAt(i);
        }
    }
    return m_musics;
}

void Folder::setMusics(const QList<QSharedPointer<Music> > &value)
{
    m_musics = value;
}


QString Folder::getPath() const
{
    return m_path;
}

void Folder::setPath(const QString &path)
{
    m_path = path;
    emit pathChanged();
}

void Folder::addMusic(QSharedPointer<Music> music)
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

QString Folder::name() const
{
    return m_name;
}

void Folder::setName(const QString &name)
{
    if(m_name!=name){
        m_name = name;
        emit nameChanged();
    }
}

QString Folder::cover() const
{
    return m_cover;
}

void Folder::setCover(const QString &cover)
{
    if(m_cover!=cover){
        m_cover = cover;
        emit coverChanged();
    }
}
void Folder::removeMusic(QString path)
{
    SearchModel search;
    int index =  search.find_music_at(m_musics,path);
    if(index!=-1){
        m_musics.removeAt(index);
    }

}


