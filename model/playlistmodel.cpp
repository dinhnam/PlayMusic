#include "playlistmodel.h"
PlayListModel::PlayListModel()
{
    m_playRule = 1;
    m_volume = 100;
    m_currentIndex = 0;
    m_mediaplayer = new QMediaPlayer;
    connect(m_mediaplayer,SIGNAL(mediaStatusChanged(QMediaPlayer::MediaStatus)),
            this,SLOT(onMediaStatusChanged(QMediaPlayer::MediaStatus)));
    connect(m_mediaplayer,SIGNAL(positionChanged(qint64)),
            this, SLOT(onPositionChanged(qint64)));
    connect(m_mediaplayer, SIGNAL(stateChanged(QMediaPlayer::State)),
            this, SLOT(onStateChanged(QMediaPlayer::State)));
    connect(m_mediaplayer, SIGNAL(durationChanged(qint64)),
            this, SLOT(onDurationChanged(qint64)));
}
PlayListModel::~PlayListModel()
{

}

void PlayListModel::init()
{
    m_currentIndex = 0;
    m_duration = 0;
    m_position = 0;
    this->setState(0);
    this->setStatus(0);
}

void PlayListModel::addMusic(QSharedPointer<Music> music)
{
    QDB<<music->path();
    m_musics<<music;
    if(m_musics.count()==1){
        this->init();
        this->setCurrentIndex(0);
        this->loadMusic();
    }
    m_randomMusic.addIndex(m_musics.size()-1);
}

void PlayListModel::removeMusic(int index)
{
    m_musics.removeAt(index);
    if(index <= m_currentIndex){
        if(m_musics.count() == 0){
            m_mediaplayer->setMedia(QUrl::fromLocalFile(""));
        }else{
            if(index == m_currentIndex){
                this->setCurrentIndex(m_currentIndex-1);
                this->loadMusic();
            }else{
                this->setCurrentIndex(m_currentIndex-1);
            }
        }
    }
    m_randomMusic.clearIndex(index);
}

void PlayListModel::loadMusic()
{
    Music *music = m_musics.at(m_currentIndex).get();
    QString path_music = music->path();
    QUrl url = QUrl::fromLocalFile(path_music);
    m_mediaplayer->setMedia(url);
}

void PlayListModel::playMusic()
{
    QDB<< "play";
    m_mediaplayer->play();
}

void PlayListModel::pauseMusic()
{
    QDB<< "pause";
    m_mediaplayer->pause();
}

void PlayListModel::stopMusic()
{
    QDB<< "stop";
    m_mediaplayer->stop();
}

unsigned char PlayListModel::getPlayRule() const
{
    return m_playRule;
}

void PlayListModel::setPlayRule(unsigned char rules)
{
    m_playRule  = rules;
    QDB<<m_playRule;
    emit playRuleChanged();
}


void PlayListModel::onDurationChanged(qint64 duration)
{
    QDB<<duration;
    m_duration = duration;
    emit durationChanged();
}

void PlayListModel::onPositionChanged(qint64 position)
{
    m_position = position;
    emit positionChanged();
}

void PlayListModel::onStateChanged(QMediaPlayer::State state)
{
    this->setState(state);
}

void PlayListModel::autoNextMusic()
{
    if(m_currentIndex >= m_musics.size()-1){
        this->setCurrentIndex(0);
        this->loadMusic();
        if(m_playRule&repeat){
            this->playMusic();
        }
    }else{
        this->setCurrentIndex(m_currentIndex+1);
        this->loadMusic();
        this->playMusic();
    }
}

void PlayListModel::shuffleMusic()
{
    if(!m_randomMusic.listIsEmpty()){
        int randIndex = m_randomMusic.getRandomIndex();
        this->setCurrentIndex(randIndex);
        this->loadMusic();
        this->playMusic();
    }else {
        m_randomMusic.createListRandom(m_musics.size());
        if(m_playRule&repeat){
            int randIndex = m_randomMusic.getRandomIndex();
            this->setCurrentIndex(randIndex);
            this->loadMusic();
            this->playMusic();
        }
    }
}

void PlayListModel::removeSelctMusics(QList<int> selections)
{
    for(int i = selections.count()-1;i>=0;i--){
        this->removeMusic(selections.at(i));
    }
}

void PlayListModel::onMediaStatusChanged(QMediaPlayer::MediaStatus status)
{
    QDB<<status;
    if(status == QMediaPlayer::EndOfMedia){
        if((m_playRule&repeatone) == repeatone){
            this->setPosition(0);
            this->playMusic();
        }else{
            if(m_playRule&shuffle){
                shuffleMusic();
            }else{
                autoNextMusic();
            }
        }

    }
    this->setStatus(status);
}

QString PlayListModel::getMusicTitle()
{
    QString title = "";
    if(m_musics.count()>0){
        title = m_musics.at(m_currentIndex)->title();
        if(title == ""){
            title = m_musics.at(m_currentIndex)->name();
        }
    }

    return title;
}


QList<QSharedPointer<Music> > PlayListModel::getMusics()
{
    return m_musics;
}

void PlayListModel::setMusics(const QList<QSharedPointer<Music> > &musics)
{
    m_musics = musics;
    m_randomMusic.createListRandom(m_musics.size());
}

int PlayListModel::getVolume() const
{
    return m_volume;
}

void PlayListModel::setVolume(int volume)
{
    if(volume>=0 && volume<=100 && volume != m_volume){
        if(m_volume != volume){
            m_volume = volume;
            m_mediaplayer->setVolume(volume);
            emit volumeChanged();
        }
    }
    QDB<<m_volume;
}

int PlayListModel::getCurrentIndex() const
{
    return m_currentIndex;
}

void PlayListModel::setCurrentIndex(int currentIndex)
{
    if(!m_musics.isEmpty()){
        if(currentIndex>= 0 && currentIndex < m_musics.size())
        {
            m_currentIndex = currentIndex;
            QDB<<currentIndex;
            emit currentIndexChanged();
        }
    }
}

int PlayListModel::getState() const
{
    return m_state;
}

void PlayListModel::setState(int state)
{
    QDB<<state;
    if(m_state!=state){
        m_state = state;
        emit stateChanged();
    }

}

qint64 PlayListModel::getDuration() const
{
    return m_duration;
}

void PlayListModel::setDuration(const qint64 &duration)
{
    QDB<<duration;
    if(m_duration!=duration){
        m_duration = duration;
        emit durationChanged();
    }

}

qint64 PlayListModel::position() const
{
    return m_position;
}

void PlayListModel::setPosition(const qint64 &position)
{
    if(position>=0 && position<=m_duration){
        if(m_position!=position){
            m_position = position;
            m_mediaplayer->setPosition(position);
            emit positionChanged();
        }
    }
}

int PlayListModel::status() const
{
    return m_status;
}

void PlayListModel::setStatus(int status)
{
    QDB<<status;
    m_status = status;
    emit statusChanged();
}


