#ifndef RANDOMMUSIC_H
#define RANDOMMUSIC_H
#include <QRandomGenerator>
#include <QObject>
#include "commondefine.h"
class RandomMusic
{
public:
    RandomMusic();
    void addIndex(int index);
    void removeIndexOfList(int index);
    void clearIndex(int index);
    int getRandomIndex();
    void createListRandom(int lenght);
    bool listIsEmpty();
    QList<int> getListIndex() const;

private:
    QList<int> m_listIndex;
};

#endif // RANDOMMUSIC_H
