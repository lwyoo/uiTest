import QtQuick 2.9
import QtQuick.Window 2.2

Window {
    visible: true
    width: 640
    height: 480
    title: qsTr("Hello World")

    Rectangle {
        id: temp1
        width: 1000
        height: 100
        color: "red"
        Text {
            text: "CubeR Regular ===  font.family : fontCube.name"
            font.family: "CubeR"
            font.pixelSize: 32
            horizontalAlignment: Text.AlignLeft
            verticalAlignment: Text.AlignVCenter
        }
    }


    Rectangle {
        id: temp2
        width: 1000
        height: 100
        anchors.top: temp1.bottom

        color: "red"
        Text {
            text: "CubeR Regular ===  font.family : fontCube.name"
            font.family: "CubeBa1"
            font.pixelSize: 32
            horizontalAlignment: Text.AlignLeft
            verticalAlignment: Text.AlignVCenter
        }
    }
}
