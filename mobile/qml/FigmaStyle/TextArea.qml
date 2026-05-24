import QtQuick
import QtQuick.Controls.impl
import QtQuick.Templates as T

T.TextArea {
    id: control

    implicitWidth: Math.max((background.minimumWidth || implicitBackgroundWidth)
                            + leftInset + rightInset,
                            contentWidth + leftPadding + rightPadding)
    implicitHeight: Math.max((background.minimumHeight || implicitBackgroundHeight)
                            + topInset + bottomInset,
                            contentHeight + topPadding + bottomPadding)

    topPadding: __config.topPadding || 0
    bottomPadding: __config.bottomPadding || 0
    leftPadding: __config.leftPadding || 0
    rightPadding: __config.rightPadding || 0

    topInset: -__config.topInset || 0
    bottomInset: -__config.bottomInset || 0
    leftInset: -__config.leftInset || 0
    rightInset: -__config.rightInset || 0

    color: control.palette.text
    selectionColor: control.palette.highlight
    selectedTextColor: control.palette.highlightedText
    verticalAlignment: control.__config.label.textVAlignment
    horizontalAlignment: control.__config.label.textHAlignment
    placeholderTextColor: control.palette.placeholderText

    readonly property string __currentState: [
        !enabled && "disabled",
        activeFocus && "focused",
        enabled && !activeFocus && hovered && "hovered",
    ].filter(Boolean).join("_") || "normal"
    readonly property var __config: Config.controls.textarea[__currentState] || {}

    PlaceholderText {
        id: placeholder
        x: control.leftPadding
        y: control.topPadding
        width: control.width - (control.leftPadding + control.rightPadding)
        height: control.height - (control.topPadding + control.bottomPadding)

        text: control.placeholderText
        font: control.font
        color: control.placeholderTextColor
        verticalAlignment: control.verticalAlignment
        horizontalAlignment: control.horizontalAlignment
        visible: !control.length && !control.preeditText && (!control.activeFocus || control.horizontalAlignment !== Qt.AlignHCenter)
        elide: Text.ElideRight
        renderType: control.renderType
    }

    background: StyleImage {
        imageConfig: control.__config.background
    }
}
