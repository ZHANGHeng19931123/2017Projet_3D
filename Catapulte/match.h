#ifndef MATCH_H
#define MATCH_H

#include <QTime>
#include <list>
#include "throw.h"

using namespace std;

class Match
{
public:
    Match();
    Match(string playerName, int nbThrow, int level);
    void addThrow(Throw * t){throwList.push_back(t);}
    void setName(string playerName){this->playerName = playerName;}
    void setScore(float totalScore){this->totalScore = totalScore;}
    int getLevel(){return level;}
    int getNbThrow(){return nbThrow;}
    int getThrowListSize(){return throwList.size();}
    void addScore(float score){totalScore += score;}
    float getTotalScore(){return totalScore;}
    QString toQString(){return "Player:"+QString::fromStdString(playerName)
                +"\nScore:"+QString::number(totalScore);}
    string getPlayerName(){return playerName;}
private:
    string playerName = "NULL";
    int nbThrow = 0;
    float totalScore = 0;
    int level = 0;
    QTime time = QTime::currentTime();
    list<Throw*> throwList;
};

#endif // MATCH_H
