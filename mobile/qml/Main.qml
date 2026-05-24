import QtQuick
import FigmaStyle
import PatternBuilder

Window {
    width: 800
    height: 600
    visible: true

    PatternBuilderScene {
        anchors.fill: parent
    }

    Button {
        id: button
        text: "test"
    }

    CheckBox {
        checked: true
        anchors.top: button.bottom
    }
}