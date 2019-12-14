#ifndef MUSICMODEL_H
#define MUSICMODEL_H
#include <QMutex>
#include <QAbstractListModel>
#include <QSharedPointer>
#include <QRegExp>
#include <QtAlgorithms>
#include "commondefine.h"
#include "model/musicmanager.h"
#include "model/folder.h"
#include "model/music.h"
class Indicator: public QObject{
    Q_OBJECT
    Q_PROPERTY(QString key READ key WRITE setKey NOTIFY keyChanged)
    Q_PROPERTY(int value READ value WRITE setValue NOTIFY valueChanged)
public:
    Indicator();
    virtual ~Indicator() {}
    QString key() const;
    void setKey(const QString &key);

    int value() const;
    void setValue(int value);
signals:
    void keyChanged();
    void valueChanged();
private:
    QString m_key;
    int m_value;
};

class MusicModel : public QAbstractListModel
{
    Q_OBJECT
    Q_ENUMS(ItemRoles)
    Q_PROPERTY(bool isSubItem READ isSubItem WRITE setIsSubItem NOTIFY isSubItemChanged)
    Q_PROPERTY(QList<QObject*> indicatorIndex READ indicatorIndex NOTIFY indicatorIndexChanged)
    Q_PROPERTY(bool isSelectOn READ selectOn WRITE setSelectOn NOTIFY isSelectOnChanged)
public:
    enum ItemRoles{
        name,
        cover,
        checked
    };
    MusicModel();
    virtual ~MusicModel();
    int rowCount(const QModelIndex & parent = QModelIndex()) const;
    QVariant data(const QModelIndex & index, int role = Qt::DisplayRole) const;
    QHash<int, QByteArray> roleNames() const;
    void setItems(QList<QSharedPointer<QObject>> items);
    void addItem(QSharedPointer<QObject> item);
    void clearItems();
    QList<QSharedPointer<QObject>> items();
    bool isSubItem() const;
    void setIsSubItem(bool isSubItem);
    void updateItems();
    void updateItem(int index);
    void itemChecked(int index);
    bool itemIsChecked(int index) const;
    void clearSlection();
    void setAllSlection();
    void sortItems();
    QList<QObject*> indicatorIndex() const;
    void setIndicatorIndex();
    QList<qint32> searchIndexOf(QString reg, int position = 1);
    bool selectOn() const;
    void setSelectOn(bool selectOn);
    void removeSelectItems();
    void removeItem(int index);
    QList<int> selectionIndex();
    void setSelectionIndex(const QList<int> &selectionIndex);

signals:
    void isSubItemChanged();
    void indicatorIndexChanged();
    void isSelectOnChanged();
private:
    QList<QSharedPointer<QObject>> m_items;
    bool m_isSubItem;
    QList<QObject*> m_indicatorIndex;
    QList<int> m_selectionIndex;
    bool m_selectOn;
 };

#endif // MUSICMODEL_H
