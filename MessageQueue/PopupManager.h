#ifndef MYQUICKITEM_H
#define MYQUICKITEM_H

#include <QQuickItem>
#include <QQuickView>
#include <QQmlIncubator>
#include <QGuiApplication>

#include <QDebug>

#include <QMap>
using ObjectName = QString;
class PopupManager : public QQuickItem
{
    Q_OBJECT
public:
    static QSharedPointer<PopupManager> instance(QQuickItem *parent=Q_NULLPTR);
    void destroyTest(const QString objectName);
    ~PopupManager();

    bool findView();
    bool settingQmlEngine();
    bool createComponent(const QString objectName);
    bool createComponent(const QString objectName, const qreal posX, const qreal posY);
    bool removeComponent(const QString objectName);

    void printMapData();

    void connectionSignal();

    bool requestCreateComponent(const QString objectName, const qreal posX, const qreal posY);

private:
    explicit PopupManager(QQuickItem *parent=Q_NULLPTR);

signals:
    void signalCreateComponent(const QString objectName, const qreal posX, const qreal posY);

public slots:
    void slotCreateComponent(const QString objectName, const qreal posX, const qreal posY);

private:
    QQuickItem* mItem;
    QQmlEngine* mEngine;
    QQuickView* mView;
    QMap<ObjectName, QQuickItem*> mTest;

};

#endif // MYQUICKITEM_H
