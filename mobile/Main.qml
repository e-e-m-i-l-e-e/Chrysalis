import QtQuick
import QtQuick.Controls
import QtOpenGLApp   // ← the URI declared in CMakeLists.txt → gives us OpenGLItem

ApplicationWindow {
    id: root
    visible: true
    width:  800
    height: 600
    title:  "QML + OpenGL – Hello Triangle"

    color: "#14141e"    // dark background behind the GL surface

    // ── OpenGL surface ────────────────────────────────────────────────────────
    // OpenGLItem is our C++ QQuickFramebufferObject subclass.
    // Qt composites the FBO output right here in the QML scene.
    OpenGLItem {
        id: glView

        // Fill most of the window, leaving room for the label below
        anchors {
            top:    parent.top
            left:   parent.left
            right:  parent.right
            bottom: infoLabel.top
            bottomMargin: 12
        }

        // ── Animate the colorOffset property we exposed from C++ ──────────────
        // The renderer reads this value each frame via synchronize(), so the
        // triangle colour will cycle through hues over 4 seconds, forever.
        NumberAnimation on colorOffset {
            from:     0.0
            to:       1.0
            duration: 4000          // ms for one full colour cycle
            loops:    Animation.Infinite
            running:  true
        }
    }

    // ── Simple HUD label ──────────────────────────────────────────────────────
    Text {
        id: infoLabel
        anchors {
            bottom:           parent.bottom
            horizontalCenter: parent.horizontalCenter
            bottomMargin:     16
        }
        text: "VAO + VBO triangle | colorOffset: " +
            glView.colorOffset.toFixed(3)
        color: "#aaaacc"
        font { pixelSize: 14; family: "monospace" }
    }
}
