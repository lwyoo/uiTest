#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QTranslator>
#include <QDebug>
int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);

    QTranslator translator;
    translator.load("HIAVN_Lang_KR");
    app.installTranslator(&translator);


    QString temp("TXTB_IVIS_SET_EM_BT_CONNECT_LID_4872");


    qDebug() << "asd : " << app.tr(temp.toUtf8().data());;


    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;

    return app.exec();
}
