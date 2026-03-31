#pragma once

#include <QDockWidget>


class MVDockWidget : public QDockWidget
{
    Q_OBJECT

public:
    explicit MVDockWidget(QWidget* parent = nullptr) : QDockWidget(parent) {}
};
