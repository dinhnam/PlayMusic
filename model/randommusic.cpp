#include "randommusic.h"

RandomMusic::RandomMusic()
{

}

void RandomMusic::addIndex(int index)
{
    m_listIndex << index;
}

void RandomMusic::removeIndexOfList(int index)
{
    int index_at_value = m_listIndex.indexOf(index);
    if(index_at_value>-1){
        m_listIndex.removeAt(index_at_value);
    }
}

void RandomMusic::clearIndex(int index)
{
    int index_at_value = m_listIndex.indexOf(index);
    if(index_at_value>-1){
        m_listIndex.removeAt(index_at_value);
        if(index_at_value < m_listIndex.count()-1)
            for(int i = index_at_value;i<m_listIndex.count();i++){
                m_listIndex[i] = m_listIndex[i]-1;
            }
    }
}

int RandomMusic::getRandomIndex()
{
    int randomIndex;
    if(m_listIndex.count() > 1){
        int random = QRandomGenerator::system()->bounded(0,m_listIndex.count()-1);
        randomIndex = m_listIndex[random];
        m_listIndex.removeAt(random);
    }else{
        randomIndex = m_listIndex[0];
        m_listIndex.clear();
    }
    return randomIndex;
}

void RandomMusic::createListRandom(int lenght)
{
    m_listIndex.clear();
    for(int i=0;i<lenght;i++){
       addIndex(i);
    }
}

bool RandomMusic::listIsEmpty()
{
    return m_listIndex.empty();
}

QList<int> RandomMusic::getListIndex() const
{
    return m_listIndex;
}

