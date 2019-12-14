#ifndef APPENGINE_H
#define APPENGINE_H
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QMutex>
#include <commondefine.h>
#include <QQmlEngine>
#include <QMediaPlayer>
#include <controller/hmicontroller.h>
#include <controller/musiccontroller.h>
#include "model/loadfolder.h"
#include "model/mytrans.h"
class AppEngine : public QObject
{
    Q_OBJECT

private:
    explicit AppEngine(QObject *parent = nullptr);

public:
    ~AppEngine();
    static AppEngine *instance();
    void initialize(QGuiApplication* app);
    int exec();

private:
    static AppEngine* m_instance;
    bool m_initialized;
    static QMutex mutex;
    QGuiApplication* m_app;
    QQmlApplicationEngine m_engine;
    MyTranslate* m_myTrans;
};

#endif // APPENGINE_H
