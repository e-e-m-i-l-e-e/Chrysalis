import QtQuick
import QtQuick.Templates as T

T.Popup {
    id: popup

    implicitWidth: Math.max(implicitBackgroundWidth + leftInset + rightInset,
                            contentWidth + leftPadding + rightPadding)
    implicitHeight: Math.max(implicitBackgroundHeight + topInset + bottomInset,
                             contentHeight + topPadding + bottomPadding)

    topPadding: __config.topPadding || 0
    leftPadding: __config.leftPadding || 0
    rightPadding: __config.rightPadding || 0
    bottomPadding: __config.bottomPadding || 0

    topInset: -__config.topInset || 0
    bottomInset: -__config.bottomInset || 0
    leftInset: -__config.leftInset || 0
    rightInset: -__config.rightInset || 0

    required property T.ComboBox __combobox

    readonly property string __currentState: [
        !__combobox.enabled && "disabled",
        __combobox.enabled && !__combobox.pressed && __combobox.hovered && "hovered",
        popup.visible && "open",
        __combobox.pressed && "pressed"
    ].filter(Boolean).join("_") || "normal"
    readonly property var __config: Config.controls.comboboxpopup[__currentState] || {}

    contentItem: ListView {
        clip: true
        implicitHeight: contentHeight
        spacing: control.__config.contentItem.spacing
        highlightMoveDuration: 0

        model: __combobox.delegateModel
        currentIndex: __combobox.highlightedIndex

        ScrollIndicator.vertical: ScrollIndicator { }
    }

    background: StyleImage {
        imageConfig: control.__config.background
    }
}
