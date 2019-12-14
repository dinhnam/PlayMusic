#include "model/musicmodel.h"

Indicator::Indicator()
{

}

QString Indicator::key() const
{
    return m_key;
}

void Indicator::setKey(const QString &key)
{
    m_key = key;
}

int Indicator::value() const
{
    return m_value;
}

void Indicator::setValue(int value)
{
    m_value = value;
}

MusicModel::MusicModel()
{
    m_isSubItem = false;
    m_selectOn = false;
}
MusicModel::~MusicModel()
{

}

void MusicModel::setItems(QList<QSharedPointer<QObject>> items)
{
    beginResetModel();
    m_items.clear();
    m_items = items;
    this->setIndicatorIndex();
    endResetModel();
}

void MusicModel::addItem(QSharedPointer<QObject> item)
{
   beginInsertRows(QModelIndex(),rowCount(),rowCount());
   m_items<<item;
   endInsertRows();
}

void MusicModel::clearItems()
{
   beginResetModel();
   m_items.clear();
   endResetModel();
}

QList<QSharedPointer<QObject> > MusicModel::items()
{
    return m_items;
}

bool MusicModel::isSubItem() const
{
    return m_isSubItem;
}

void MusicModel::setIsSubItem(bool isSubItem)
{
    m_isSubItem = isSubItem;
    emit isSubItemChanged();
}

void MusicModel::updateItems()
{
    beginResetModel();
    endResetModel();
}

void MusicModel::updateItem(int row_index)
{
   Q_UNUSED(row_index)
}

void MusicModel::itemChecked(int index)
{
   if(!itemIsChecked(index)){
       m_selectionIndex << index;
       std::sort(m_selectionIndex.begin(),m_selectionIndex.end());
   }else{
       m_selectionIndex.removeAt(m_selectionIndex.indexOf(index));
   }
   this->updateItems();
}

bool MusicModel::itemIsChecked(int index) const
{
    int i = m_selectionIndex.indexOf(index);
    return -1 != i;
}

void MusicModel::clearSlection()
{
     m_selectionIndex.clear();
     this->updateItems();
}

void MusicModel::setAllSlection()
{
    for(int i=0; i<m_items.count();i++){
        m_selectionIndex << i;
    }
    this->updateItems();
}

void MusicModel::sortItems(){
    qSort(m_items.begin(),m_items.end(),
          [=](const QSharedPointer<QObject> &s1,const QSharedPointer<QObject> &s2){
          QString name_1 = s1->property("name").toString();
          QString name_2 = s2->property("name").toString();
          bool compare = QString::compare(name_1, name_2,Qt::CaseInsensitive) < 0;
          return compare;
    });
    this->setIndicatorIndex();
}

QList<QObject*> MusicModel::indicatorIndex() const
{
    return m_indicatorIndex;
}

QList<qint32> MusicModel::searchIndexOf(QString reg, int position){
     QList<qint32> results;
     int index = -1;
     for(int i = 0; i < m_items.count(); i++){
          index = m_items.at(i)->property("name").toString().indexOf(
                      QRegExp(reg,Qt::CaseInsensitive, QRegExp::Wildcard),0);
          if(position == 0){
              if(index == 0) results << i;
          }else{
              if(index != -1) results << i;
          }
          index = -1;
     }
     return results;
}

bool MusicModel::selectOn() const
{
    return m_selectOn;
}

void MusicModel::setSelectOn(bool selectOn)
{
    m_selectOn = selectOn;
    emit isSelectOnChanged();
}

void MusicModel::removeSelectItems()
{
    for(int i=m_selectionIndex.count()-1;i>=0;i--){
         this->removeItem(m_selectionIndex.at(i));
    }
    this->clearSlection();
}

void MusicModel::removeItem(int index)
{
   beginRemoveRows(QModelIndex(),index,index);
   m_items.removeAt(index);
   endRemoveRows();
}

QList<int> MusicModel::selectionIndex()
{
    return m_selectionIndex;
}

void MusicModel::setSelectionIndex(const QList<int> &selectionIndex)
{
    m_selectionIndex = selectionIndex;
}

void MusicModel::setIndicatorIndex(){
    m_indicatorIndex.clear();
    QString key;
    QList<int> results;
    for(int i = 0;i<28;i++){
        if(i == 0){
            key = "0";
            results = this->searchIndexOf("[!-9]*",0);
        }else if(i== 27){
            key = "#";
            results = this->searchIndexOf("[^!-9a-zA-Z]*",0);
        }else{
           key = QChar(i+64);
           results = this->searchIndexOf(key+"*",0);
        }
        Indicator *indicator =  new Indicator();
        indicator->setKey(key);
        if(results.count() == 0){
            indicator->setValue(-1);
        }else {
           indicator->setValue(results[0]);
        }
        m_indicatorIndex.append(indicator);
    }
    emit indicatorIndexChanged();
}

int MusicModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return m_items.count();
}

QVariant MusicModel::data(const QModelIndex &index, int role) const
{
    if (index.row() < 0 || index.row() >= m_items.count())
        return QVariant();
    const QSharedPointer<QObject> item = m_items[index.row()];
    if (role == name)
        return item->property("name");
    if (role == cover)
        return item->property("cover");
    if (role == checked){
        return QVariant(this->itemIsChecked(index.row()));
    }
    return QVariant();
}
QHash<int, QByteArray> MusicModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[name] = "name";
    roles[cover] = "cover";
    roles[checked] = "checked";
    return roles;
}





