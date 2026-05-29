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
        parameters: PatternParametersModel {}
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

                        x: 0
                        y: parent.height
                        width: parent.height
                        rotation: -90
                        transformOrigin: Item.TopLeft

                        LayoutMirroring.enabled: true
                        LayoutMirroring.childrenInherit: true

                        currentIndex: 0

                        TabButton {
                            text: "Project"
                            width: implicitWidth
                            topPadding: 0
                        }

                        TabButton {
                            text: "Parameters"
                            width: implicitWidth
                            topPadding: 0
                        }

                        TabButton {
                            text: "Construction"
                            width: implicitWidth
                            topPadding: 0
                        }
                    }

                    StackLayout {
                        currentIndex: stageTab.currentIndex
                        anchors {
                            left: parent.left
                            margins: 0
                            leftMargin: stageTab.height
                            right: parent.right
                            top: parent.top
                            bottom: parent.bottom
                        }

                        ChrysalisProjectData {
                            project: patternProject
                        }

                        ChrysalisPatternParameters {
                            parameters: patternProject.parameters
                        }

                        Item {
                            TabBar {
                                id: patternTab

                                x: 0
                                y: parent.height
                                width: parent.height
                                rotation: -90
                                transformOrigin: Item.TopLeft

                                LayoutMirroring.enabled: true
                                LayoutMirroring.childrenInherit: true

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