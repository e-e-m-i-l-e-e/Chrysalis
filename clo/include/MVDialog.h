#pragma once
// =============================================================================
//  MVDialog
//  CLO3D intermediate dialog base class that sits between QDialog and all
//  MV-prefixed application dialogs (e.g. DialogPreference).
//
//  This is a stub for compilation / automoc purposes only.
//  The real implementation lives inside the CLO3D host binary.
// =============================================================================
#include <QDialog>

#include <CLOAPIInterface.h>

class MVDialog : public QDialog
{
    Q_OBJECT

public:
    explicit MVDialog(QWidget* parent = nullptr) : QDialog(parent) {
        setWindowFlags(Qt::FramelessWindowHint | Qt::Dialog);
        setWindowModality(Qt::WindowModal);
    }
};
