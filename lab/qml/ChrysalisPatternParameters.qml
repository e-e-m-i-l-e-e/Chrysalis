import QtQuick
import QtQuick.Layouts
import QtQuick.Controls

import FigmaStyle

Item {
    property ChrysalisParametersModel parameters: null

    HorizontalHeaderView {
        id: headerView
        syncView: tableView
        anchors.top: parent.top
        anchors.left: parent.left
        anchors.right: parent.right
    }

    TableView {
        id: tableView
        model: parameters
        anchors.top: headerView.bottom
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.bottom: buttonRow.top

        delegate: Rectangle {
            implicitWidth: tableView.width / 4
            implicitHeight: 20

            TextEdit {
                anchors.centerIn: parent
                text: display ?? ""
            }
        }
    }

    RowLayout {
        id: buttonRow
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.bottom: parent.bottom

        Button { text: "Add" }
    }
}