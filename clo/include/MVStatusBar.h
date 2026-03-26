#pragma once

#include <QDockWidget>

class MVStatusBar : public QDockWidget
{
    Q_OBJECT

public:
    explicit MVStatusBar(QWidget* parent = nullptr) : QDockWidget(parent) {}
};
