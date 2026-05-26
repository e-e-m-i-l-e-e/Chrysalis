import QtQuick
import QtQuick.Layouts

import FigmaStyle

Item {
    property ChrysalisPatternProject project: null

    QtObject {
        id: config
    }

    GridLayout {
        columns: 2
        anchors.margins: 10
        anchors.top: parent.top
        anchors.left: parent.left
        anchors.right: parent.right

        Label {
            text: "File Location"
        }
        RowLayout {
            TextField {
                text: project.filePath
                Layout.fillWidth: true
            }
            ToolButton {
                icon.source: "FigmaStyle/dark/images/busyindicator-indicator.png"
            }
            Layout.fillWidth: true
        }

        Label {
            text: "Name"
        }
        TextField {
            text: project.name
            onEditingFinished: project.name = text

            Layout.fillWidth: true
        }
    }
}