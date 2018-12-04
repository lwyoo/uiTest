#include "MyQuickItem.h"
#include <QGuiApplication>
#include <QQuickView>
#include <QDebug>
#include <QQmlIncubator>
//#define ACTIVITY
#define DCP
static QSharedPointer<MyQuickItem> gMyQuickItemIstance;

QSharedPointer<MyQuickItem> MyQuickItem::instance(QQuickItem *parent)
{
    if(gMyQuickItemIstance.isNull())
    {
        gMyQuickItemIstance = QSharedPointer<MyQuickItem>(new MyQuickItem(parent));
    }

    return gMyQuickItemIstance;
}

void MyQuickItem::destroyTest()
{
    mItem->setEnabled(false);
    this->deleteLater();
}

MyQuickItem::~MyQuickItem()
{
    qDebug() << "~MyQuickItem()" ;
}

#ifdef DCP
MyQuickItem::MyQuickItem(QQuickItem *parent)
    :QQuickItem(parent)
    , mItem(nullptr)
{
    QWindowList windowList = qApp->allWindows();
    qDebug() << "windowList count : " << windowList.count();

    if (windowList.count() > 0 ) {
        const QQuickView* view = qobject_cast<QQuickView*>(windowList.at(0));
        QQmlEngine* engine = view->engine();
        //        QQmlComponent component(engine, QUrl("qrc:/main.qml"));

        QQmlComponent component(engine, QUrl("main.qml"));
        mItem = qobject_cast<QQuickItem *>(component.create());

        if(mItem ) {
            mItem->setParent(this);
            //this->setParent(view->contentItem()->parent());
            mItem->setParentItem(this);
            this->setParentItem(view->contentItem());
            this->setWidth(mItem->width());
            this->setHeight(mItem->height());

            this->setEnabled(true);

            mItem->setZ(10);
            qDebug() << "Component setting is sucess [OK]";
        } else {
            qDebug() << "Component is nullptr [ERROR]";
        }

    } else {
        qDebug() << "window size is 0 [ERROR]";
    }
}

#endif

#ifdef ACTIVITY
MyQuickItem::MyQuickItem(QQuickItem *parent)
    :QQuickItem(parent)
    , mItem(nullptr)
{
    QWindowList windowlist = qApp->allWindows();
    qDebug() << Q_FUNC_INFO << "window list count: " << windowlist.count();
    if (windowlist.count()) {
        QQuickView* view = qobject_cast<QQuickView*>(windowlist.at(0));
        QQmlEngine* engine = view->engine();
        QQmlIncubator incubator;
        QQmlComponent component(engine, QUrl("main.qml"));
        component.create(incubator);

        if (!incubator.isReady()) {
            qDebug() << "incubator.isReady() is not ready [ERROR]";
            incubator.forceCompletion();
        }

        QQuickItem *item = qobject_cast<QQuickItem *>(incubator.object());
        if (item) {
            this->setWidth(item->width());
            this->setHeight(item->height());
            item->setParent(this);
            this->setParent(view->contentItem());
            item->setParentItem(this);
            this->setParentItem(view->contentItem());

            this->setEnabled(false);

            mItem = item;
            qDebug() << "Component setting is sucess [OK]";
        } else {
            qDebug() << "Component is nullptr [ERROR]";
        }
    } else {
        qDebug() << "window size is 0 [ERROR]";
    }
}
#endif
