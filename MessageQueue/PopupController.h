#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QQuickItem>
#include <QQuickView>

class PopupController : public QQuickView
{
    Q_OBJECT

public:
    static QSharedPointer<PopupController> instance(QQuickView *parent=Q_NULLPTR);
    void findChiledItem(const QString objectName);
    void destroyTest(const QString objName);

//    bool requestCreateComponent(const QString objectName, const qreal posX, const qreal posY);


    void createComponent(const QString objectName, const qreal posX, const qreal posY);
    void requestCreateComponent(const QString objectName, const qreal posX, const qreal posY);


    void updateQml();

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




};

#endif // MAINWINDOW_H
