#include "searchmodel.h"

SearchModel::SearchModel()
{

}


int SearchModel::find_music_at(QList<QSharedPointer<Music>> &musics , QString music_path)
{
    for(int i=0;i<musics.size();i++){
        if(musics[i]->path() == music_path){
            return i;
        }
    }
    return  -1;
}

