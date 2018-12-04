#ifndef MYQUICKITEM_H
#define MYQUICKITEM_H

#include <QQuickItem>
#include <QQuickView>
#include <QQmlIncubator>
#include <QGuiApplication>

#include <QDebug>

#include <QMap>
using ObjectName = QString;
class MyQuickItem : public QQuickItem
{
    Q_OBJECT
public:
    static QSharedPointer<MyQuickItem> instance(QQuickItem *parent=Q_NULLPTR);
    void destroyTest(const QString objectName);
    ~MyQuickItem();

    bool findView();
    bool settingQmlEngine();
    bool createComponent(const QString objectName);
    bool createComponent(const QString objectName, const qreal posX, const qreal posY);
    bool removeComponent(const QString objectName);

    void printMapData();

private:
    explicit MyQuickItem(QQuickItem *parent=Q_NULLPTR);

private:
    QQuickItem* mItem;
    QQmlEngine* mEngine;
    QQuickView* mView;
    QMap<ObjectName, QQuickItem*> mTest;

};

#endif // MYQUICKITEM_H
