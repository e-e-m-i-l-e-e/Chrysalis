import QtQuick
import QtQuick.Layouts
import QtQuick.Controls
import Qt.labs.qmlmodels 1.0

import FigmaStyle
import PatternBuilder

ApplicationWindow {
    id: root
    visibility: Window.Maximized
    visible: true

    menuBar: ChrysalisLabMenuBar {
        patternProject: patternProject
    }

    contentData: ChrysalisPatternProject {
        id: patternProject
        anchors.fill: parent

        Loader {
            id: content
            anchors.fill: parent
            sourceComponent: patternProject.hasProject ? projectEditor : welcomeComponent
        }

        Component {
            id: welcomeComponent
            ChrysalisLabWelcomeContent {
                Component.onCompleted: {
                    projectOpened.connect(patternProject.openProject)
                    createProject.connect(patternProject.createProject)
                }
            }
        }

        Component {
            id: projectEditor
            SplitView {
                anchors.fill: parent
                orientation: Qt.Horizontal

                Item {
                    SplitView.minimumWidth: root.width / 3
                    SplitView.maximumWidth: root.width / 2

                    TabBar {
                        id: stageTab
                        rotation: -90
                        transformOrigin: Item.TopLeft
                        width: parent.height
                        x: 0
                        y: parent.height

                        currentIndex: 0

                        TabButton {
                            text: "Construction"
                            width: implicitWidth
                        }
                        TabButton {
                            text: "Parameters"
                            width: implicitWidth
                        }
                        TabButton {
                            text: "Project"
                            width: implicitWidth
                        }
                    }

                    StackLayout {
                        currentIndex: stageTab.currentIndex
                        anchors {
                            left: parent.left
                            margins: 8
                            leftMargin: stageTab.height + 8
                            right: parent.right
                            top: parent.top
                            bottom: parent.bottom
                        }

                        Item {
                            TabBar {
                                id: patternTab
                                rotation: -90
                                transformOrigin: Item.TopLeft
                                width: parent.height
                                x: 0
                                y: parent.height

                                currentIndex: 0

                                TabButton {
                                    text: "Pattern 1"
                                    width: implicitWidth
                                }
                                TabButton {
                                    text: "Pattern 2"
                                    width: implicitWidth
                                }
                            }
                            StackLayout {
                                currentIndex: patternTab.currentIndex
                                anchors {
                                    left: parent.left
                                    margins: 8
                                    leftMargin: patternTab.height + 8
                                    right: parent.right
                                    top: parent.top
                                    bottom: parent.bottom
                                }

                                ColumnLayout {
                                    spacing: 6
                                    anchors.margins: 8

                                    Label { text: "Pattern 1"; font.bold: true }
                                    MenuSeparator { Layout.fillWidth: true }
                                    Button { text: "Add Layer"; Layout.fillWidth: true }
                                    CheckBox { checked: true; text: "Visible" }
                                    Item { Layout.fillHeight: true }
                                }

                                ColumnLayout {
                                    spacing: 6
                                    anchors.margins: 8

                                    Label { text: "Pattern 2"; font.bold: true }
                                    MenuSeparator { Layout.fillWidth: true }
                                    Button { text: "Add Layer"; Layout.fillWidth: true }
                                    CheckBox { checked: true; text: "Visible" }
                                    Item { Layout.fillHeight: true }
                                }
                            }
                        }

                        ColumnLayout {
                            spacing: 6
                            anchors.margins: 8

                            Label { text: "Parameters"; font.bold: true }
                            MenuSeparator { Layout.fillWidth: true }

                            // Dummy table
                            HorizontalHeaderView {
                                id: header
                                syncView: tableView
                                Layout.fillWidth: true
                            }

                            TableView {
                                id: tableView
                                Layout.fillWidth: true
                                Layout.fillHeight: true
                                clip: true

                                model: TableModel {
                                    TableModelColumn { display: "name" }
                                    TableModelColumn { display: "type" }
                                    TableModelColumn { display: "value" }

                                    rows: [
                                        { name: "Layer 1", type: "Shape",  value: "Circle" },
                                        { name: "Layer 2", type: "Color",  value: "#ff0000" },
                                        { name: "Layer 3", type: "Shape",  value: "Rect" },
                                        { name: "Layer 4", type: "Offset", value: "10, 20" },
                                        { name: "Layer 5", type: "Scale",  value: "1.5" },
                                    ]
                                }

                                delegate: Rectangle {
                                    implicitWidth: 80
                                    implicitHeight: 24
                                    border.color: "#e0e0e0"
                                    border.width: 1
                                    color: row % 2 === 0 ? palette.base : palette.alternateBase

                                    Label {
                                        anchors.centerIn: parent
                                        text: display
                                        font.pixelSize: 12
                                        elide: Text.ElideRight
                                    }
                                }
                            }

                            Button { text: "Add Layer"; Layout.fillWidth: true }
                            CheckBox { checked: true; text: "Visible" }
                        }
                    }
                }

                Item {
                    SplitView.fillWidth: true
                    SplitView.fillHeight: true

                    PatternBuilderScene {
                        anchors.fill: parent
                    }
                }
            }
        }
    }
}