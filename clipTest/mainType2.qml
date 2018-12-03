import QtQuick 2.9
import QtQuick.Window 2.2


Window {
    visible: true
    width: 640
    height: 720
    title: qsTr("Hello World")
    property real imageWidth: 1022
    property real popupDuration: 1000

    property string popupState: "hide"

    onPopupStateChanged: {
        console.log("value : " , popupState)
        testItem.state = popupState
        testItem2.state = popupState
        testBG.state = popupState
    }

    ////////////////////////////////////
    ////           bg               ////
    ////////////////////////////////////
    Rectangle{
        id: testBG
        x: 1022/2
        width: 0
        height: 720
        color: "yellow"

        states: [
            State {
                name: "show"
                PropertyChanges {
                    target: testBG
                    width: 1022
                    x:0
                }
            },
            State {
                name: "hide"
                PropertyChanges {
                    target: testBG
                    width: 0
                }
            }
        ]
        Behavior on width {
            NumberAnimation { duration: popupDuration }
        }
        Behavior on x {
            NumberAnimation { duration: popupDuration }
        }
    }

    ////////////////////////////////////
    ////      left top & bottom     ////
    ////////////////////////////////////
    Item{
        id: testItem
        x: imageWidth/2

        width: 0
        height: 720
        clip : true

        states: [
            State {
                name: "show"
                PropertyChanges {
                    target: testItem
                    width: imageWidth/2
                    x: 0
                }
                PropertyChanges {
                    target: testText
                    opacity:1
                }
            },
            State {
                name: "hide"
                PropertyChanges {
                    target: testItem
                    width: 0
                    x: imageWidth/2
                }
            }
        ]

        Image {
            id: testImageTop
            source: "POP_UP_TOP_R.png"
        }

        Image {
            id: testImageBottom
            y:652
            source: "POP_UP_BOTTOM_W.png"
        }

        Behavior on width {
            NumberAnimation { duration: popupDuration }
        }
        Behavior on x {
            NumberAnimation { duration: popupDuration }
        }
    }

    Text {
        id: testText
        text: qsTr("text")
        color: "black"
        font.pixelSize : 100
        opacity: 0


        Behavior on opacity {
            NumberAnimation { duration: popupDuration }
        }
    }

    ////////////////////////////////////
    ////     right top & bottom     ////
    ////////////////////////////////////
    Item{
        id: testItem2
        x: imageWidth/2

        width: 0
        height: 720
        clip : true

        states: [
            State {
                name: "show"
                PropertyChanges {
                    target: testItem2
                    width: imageWidth/2
                }
                PropertyChanges {
                    target: testImage2
                    x: -imageWidth/2
                }
                PropertyChanges {
                    target: testImageTop2
                    x: -imageWidth/2
                }
            },
            State {
                name: "hide"
                PropertyChanges {
                    target: testItem2
                    x: imageWidth/2
                    width: 0

                }
            }
        ]
        Image {
            id: testImageTop2
            x: -imageWidth
            source: "POP_UP_TOP_R.png"
            Behavior on x {
                NumberAnimation { duration: popupDuration }
            }
        }

        Image {
            id: testImage2
            x: -imageWidth
            y:652
            source: "POP_UP_BOTTOM_W.png"
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

    ////////////////////////////////////
    ////     show & hide button     ////
    ////////////////////////////////////
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

