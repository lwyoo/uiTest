#ifndef MYQUICKITEM_H
#define MYQUICKITEM_H

#include <QQuickItem>
#include <QQuickView>
#include <QQmlIncubator>
#include <QGuiApplication>

#include <QDebug>

#include <QMap>

#include <QObject>

#include <mutex>

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

    void updateQml();
    void updateCount(const QString objectName, int value);

    //test code
    int dispatch(void* msg);
private:
    explicit PopupManager(QQuickItem *parent=Q_NULLPTR);

signals:
    void signalCreateComponent(const QString objectName, const qreal posX, const qreal posY);
    void signalUpdateQml();
    void signalUpdateCall(QString objectName, int value);

public slots:
    void slotCreateComponent(const QString objectName, const qreal posX, const qreal posY);


    void slotUpdateCall(QString objectName, int value);

private:
    QQuickItem* mItem;
    QQmlEngine* mEngine;
    QQuickView* mView;
    QMap<ObjectName, QQuickItem*> mTest;

    std::mutex m_thread_mutex;


};

#endif // MYQUICKITEM_H
