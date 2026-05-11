import QtQuick
import QtQuick.Controls
import QtOpenGLApp

ApplicationWindow {
    id: root
    visible: true
    width: 800; height: 600
    title: "Polygon outline"
    color: "#14141e"

    OpenGLItem {
        anchors {
            top:    parent.top
            left:   parent.left
            right:  parent.right
            bottom: infoLabel.top
            bottomMargin: 12
        }

        points: [
            Qt.point(0,  0),  Qt.point(10, 0),
            Qt.point(10, 10), Qt.point(0,  10)
        ]
        lineColor: "#00d4ff"
        lineWidth: 2.0
        pointSize: 14.0
    }

    Text {
        id: infoLabel
        anchors { bottom: parent.bottom
            horizontalCenter: parent.horizontalCenter
            bottomMargin: 16 }
        text: "GL_LINE_LOOP — simple polygon outline"
        color: "#aaaacc"
        font { pixelSize: 14; family: "monospace" }
    }
}