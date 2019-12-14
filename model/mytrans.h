#ifndef MYTRANS_H
#define MYTRANS_H

#include <QObject>
#include <QTranslator>
#include <QGuiApplication>
#include "model/Mylang.h"
class MyTranslate : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString emptyString READ emptyString NOTIFY languageUpdate)
    Q_PROPERTY(int emptyNumber READ emptyNumber NOTIFY languageUpdate)
public:
    MyTranslate(QGuiApplication* app);
    Q_INVOKABLE QString emptyString();
    Q_INVOKABLE int emptyNumber();
    virtual ~MyTranslate() {}
signals:
    void languageUpdate();
public slots:
    void updateLanguage(int lang);
private:
    QGuiApplication* m_app;
    QTranslator m_trans;
};

#endif // MYTRANS_H
