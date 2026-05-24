import QtQuick
import QtQuick.Controls.impl
import QtQuick.Templates as T

T.SpinBox {
    id: control

    implicitWidth: Math.max(implicitBackgroundWidth + leftInset + rightInset,
                            contentItem.implicitWidth + leftPadding + rightPadding)
    implicitHeight: Math.max(implicitBackgroundHeight + topInset + bottomInset,
                             implicitContentHeight + topPadding + bottomPadding,
                             up.implicitIndicatorHeight, down.implicitIndicatorHeight)

    property string __controlState: [
        enabled && hovered && (down.hovered || down.pressed) && "down",
        enabled && hovered && (up.hovered || up.pressed) && "up",
        enabled && (down.pressed || up.pressed) && "pressed",
        enabled && hovered && !(down.pressed || up.pressed) && "hovered"
    ].filter(Boolean).join("_") || "normal"
    readonly property var __config: Config.controls.spinbox[__controlState] || {}
    readonly property var __downConfig: value == from ? Config.controls.spinbox["atlimit"] : __config
    readonly property var __upConfig: value == to ? Config.controls.spinbox["atlimit"] : __config

    readonly property bool __mirroredIndicators: control.mirrored !== (__config.mirrored || false)

    leftPadding: __config.leftPadding || 0
    rightPadding: __config.rightPadding || 0
    topPadding: __config.topPadding || 0
    bottomPadding: __config?.bottomPadding || 0

    topInset: -__config?.topInset || 0
    bottomInset: -__config?.bottomInset || 0
    leftInset: -__config?.leftInset || 0
    rightInset: -__config?.rightInset || 0

    validator: IntValidator {
        locale: control.locale.name
        bottom: Math.min(control.from, control.to)
        top: Math.max(control.from, control.to)
    }

    contentItem: TextInput {
        clip: width < implicitWidth
        text: control.displayText
        opacity: control.enabled ? 1 : 0.3

        font: control.font
        color: control.palette.text
        selectionColor: control.palette.highlight
        selectedTextColor: control.palette.highlightedText
        horizontalAlignment: control.__config.textInput.textHAlignment
        verticalAlignment: control.__config.textInput.textVAlignment

        readOnly: !control.editable
        validator: control.validator
        inputMethodHints: control.inputMethodHints
    }

    down.indicator: StyleImage {
        height: control.height
        imageConfig: control.__downConfig.indicator_down_background

        StyleImage {
            x: (parent.width - width) / 2
            y: (parent.height - height) / 2
            imageConfig: control.mirrored
                ? control.__upConfig.indicator_up_icon
                : control.__downConfig.indicator_down_icon
        }
    }

    up.indicator: StyleImage {
        x: control.width - width
        height: control.height
        imageConfig: control.__upConfig.indicator_up_background

        StyleImage {
            x: (parent.width - width) / 2
            y: (parent.height - height) / 2
            imageConfig: control.mirrored
                ? control.__downConfig.indicator_down_icon
                : control.__upConfig.indicator_up_icon
        }
    }

    background: StyleImage {
        imageConfig: control.__config.background
    }
}
