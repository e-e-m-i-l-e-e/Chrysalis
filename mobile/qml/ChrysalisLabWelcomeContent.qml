import QtQuick
import QtQuick.Dialogs
import QtQuick.Layouts
import QtQuick.Controls

import FigmaStyle

Item {
    anchors.fill: parent

    signal projectOpened(url filePath)
    signal createProject()

    ColumnLayout {

        anchors.centerIn: parent

        Button {
            width: 100
            text: "New project"
            icon.source: "FigmaStyle/dark/images/busyindicator-indicator.png"
            onClicked: createProject()
        }

        Button {
            width: 100
            text: "Open project"
            icon.source: "FigmaStyle/dark/images/busyindicator-indicator.png"
            onClicked: fileDialog.open()
        }

    }

    FileDialog {
        id: fileDialog
        title: "Open Project"
        onAccepted: () => {
            projectOpened(selectedFile)
        }
    }
}