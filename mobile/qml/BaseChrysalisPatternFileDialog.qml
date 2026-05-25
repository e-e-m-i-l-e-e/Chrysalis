import QtQuick
import QtQuick.Dialogs

import PatternBuilder

Item {
    property alias title: fileDialog.title
    property alias fileMode: fileDialog.fileMode
    property ChrysalisPatternProject project: null

    function open() {
        fileDialog.open()
    }

    signal fileChosen(url filePath)

    FileDialog {
        id: fileDialog
        onAccepted: fileChosen(selectedFile)
    }
}