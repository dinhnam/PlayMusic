#include "item.h"

Item::Item(QObject *parent) : QObject(parent)
{

}

QString Item::name() const
{
    return m_name;
}

void Item::setName(const QString &name)
{
    if(m_name!=name){
        m_name = name;
        emit nameChanged();
    }
}

QString Item::cover() const
{
    return m_cover;
}

void Item::setCover(const QString &cover)
{
    if(m_cover!=cover){
        m_cover = cover;
        emit coverChanged();
    }
}

