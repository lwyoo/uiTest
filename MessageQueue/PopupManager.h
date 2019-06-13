#ifndef MYQUICKITEM_H
#define MYQUICKITEM_H

#include <QQuickItem>
#include <QQuickView>
#include <QQmlIncubator>
#include <QGuiApplication>

#include <QDebug>

#include <QMap>

#include <QObject>

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
private:
    explicit PopupManager(QQuickItem *parent=Q_NULLPTR);

signals:
    void signalCreateComponent(const QString objectName, const qreal posX, const qreal posY);
    void signalUpdateQml();

public slots:
    void slotCreateComponent(const QString objectName, const qreal posX, const qreal posY);

    //QQuickItem siganl
    void slotstateChanged(const QString &);
    void slotfocusChanged(bool);
    void slotactiveFocusChanged(bool);
    void slotactiveFocusOnTabChanged(bool);
    void slottransformOriginChanged(TransformOrigin);
    void slotsmoothChanged(bool);
    void slotantialiasingChanged(bool);
    void slotclipChanged(bool);
    void slotchildrenChanged();
    void slotopacityChanged();
    void slotenabledChanged();
    void slotvisibleChanged();
    void slotvisibleChildrenChanged();
    void slotrotationChanged();
    void slotscaleChanged();
    void slotxChanged();
    void slotyChanged();
    void slotwidthChanged();
    void slotheightChanged();
    void slotzChanged();
    void slotimplicitWidthChanged();
    void slotimplicitHeightChanged();
    void slotcontainmentMaskChanged();

//    QQmlComponent signal
    void slotstatusChanged(QQmlComponent::Status);
    void slotprogressChanged(qreal);

    void slotUpdateQml();


protected:
    bool event(QEvent *event);

private:
    QQuickItem* mItem;
    QQmlEngine* mEngine;
    QQuickView* mView;
    QMap<ObjectName, QQuickItem*> mTest;


};

#endif // MYQUICKITEM_H
