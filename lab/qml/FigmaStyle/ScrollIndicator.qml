import QtQuick
import QtQuick.Controls.impl
import QtQuick.Templates as T

T.ScrollIndicator {
    id: control

    implicitWidth: Math.max(implicitBackgroundWidth + leftInset + rightInset,
                            implicitContentWidth + leftPadding + rightPadding)
    implicitHeight: Math.max(implicitBackgroundHeight + topInset + bottomInset,
                             implicitContentHeight + topPadding + bottomPadding)

    topPadding: (horizontal ? __config.topPadding : __config.leftPadding) || 0
    leftPadding: (horizontal ? __config.leftPadding : __config.bottomPadding) || 0
    rightPadding: (horizontal ? __config.rightPadding : __config.topPadding) || 0
    bottomPadding: (horizontal ? __config.bottomPadding : __config.rightPadding) || 0

    topInset: (horizontal ? -__config.topInset : -__config.leftInset) || 0
    leftInset: (horizontal ? -__config.leftInset : -__config.bottomInset) || 0
    rightInset: (horizontal ? -__config.rightInset : -__config.topInset) || 0
    bottomInset: (horizontal ? -__config.bottomInset : -__config.rightInset) || 0

    readonly property var __config: Config.controls.scrollindicator["normal"] || {}

    contentItem: StyleImage {
        imageConfig: control.__config.handle
        horizontal: control.horizontal
        width: control.availableWidth
        height: control.availableHeight
        opacity: 0.0
    }

    background: StyleImage {
        imageConfig: control.__config.background
        horizontal: control.horizontal
        opacity: 0.0
    }

    states: [
        State {
            name: "active"
            when: control.active && control.size < 1.0
        }
    ]

    transitions: [
        // TODO: Set transition based on Figma prototype
        Transition {
            to: "active"
            NumberAnimation { targets: [control.contentItem, control.background]; property: "opacity"; to: 1.0 }
        },
        Transition {
            from: "active"
            SequentialAnimation {
                PauseAnimation { duration: 5000 }
                NumberAnimation { targets: [control.contentItem, control.background]; property: "opacity"; to: 0.0 }
            }
        }
    ]
}
