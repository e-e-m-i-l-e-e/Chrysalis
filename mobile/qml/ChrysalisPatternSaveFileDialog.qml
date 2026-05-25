import QtQuick
import QtQuick.Dialogs

Item {
    property alias project: fileDialog.project

    function open() {
        fileDialog.open()
    }

    QtObject {
        id: config
        readonly property string title: "Save pattern project"
    }

    BaseChrysalisPatternFileDialog {
        id: fileDialog
        title: config.title
        fileMode: FileDialog.SaveFile

        Component.onCompleted: {
            fileChosen.connect(project.saveProject)
        }
    }
}