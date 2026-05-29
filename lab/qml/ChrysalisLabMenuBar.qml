import QtQuick
import QtQuick.Controls

MenuBar {
    property ChrysalisProject patternProject: null

    readonly property alias openPatternFileDialog: openPatternFileDialog
    readonly property alias savePatternFileDialog: savePatternFileDialog

    QtObject {
        id: config
    }

    ChrysalisPatternOpenFileDialog {
        id: openPatternFileDialog
        project: patternProject
    }

    ChrysalisPatternSaveFileDialog {
        id: savePatternFileDialog
        project: patternProject
    }

    id: menuBar
    topPadding: 2
    bottomPadding: 2

    delegate: MenuBarItem {
        topPadding: 0
        bottomPadding: 0
    }

    Menu {
        title: "File"

        MenuItem {
            id: newPatternAction
            text: "New Pattern"
            height: menuBar.height
            onTriggered: patternProject.createProject()
        }
        MenuItem {
            id: openProjectAction
            text: "Open"
            height: menuBar.height
            onTriggered: openPatternFileDialog.open()
        }
        MenuItem {
            id: saveProjectAction
            text: "Save"
            height: patternProject.hasProject ? menuBar.height : 0
            onTriggered: savePatternFileDialog.open()
        }
        MenuItem {
            id: closeProjectAction
            text: "Close"
            height: patternProject.hasProject ? menuBar.height : 0
            onTriggered: patternProject.closeProject()
        }
    }
}