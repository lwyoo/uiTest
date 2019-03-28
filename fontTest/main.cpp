#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QFont>
#include <QDir>
#include <iostream>
#include <QLoggingCategory>
#include <QFile>
#include <QFontDatabase>
int main(int argc, char *argv[])
{

//    QLoggingCategory::setFilterRules(QString("*=true"));





    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);


//    if ( true == QDir::setCurrent(QCoreApplication::applicationDirPath()) ) {
//        std::cout << "current() xxxx: " << QDir::currentPath().toStdString().c_str() << std::endl;
//    } else {
//        std::cout << "current() : " << QDir::currentPath().toStdString().c_str() << std::endl;
//    }

    QString fontFiles;
    fontFiles = "/home/ooo/fontTest/Cube.ttf";
    QFile fontFile(fontFiles);

    if( true == fontFile.open(QIODevice::ReadOnly) )
    {
        std::cout << "OK 1" << std::endl;
        QFontDatabase::addApplicationFontFromData(fontFile.readAll());
        fontFile.close();
    } else{
        std::cout << "Fail 1 " << std::endl;
    }




    QString fontFiles2;
    fontFiles2 = "/home/ooo/fontTest/CubeBa1.ttf";
    QFile fontFile2(fontFiles2);

    if( true == fontFile2.open(QIODevice::ReadOnly) )
    {
        std::cout << "OK 2" << std::endl;
        QFontDatabase::addApplicationFontFromData(fontFile2.readAll());
        fontFile2.close();
    } else{
        std::cout << "Fail 2" << std::endl;
    }


//    QStringList fontList1;

//    fontList1 << "CubeR Regular"; // name

//    QFont::insertSubstitutions(QString("CubeR"), fontList1); // qml name



//    QStringList fontList2;

//    fontList2 << "CubeBa1 Bold"; // name

//    QFont::insertSubstitutions(QString("CubeBa"), fontList2); // qml name




    QQmlApplicationEngine engine;

    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));




    if (engine.rootObjects().isEmpty())
        return -1;






    return app.exec();
}
