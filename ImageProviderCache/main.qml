import QtQuick 2.9
import QtQuick.Window 2.2

Window {
    visible: true
    width: 640
    height: 480
    title: qsTr("Hello World")

    Item {
        width: 640
        height: 480


        Grid {
            columns: 2
            anchors.fill: parent

            Image {
                //source: "image://cache/1"
                id: image1
//                asynchronous: true
                cache: false
                width: parent.width/2
                height: parent.height/2
//                clip: true
            }

            Image {
                //source: "image://cache/2"
                id: image2
//                asynchronous: true
                cache: false
                width: parent.width/2
                height: parent.height/2
//                clip: true
            }

            Image {
                //source: "image://cache/3"
                id: image3
//                asynchronous: true
                cache: false
                width: parent.width/2
                height: parent.height/2
//                clip: true
            }

            Image {
                //source: "image://cache/4"
                id: image4
//                asynchronous: true
                cache: false
                width: parent.width/2
                height: parent.height/2
//                clip: true
            }
        }

        MouseArea {
            property var flag: false
            anchors.fill: parent
            onClicked: {
                if (flag)
                {
                    image1.source = ""
                    image2.source = ""
                    image3.source = ""
                    image4.source = ""
                    flag = false
                }

                else
                {
                    image1.source = "image://cache/1"
                    image2.source = "image://cache/2"
                    image3.source = "image://cache/3"
                    image4.source = "image://cache/4"
                    flag = true
                }
            }
        }
    }
}
