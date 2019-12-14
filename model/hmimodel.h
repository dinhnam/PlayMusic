#ifndef HMIMODEL_H
#define HMIMODEL_H
#include "commondefine.h"
#include <QObject>
#include <QMutex>
#include <QStack>
class HMIModel : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString currentScreen READ topScreen NOTIFY currentScreenChanged)
    Q_PROPERTY(QString currentPopup READ topPopup NOTIFY currentPopupChanged)
public:
    explicit HMIModel(QObject *parent = nullptr);
    QString topScreen();
    void popScreen();
    void pushScreen(const QString &currentScreen);
    QString topPopup();
    void popPopup();
    void pushPopup(const QString &currentPopup);
    void resetScreen(const QString &screen);
    bool isEmptyPopup();

signals:
    void currentScreenChanged();
    void currentPopupChanged();
public slots:
private:
    QStack<QString> m_popups;
    QStack<QString> m_screens;
};
#endif // HMIMODEL_H
