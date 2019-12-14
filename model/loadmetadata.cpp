#include "model/loadmetadata.h"

LoadMetaData::LoadMetaData()
{
     isloading = false;
      m_media = new QMediaPlayer();
      connect(m_media,&QMediaPlayer::mediaStatusChanged,
              this,&LoadMetaData::onMediaStatusChanged);
}

void LoadMetaData::onMediaStatusChanged(QMediaPlayer::MediaStatus status)
{
    if(status == QMediaPlayer::InvalidMedia){
        QDB<<"media is invalid";
        m_manager->removeMusic(m_music->path());
    }else
    if(status == QMediaPlayer::LoadedMedia)
    {
        QString cover  = m_media->metaData(QMediaMetaData::CoverArtUrlSmall).toString();
        QString title = m_media->metaData(QMediaMetaData::Title).toString();
        QString album = m_media->metaData(QMediaMetaData::AlbumTitle).toString();
        QString artist =  m_media->metaData(QMediaMetaData::AlbumArtist).toString();
        if(artist == "" || artist == nullptr){
            artist  = "unknow";
        }
        if(album == "" || album == nullptr){
            album  = "unknow";
        }
        if(cover == "" || cover == nullptr){
            cover  = "qrc:/imgSrc/music.png";
        }
        m_music->setAlbum(album);
        m_music->setCover(cover);
        m_music->setArtist(artist);
        m_music->setTitle(title);
        QSharedPointer<Album> album_ptr = m_manager->addAlbum(album);
        album_ptr->addMusic(m_music);
        QSharedPointer<Artist> artist_ptr = m_manager->addArtist(artist);
        artist_ptr->addMusic(m_music);
        if(m_musicQueue.isEmpty()){
            isloading = false;
            emit finishGetMetaData();
        }else{
           loadMusic();
        }
    }

}

void LoadMetaData::onStartLoadData(QSharedPointer<Music> music)
{
    QDB<<"engqueue: "<<music->path();
    m_musicQueue.enqueue(music);
    if(isloading == false){
        isloading = true;
        loadMusic();
    }

}

void LoadMetaData::setManager(MusicManager* manager)
{
    m_manager = manager;
}

void LoadMetaData::loadMusic()
{
    m_music = m_musicQueue.dequeue();
    QDB<<m_music->path();
    m_media->setMedia(QMediaContent(QUrl::fromLocalFile(m_music->path())));
}





