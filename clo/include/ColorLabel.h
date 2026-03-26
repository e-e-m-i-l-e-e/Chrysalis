#pragma once
// =============================================================================
//  ColorLabel
//  CLO3D label widget that extends QLabel, used to display swatches /
//  colored text inside style panels.
//
//  Hierarchy: ColorLabel > QLabel > QFrame > QWidget > QObject
//
//  Stub for compilation / automoc purposes only.
// =============================================================================
#include <CLOAPIInterface.h>
#include <QLabel>

class ColorLabel : public QLabel
{
    Q_OBJECT

public:
    explicit ColorLabel(QWidget* parent = nullptr) : QLabel(parent) {
        UTILITY_API->UpdateCloStyleForPlugIn(this);
    }
    explicit ColorLabel(const QString& text, QWidget* parent = nullptr) : QLabel(text, parent) {
        UTILITY_API->UpdateCloStyleForPlugIn(this);
    }
};
