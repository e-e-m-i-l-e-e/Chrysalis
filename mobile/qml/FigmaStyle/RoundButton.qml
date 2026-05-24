import QtQuick
import QtQuick.Controls.impl
import QtQuick.Templates as T

T.RoundButton {
    id: control

    implicitWidth: Math.max(implicitBackgroundWidth + leftInset + rightInset,
                            implicitContentWidth + leftPadding + rightPadding)
    implicitHeight: Math.max(implicitBackgroundHeight + topInset + bottomInset,
                             implicitContentHeight + topPadding + bottomPadding)

    spacing: __config.spacing || 0

    topPadding: __config.topPadding || 0
    bottomPadding: __config.bottomPadding || 0
    leftPadding: __config.leftPadding || 0
    rightPadding: __config.rightPadding || 0

    topInset: -__config.topInset || 0
    bottomInset: -__config.bottomInset || 0
    leftInset: -__config.leftInset || 0
    rightInset: -__config.rightInset || 0

    icon.width: 17
    icon.height: 17
    icon.color: control.flat
        ? (control.enabled
            ? (control.down ? control.palette.highlight : control.palette.button)
            : control.palette.mid)
        : control.palette.buttonText

    readonly property string __currentState: [
        control.checked && "checked",
        !control.enabled && "disabled",
        control.enabled && !control.down && control.hovered && "hovered",
        control.down && "pressed"
    ].filter(Boolean).join("_") || "normal"
    readonly property var __config: Config.controls.roundbutton[__currentState] || {}

    contentItem: IconLabel {
        spacing: control.spacing
        mirrored: control.mirrored
        display: control.display
        alignment: control.__config.label.textVAlignment | control.__config.label.textHAlignment
        icon: control.icon
        text: control.text
        font: control.font
        color: control.icon.color
    }

    background: StyleImage {
        imageConfig: control.__config.background
    }
}
