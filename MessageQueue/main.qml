import QtQuick 2.9
import QtQuick.Window 2.2

Item {
    visible: true
    width: 100
    height: 100
    property string myQml:""
    property int myCount:0
    onMyQmlChanged: {
        console.log("onMyQmlChanged")
    }


    Rectangle{
        anchors.fill: parent
        color: "red"
    }
    Rectangle {
        width: 100; height: 100; color: "green"
        RotationAnimation on rotation {
            loops: Animation.Infinite
            from: 0
            to: 360
        }
    }

//    Loader {
//        source: myQml
////        source: "MyRec1.qml"
//    }


    Text {
        id: name
        font.pointSize : 30
        text: myCount
    }

}
