#pragma once
// =============================================================================
//  MVCustomDoubleSpinBox
//  CLO3D custom double spin box extending QDoubleSpinBox.
//
//  Hierarchy: MVCustomDoubleSpinBox > QDoubleSpinBox > QAbstractSpinBox > QWidget > QObject
//
//  Stub for compilation / automoc purposes only.
// =============================================================================
#include <QDoubleSpinBox>

class MVCustomDoubleSpinBox : public QDoubleSpinBox
{
    Q_OBJECT

public:
    explicit MVCustomDoubleSpinBox(QWidget* parent = nullptr) : QDoubleSpinBox(parent) {
        UTILITY_API->UpdateCloStyleForPlugIn(this);
    }
};
