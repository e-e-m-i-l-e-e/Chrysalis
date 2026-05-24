import QtQuick
import QtQuick.Templates as T

StyleImage {
    id: delegate

    required property T.PageIndicator pageIndicator
    required property int index

    readonly property string __currentState: [
        !pageIndicator.enabled && "disabled",
        pageIndicator.enabled && (index === pageIndicator.currentIndex || pressed) && "delegate",
        pageIndicator.enabled && index === pageIndicator.currentIndex && "current",
        pageIndicator.enabled && pageIndicator.interactive && pressed && "pressed"
    ].filter(Boolean).join("_") || (pageIndicator.hovered ? "hovered" : "normal")
    readonly property var __config: Config.controls.pageindicatordelegate[__currentState].indicator || {}

    imageConfig: __config
}
