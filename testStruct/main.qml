import QtQuick 2.6
import QtQuick.Controls 2.2
import QtQuick.Window 2.3

ApplicationWindow {

    id: applicationWindow

    visible: true
    width: 600
    height: 400
    title: qsTr("My App")

    Rectangle {
        id : mainform
        width: 100
        height: 100
        color: "red"

        Component.onCompleted: {

            //EDIT added more code to explain the use case.

//            console.log("name===="+classObj.mystr.val)

            console.log("name===="+classObj.mystr2.fullDescription)

            console.log("");
            console.log("");

            console.log("name===="+classObj.mystr2.vehicleInfo.bodyType)

            console.log("name===="+classObj.mystr2.vehicleInfo.vehicle_CD)



            console.log("test : "+classObj.mystr.val)
            console.log("test : "+classObj.mystr.name1)



        }
    }
}
