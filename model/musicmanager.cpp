#include "model/musicmanager.h"
#include "model/loadfolder.h"
#include "model/loadmetadata.h"
QMutex MusicManager::mutex;

MusicManager::MusicManager()
{
    m_currentTab = 0;
    qRegisterMetaType<QSharedPointer<Folder>>("QSharedPointer<Folder>");
    qRegisterMetaType<QSharedPointer<Music>>("QSharedPointer<Music>");
    m_loadingFolder = new LoadingFolder();
    m_loadingFolder->setManager(this);
    m_loadingFolder->moveToThread(&getFolderThread);
    connect(&getFolderThread, &QThread::finished, m_loadingFolder, &QObject::deleteLater);
    connect(this, &MusicManager::startLoadFolder, m_loadingFolder, &LoadingFolder::loadFolder);
    connect(m_loadingFolder, &LoadingFolder::finishLoadFolder,
            this, &MusicManager::onFinishLoadFolder);
    connect(m_loadingFolder, &LoadingFolder::startLoadData,
            this, &MusicManager::onFinishLoadMusic);
    connect(m_loadingFolder, &LoadingFolder::completeLoadFolder,
             this, &MusicManager::onCompleteLoadFolder);
    getFolderThread.start();
    m_loadMetaData = new LoadMetaData();
    m_loadMetaData->setManager(this);
    m_loadMetaData->moveToThread(&getDataThread);
    connect(&getDataThread, &QThread::finished, m_loadMetaData, &QObject::deleteLater);
    connect(m_loadingFolder,SIGNAL(startLoadData(QSharedPointer<Music>)),
                m_loadMetaData,SLOT(onStartLoadData(QSharedPointer<Music>)));
    connect(this,SIGNAL(startLoadData(QSharedPointer<Music>)),
                m_loadMetaData,SLOT(onStartLoadData(QSharedPointer<Music>)));
    connect(m_loadMetaData,SIGNAL(finishGetMetaData()),
                this,SIGNAL(listItemUpdate()));
    getDataThread.start();
    QDB<<"currentThread "<<QThread::currentThread();
}


void MusicManager::openFolder()
{
    QString dir = m_qfile.getExistingDirectory();
    emit startLoadFolder(dir);
}

void MusicManager::selectFiles()
{
    m_qfile.filter();
    QStringList mimeTypeFilters;
    QStringList files = m_qfile.getOpenFileNames(&m_qfile,
                                                 "Select one or more files to open",
                                                 "/home",
                                                 "Musics (*.mp3 *.flac *.wav)");
    if(!files.isEmpty()){
        QFileInfo qfileinfo(files[0]);
        QString pathFolder = qfileinfo.dir().absolutePath();
        QSharedPointer<Folder> folder = this->addFolder(pathFolder);
        foreach (QString var, files) {
            QSharedPointer<Music> music = this->addMusic(var);
            folder->addMusic(music);
            emit startLoadData(music);
        }
    }
}

void MusicManager::onFinishLoadFolder(QSharedPointer<Folder> folder)
{
    QDB<<folder->getPath();
    m_folders<<folder;
    emit folderUpdate();
}

void MusicManager::onFinishLoadMusic(QSharedPointer<Music> music)
{
    QDB<<music->path();
    m_musics<<music;
    emit musicUpdate();
}

void MusicManager::onCompleteLoadFolder()
{
    emit listItemUpdate();
}


bool MusicManager::isloading() const
{
    return m_isloading;
}

void MusicManager::setIsloading(bool isloading)
{
    m_isloading = isloading;
    emit isloadingChanged();
    QDB<<m_isloading;
}

int MusicManager::musicTotal()
{
    return m_musics.size();
}

int MusicManager::folderTotal()
{
    return m_folders.size();
}

int MusicManager::albumTotal()
{
    return m_albums.size();
}

int MusicManager::artistTotal()
{
    return m_artists.size();
}


QSharedPointer<Music> MusicManager::addMusic(QString path_music)
{
    QDB<<QThread::currentThread();
    QList<QSharedPointer<Music>>::iterator pos;
    pos = std::find_if(m_musics.begin(),m_musics.end(),
                       [&](QSharedPointer<Music> &music){
            return music->path() == path_music;
    });
    if(pos == m_musics.end()){
        QSharedPointer<Music> music = QSharedPointer<Music>(new Music());
        music->setPath(path_music);
        music->setCover("qrc:/imgSrc/music.png");
        QFileInfo f(path_music);
        music->setName(f.fileName());
        QDB<<music->path();
        mutex.lock();
        m_musics << music;
        mutex.unlock();
        emit musicUpdate();
        emit startLoadData(music);
        return  music;
    }else{
        return  *pos;
    }
}

void MusicManager::removeMusic(QString path)
{
    SearchModel search;
    QFileInfo f(path);
    int index =  search.find_music_at(m_musics,path);
    if(index!=-1)
       m_musics.removeAt(index);
    QString path_folder = f.dir().path();
    foreach(QSharedPointer<Folder> folder, m_folders){
        if(folder->getPath() == path_folder){
            folder->removeMusic(path);
        }
    }
    emit listItemUpdate();
}

void MusicManager::setFolders(QList<QSharedPointer<Folder> > folders)
{
    m_folders << folders;
    foreach(QSharedPointer<Folder> folder, m_folders){
        foreach(QSharedPointer<Music> music , folder->musics()){
            m_musics << music;
            QSharedPointer<Album> album = this->addAlbum(music->album());
            QSharedPointer<Artist> artist = this->addArtist(music->artist());
            album->addMusic(music);
            artist->addMusic(music);
        }
    }
    emit listItemUpdate();
}

QSharedPointer<Folder> MusicManager::addFolder(QString path_folder)
{
    QList<QSharedPointer<Folder>>::iterator pos;
    pos = std::find_if(m_folders.begin(),m_folders.end(),
                       [&](QSharedPointer<Folder> &folder){
            return folder->getPath() == path_folder;
    });
    if(pos == m_folders.end()){
        QSharedPointer<Folder> folder = QSharedPointer<Folder>(new Folder());
        folder->setPath(path_folder);
        QDir d(path_folder);
        folder->setName(d.dirName());
        folder->setCover("qrc:/imgSrc/folder.png");
        QDB<<folder->name();
        mutex.lock();
        m_folders << folder;
        mutex.unlock();
        emit folderUpdate();
        return  folder;
    }else{
        return  *pos;
    }
}

QSharedPointer<Artist>  MusicManager::addArtist(QString name_artist)
{
    QList<QSharedPointer<Artist>>::iterator pos;
    pos = std::find_if(m_artists.begin(),m_artists.end(),
                       [&](QSharedPointer<Artist> &artist){
            return artist->name() == name_artist;
    });
    if(pos == m_artists.end()){
        QSharedPointer<Artist> artist = QSharedPointer<Artist>(new Artist());
        artist->setName(name_artist);
        artist->setCover("qrc:/imgSrc/artist.png");
        QDB<<artist->name();
        m_artists << artist;
        emit artistUpdate();
        return  artist;
    }else{
        return  *pos;
    }
}

QSharedPointer<Album> MusicManager::addAlbum(QString name_album)
{
    QList<QSharedPointer<Album>>::iterator pos;
    pos = std::find_if(m_albums.begin(),m_albums.end(),
                       [&](QSharedPointer<Album> &album){
            return album->name() == name_album;
    });
    if(pos == m_albums.end()){
        QSharedPointer<Album> album = QSharedPointer<Album>(new Album);
        album->setName(name_album);
        album->setCover("qrc:/imgSrc/album.png");
        QDB<<album->name();
        m_albums << album;
        emit albumUpdate();
        return  album;
    }else{
        return  *pos;
    }
}

int MusicManager::currentTab() const
{
    return m_currentTab;
}

void MusicManager::setCurrentTab(int currentTab)
{
    m_currentTab = currentTab;
    emit currentTabChanged();
}

QList<QSharedPointer<Music> >& MusicManager::musics()
{
    return m_musics;
}

QList<QSharedPointer<Folder> >& MusicManager::folders()
{
    return  m_folders;
}

QList<QSharedPointer<Album>>& MusicManager::albums()
{
    return m_albums;
}

QList<QSharedPointer<Artist>>& MusicManager::artists()
{
    return  m_artists;
}




