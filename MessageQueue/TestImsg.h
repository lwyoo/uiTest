#ifndef TESTIMSG_H
#define TESTIMSG_H

#include "MessageThread.h"
#include <QString>
#include <string>
#include <vector>
class TestImsg : public MessageThread::IMsg
{
public:
    TestImsg(QString objName, int posX, int posY, int myCount, int popupType);

    QString getObjName();
    int getPosX();
    int getPosY();
    int getMyCount();
    int getPopupType();


private:
    QString mObjName;
    int     mPosX;
    int     mPosY;
    int     mMyCount;
    int     mPopupType;
};

#endif // TESTIMSG_H
