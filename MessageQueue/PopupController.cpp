#include "PopupController.h"
#include "PopupManager.h"


#define SCREEN_INFO_X 0
#define SCREEN_INFO_Y 0
#define SCREEN_INFO_WIDTH 1920
#define SCREEN_INFO_HEIGHT 720

static QSharedPointer<PopupController> gMainWindowIstance;

QSharedPointer<PopupController> PopupController::instance(QQuickView *parent)
{
    if(gMainWindowIstance.isNull())
    {
        gMainWindowIstance = QSharedPointer<PopupController>(new PopupController(parent));
    }

    return gMainWindowIstance;
}

void PopupController::findChiledItem(const QString objectName)
{
    qDebug() << "objectName : " << objectName;

    QQuickItem* tmp = Q_NULLPTR;
    tmp = findChild<QQuickItem*>(objectName);

    if (Q_NULLPTR != tmp) {
        qDebug() << "Valied data " ;
    } else {
        qDebug() << "InValied data " ;
    }

}

void PopupController::destroyTest(const QString objName)
{
    PopupManager::instance()->destroyTest(objName);
}

//bool MainWindow::requestCreateComponent(const QString objectName, const qreal posX, const qreal posY)
//{
//    emit signalCreateComponent(objectName, posX, posY);
//}

void PopupController::createComponent(const QString objectName, const qreal posX, const qreal posY)
{
//    bool res = MyQuickItem::instance()->createComponent(objectName, posX, posY);
//    return res;
    PopupManager::instance()->createComponent(objectName, posX, posY);
//    PopupManager::instance()->slotUpdateQml();


}

void PopupController::requestCreateComponent(const QString objectName, const qreal posX, const qreal posY)
{
    PopupManager::instance()->requestCreateComponent(objectName, posX, posY);
}

void PopupController::updateQml()
{
    PopupManager::instance()->updateQml();
}

PopupController::PopupController(QQuickView *parent)
    :QQuickView(parent)
{
    this->setColor(QColor(Qt::darkGray));
    this->setResizeMode(QQuickView::SizeViewToRootObject);
    this->setGeometry(QRect(SCREEN_INFO_X, SCREEN_INFO_Y, SCREEN_INFO_WIDTH, SCREEN_INFO_HEIGHT));
    this->setMinimumSize(QSize(SCREEN_INFO_WIDTH, SCREEN_INFO_HEIGHT));
    this->setMaximumSize(QSize(SCREEN_INFO_WIDTH, SCREEN_INFO_HEIGHT));

//    PopupManager::instance()->findView();
//    PopupManager::instance()->settingQmlEngine();
    PopupManager::instance();

    connect(this, SIGNAL(testSignal(QString, qreal, qreal)), this, SLOT(testSlot(QString, qreal, qreal)));

    connect(this, SIGNAL(sceneGraphInitialized()), this, SLOT(testSceneGraphInitialized()));
    connect(this, SIGNAL(sceneGraphInvalidated()), this, SLOT(  testsceneGraphInvalidated()));
    connect(this, SIGNAL(beforeSynchronizing   ()), this, SLOT(  testbeforeSynchronizing   ()));
    connect(this, SIGNAL(afterSynchronizing    ()), this, SLOT(  testafterSynchronizing    ()));
    connect(this, SIGNAL(beforeRendering       ()), this, SLOT(  testbeforeRendering       ()));
    connect(this, SIGNAL(afterRendering        ()), this, SLOT(  testafterRendering        ()));
    connect(this, SIGNAL(afterAnimating        ()), this, SLOT(  testafterAnimating        ()));
    connect(this, SIGNAL(sceneGraphAboutToStop ()), this, SLOT(  testsceneGraphAboutToStop ()));
    connect(this, SIGNAL(activeFocusItemChanged()), this, SLOT(  testactiveFocusItemChanged()));



//                    testcolorChanged
//                    testsceneGraphErrorṡ
//    void frameSwapped();
//    Q_REVISION(2) void openglContextCreated(QOpenGLContext *context);
//    void sceneGraphInitialized();
//    void sceneGraphInvalidated();
//    void beforeSynchronizing();
//    Q_REVISION(2) void afterSynchronizing();
//    void beforeRendering();
//    void afterRendering();
//    Q_REVISION(2) void afterAnimating();
//    Q_REVISION(2) void sceneGraphAboutToStop();

//    Q_REVISION(1) void closing(QQuickCloseEvent *close);
//    void colorChanged(const QColor &);
//    Q_REVISION(1) void activeFocusItemChanged();
//    Q_REVISION(2) void sceneGraphError(QQuickWindow::SceneGraphError error, const QString &message);



}

//void MainWindow::connectionSignal()
//{
//    connect(this, SIGNAL(signalCreateComponent(const QString , const qreal , const qreal )), SLOT(createComponent(const QString , const qreal , const qreal )) );
//}

void PopupController::testSlot(QString ob, qreal posX, qreal posY)
{
    createComponent(ob, posX, posY) ;
}

void PopupController::testSceneGraphInitialized()
{
    qDebug() << Q_FUNC_INFO;
}

void PopupController::testsceneGraphInvalidated()
{
    qDebug() << Q_FUNC_INFO;

}

void PopupController::testbeforeSynchronizing()
{
    qDebug() << Q_FUNC_INFO;

}

void PopupController::testafterSynchronizing()
{
    qDebug() << Q_FUNC_INFO;

}

void PopupController::testbeforeRendering()
{
    qDebug() << Q_FUNC_INFO;

}

void PopupController::testafterRendering()
{
    qDebug() << Q_FUNC_INFO;

}

void PopupController::testafterAnimating()
{
    qDebug() << Q_FUNC_INFO;

}

void PopupController::testsceneGraphAboutToStop()
{
    qDebug() << Q_FUNC_INFO;

}

void PopupController::testactiveFocusItemChanged()
{
    qDebug() << Q_FUNC_INFO;

}
