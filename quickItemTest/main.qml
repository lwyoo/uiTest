import QtQuick 2.9
import QtQuick.Window 2.2

Item {
    id: root
    objectName: "tttt"
    visible: true
    width: 100
    height: 100
    property real myOpacity: 0.5
    signal qmlSignal(string msg)

    Rectangle{
        //        anchors.fill: parent
        width: 100
        height: 100

        color: "yellow"
        y: 50
        opacity: myOpacity
        Component.onCompleted: {
            console.log("@@@@@@@@")
        }

        MouseArea{
            anchors.fill: parent
            onClicked: {
                console.log("@@@@@@@@")
                root.qmlSignal("tttttttttttttttt")
            }
        }
    }



    Rectangle{
        x: 300
        width: 100
        height: 100

        color: "blue"
        MouseArea{
            anchors.fill: parent
            onClicked: {
                console.log("@@@@@@@@ upOpacity")
                MainWindow.upOpacity()
            }
        }

    }
    Rectangle{
        x: 400
        width: 100
        height: 100

        color: "yellow"
        MouseArea{
            anchors.fill: parent
            onClicked: {
                console.log("@@@@@@@@ downOpacity")
                MainWindow.downOpacity()
            }
        }
    }

}
