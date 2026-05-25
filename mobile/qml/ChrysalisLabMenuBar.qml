import QtQuick
import QtQuick.Controls

MenuBar {
    property ChrysalisPatternProject patternProject: null

    readonly property alias openPatternFileDialog: openPatternFileDialog
    readonly property alias savePatternFileDialog: savePatternFileDialog

    QtObject {
        id: config
        readonly property int menuBarHeight: 23;
    }

    ChrysalisPatternSaveFileDialog {
        id: openPatternFileDialog
        project: patternProject
    }

    ChrysalisPatternSaveFileDialog {
        id: savePatternFileDialog
        project: patternProject
    }

    height: implicitHeight

    delegate: MenuBarItem {
        height: config.menuBarHeight
        padding: 0
    }

    Menu {
        title: "File"
        padding: 0

        delegate: MenuItem {
            height: config.menuBarHeight
            padding: 0
        }

        MenuItem {
            id: newPatternAction
            text: "New Pattern"
            height: config.menuBarHeight
        }
        MenuItem {
            id: openProjectAction
            text: "Open"
            height: config.menuBarHeight
        }
        MenuItem {
            id: saveProjectAction
            text: "Save"
            // onTriggered: savePatternFileDialog.open()
            height: patternProject.hasProject ? config.menuBarHeight : 0
        }
        MenuItem {
            id: closeProjectAction
            text: "Close"
            height: patternProject.hasProject ? config.menuBarHeight : 0
        }
    }

    Component.onCompleted: {
        newPatternAction.triggered.connect(patternProject.createProject)
        closeProjectAction.triggered.connect(patternProject.closeProject)
    }
}