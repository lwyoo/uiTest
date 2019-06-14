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

    // standard in/out , use terminor
//    thread t1 = thread([&] {
//        while(1)
//        {
//            int value;
//            cout << endl;
//            cout << endl;
//            cout << endl;
//            cout << endl;

//            cout << "1. create Component " << endl;
//            cout << "2. 자동으로 사각형 만들기  " << endl;
//            cout << "3. 다른 쓰레드에서 이미지 생성 요청 하기   " << endl;
//            cout << "4. destroy item" << endl;


//            cin >> value;



//            switch (value) {
////            case 1: {
////                string objectName = "";
////                cout << "input ObjectName : " << endl;
////                cin >> objectName;
////                QString qObjectName = QString::fromUtf8(objectName.c_str());

////                int posX;
////                qreal qPosX;
////                cout << "input position X  : " << endl;
////                cin >> posX;
////                qPosX = static_cast<qreal>(posX);

////                int posY;
////                qreal qPosY;
////                cout << "input position Y  : " << endl;
////                cin >> posY;
////                qPosY = static_cast<qreal>(posY);
////                PopupController::instance()->requestCreateComponent(qObjectName, qPosX, qPosY);
////                //                PopupController::instance()->createComponent(qObjectName, qPosX, qPosY);
////            }
////                break;
////            case 2:
////                PopupController::instance()->requestCreateComponent("aa", 0, 50);
////                break;
////            case 3:
////                //                PopupController::instance()->createComponent("aa", 0, 50);
////                for(int i = 0 ; i < 10001; i++)
////                    PopupController::instance()->updateQml();
////                break;
////            case 4: {

////                string objectName = "";
////                cout << "input ObjectName : " << endl;
////                cin >> objectName;
////                QString qObjectName = QString::fromUtf8(objectName.c_str());
////                PopupController::instance()->destroyTest(qObjectName);
////            }
//            case 1: {
//                PopupController::instance()->initMessageThread();

//                }
//                break;
//            case 2: {
//                PopupController::instance()->makeMessage();

//                }
//                break;
//            case 3: {
//                PopupController::instance()->startMessageThread();

//                }
//                break;
//            default:
//                break;

//            }

//        }
//    });



#if MESSAGE_TEST
    //message Test
    thread t1 = thread([&] {
        while(1)
        {
            int value;
            cout << endl;
            cout << endl;
            cout << endl;
            cout << endl;

            cout << "1. initMessageThread" << endl;
            cout << "2. makeMessage  " << endl;
            cout << "3. [start] MessageThread   " << endl;
            cout << "4. [resum] MessageThread   " << endl;
            cout << "5. [stop ] MessageThread   " << endl;
            cout << "6. Current Message State" << endl;

            cin >> value;


            switch (value) {
            case 1: {
                PopupController::instance()->initMessageThread();

                }
                break;
            case 2: {
                PopupController::instance()->makeMessage();

                }
                break;
            case 3: {
                PopupController::instance()->startMessageThread();
                }
                break;
            case 4: {
                PopupController::instance()->resumeMessageThread();
                }
                break;
            case 5: {
                PopupController::instance()->stopMessageThread();
                }
            case 6: {
                cout << "Current : " << PopupController::instance()->getState().toStdString()  << endl;

            }
                break;
            default:
                break;

            }

        }
    });
#endif
    //    PopupController::instance()->requestCreateComponent("aa", 0, 50);
    //    PopupManager::instance()->slotUpdateQml();


    PopupController::instance()->initMessageThread();

    PopupController::instance()->startMessageThread();

    PopupController::instance()->requestCreateComponent("aa", 0, 50);


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

                    for(int i = 0 ; i < 10000000; i++) {
                        PopupController::instance()->putMessage("aa", 0, 50, i);
                    }


                    }
                    break;
                case 2: {
                    for(int i = 0 ; i < 100000; i++)
                        PopupManager::instance()->updateCount(i);

                    }
                    break;
                case 3: {

                    PopupController::instance()->putMessage("aa", 0, 50, 0);

                    }
                    break;
                case 4: {
                    PopupController::instance()->putMessage("aa", 0, 50, 2);
                    cout << "Current : " << PopupController::instance()->getState().toStdString()  << endl;
//                    PopupController::instance()->putMessage("aa", 0, 50, 2);
                }
                    break;
                default:
                    break;

                }

            }
        });

    return app.exec();
}
