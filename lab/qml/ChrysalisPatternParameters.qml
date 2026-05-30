import QtQuick
import QtQuick.Layouts
import QtQuick.Controls

import FigmaStyle

Item {
    id: root
    property ChrysalisParametersModel parameters: null

    function clearFocus() {
        root.forceActiveFocus()
    }

    // Dismisses text field focus when clicking background/empty layout areas
    TapHandler {
        onTapped: root.clearFocus()
    }

    // 1. Button Row sits at the very top
    RowLayout {
        id: buttonRow
        anchors.top: parent.top
        anchors.left: parent.left
        anchors.right: parent.right
        height: 40
        spacing: 8

        // Invisible spacer that pushes everything after it to the right
        Item {
            Layout.fillWidth: true
        }

        Button {
            text: "Add"
        }
    }

    // 2. Header Container shifts down beneath the button row
    Item {
        id: headerContainer
        anchors.top: buttonRow.bottom
        anchors.left: parent.left
        anchors.right: parent.right
        height: headerView.height + 4

        Rectangle {
            anchors.top: parent.top
            anchors.left: parent.left
            anchors.right: parent.right
            height: 2
            color: palette.highlight
            z: 1
        }

        HorizontalHeaderView {
            id: headerView
            syncView: tableView
            anchors.top: parent.top
            anchors.topMargin: 2
            anchors.left: parent.left
            anchors.right: parent.right
            resizableColumns: false

            delegate: Rectangle {
                implicitHeight: 32
                color: "#101012"

                Rectangle {
                    anchors.right: parent.right
                    anchors.top: parent.top
                    anchors.bottom: parent.bottom
                    anchors.topMargin: 4
                    anchors.bottomMargin: 4
                    width: 1
                    color: palette.midlight
                    visible: column < tableView.columns - 1
                }

                Text {
                    anchors.fill: parent
                    text: model.display
                    color: palette.brightText
                    font.pixelSize: 13
                    font.weight: Font.Bold
                    font.family: Qt.application.font.family
                    font.letterSpacing: Qt.application.font.letterSpacing
                    verticalAlignment: Text.AlignVCenter
                    horizontalAlignment: Text.AlignHCenter
                }
            }
        }

        Rectangle {
            anchors.bottom: parent.bottom
            anchors.left: parent.left
            anchors.right: parent.right
            height: 2
            color: palette.highlight
            z: 1
        }
    }

    // 3. Table View stretches to fill the rest of the bottom space
    TableView {
        id: tableView
        model: parameters
        anchors.top: headerContainer.bottom
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.bottom: parent.bottom // Anchored all the way to the bottom
        anchors.topMargin: -1

        columnWidthProvider: function(column) {
            let firstColumnWidth = 0.4;
            if (column === 0) return firstColumnWidth * tableView.width;
            return (1 - firstColumnWidth) * tableView.width / (tableView.columns - 1)
        }

        delegate: Rectangle {
            implicitWidth: tableView.columnWidthProvider(column)
            implicitHeight: 25
            color: (row % 2 === 0) ? palette.window : palette.alternateBase
            clip: true

            Rectangle {
                anchors.bottom: parent.bottom
                anchors.left: parent.left
                anchors.right: parent.right
                height: 1
                color: palette.mid
            }

            Rectangle {
                anchors.right: parent.right
                anchors.top: parent.top
                anchors.bottom: parent.bottom
                width: 1
                color: palette.mid
                visible: column < tableView.columns - 1
            }

            Rectangle {
                anchors.fill: parent
                color: "transparent"
                border.color: palette.highlight
                border.width: 1
                visible: textField.activeFocus
                z: 1
            }

            Rectangle {
                anchors.left: parent.left
                anchors.top: parent.top
                anchors.bottom: parent.bottom
                width: 2
                color: palette.highlight
                visible: textField.activeFocus
                z: 2
            }

            TextField {
                id: textField
                width: parent.width
                height: parent.height
                anchors.centerIn: parent
                leftPadding: 12
                rightPadding: 10
                topPadding: 5
                bottomPadding: 5
                leftInset: 0
                rightInset: 0
                topInset: 0
                bottomInset: 0
                color: activeFocus ? palette.brightText : palette.text
                selectionColor: palette.highlight
                selectedTextColor: palette.highlightedText
                placeholderTextColor: palette.placeholderText
                text: display
                background: Rectangle {
                    color: "transparent"
                    radius: 0
                    border.width: 0
                }
                horizontalAlignment: TextInput.AlignHCenter
                onAccepted: root.forceActiveFocus()
                onEditingFinished: {
                    model.display = textField.text
                }
            }
        }
    }
}