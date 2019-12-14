#include "model/loadfolder.h"
QMutex LoadingFolder::mutex;
LoadingFolder::LoadingFolder()
{ 
    qRegisterMetaType<QSharedPointer<Folder>>("QSharedPointer<Folder>");
    qRegisterMetaType<QSharedPointer<Music>>("QSharedPointer<Music>");
}

void LoadingFolder::setManager(MusicManager* manager)
{
    m_manager = manager;
}

void LoadingFolder::loadFolder(QString pathFolder)
{
    QElapsedTimer timer;
    timer.start();
    readDir(pathFolder);
    QDB<<timer.elapsed()<<"milliseconds";
    emit completeLoadFolder();
}

void LoadingFolder::readDir(QString pathFolder)
{
    QDB<<"loading: "+ pathFolder;
    QDir directory(pathFolder);
    QStringList listFolders = directory.entryList(QDir::NoDotAndDotDot|QDir::AllDirs);
    QStringList listSongs = directory.entryList(
                QStringList() << "*.mp3" << "*.MP3" <<"*.flac" <<"*.wav",
                QDir::Files);
    if(!listSongs.isEmpty()){
        QSharedPointer<Folder> folder = m_manager->addFolder(pathFolder);
        foreach(QString filename, listSongs) {
            QSharedPointer<Music> music = m_manager->addMusic(pathFolder+"/"+filename);
            folder->addMusic(music);
        }
    }
    foreach(QString folderName, listFolders) {
          readDir(pathFolder+"/"+folderName);
    }
}

QString LoadingFolder::folder() const
{
    return m_folder;
}

void LoadingFolder::setFolder(const QString &folder)
{
    m_folder = folder;
}


