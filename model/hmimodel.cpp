#include "model/hmimodel.h"
HMIModel::HMIModel(QObject *parent):QObject(parent)
{

}
QString HMIModel::topScreen()
{
      if(!m_screens.isEmpty())
           return m_screens.top();
      else
           return  "";
}
void HMIModel::popScreen()
{
    if(m_screens.count()>1){
        m_screens.pop();
        emit currentScreenChanged();
    }
}

void HMIModel::pushScreen(const QString &currentScreen)
{
    if(m_screens.isEmpty()){
        m_screens.push(currentScreen);
    }else if(m_screens.top()!=currentScreen){
        m_screens.push(currentScreen);
        emit currentScreenChanged();
    }
}

QString HMIModel::topPopup()
{
    if(!m_popups.isEmpty())
       return m_popups.top();
    else
       return "";
}

void HMIModel::popPopup()
{
    if(!m_popups.isEmpty()){
        m_popups.pop();
        emit currentPopupChanged();
    }
}

void HMIModel::pushPopup(const QString &currentPopup)
{
    m_popups.push(currentPopup);
    emit currentPopupChanged();
    QDB<<currentPopup;
}

void HMIModel::resetScreen(const QString &screen){
   m_popups.clear();
   m_screens.clear();
   m_screens.push(screen);
   emit currentPopupChanged();
   emit currentScreenChanged();
   QDB<<screen;
}

bool HMIModel::isEmptyPopup()
{
    return m_popups.isEmpty();
}

