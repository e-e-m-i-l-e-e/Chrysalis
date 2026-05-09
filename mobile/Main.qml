import QtQuick
import QtQuick.Window

Window {
    width: 640
    height: 480
    visible: true
    title: "QmlApp"

    Rectangle {
        anchors.fill: parent
        color: "#202020"

        Text {
            anchors.centerIn: parent
            text: "Hello from QML"
            color: "white"
            font.pixelSize: 32
        }
    }
}