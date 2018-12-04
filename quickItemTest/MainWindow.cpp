#include "MainWindow.h"
#include "MyQuickItem.h"
#define SCREEN_INFO_X 0
#define SCREEN_INFO_Y 0
#define SCREEN_INFO_WIDTH 1920
#define SCREEN_INFO_HEIGHT 720

static QSharedPointer<MainWindow> gMainWindowIstance;

QSharedPointer<MainWindow> MainWindow::instance(QQuickView *parent)
{
    if(gMainWindowIstance.isNull())
    {
        gMainWindowIstance = QSharedPointer<MainWindow>(new MainWindow(parent));
    }

    return gMainWindowIstance;
}

void MainWindow::findChiledItem(const QString objectName)
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

MainWindow::MainWindow(QQuickView *parent)
    :QQuickView(parent)
{
    this->setColor(QColor(Qt::darkGray));
    this->setResizeMode(QQuickView::SizeViewToRootObject);
    this->setGeometry(QRect(SCREEN_INFO_X, SCREEN_INFO_Y, SCREEN_INFO_WIDTH, SCREEN_INFO_HEIGHT));
    this->setMinimumSize(QSize(SCREEN_INFO_WIDTH, SCREEN_INFO_HEIGHT));
    this->setMaximumSize(QSize(SCREEN_INFO_WIDTH, SCREEN_INFO_HEIGHT));

    MyQuickItem::instance();

}
