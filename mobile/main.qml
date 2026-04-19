import QtQuick 2.15
import QtQuick.Controls 2.15

ApplicationWindow {
    visible: true
    width: 400
    height: 600

    Button {
        text: "Click me"
        anchors.centerIn: parent
        onClicked: console.log("Hello from QML")
    }
}