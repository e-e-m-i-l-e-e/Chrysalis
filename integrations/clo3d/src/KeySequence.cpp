#include "KeySequence.h"

#include "BaseNativeShortcutHandler.h"

using namespace CLO3D::UI;

KeySequence::KeySequence(QWidget* parent): QKeySequenceEdit(parent) {}

void KeySequence::focusInEvent(QFocusEvent *event) {
    QKeySequenceEdit::focusInEvent(event);
    BaseNativeShortcutHandler::stopListening();
}

void KeySequence::focusOutEvent(QFocusEvent *event) {
    QKeySequenceEdit::focusOutEvent(event);
    BaseNativeShortcutHandler::startListening();
}
