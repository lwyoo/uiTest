#include <QGuiApplication>
#include <QQmlApplicationEngine>

#include <unistd.h>
#include <iostream>
#include "PopupController.h"
#include "PopupManager.h"
#include <thread>

#include <functional>

#define MESSAGE_TEST 0
using namespace std;


struct PopupItem {

};

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);

    PopupController::instance()->show();

    PopupController::instance()->initMessageThread();

    PopupController::instance()->startMessageThread();

    PopupController::instance()->requestCreateComponent("aa", 0, 50);

    PopupController::instance()->requestCreateComponent("ccc", 300, 50);

    thread t1 = thread([&] {
        while(1)
        {
            int value;
            cout << endl;
            cout << endl;
            cout << endl;
            cout << endl;


            cout << "1. MessageQueue 미적용 버전" <<endl;
            cout << "2. MessageQueue 적용 버전 " <<endl;
            cout << "3. Index 초기화          " <<endl;
            cout << "4. Current State        " <<endl;


            cin >> value;



            switch (value) {

            case 1: {

                for(int i = 0 ; i < 1000000; i++) {
                    PopupController::instance()->putMessage("aa", 0, 50, i);
                }


            }
                break;
            case 2: {
                for(int i = 0 ; i < 10; i++) {
                    PopupController::instance()->putMessage("ccc", 0, 50, i);
                }

            }
                break;
            case 3: {

                PopupController::instance()->putMessage("aa", 0, 50, 0);

            }
                break;
            case 4: {
                PopupController::instance()->putMessage("aa", 0, 50, 2);
            }
                break;
            case 5: {
//                PopupController::instance()->createComponent("dd", 0, 50);
                PopupController::instance()->putMessage("dd", 0, 50, 0);
            }
                break;

            default:
                PopupController::instance()->check();
                cout << "Current : " << PopupController::instance()->getState().toStdString()  << endl;
                break;

            }

        }
    });

    return app.exec();
}
