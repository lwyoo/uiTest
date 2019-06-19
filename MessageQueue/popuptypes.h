#ifndef POPUPTYPES_H
#define POPUPTYPES_H

#include <QString>

struct PopupItemItem {
    QString popupType;
    QString requestType;
    QString data;

};

struct PopupTestItem {
    QString objName;
    int posX;
    int posY;
    int myCount;
    int popupType;
};

#endif // POPUPTYPES_H
