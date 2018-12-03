import QtQuick 2.9
import QtQuick.Window 2.2

Window {
    visible: true
    width: 640
    height: 480
    title: qsTr("Hello World")

    property string popupState: "hide"
    property real imageWidth: 1022
    property real popupDuration: 1000

    onPopupStateChanged: {
        console.log("value : " , popupState)
        testItem.state = popupState
    }

    Item{
        id:testItem
        width: 0
        height: 720
        clip:true
//        color: "red"
        x: 1100/2


        states: [
            State {
                name: "show"
                PropertyChanges {
                    target: testItem
                    width:imageWidth
                    x: 0
                }
                PropertyChanges {
                    target: testImage
                    x: 0
                }
                PropertyChanges {
                    target: testImageTop
                    x: 0
                }
            },
            State {
                name: "hide"
                PropertyChanges {
                    target: testItem
                    width:0
                    x: 1100/2
                }
                PropertyChanges {
                    target: testImage
                    x: -1100/2
                }
                PropertyChanges {
                    target: testImageTop
                    x: -1100/2
                }
            }

        ]

        Image {
            id: testImageTop
            source: "POP_UP_TOP_R.png"
            x: -imageWidth/2
            Behavior on x {
                NumberAnimation { duration: popupDuration }
            }
        }


        Image {
            id: testImage
            source: "POP_UP_BOTTOM_W.png"
            x: -imageWidth/2
            y:652
            Behavior on x {
                NumberAnimation { duration: popupDuration }
            }
        }
        Behavior on width {
            NumberAnimation { duration: popupDuration }
        }
        Behavior on x {
            NumberAnimation { duration: popupDuration }
        }
    }

    Rectangle{
        x: 100
        y: 500
        width: 100
        height: 100
        color: "red"
        MouseArea{
            anchors.fill: parent
            onClicked: {
                if (popupState === "show") {
                    popupState = "hide"
                } else {
                    popupState = "show"
                }
            }
        }
    }
}

