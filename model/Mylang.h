#ifndef MYLANG_H
#define MYLANG_H
#include <QObject>
#include <QLocale>
class MyLang : public QObject
{
    Q_OBJECT
    Q_ENUMS(Languages)
public:
    enum Languages{
        EN = QLocale::English,
        VI = QLocale::Vietnamese,
        JP = QLocale::Japanese
    };
    MyLang() {}
    virtual ~MyLang() {}
};
#endif // MYLANG_H
