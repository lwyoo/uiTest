#include "TestImsg.h"


TestImsg::TestImsg(QString objName, int posX, int posY, int myCount, int popupType)
{
    mObjName =          objName;
    mPosX =             posX;
    mPosY =             posY;
    mMyCount =          myCount;
    mPopupType =        popupType;
}

QString TestImsg::getObjName()
{
    return mObjName ;
}

int TestImsg::getPosX()
{
    return mPosX ;

}

int TestImsg::getPosY() {

    return mPosY ;
}

int TestImsg::getMyCount()
{
    return mMyCount ;
}

int TestImsg::getPopupType()
{
    return mPopupType ;

}
