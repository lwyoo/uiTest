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


}

void PopupController::requestCreateComponent(const QString objectName, const qreal posX, const qreal posY)
{
    PopupManager::instance()->requestCreateComponent(objectName, posX, posY);
}

PopupController::PopupController(QQuickView *parent)
    :QQuickView(parent)
{
    this->setColor(QColor(Qt::darkGray));
    this->setResizeMode(QQuickView::SizeViewToRootObject);
    this->setGeometry(QRect(SCREEN_INFO_X, SCREEN_INFO_Y, SCREEN_INFO_WIDTH, SCREEN_INFO_HEIGHT));
    this->setMinimumSize(QSize(SCREEN_INFO_WIDTH, SCREEN_INFO_HEIGHT));
    this->setMaximumSize(QSize(SCREEN_INFO_WIDTH, SCREEN_INFO_HEIGHT));

    PopupManager::instance()->findView();
    PopupManager::instance()->settingQmlEngine();

    connect(this, SIGNAL(testSignal(QString, qreal, qreal)), this, SLOT(testSlot(QString, qreal, qreal)));

}

//void MainWindow::connectionSignal()
//{
//    connect(this, SIGNAL(signalCreateComponent(const QString , const qreal , const qreal )), SLOT(createComponent(const QString , const qreal , const qreal )) );
//}

void PopupController::testSlot(QString ob, qreal posX, qreal posY)
{
    createComponent(ob, posX, posY) ;
}
