#ifndef HMICONTROLLER_H
#define HMICONTROLLER_H
#include "commondefine.h"
#include <QObject>
#include <QMutex>
#include <QQmlContext>
#include "model/hmimodel.h"
class HMIController : public QObject
{
    Q_OBJECT
private:
    explicit HMIController(QObject *parent = nullptr);
public:
    HMIModel& hmiModel();
    static HMIController *instance();
    void initialize(QQmlContext* context);
    Q_INVOKABLE void showScreen(const QString &screen);
    Q_INVOKABLE void showPopup(const QString &screen);
    Q_INVOKABLE void exitScreen();
    Q_INVOKABLE void exitAllScreen(const QString &screen);
signals:

public slots:

private:
    static HMIController *m_instance;
    bool m_initialized;
    static QMutex mutex;
    HMIModel m_hmiModel;
};


#endif // HMICONTROLLER_H


