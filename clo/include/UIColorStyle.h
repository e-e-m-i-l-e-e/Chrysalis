#pragma once
// =============================================================================
//  UIColorStyle
//  CLO3D colour-style panel widget — the top-level container that owns
//  ColorStyleColorItem / ColorStyleDoubleSpinBoxItem / ColorStyleSpinBoxItem rows.
//
//  Hierarchy: UIColorStyle > QWidget > QObject
//
//  Stub for compilation / automoc purposes only.
// =============================================================================
#include <QWidget>

class UIColorStyle : public QWidget
{
    Q_OBJECT

public:
    explicit UIColorStyle(QWidget* parent = nullptr) : QWidget(parent) {
        UTILITY_API->UpdateCloStyleForPlugIn(this);
    }
};
