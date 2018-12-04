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

void MainWindow::checkoutChiledItem(const QString objName)
{
    // test
    qDebug() << "input objectName : " << objName;
    QQuickItem* temp;
    temp = this->findChild<QQuickItem*>("dldyddn");

    if (temp) {
        qDebug() << "chiled is InValied [ERROR]";
    } else {
        qDebug() << "chiled is Valied [OK]";
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
