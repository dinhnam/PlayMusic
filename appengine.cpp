#include "appengine.h"

AppEngine* AppEngine::m_instance = nullptr;
QMutex AppEngine::mutex;
AppEngine::AppEngine(QObject *parent)
    : QObject(parent), m_initialized(false), m_app(nullptr)
{

}

AppEngine::~AppEngine()
{

}

AppEngine *AppEngine::instance()
{
    mutex.lock();
    if(m_instance == nullptr)
    {
        m_instance = new AppEngine();
    }
    mutex.unlock();

    return m_instance;
}

void AppEngine::initialize(QGuiApplication *app)
{
    mutex.lock();
    if(!m_initialized)
    {
        m_initialized = true;
        m_app = app;
        qmlRegisterType<QMediaPlayer>("QMediaPlayer.MediaStatus",1,0,"QMediaPlayer");
        HMIController::instance()->initialize(m_engine.rootContext());
        MusicController::instance()->initialize(m_engine.rootContext());
        m_myTrans = new MyTranslate(app);
        qmlRegisterType<MyLang>("MyLang",1,0,"MyLang");
        m_engine.rootContext()->setContextProperty("mytrans",m_myTrans);
        HMIController::instance()->showScreen(HOME_QML);
        m_engine.load(QUrl(QStringLiteral(MAIN_QML)));
    }
    mutex.unlock();
}

int AppEngine::exec()
{
    if(m_app != nullptr)
    {
        return m_app->exec();
    }
    return 0;
}
