#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QDebug>
#include <QObject>

#include "MyClass.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);
    QQmlApplicationEngine engine;


    MyClass classObj;

    VehicleInfoStruct tempV;
    tempV.setBodyType("dldyddnBody");
    tempV.setVehicle_CD(true);

    DefaultStruct tempD;
    tempD.setDataValue(99);
    tempD.setFullDescription("dldyddn");
    tempD.setVehicleInfo(tempV);
    classObj.setMyStruct2(tempD);



    string temp = "";
    qDebug() << "dldyddn@@@@@@@@@@@" << temp.c_str() << "asda";




    engine.rootContext()->setContextProperty("classObj",&classObj);

    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

    if (engine.rootObjects().isEmpty())
        return -1;

    return app.exec();
}
