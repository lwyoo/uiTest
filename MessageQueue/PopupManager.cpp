#include "PopupManager.h"
#include "PopupController.h"
#define ACTIVITY
//#define DCP
static QSharedPointer<PopupManager> gMyQuickItemIstance;

QSharedPointer<PopupManager> PopupManager::instance(QQuickItem *parent)
{
    if(gMyQuickItemIstance.isNull())
    {
        gMyQuickItemIstance = QSharedPointer<PopupManager>(new PopupManager(parent));
    }

    return gMyQuickItemIstance;
}

void PopupManager::destroyTest(const QString objectName)
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

PopupManager::~PopupManager()
{
    qDebug() << "~MyQuickItem()";
}

bool PopupManager::findView()
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

bool PopupManager::settingQmlEngine()
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

bool PopupManager::createComponent(const QString objectName)
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

bool PopupManager::createComponent(const QString objectName, const qreal posX, const qreal posY)
{
    qDebug() << Q_FUNC_INFO << "start<<<<<<<<<<<<<<<<<<--------";
    bool res = false;
    if (Q_NULLPTR ==  mEngine || Q_NULLPTR == mView ) {
        qDebug() << Q_FUNC_INFO << "engine is InValied [ERROR]";
    } else {

        QQmlIncubator incubator;
        QQmlComponent component(mEngine, QUrl("main.qml"));
        component.create(incubator);

        //        QObject::connect(item, SIGNAL(animationFinish(int)), this, SLOT(SlotMiniPopupAnimationFinish(int)));
        QObject::connect(&component, SIGNAL(statusChanged(QQmlComponent::Status)),   SLOT(slotstatusChanged(QQmlComponent::Status)));
        QObject::connect(&component, SIGNAL(progressChanged(qreal)),                 SLOT(slotprogressChanged(qreal)             ));


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

            this->setEnabled(false);


            if (item->property("myQml").isValid())             {
                qDebug() << "data update OOOOOOOOOOOOO";
                item->setProperty("myQml", QUrl("MyRec1.qml"));
            } else {
                qDebug() << "data update XXXXXXXXXXXXXx";
            }


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
    qDebug() << Q_FUNC_INFO << "end ------__>>>>>>>>>>>>>>>>";
    return res;
}

bool PopupManager::removeComponent(const QString objectName)
{
    bool res = false;
    if (false == mTest.contains(objectName)) {

    } else {

    }

    return res;
}

PopupManager::PopupManager(QQuickItem *parent)
    :QQuickItem(parent)
    , mItem(Q_NULLPTR)
    , mEngine(Q_NULLPTR)
{
    connectionSignal();
    findView();
    settingQmlEngine();
}

void PopupManager::printMapData()
{

    QMap<QString, QQuickItem*>::const_iterator i =  mTest.constBegin();
    while (i != mTest.constEnd()) {
        qDebug() << "key: " << i.key();
        ++i;
    }
}

void PopupManager::connectionSignal()
{
    connect(this, SIGNAL(signalCreateComponent(const QString , const qreal , const qreal )), SLOT(slotCreateComponent(const QString , const qreal , const qreal )) );
    connect(this, SIGNAL(signalCreateComponent()), SLOT(slotCreateComponent()) );

    connect(this, SIGNAL(stateChanged(const QString &)          ), SLOT( slotstateChanged(const QString &)               ))   ;
    connect(this, SIGNAL(focusChanged(bool)                     ), SLOT( slotfocusChanged(bool)                          ))   ;
    connect(this, SIGNAL(activeFocusChanged(bool)               ), SLOT( slotactiveFocusChanged(bool)                    ))   ;
    connect(this, SIGNAL(activeFocusOnTabChanged(bool)          ), SLOT( slotactiveFocusOnTabChanged(bool)               ))   ;
    connect(this, SIGNAL(transformOriginChanged(TransformOrigin)), SLOT( slottransformOriginChanged(TransformOrigin)     ))   ;
    connect(this, SIGNAL(smoothChanged(bool)                    ), SLOT( slotsmoothChanged(bool)                        ))    ;
    connect(this, SIGNAL(antialiasingChanged(bool)              ), SLOT( slotantialiasingChanged(bool)                   ))   ;
    connect(this, SIGNAL(clipChanged(bool)                      ), SLOT( slotclipChanged(bool)                           ))   ;
    connect(this, SIGNAL(childrenChanged()                      ), SLOT( slotchildrenChanged()                           ))   ;
    connect(this, SIGNAL(opacityChanged()                       ), SLOT( slotopacityChanged()                            ))   ;
    connect(this, SIGNAL(enabledChanged()                       ), SLOT( slotenabledChanged()                            ))   ;
    connect(this, SIGNAL(visibleChanged()                       ), SLOT( slotvisibleChanged()                            ))   ;
    connect(this, SIGNAL(visibleChildrenChanged()               ), SLOT( slotvisibleChildrenChanged()                    ))   ;
    connect(this, SIGNAL(rotationChanged()                      ), SLOT( slotrotationChanged()                           ))   ;
    connect(this, SIGNAL(scaleChanged()                         ), SLOT( slotscaleChanged()                              ))   ;
    connect(this, SIGNAL(xChanged()                             ), SLOT( slotxChanged()                                  ))   ;
    connect(this, SIGNAL(yChanged()                             ), SLOT( slotyChanged()                                  ))   ;
    connect(this, SIGNAL(widthChanged()                         ), SLOT( slotwidthChanged()                              ))   ;
    connect(this, SIGNAL(heightChanged()                        ), SLOT( slotheightChanged()                             ))   ;
    connect(this, SIGNAL(zChanged()                             ), SLOT( slotzChanged()                                  ))   ;
    connect(this, SIGNAL(implicitWidthChanged()                 ), SLOT( slotimplicitWidthChanged()                      ))   ;
    connect(this, SIGNAL(implicitHeightChanged()                ), SLOT( slotimplicitHeightChanged()                     ))   ;
    connect(this, SIGNAL(containmentMaskChanged()               ), SLOT( slotcontainmentMaskChanged()                    ))   ;


    connect(this, SIGNAL(signalUpdateQml()               ), SLOT( slotUpdateQml()                    ))   ;
    connect(this, SIGNAL(signalUpdateCall(int)               ), SLOT( slotUpdateCall(int)                    ))   ;




}

bool PopupManager::requestCreateComponent(const QString objectName, const qreal posX, const qreal posY)
{
    emit signalCreateComponent(objectName, posX, posY);
}

void PopupManager::updateQml()
{
    emit signalUpdateQml();
}

void PopupManager::updateCount(int value)
{
    emit signalUpdateCall(value);
}

void PopupManager::slotCreateComponent(const QString objectName, const qreal posX, const qreal posY)
{
    qDebug() << Q_FUNC_INFO <<"objectName : " << objectName << " posX : " << posX << " posY : " << posY ;

    createComponent(objectName, posX, posY );
}

void PopupManager::slotstateChanged(const QString &value)
{
    qDebug() << Q_FUNC_INFO << value ;
}

void PopupManager::slotfocusChanged(bool value )
{
    qDebug() << Q_FUNC_INFO << value ;
}

void PopupManager::slotactiveFocusChanged(bool value )
{
    qDebug() << Q_FUNC_INFO << value ;
}

void PopupManager::slotactiveFocusOnTabChanged(bool value )
{
    qDebug() << Q_FUNC_INFO << value ;
}

void PopupManager::slottransformOriginChanged(QQuickItem::TransformOrigin value)
{
    qDebug() << Q_FUNC_INFO << value ;
}

void PopupManager::slotsmoothChanged(bool value)
{
    qDebug() << Q_FUNC_INFO << value ;
}

void PopupManager::slotantialiasingChanged(bool value)
{
    qDebug() << Q_FUNC_INFO << value ;
}

void PopupManager::slotclipChanged(bool value)
{
    qDebug() << Q_FUNC_INFO << value ;
}

void PopupManager::slotchildrenChanged()
{
    qDebug() << Q_FUNC_INFO;
}

void PopupManager::slotopacityChanged()
{
    qDebug() << Q_FUNC_INFO;
}

void PopupManager::slotenabledChanged()
{
    qDebug() << Q_FUNC_INFO;
}

void PopupManager::slotvisibleChanged()
{
    qDebug() << Q_FUNC_INFO;
}

void PopupManager::slotvisibleChildrenChanged()
{
    qDebug() << Q_FUNC_INFO;
}

void PopupManager::slotrotationChanged()
{
    qDebug() << Q_FUNC_INFO;
}

void PopupManager::slotscaleChanged()
{
    qDebug() << Q_FUNC_INFO;
}

void PopupManager::slotxChanged()
{
    qDebug() << Q_FUNC_INFO;
}

void PopupManager::slotyChanged()
{
    qDebug() << Q_FUNC_INFO;
}

void PopupManager::slotwidthChanged()
{
    qDebug() << Q_FUNC_INFO;
}

void PopupManager::slotheightChanged()
{
    qDebug() << Q_FUNC_INFO;
}

void PopupManager::slotzChanged()
{
    qDebug() << Q_FUNC_INFO;
}

void PopupManager::slotimplicitWidthChanged()
{
    qDebug() << Q_FUNC_INFO;
}

void PopupManager::slotimplicitHeightChanged()
{
    qDebug() << Q_FUNC_INFO;
}

void PopupManager::slotcontainmentMaskChanged()
{
    qDebug() << Q_FUNC_INFO;
}

void PopupManager::slotstatusChanged(QQmlComponent::Status value )
{
    qDebug() << Q_FUNC_INFO << value ;
}

void PopupManager::slotprogressChanged(qreal value )
{
    qDebug() << Q_FUNC_INFO << value ;
}

void PopupManager::slotUpdateQml()
{
    qDebug() << Q_FUNC_INFO ;
    QQuickItem* temp = mTest["aa"];

    if (temp->property("myQml").isValid())
    {
        if (temp->property("myQml").toString().compare("MyRec1.qml") == 0) {
            temp->setProperty("myQml", QUrl("MyRec2.qml"));
        } else {
            temp->setProperty("myQml", QUrl("MyRec1.qml"));
        }
    }

    qDebug() << Q_FUNC_INFO << "endl";
}

void PopupManager::slotUpdateCall(int value)
{
//    qDebug() << Q_FUNC_INFO ;
    QQuickItem* temp = mTest["aa"];

    if (temp->property("myCount").isValid())
    {
        temp->setProperty("myCount", value);

    }
//    qDebug() << Q_FUNC_INFO << "endl";3
}

bool PopupManager::event(QEvent *event)
{
//    qDebug() << Q_FUNC_INFO << "Event Type ["<< static_cast<int>(event->type())  <<"]";
    QObject::event(event);
}
