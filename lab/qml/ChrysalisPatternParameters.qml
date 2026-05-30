import QtQuick
import QtQuick.Layouts
import QtQuick.Controls

import FigmaStyle

Item {
    property ChrysalisParametersModel parameters: null

    Item {
        id: headerContainer
        anchors.top: parent.top
        anchors.left: parent.left
        anchors.right: parent.right
        height: headerView.height + 2 + 1  // accent top + accent bottom

        // Top accent
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
            anchors.topMargin: 2       // push down below top accent
            anchors.left: parent.left
            anchors.right: parent.right

            delegate: Rectangle {
                implicitHeight: 32
                color: "#101012"

                // Column separator
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

        // Bottom accent
        Rectangle {
            anchors.bottom: parent.bottom
            anchors.left: parent.left
            anchors.right: parent.right
            height: 1
            color: palette.highlight
            z: 1
        }
    }

    TableView {
        id: tableView
        model: parameters
        resizableColumns: true
        anchors.top: headerContainer.bottom
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.bottom: buttonRow.top

        readonly property real minColumnWidth: 60

        columnWidthProvider: function(col) {
            const explicit = explicitColumnWidth(col)
            if (explicit > 0) return Math.max(minColumnWidth, explicit)

            let usedWidth = 0
            let freeCols = 0
            for (let i = 0; i < columns; i++) {
                const w = explicitColumnWidth(i)
                if (w > 0) usedWidth += w
                else freeCols++
            }
            return Math.max(minColumnWidth, (width - usedWidth) / Math.max(1, freeCols))
        }

        onLayoutChanged: {
            let clamped = false
            for (let i = 0; i < columns; i++) {
                const w = explicitColumnWidth(i)
                if (w > 0 && w < minColumnWidth) {
                    setColumnWidth(i, minColumnWidth)
                    clamped = true
                }
            }
            if (clamped) Qt.callLater(forceLayout)
        }

        onWidthChanged: forceLayout()
        onColumnsChanged: {
            if (columns > 0) forceLayout()
        }

        delegate: Rectangle {
            implicitHeight: 25
            color: (row % 2 === 0) ? palette.window : palette.alternateBase
            clip: true

            // Row divider
            Rectangle {
                anchors.bottom: parent.bottom
                anchors.left: parent.left
                anchors.right: parent.right
                height: 1
                color: palette.mid
            }

            // Column divider
            Rectangle {
                anchors.right: parent.right
                anchors.top: parent.top
                anchors.bottom: parent.bottom
                width: 1
                color: palette.mid
                visible: column < tableView.columns - 1
            }

            // Focus border
            Rectangle {
                anchors.fill: parent
                color: "transparent"
                border.color: palette.highlight
                border.width: 1
                visible: textField.activeFocus
                z: 1
            }

            // Focus left accent bar
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
            }
        }
    }

    RowLayout {
        id: buttonRow
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        spacing: 8

        Button { text: "Add" }
    }
}