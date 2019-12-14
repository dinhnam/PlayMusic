#ifndef MUSICCONTROLLER_H
#define MUSICCONTROLLER_H
#include "commondefine.h"
#include <QObject>
#include <QMutex>
#include <QQmlContext>
#include <QSharedPointer>
#include "model/musicmodel.h"
#include "model/playlistmodel.h"
#include "model/searchmodel.h"
#include "model/jsonmanager.h"
class MusicController : public QObject
{
    Q_OBJECT

private:
    explicit MusicController(QObject *parent = nullptr);
public:
    static MusicController *instance();
    void initialize(QQmlContext* context);
    Q_INVOKABLE void showFolders();
    Q_INVOKABLE void showAlbums();
    Q_INVOKABLE void showArtists();
    Q_INVOKABLE void showMusics(QList<QSharedPointer<Music>> musics);
    Q_INVOKABLE void showPlayList();
    Q_INVOKABLE void openItemAt(int index);
    Q_INVOKABLE void openTabAt(int index);
    Q_INVOKABLE void openDialogFolder();
    Q_INVOKABLE void openSelectFiles();
    Q_INVOKABLE void searchItems(QString name);
    Q_INVOKABLE void checkItem(int index);
    Q_INVOKABLE void checkAllItem(int index);
    Q_INVOKABLE void clearSlections();
    Q_INVOKABLE void removeItemInModel();
    Q_INVOKABLE void removeMusicInPlaylsit();
    Q_INVOKABLE void next(int count);
    Q_INVOKABLE void setMusicPosition(qint64 position);
    Q_INVOKABLE void setCurrentIndex(int index);
    Q_INVOKABLE void setMusicRule(unsigned char rule);
    Q_INVOKABLE void setMusicVolume(int volume);
    Q_INVOKABLE void addMusicAtItem(QSharedPointer<QObject> item);
    Q_INVOKABLE void addMusicToPlaylsit();
    Q_INVOKABLE void play();
    Q_INVOKABLE void wirteFileJson();
    Q_INVOKABLE void readFileJson();
public slots:
    void onlistItemUpdate();
signals:
    void addMusic(QSharedPointer<Music> music);
private:
    static MusicController *m_instance;
    bool m_initialized;
    static QMutex mutex;
    MusicModel m_musicModel;
    PlayListModel m_playlist;
    MusicManager m_musicManager;
    SearchModel m_searchModel;
    JsonManager m_jsonManager;
};

#endif // MUSICCONTROLLER_H
