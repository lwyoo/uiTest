#include <QGuiApplication>
#include <QQmlApplicationEngine>

#include "MainWindow.h"
int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);

//    QQmlApplicationEngine engine;
//    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
//    if (engine.rootObjects().isEmpty())
//        return -1;

    MainWindow::instance();
    MainWindow::instance()->show();

    MainWindow::instance()->checkoutChiledItem("dldytddn1");




    return app.exec();
}
