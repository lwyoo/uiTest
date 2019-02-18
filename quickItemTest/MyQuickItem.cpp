#include "MyQuickItem.h"

#define ACTIVITY
//#define DCP
static QSharedPointer<MyQuickItem> gMyQuickItemIstance;

QSharedPointer<MyQuickItem> MyQuickItem::instance(QQuickItem *parent)
{
    if(gMyQuickItemIstance.isNull())
    {
        gMyQuickItemIstance = QSharedPointer<MyQuickItem>(new MyQuickItem(parent));
    }

    return gMyQuickItemIstance;
}

void MyQuickItem::destroyTest(const QString objectName)
{
    if (false == mTest.contains(objectName)) {
        qDebug() << "not find QQuickItem";
    } else {
        qDebug() << "remove data";
       QQuickItem* rmItem =  mTest[objectName];
       mTest.remove(objectName);

       rmItem->setEnabled(false);
       rmItem->deleteLater();
    }
}

MyQuickItem::~MyQuickItem()
{
    qDebug() << "~MyQuickItem()";
}

bool MyQuickItem::findView()
{
    QWindowList windowlist = qApp->allWindows();
    qDebug() << Q_FUNC_INFO << "window list count: " << windowlist.count();
    bool res = false ;
    if (windowlist.count() > 0) {
        mView = qobject_cast<QQuickView*>(windowlist.at(0));
        res = true;
    } else {
        qDebug() << Q_FUNC_INFO << "window list count: " << windowlist.count() << "InValied Data [ERROR]";
    }
    return res;

}

bool MyQuickItem::settingQmlEngine()
{
    QWindowList windowlist = qApp->allWindows();
    qDebug() << Q_FUNC_INFO << "window list count: " << windowlist.count();
    bool res = false ;

    if (Q_NULLPTR ==  mView) {
        qDebug() << Q_FUNC_INFO << "View is InValied [ERROR]";
    } else {
        mEngine = mView->engine();

        if (Q_NULLPTR ==  mEngine) {
            qDebug() << Q_FUNC_INFO << "engine is InValied [ERROR]";
        } else {
            res = true;
        }
    }

    return res;
}

bool MyQuickItem::createComponent(const QString objectName)
{
    bool res = false;
    if (Q_NULLPTR ==  mEngine || Q_NULLPTR == mView ) {
        qDebug() << Q_FUNC_INFO << "engine is InValied [ERROR]";
    } else {
        QQmlIncubator incubator;
        QQmlComponent component(mEngine, QUrl("main.qml"));
        component.create(incubator);

        if (!incubator.isReady()) {
            qDebug() << "incubator.isReady() is not ready [ERROR]";
            incubator.forceCompletion();
        }

        QQuickItem *item = qobject_cast<QQuickItem *>(incubator.object());
        if (item) {
            item->setObjectName(objectName);
            this->setWidth(item->width());
            this->setHeight(item->height());
            item->setParent(this);
            this->setParent(mView->contentItem());
            item->setParentItem(this);
            this->setParentItem(mView->contentItem());


            this->setEnabled(false);
            QObject::connect(item, SIGNAL(qmlSignal(QString)),
                             this, SLOT(cppSlot(QString)));

            if (false == mTest.contains(objectName)) {
            } else {
                qDebug() << "data update ";
            }
            mTest[objectName] = item;
            res = true;

            qDebug() << "Component setting is sucess [OK]";
        } else {
            qDebug() << "Component is nullptr [ERROR]";
        }
    }

    qDebug() << "QQuickItem Map size is : " <<  mTest.size();




    return res;
}

bool MyQuickItem::createComponent(const QString objectName, const qreal posX, const qreal posY)
{
    qDebug() << Q_FUNC_INFO << "objectName : " <<objectName ;
    bool res = false;
    if (Q_NULLPTR ==  mEngine || Q_NULLPTR == mView ) {
        qDebug() << Q_FUNC_INFO << "engine is InValied [ERROR]";
    } else {
        QQmlIncubator incubator;
        QQmlComponent component(mEngine, QUrl("main.qml"));
        component.create(incubator);


        if (!incubator.isReady()) {
            qDebug() << "incubator.isReady() is not ready [ERROR]";
            incubator.forceCompletion();
        }

        QQuickItem *item = qobject_cast<QQuickItem *>(incubator.object());

        if (item) {
            item->setX(posX);
            item->setY(posY);
            item->setObjectName(objectName);
            this->setWidth(item->width());
            this->setHeight(item->height());
            item->setParent(this);
            this->setParent(mView->contentItem());
            item->setParentItem(this);
            this->setParentItem(mView->contentItem());

            this->setEnabled(true);
//            this->setVisible(false);
            QObject::connect(item, SIGNAL(qmlSignal(QString)),
                             this, SLOT(cppSlot(QString)));

            if (false == mTest.contains(objectName)) {
            } else {
                qDebug() << "data update ";
            }
            mTest[objectName] = item;

            qDebug() << "Component setting is sucess [OK]";
        } else {
            qDebug() << "Component is nullptr [ERROR]";
        }
    }
    return res;
}

bool MyQuickItem::removeComponent(const QString objectName)
{
    bool res = false;
    if (false == mTest.contains(objectName)) {
        qDebug() << "not find QQuickItem";
    } else {
        qDebug() << "remove data";
       QQuickItem* rmItem =  mTest[objectName];
       mTest.remove(objectName);

       rmItem->setEnabled(false);
       rmItem->deleteLater();
       res = true;
    }
    return res;
}

MyQuickItem::MyQuickItem(QQuickItem *parent)
    :QQuickItem(parent)
    , mItem(Q_NULLPTR)
    , mEngine(Q_NULLPTR)
{

}

void MyQuickItem::cppSlot(QString temp)
{
       qDebug() << "text : !!" <<temp;
}

void MyQuickItem::printMapData()
{

    QMap<QString, QQuickItem*>::const_iterator i =  mTest.constBegin();
    while (i != mTest.constEnd()) {
        qDebug() << "key: " << i.key();
        ++i;
    }
}

void MyQuickItem::upOpacity()
{
    if (mTest.end() !=  mTest.find(QString("aa"))) {
        qDebug() << "valied Map";
        if (Q_NULLPTR == mTest[QString("aa")]->findChild<QQuickItem*>(QString("aa"))) {

            qDebug() << "valied Map xxxxxxxxxxxxxx2 : " <<mTest[QString("aa")]->childItems().size();
            qDebug() << "valied Map xxxxxxxxxxxxxx2 : " <<mTest[QString("aa")]->childItems().at(0)->objectName();
            qDebug() << "valied Map xxxxxxxxxxxxxx2 : " <<mTest[QString("aa")]->childItems().at(1)->objectName();
            qDebug() << "valied Map xxxxxxxxxxxxxx2 : " <<mTest[QString("aa")]->childItems().at(2)->objectName();
            mTest[QString("aa")]->setProperty("myOpacity",0);
        } else {
            qDebug() << "valied Map oooooooooooooo2 ";
            mTest[QString("aa")]->findChild<QQuickItem*>(QString("aa"))->setProperty("myOpacity",0);
        }

    } else {
        qDebug() << "valied Map xx";
    }
}

void MyQuickItem::downOpacity()
{
        qDebug() << "upOpacity :: valied data !!" ;
        mTest[QString("aa")]->setProperty("myOpacity",1);
}
