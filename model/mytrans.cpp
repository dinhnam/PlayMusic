#include "mytrans.h"

MyTranslate::MyTranslate(QGuiApplication* app){
    m_app = app;
}

QString MyTranslate::emptyString()
{
    return "";
}

int MyTranslate::emptyNumber()
{
    return  0;
}

void MyTranslate::updateLanguage(int lang)
{
    switch (lang) {
        case MyLang::EN:
            m_trans.load("Trans_EN",":/translator");
            m_app->installTranslator(&m_trans);
            break;
        case MyLang::VI:
            m_trans.load("Trans_VI",":/translator");
            m_app->installTranslator(&m_trans);
            break;
    }
    emit languageUpdate();

}
