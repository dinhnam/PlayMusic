#ifndef SEARCHMODEL_H
#define SEARCHMODEL_H

#include <QObject>
#include <QSharedPointer>
#include <QRegExp>
#include <QtAlgorithms>
#include "model/album.h"
#include "model/artist.h"
#include "model/folder.h"
#include "model/music.h"
class SearchModel : public QObject
{
    Q_OBJECT
public:
    SearchModel();
    int find_music_at(QList<QSharedPointer<Music>> &musics,QString music_path);
    template <class T>
    QList<QSharedPointer<QObject>> searchIndexOf(QList<QSharedPointer<T> > datas, QString reg, int position = 1);
};

template <class T>
QList<QSharedPointer<QObject> > SearchModel::searchIndexOf(QList<QSharedPointer<T> > datas, QString reg, int position){
     QList<QSharedPointer<QObject> > results;
     int index = -1;
     for(int i = 0; i < datas.count(); i++){
          index = datas[i]->name().indexOf(QRegExp(reg,Qt::CaseInsensitive, QRegExp::Wildcard),0);
          if(position == 0){
              if(index == 0) results << datas[i];
          }else{
              if(index != -1) results << datas[i];
          }

          index = -1;
     }
     return results;
}

#endif // SEARCHMODEL_H
