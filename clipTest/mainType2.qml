import QtQuick 2.9
import QtQuick.Window 2.2


Window {
    visible: true
    width: 640
    height: 720
    title: qsTr("Hello World")
    property real imageWidth: 1022
    property real popupDuration: 200

    property string popupState: "hide"
    property real middleShowY: 516
    property real fullShowY: 516 + 138
    property bool enableAnimation: true

    onPopupStateChanged: {
        console.log("value : " , popupState)

        testItem.state = popupState
        testBG.state = popupState
        testItem2.state = popupState
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
            },
            State {
                name: "middleShow"
                PropertyChanges {
                    target: testBG
                    width: 1022
                    x:0
                }
            },
            State {
                name: "middleHide"
                PropertyChanges {
                    target: testBG
                    width: 1022
                    x:0
                }
            }
        ]
        Behavior on width {
            NumberAnimation { duration: enableAnimation? popupDuration : 0 }
        }
        Behavior on x {
            NumberAnimation { duration: enableAnimation? popupDuration : 0 }
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
            },
            State {
                name: "middleShow"
                PropertyChanges {
                    target: testImageBottom
                    y: middleShowY
                }
                PropertyChanges {
                    target: testItem
                    width: imageWidth/2
                    x: 0
                }
            },
            State {
                name: "middleHide"
                PropertyChanges {
                    target: testItem
                    width: imageWidth/2
                    x: 0
                }
                PropertyChanges {
                    target: testImageBottom
                    y: fullShowY
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
            Behavior on y {
                NumberAnimation { duration: enableAnimation? popupDuration : 0 }
            }
        }

        Behavior on width {
            NumberAnimation { duration: enableAnimation? popupDuration : 0 }
        }
        Behavior on x {
            NumberAnimation { duration: enableAnimation? popupDuration : 0 }
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
            },
            State {
                name: "middleShow"
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
                PropertyChanges {
                    target: testImage2
                    y: middleShowY
                }
            },
            State {
                name: "middleHide"
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
                PropertyChanges {
                    target: testImage2
                    y: fullShowY
                }
            }
        ]
        Image {
            id: testImageTop2
            x: -imageWidth
            source: "POP_UP_TOP_R.png"
            Behavior on x {
                NumberAnimation { duration: enableAnimation? popupDuration : 0 }
            }

        }

        Image {
            id: testImage2
            x: -imageWidth
            y:652
            source: "POP_UP_BOTTOM_W.png"
            Behavior on x {
                NumberAnimation { duration: enableAnimation? popupDuration : 0 }
            }
            Behavior on y {
                NumberAnimation { duration: enableAnimation? popupDuration : 0 }
            }
        }

        Behavior on width {
            NumberAnimation { duration: enableAnimation? popupDuration : 0 }
        }
        Behavior on x {
            NumberAnimation { duration: enableAnimation? popupDuration : 0 }
        }
    }

    ////////////////////////////////////
    ////           data area        ////
    ////////////////////////////////////
    Text {
        id: testText
        text: qsTr("text")
        color: "black"
        font.pixelSize : 100
        opacity: 0

        Behavior on opacity {
            NumberAnimation { duration: enableAnimation? popupDuration : 0 }
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

    Rectangle{
        x: 400
        y: 500
        width: 100
        height: 100
        color: "blue"
        MouseArea{
            anchors.fill: parent
            onClicked: {
                if (popupState === "show" || popupState === "middleHide") {
                    popupState = "middleShow"
                } else {
                    popupState = "middleHide"
                }

            }
        }
    }
}

