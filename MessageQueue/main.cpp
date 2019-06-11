#include <QGuiApplication>
#include <QQmlApplicationEngine>

#include <unistd.h>
#include <iostream>
#include "MainWindow.h"

#include <thread>
using namespace std;

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);

    MainWindow::instance()->show();

    // standard in/out , use terminor
    thread t1 = thread([&] {
        while(1)
        {
            int value;
            cout << endl;
            cout << endl;
            cout << endl;
            cout << endl;

            cout << "1. create Component " << endl;
            //            cout << "2. object list " << endl;
            //            cout << "3. findeChiled" << endl;
            cout << "4. destroy item" << endl;


            cin >> value;


            switch (value) {
            case 1: {
                string objectName = "";
                cout << "input ObjectName : " << endl;
                cin >> objectName;
                QString qObjectName = QString::fromUtf8(objectName.c_str());

                int posX;
                qreal qPosX;
                cout << "input position X  : " << endl;
                cin >> posX;
                qPosX = static_cast<qreal>(posX);

                int posY;
                qreal qPosY;
                cout << "input position Y  : " << endl;
                cin >> posY;
                qPosY = static_cast<qreal>(posY);
                MainWindow::instance()->testSignal(qObjectName, qPosX, qPosY);
            }
                break;
            case 2:
                MainWindow::instance()->createComponent("aa", 0, 50);
                break;
            case 3:
                break;
            case 4: {

                string objectName = "";
                cout << "input ObjectName : " << endl;
                cin >> objectName;
                QString qObjectName = QString::fromUtf8(objectName.c_str());
                MainWindow::instance()->destroyTest(qObjectName);
            }
                break;
            default:
                break;

            }

        }
    });


    return app.exec();
}
