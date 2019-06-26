#include "PopupController.h"
#include "PopupManager.h"

#include <functional>

#include <memory>
#include <QSharedPointer>

#include <sstream>
#include <iostream>

#include "TestImsg.h"

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
    MessageThread::ThreadState value = m_msgThread->getState();
    QString temp;
    switch (value) {
    case MessageThread::ThreadState::UNINITED  : temp = "UNINITED,  " ;break;
    case MessageThread::ThreadState::INITED    : temp = "INITED,    " ;break;
    case MessageThread::ThreadState::STARTED   : temp = "STARTED,   " ;break;
    case MessageThread::ThreadState::RUNNING   : temp = "RUNNING,   " ;break;
    case MessageThread::ThreadState::TERMINATED: temp = "TERMINATED," ;break;
    case MessageThread::ThreadState::MAX       : temp = "MAX        " ;break;

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
//    m_msgThread->stop();
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

void PopupController::responeGUIUpdateComplete()
{
    std::lock_guard<std::mutex> lock(mMutex);

    TestImsg* temp = (TestImsg*)m_msgThread->getMsg();

    if (nullptr != temp ) {
        delete temp;
    } else {

    }

    m_msgThread->resume();
}

PopupController::PopupController(QQuickView *parent)
    :QQuickView(parent) {
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
    qDebug() << Q_FUNC_INFO << 0 ;
    TestImsg* temp = (TestImsg*)msg;
    qDebug() << Q_FUNC_INFO<< 1 ;



    PopupController::instance()->m_msgThread->suspend();
    qDebug() << Q_FUNC_INFO<< 2 ;

    PopupManager::instance()->updateCount(temp->getObjName(), temp->getMyCount());
    qDebug() << Q_FUNC_INFO<< 3 ;

    checkCount = checkCount + 1;

}

void PopupController::putMessage(const QString objectName, const qreal posX, const qreal posY, const int myCount)
{
    qDebug() << Q_FUNC_INFO;

    qDebug() << Q_FUNC_INFO << "0";
    TestImsg* temp = new TestImsg(objectName, posX, posY, myCount, (myCount%5));


    qDebug() << Q_FUNC_INFO << "1";
    m_msgThread->postMessage(temp);
    qDebug() << Q_FUNC_INFO << "2";

    checkInput =checkInput + 1;



}
