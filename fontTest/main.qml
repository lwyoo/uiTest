import QtQuick 2.9
import QtQuick.Window 2.2

Window {
    visible: true
    width: 1000
    height: 480
    title: qsTr("Hello World")

    Rectangle {
        id: temp1
        width: 1000
        height: 100
        color: "green"
        Text {
            text: "스마트 크루즈 컨트롤 시스템을 점검하십시오 - CubeR 최대 Maks"
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

        color: "green"
        Text {
            text: "스마트 크루즈 컨트롤 시스템을 점검하십시오 - CubeBa1 최대 Maks"
            font.family: "CubeBa1"
            font.pixelSize: 32
            horizontalAlignment: Text.AlignLeft
            verticalAlignment: Text.AlignVCenter
        }
    }

    Rectangle {
        id: temp3
        width: 1000
        height: 100
        anchors.top: temp2.bottom

        color: "green"
        Text {
            text: "스마트 크루즈 컨트롤 시스템을 점검하십시오 - Default 최대 Maks."
//            font.family: "CubeBa1"
            font.pixelSize: 32
            horizontalAlignment: Text.AlignLeft
            verticalAlignment: Text.AlignVCenter
        }
    }
}
