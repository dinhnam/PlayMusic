#include "controller/hmicontroller.h"
HMIController* HMIController::m_instance = nullptr;
QMutex HMIController::mutex;
HMIController::HMIController(QObject *parent):
    QObject(parent), m_initialized(false)
{

}

HMIController *HMIController::instance()
{
    mutex.lock();
    if(m_instance == nullptr){
        m_instance = new HMIController();
    }
    mutex.unlock();
    return m_instance;
}

void HMIController::initialize(QQmlContext *context)
{
    mutex.lock();
    if(!m_initialized)
    {
        m_initialized = true;
        context->setContextProperty("HMIController", this);
        context->setContextProperty("HMIModel", &m_hmiModel);
    }
    mutex.unlock();
}

HMIModel &HMIController::hmiModel()
{
   return m_hmiModel;
}
void HMIController::showScreen(const QString &screen)
{

    m_hmiModel.pushScreen(screen);
    QDB << screen;
}
void HMIController::showPopup(const QString &screen)
{
    QDB << screen;
    if(screen != m_hmiModel.topPopup()){
         m_hmiModel.pushPopup(screen);
    }

}

void HMIController::exitScreen()
{
    if(!m_hmiModel.isEmptyPopup()){
        m_hmiModel.popPopup();
    }
    else{
        m_hmiModel.popScreen();
    }
}

void HMIController::exitAllScreen(const QString &screen)
{
    m_hmiModel.resetScreen(screen);
    QDB<<screen;
}



