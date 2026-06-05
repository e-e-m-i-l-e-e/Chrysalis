import QtQuick
import QtQuick.Dialogs

import PatternBuilder

Item {
    property alias title: fileDialog.title
    property alias fileMode: fileDialog.fileMode
    property ChrysalisProject project: null

    function open() {
        fileDialog.open()
    }

    signal fileChosen(url filePath)

    FileDialog {
        id: fileDialog
        nameFilters: ["Chrysalis Project (*.chrysalis)"]
        defaultSuffix: "chrysalis"
        onAccepted: fileChosen(selectedFile)
    }
}