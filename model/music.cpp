#include "music.h"

Music::Music()
{
}

QString Music::name() const
{
    return m_name;
}

void Music::setName(const QString &name)
{
    if(m_name!=name){
        m_name = name;
        emit nameChanged();
    }
}

QString Music::cover() const
{
    return m_cover;
}

void Music::setCover(const QString &cover)
{
    if(m_cover!=cover){
        m_cover = cover;
        emit coverChanged();
    }
}


QString Music::path()
{
    return m_path;
}

void Music::setPath(const QString &path)
{
    if(m_path!=path){
        m_path = path;
        emit pathChanged();
    }
}

QString Music::album() const
{
    return m_album;
}

void Music::setAlbum(const QString &album)
{
    m_album = album;
}

QString Music::artist() const
{
    return m_artist;
}

void Music::setArtist(const QString &artist)
{
    m_artist = artist;
}

QString Music::lyric() const
{
    return m_lyric;
}

void Music::setLyric(const QString &lyric)
{
    m_lyric = lyric;
    emit lyricChanged();
}

QString Music::year() const
{
    return m_year;
}

void Music::setYear(const QString &year)
{
    m_year = year;
}

QString Music::size() const
{
    return m_size;
}

void Music::setSize(const QString &size)
{
    m_size = size;
}

qint64 Music::duration() const
{
    return m_duration;
}

void Music::setDuration(qint64 duration)
{
    m_duration = duration;
    emit durationChanged();
}

QString Music::title() const
{
    return m_title;
}

void Music::setTitle(const QString &title)
{
    m_title = title;
    emit titleChanged();
}

int Music::trackNumber() const
{
    return m_trackNumber;
}

void Music::setTrackNumber(int trackNumber)
{
    m_trackNumber = trackNumber;
}

QImage Music::image() const
{
    return m_image;
}

void Music::setImage(const QImage &image)
{
    m_image = image;
    emit imageChanged();
}



