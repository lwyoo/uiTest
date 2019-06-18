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
        //qDebug() << "not find QQuickItem";
    } else {
        //qDebug() << "remove data";
        QQuickItem* rmItem =  mTest[objectName];
        mTest.remove(objectName);

        rmItem->setEnabled(false);
        rmItem->deleteLater();
    }
}

PopupManager::~PopupManager()
{
    //qDebug() << "~MyQuickItem()";
}

bool PopupManager::findView()
{
    QWindowList windowlist = qApp->allWindows();
    //qDebug() << Q_FUNC_INFO << "window list count: " << windowlist.count();
    bool res = false ;
    if (windowlist.count() > 0) {
        mView = qobject_cast<QQuickView*>(windowlist.at(0));
        res = true;
    } else {
        //qDebug() << Q_FUNC_INFO << "window list count: " << windowlist.count() << "InValied Data [ERROR]";
    }
    return res;

}

bool PopupManager::settingQmlEngine()
{
    //qDebug() << Q_FUNC_INFO << "window list count: " << windowlist.count();
    bool res = false ;

    if (Q_NULLPTR ==  mView) {
        //qDebug() << Q_FUNC_INFO << "View is InValied [ERROR]";
    } else {
        mEngine = mView->engine();

        if (Q_NULLPTR ==  mEngine) {
            //qDebug() << Q_FUNC_INFO << "engine is InValied [ERROR]";
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
        //qDebug() << Q_FUNC_INFO << "engine is InValied [ERROR]";
    } else {
        QQmlIncubator incubator;
        QQmlComponent component(mEngine, QUrl("main.qml"));
        component.create(incubator);

        if (!incubator.isReady()) {
            //qDebug() << "incubator.isReady() is not ready [ERROR]";
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
                //qDebug() << "data update ";
            }
            mTest[objectName] = item;
            res = true;

            //qDebug() << "Component setting is sucess [OK]";



        } else {
            //qDebug() << "Component is nullptr [ERROR]";
        }
    }

    //qDebug() << "QQuickItem Map size is : " <<  mTest.size();




    return res;
}

bool PopupManager::createComponent(const QString objectName, const qreal posX, const qreal posY)
{
    //qDebug() << Q_FUNC_INFO << "start<<<<<<<<<<<<<<<<<<--------";
    bool res = false;
    if (Q_NULLPTR ==  mEngine || Q_NULLPTR == mView ) {
        //qDebug() << Q_FUNC_INFO << "engine is InValied [ERROR]";
    } else {

        QQmlIncubator incubator;
        QQmlComponent component(mEngine, QUrl("main.qml"));
        component.create(incubator);

        //        QObject::connect(item, SIGNAL(animationFinish(int)), this, SLOT(SlotMiniPopupAnimationFinish(int)));


        if (!incubator.isReady()) {
            //qDebug() << "incubator.isReady() is not ready [ERROR]";
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
                //qDebug() << "data update OOOOOOOOOOOOO";
                item->setProperty("myQml", QUrl("MyRec1.qml"));
            } else {
                //qDebug() << "data update XXXXXXXXXXXXXx";
            }


            if (false == mTest.contains(objectName)) {
            } else {
                //qDebug() << "data update ";
            }
            mTest[objectName] = item;

            //qDebug() << "Component setting is sucess [OK]";
        } else {
            //qDebug() << "Component is nullptr [ERROR]";
        }
    }
    //qDebug() << Q_FUNC_INFO << "end ------__>>>>>>>>>>>>>>>>";
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
        ++i;
    }
}

void PopupManager::connectionSignal()
{
    connect(this, SIGNAL(signalCreateComponent(const QString , const qreal , const qreal )), SLOT(slotCreateComponent(const QString , const qreal , const qreal )) );

    connect(this, SIGNAL(signalUpdateCall(QString, int)               ), SLOT( slotUpdateCall(QString, int)                    ))   ;




}

bool PopupManager::requestCreateComponent(const QString objectName, const qreal posX, const qreal posY)
{
    emit signalCreateComponent(objectName, posX, posY);
}

void PopupManager::updateQml()
{
    emit signalUpdateQml();
}

void PopupManager::updateCount(const QString objectName, int value)
{
    emit signalUpdateCall(objectName, value);
}

int PopupManager::dispatch(void *msg)
{
    PopupTestItem* temp = (PopupTestItem*)msg;

    PopupController::instance()->m_msgThread->stop();

    PopupController::instance()->createComponent("dd", 0, 50);

}

void PopupManager::slotCreateComponent(const QString objectName, const qreal posX, const qreal posY)
{
    //qDebug() << Q_FUNC_INFO <<"objectName : " << objectName << " posX : " << posX << " posY : " << posY ;

    createComponent(objectName, posX, posY );
}

void PopupManager::slotUpdateCall(QString objectName, int value)
{
    QQuickItem* temp = mTest[objectName];

    if (temp->property("myCount").isValid())
    {
        temp->setProperty("myCount", value);

    }

//    if (temp->property("myX").isValid()) {
//        temp->setProperty("myCount", value);
//        temp->setProperty("myX", value%300);
//    }


//    std::stringstream strS;
//    strS << PopupController::instance()->m_msgThread->getMsg();
//    qDebug() << Q_FUNC_INFO << "address" << strS.str().c_str();

    delete  PopupController::instance()->m_msgThread->getMsg();
    PopupController::instance()->m_msgThread->resume();
}
