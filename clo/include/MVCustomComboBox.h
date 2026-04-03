#pragma once
// =============================================================================
//  MVCustomComboBox
//  CLO3D custom combo box extending QComboBox.
//
//  Hierarchy: MVCustomComboBox > QComboBox > QWidget > QObject
//
//  Stub for compilation / automoc purposes only.
// =============================================================================
#include <CLOAPIInterface.h>
#include <QComboBox>

class MVCustomComboBox : public QComboBox
{
    Q_OBJECT

public:
    explicit MVCustomComboBox(QWidget* parent = nullptr) : QComboBox(parent) {
        UTILITY_API->UpdateCloStyleForPlugIn(this);
    }
};
