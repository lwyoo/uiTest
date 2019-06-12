#include <QGuiApplication>
#include <QQmlApplicationEngine>

#include <unistd.h>
#include <iostream>
#include "PopupController.h"

#include <thread>
using namespace std;

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);

    PopupController::instance()->show();

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
            cout << "2. 자동으로 사각형 만들기  " << endl;
            cout << "3. 다른 쓰레드에서 이미지 생성 요청 하기   " << endl;
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
                PopupController::instance()->createComponent(qObjectName, qPosX, qPosY);
            }
                break;
            case 2:
                PopupController::instance()->requestCreateComponent("aa", 0, 50);
                break;
            case 3:
                PopupController::instance()->createComponent("aa", 0, 50);
                break;
            case 4: {

                string objectName = "";
                cout << "input ObjectName : " << endl;
                cin >> objectName;
                QString qObjectName = QString::fromUtf8(objectName.c_str());
                PopupController::instance()->destroyTest(qObjectName);
            }
                break;
            default:
                break;

            }

        }
    });


    return app.exec();
}
