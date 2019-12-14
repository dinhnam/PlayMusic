#include "controller/musiccontroller.h"

MusicController* MusicController::m_instance = nullptr;
QMutex MusicController::mutex;
MusicController::MusicController(QObject *parent):
    QObject(parent), m_initialized(false)
{

}

MusicController *MusicController::instance()
{
    mutex.lock();
    if(m_instance == nullptr){
        m_instance = new MusicController();
    }
    mutex.unlock();
    return m_instance;
}

void MusicController::initialize(QQmlContext *context)
{
    mutex.lock();
    if(!m_initialized)
    {
        m_initialized = true;
        connect(&m_musicManager,&MusicManager::listItemUpdate,this,&MusicController::onlistItemUpdate);
        m_musicManager.setCurrentTab(0);
        m_playlist.init();
        context->setContextProperty("MusicController", this);
        context->setContextProperty("MusicModel", &m_musicModel);
        context->setContextProperty("PlayListModel", &m_playlist);
        context->setContextProperty("MusicManager", &m_musicManager);
        context->setContextProperty("JsonManager", &m_jsonManager);
    }
    mutex.unlock();
}

void MusicController::setMusicPosition(qint64 position)
{
    if(position>m_playlist.getDuration()){
        position = m_playlist.getDuration();
    }
    if(position<0){
        position = 0;
    }
    m_playlist.setPosition(position);
}

void MusicController::setCurrentIndex(int index)
{
    m_playlist.setCurrentIndex(index);
    m_playlist.loadMusic();
    m_playlist.playMusic();
}

void MusicController::play()
{
   if(m_playlist.getState() == QMediaPlayer::StoppedState || m_playlist.getState() == QMediaPlayer::PausedState){
       m_playlist.playMusic();
   }else{
       m_playlist.pauseMusic();
   }
}

void MusicController::wirteFileJson()
{
    m_jsonManager.wirteFile(m_musicManager.folders());
}

void MusicController::readFileJson()
{
    m_musicManager.setFolders(m_jsonManager.readFile());
}


void MusicController::next(int count)
{
    int lastState = m_playlist.getState();
    if(m_playlist.getCurrentIndex() == 0 && count == -1){
        m_playlist.pauseMusic();
        m_playlist.setPosition(0);
    }else{
        int nextIndex = m_playlist.getCurrentIndex()+count;
        if(nextIndex < 0) nextIndex = m_playlist.getMusics().count()-1;
        if(nextIndex >=  m_playlist.getMusics().count()) nextIndex = 0;
        m_playlist.setCurrentIndex(nextIndex);
        m_playlist.loadMusic();
    }
    if(lastState == QMediaPlayer::PlayingState){
        m_playlist.stopMusic();
        m_playlist.playMusic();
    }

}

void MusicController::setMusicRule(unsigned char rule)
{
    unsigned char rules = m_playlist.getPlayRule();
    if(rule<=m_playlist.repeatone){
        rules = (rules&4)|rule;
    }else{
        rules = rules^rule;
    }
    m_playlist.setPlayRule(rules);
}


void MusicController::setMusicVolume(int volume)
{
    m_playlist.setVolume(volume);
}

void MusicController::showFolders()
{
    m_musicModel.clearItems();

    foreach (QSharedPointer<Folder> folder, m_musicManager.folders()) {
        if(folder->musics().size() == 0){
            m_musicManager.folders().removeOne(folder);
        }else{
            m_musicModel.addItem(folder);
        }

    }
    m_musicModel.sortItems();
    m_musicModel.updateItems();
}

void MusicController::showAlbums()
{
    m_musicModel.clearItems();
    foreach (QSharedPointer<Album> album, m_musicManager.albums()) {
        if(album->musics().size() == 0){
            m_musicManager.albums().removeOne(album);
        }else{
            m_musicModel.addItem(album);
        }
    }
    m_musicModel.sortItems();
    m_musicModel.updateItems();
}

void MusicController::showArtists()
{
    m_musicModel.clearItems();
    foreach (QSharedPointer<Artist> artist, m_musicManager.artists()) {
        if(artist->musics().size() == 0){
            m_musicManager.artists().removeOne(artist);
        }else{
            m_musicModel.addItem(artist);
        }
    }
    m_musicModel.sortItems();
    m_musicModel.updateItems();
}

void MusicController::showMusics(QList<QSharedPointer<Music>> musics)
{
    m_musicModel.clearItems();
    foreach (QSharedPointer<Music> music, musics) {
        m_musicModel.addItem(music);
    }
    m_musicModel.sortItems();
    m_musicModel.updateItems();
}

void MusicController::showPlayList()
{
    QDB<<"show playlist";
    m_musicModel.clearItems();
    foreach (QSharedPointer<Music> music, m_playlist.getMusics()) {
        m_musicModel.addItem(music);
    }
}

void MusicController::openItemAt(int index)
{
    QSharedPointer<QObject> item = m_musicModel.items()[index];
    QString class_name = item->metaObject()->className();
    QDB<<"open "<<class_name;
    if(class_name == "Folder"){
        QSharedPointer<Folder> folder = qSharedPointerCast<Folder>(item);
        this->showMusics(folder->musics());
        m_musicModel.setIsSubItem(true);
    }
    if(class_name == "Artist"){
        QSharedPointer<Artist> artist = qSharedPointerCast<Artist>(item);
        this->showMusics(artist->musics());
        m_musicModel.setIsSubItem(true);
    }
    if(class_name == "Album"){
        QSharedPointer<Album> album = qSharedPointerCast<Album>(item);
        this->showMusics(album->musics());
        m_musicModel.setIsSubItem(true);
    }
    if(class_name == "Music"){
        QSharedPointer<Music> music = qSharedPointerCast<Music>(item);
        m_playlist.addMusic(music);
    }
}

void MusicController::openTabAt(int index)
{
    switch (index) {
        case 0: showMusics(m_musicManager.musics());break;
        case 1: showFolders();break;
        case 2: showAlbums();break;
        case 3: showArtists();break;
    }
    m_musicModel.setIsSubItem(false);
}

void MusicController::openDialogFolder()
{
    m_musicManager.openFolder();
}

void MusicController::openSelectFiles()
{
    m_musicManager.selectFiles();
}


void MusicController::searchItems(QString name)
{
   QList<QSharedPointer<QObject>> resutls;
   resutls << m_searchModel.searchIndexOf<Folder>(m_musicManager.folders(),"*"+name+"*");
   resutls << m_searchModel.searchIndexOf<Album>(m_musicManager.albums(),"*"+name+"*");
   resutls << m_searchModel.searchIndexOf<Artist>(m_musicManager.artists(),"*"+name+"*");
   resutls << m_searchModel.searchIndexOf<Music>(m_musicManager.musics(),"*"+name+"*");
   m_musicModel.setItems(resutls);
   m_musicModel.clearSlection();
}

void MusicController::checkItem(int index)
{
    m_musicModel.itemChecked(index);
}

void MusicController::checkAllItem(int index)
{
   if(m_musicModel.itemIsChecked(index)){
       m_musicModel.clearSlection();
   }else{
       m_musicModel.setAllSlection();
   }
}

void MusicController::clearSlections()
{
    m_musicModel.clearSlection();
    m_musicModel.setSelectOn(false);
}

void MusicController::removeItemInModel()
{

    if(m_musicModel.selectOn() == false){
        m_musicModel.setSelectOn(true);
    }else{
        foreach(int i, m_musicModel.selectionIndex()){
             QSharedPointer<QObject> item = m_musicModel.items().at(i);
             m_musicManager.removeMusic(item->property("path").toString());
        }
        m_musicModel.clearSlection();
        m_musicModel.setSelectOn(false);
    }
}

void MusicController::removeMusicInPlaylsit()
{
    if(m_musicModel.selectOn() == false){
        m_musicModel.setSelectOn(true);
    }else{
        m_playlist.removeSelctMusics(m_musicModel.selectionIndex());
        m_musicModel.removeSelectItems();
        m_musicModel.setSelectOn(false);
    }

}

void MusicController::addMusicAtItem(QSharedPointer<QObject> item)
{
    QString class_name = item->metaObject()->className();
    if(class_name == "Folder"){
        QDB<< "Add Folder to playlist";
        QSharedPointer<Folder> folder = qSharedPointerCast<Folder>(item);
        foreach(QSharedPointer<Music> music, folder->musics()){
            m_playlist.addMusic(music);
        }
    }
    if(class_name == "Artist"){
        QDB<< "Add Artist to playlist";
        QSharedPointer<Artist> aritst = qSharedPointerCast<Artist>(item);
        foreach(QSharedPointer<Music> music, aritst->musics()){
            m_playlist.addMusic(music);
        }
    }
    if(class_name == "Album"){
        QDB<< "Add Album to playlist";
        QSharedPointer<Album> album = qSharedPointerCast<Album>(item);
        foreach(QSharedPointer<Music> music, album->musics()){
            m_playlist.addMusic(music);
        }
    }
    if(class_name == "Music"){
        QDB<< "Add Music to playlist";
        QSharedPointer<Music> music = qSharedPointerCast<Music>(item);
        m_playlist.addMusic(music);
    }
}

void MusicController::addMusicToPlaylsit()
{
    if(m_musicModel.selectOn() == false){
        m_musicModel.setSelectOn(true);
    }else{
        foreach(int index, m_musicModel.selectionIndex()){
            QSharedPointer<QObject> item = m_musicModel.items().at(index);
            this->addMusicAtItem(item);
        }
        m_musicModel.setSelectOn(false);
        m_musicModel.clearSlection();
    }
}

void MusicController::onlistItemUpdate()
{
    this->openTabAt(m_musicManager.currentTab());
}



