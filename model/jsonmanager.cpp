#include "jsonmanager.h"

JsonManager::JsonManager()
{

}

void JsonManager::wirteFile(QList<QSharedPointer<Folder> > &folders)
{
    QDir dir;
    QFile file(QStringLiteral("save.json"));
    file.open(QIODevice::WriteOnly);
    QJsonArray jsonArrayFolders;
    foreach (QSharedPointer<Folder> folder, folders) {
        QJsonObject jsonFolder;
        QJsonArray jsonArrayMusics;
        jsonFolder["name"] = folder->name();
        jsonFolder["path"] = folder->getPath();
        jsonFolder["cover"] = folder->cover();
        foreach(QSharedPointer<Music> music, folder->musics() ){
           QJsonObject jsonMusic;
           jsonMusic["name"] = music->name();
           jsonMusic["path"] = music->path();
           jsonMusic["cover"] = music->cover();
           jsonMusic["title"] = music->title()==""?"unknow":music->title();
           jsonMusic["album"] = music->album()==""?"unknow":music->album();
           jsonMusic["artist"] = music->artist()==""?"unknow":music->artist();
           jsonArrayMusics.push_back(jsonMusic);
        }
        jsonFolder["Musics"] = jsonArrayMusics;
        jsonArrayFolders.push_back(jsonFolder);
    }
    QJsonDocument doc(jsonArrayFolders);
    file.write(doc.toJson());
    QDB<<"save: "<<dir.current().path();
    emit wirteComplete();
}

QList<QSharedPointer<Folder> > JsonManager::readFile()
{
    QDB<<"read save.json";
    QList<QSharedPointer<Folder> > folders;
    if(QFileInfo::exists("save.json") == false) return folders;
    QFile file(QStringLiteral("save.json"));
    file.open(QIODevice::ReadOnly);
    QByteArray saveData = file.readAll();
    QJsonDocument doc(QJsonDocument::fromJson(saveData));
    QJsonArray jsonFolders = doc.array();
    for(int i=0;i<jsonFolders.size();i++){
        folders << getFolder(jsonFolders[i].toObject());
    }
    return  folders;
}

QSharedPointer<Folder> JsonManager::getFolder(QJsonObject jsonFolder)
{
    QDB<<jsonFolder["path"].toString();
    QSharedPointer<Folder> folder = QSharedPointer<Folder>(new Folder());
    folder->setName(jsonFolder["name"].toString());
    folder->setPath(jsonFolder["path"].toString());
    folder->setCover(jsonFolder["cover"].toString());
    QJsonArray jsonMusics = jsonFolder["Musics"].toArray();
    for(int i = 0;i<jsonMusics.size();i++){
       QJsonObject jsonMusic;
       jsonMusic = jsonMusics[i].toObject();
       folder->addMusic(getMusic(jsonMusic));
    }
    return  folder;
}

QSharedPointer<Music> JsonManager::getMusic(QJsonObject jsonMusic)
{
    QDB<<jsonMusic["name"].toString()<<jsonMusic["album"].toString();
    QSharedPointer<Music> music = QSharedPointer<Music>(new Music());
    music->setName(jsonMusic["name"].toString());
    music->setPath(jsonMusic["path"].toString());
    music->setCover(jsonMusic["cover"].toString());
    music->setAlbum(jsonMusic["album"].toString());
    music->setArtist(jsonMusic["artist"].toString());
    music->setTitle(jsonMusic["title"].toString());
    return  music;
}

