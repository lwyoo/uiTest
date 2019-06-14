#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QQuickItem>
#include <QQuickView>

#include "MessageThread.h"


struct PopupItemItem {
    QString popupType;
    QString requestType;
    QString data;

};

struct PopupTestItem {
    QString objName;
    int posX;
    int posY;
    int myCount;
};

class PopupController : public QQuickView
{
    Q_OBJECT

public:
    static QSharedPointer<PopupController> instance(QQuickView *parent=Q_NULLPTR);
    void findChiledItem(const QString objectName);
    void destroyTest(const QString objName);

    void createComponent(const QString objectName, const qreal posX, const qreal posY);
    void requestCreateComponent(const QString objectName, const qreal posX, const qreal posY);


    void updateQml();


    ~PopupController();





private:
    explicit PopupController(QQuickView *parent = nullptr );

//    void connectionSignal();

// test code
//signals:
//    void signalCreateComponent(const QString objectName, const qreal posX, const qreal posY);


//    void testSignal(QString, qreal, qreal);

public slots:
    void testSlot(QString ob, qreal posX, qreal posY);
    void testSceneGraphInitialized();
    void testsceneGraphInvalidated ()  ;
    void testbeforeSynchronizing   ()  ;
    void testafterSynchronizing    ()  ;
    void testbeforeRendering       ()  ;
    void testafterRendering        ()  ;
    void testafterAnimating        ()  ;
    void testsceneGraphAboutToStop ()  ;
    void testactiveFocusItemChanged()  ;


public:

    void initMessageThread();
    void makeMessage();
    void putMessage(const QString objectName, const qreal posX, const qreal posY, const int myCount);
    void startMessageThread();
    void resumeMessageThread();
    void stopMessageThread();

    int dispatch(void* msg);
    QString getState();


    MessageThread* m_msgThread;
private:
    int mIndex = 0;

};

#endif // MAINWINDOW_H
