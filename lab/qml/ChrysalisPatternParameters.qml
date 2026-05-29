import QtQuick
import QtQuick.Layouts
import QtQuick.Controls

import FigmaStyle

Item {
    property PatternParametersModel parameters: null

    HorizontalHeaderView {
        id: header
        anchors.top: parent.top
        anchors.left: tableView.left
        anchors.right: tableView.right
        syncView: tableView
        model: ["Name", "Value"]
    }

    TableView {
        id: tableView
        anchors.top: header.bottom
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.bottom: buttonRow.top   // ← stop above the buttons
        model: parameters

        columnWidthProvider: (col) => col === 0 ? 200 : width - 200

        delegate: Loader {
            required property int column
            required property int row
            required property var display

            height: 36
            width: tableView.columnWidthProvider(column)

            sourceComponent: column === 0 ? nameCell : valueCell

            Component {
                id: nameCell
                Rectangle {
                    border.color: "#e0e0e0"
                    Label {
                        anchors.fill: parent
                        anchors.margins: 8
                        text: display
                        verticalAlignment: Text.AlignVCenter
                    }
                }
            }

            Component {
                id: valueCell
                Rectangle {
                    border.color: "#e0e0e0"
                    TextField {
                        anchors.fill: parent
                        text: display
                        onEditingFinished: parameters.setValue(row, text)
                    }
                }
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