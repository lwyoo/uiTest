#include "PopupController.h"
#include "PopupManager.h"

#include <functional>

#include <memory>
#include <QSharedPointer>

#include <sstream>
#include <iostream>

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
    //qDebug() << "objectName : " << objectName;

    QQuickItem* tmp = Q_NULLPTR;
    tmp = findChild<QQuickItem*>(objectName);

    if (Q_NULLPTR != tmp) {
        //qDebug() << "Valied data " ;
    } else {
        //qDebug() << "InValied data " ;
    }

}

void PopupController::destroyTest(const QString objName)
{
    PopupManager::instance()->destroyTest(objName);
}

void PopupController::createComponent(const QString objectName, const qreal posX, const qreal posY)
{
    PopupManager::instance()->createComponent(objectName, posX, posY);
}

void PopupController::requestCreateComponent(const QString objectName, const qreal posX, const qreal posY)
{
    PopupManager::instance()->requestCreateComponent(objectName, posX, posY);
}



QString PopupController::getState()
{
    MessageThreadState value = m_msgThread->getState();
    QString temp;
    switch (value) {
    case MessageThreadState::UNINITED  : temp = "UNINITED,  " ;break;
    case MessageThreadState::INITED    : temp = "INITED,    " ;break;
    case MessageThreadState::STARTED   : temp = "STARTED,   " ;break;
    case MessageThreadState::RUNNING   : temp = "RUNNING,   " ;break;
    case MessageThreadState::STOPPED   : temp = "STOPPED,   " ;break;
    case MessageThreadState::SUSPEND   : temp = "SUSPEND,   " ;break;
    case MessageThreadState::TERMINATED: temp = "TERMINATED," ;break;
    case MessageThreadState::MAX       : temp = "MAX        " ;break;

    }
    return temp;
}

void PopupController::initMessageThread()
{
    //qDebug() << Q_FUNC_INFO;

    std::function<int(void *)> handler = [this](void *msg)->int {
        return this->dispatch(msg);
    };


    m_msgThread = new MessageThread(handler, "PopupController");
}

void PopupController::startMessageThread()
{
    //qDebug() << Q_FUNC_INFO;
    m_msgThread->start();
}

void PopupController::resumeMessageThread()
{
    //qDebug() << Q_FUNC_INFO;
    m_msgThread->resume();
}

void PopupController::stopMessageThread()
{
    //qDebug() << Q_FUNC_INFO;
    m_msgThread->stop();
}

PopupController::~PopupController()
{
    m_msgThread->exit();
    delete m_msgThread;
}

void PopupController::check()
{
    qDebug() << Q_FUNC_INFO << "put Message Count : " << checkInput;
    qDebug() << Q_FUNC_INFO << "dispatch Count : " << checkCount;

    checkCount = 0;
    checkInput = 0;

}

PopupController::PopupController(QQuickView *parent)
    :QQuickView(parent)
{
    this->setColor(QColor(Qt::darkGray));
    this->setResizeMode(QQuickView::SizeViewToRootObject);
    this->setGeometry(QRect(SCREEN_INFO_X, SCREEN_INFO_Y, SCREEN_INFO_WIDTH, SCREEN_INFO_HEIGHT));
    this->setMinimumSize(QSize(SCREEN_INFO_WIDTH, SCREEN_INFO_HEIGHT));
    this->setMaximumSize(QSize(SCREEN_INFO_WIDTH, SCREEN_INFO_HEIGHT));

    PopupManager::instance();

//    connect(this, SIGNAL(testSignal(QString, qreal, qreal)), this, SLOT(testSlot(QString, qreal, qreal)));
}

void PopupController::testSlot(QString ob, qreal posX, qreal posY)
{
    createComponent(ob, posX, posY) ;
}

int PopupController::dispatch(void *msg)
{
    PopupTestItem* temp = (PopupTestItem*)msg;



    PopupController::instance()->m_msgThread->stop();

    PopupManager::instance()->updateCount(temp->objName, temp->myCount);
//    PopupManager::instance()->slotUpdateCall(temp->objName, temp->myCount);

    checkCount = checkCount + 1;

//    std::stringstream strS;
//    strS << temp;
//    qDebug() << Q_FUNC_INFO << " index [" << temp->myCount << "] address" << strS.str().c_str();
}

void PopupController::putMessage(const QString objectName, const qreal posX, const qreal posY, const int myCount)
{
//    qDebug() << Q_FUNC_INFO;

    PopupTestItem* temp = new PopupTestItem;

    temp->objName = objectName;
    temp->posX = posX;
    temp->posY = posY;
    temp->myCount = myCount;

    m_msgThread->putMessage(temp);
    checkInput =checkInput + 1;

//    std::stringstream strS;
//    strS << temp;
//    qDebug() << Q_FUNC_INFO << " index [" << myCount << "] address" << strS.str().c_str();


}
