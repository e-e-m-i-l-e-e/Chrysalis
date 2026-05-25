import QtQuick
import QtQuick.Dialogs
import QtQuick.Layouts
import QtQuick.Controls

import FigmaStyle

Item {
    anchors.fill: parent
    Button {
        text: "Open project"
        anchors.centerIn: parent
        icon.source: "FigmaStyle/dark/images/busyindicator-indicator.png"
        onClicked: fileDialog.open()
    }

    FileDialog {
        id: fileDialog
        title: "Open Project"
    }
}