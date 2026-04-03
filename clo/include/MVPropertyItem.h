#pragma once

#include <QWidget>

class MVPropertyItem : public QWidget
{
    Q_OBJECT

public:
    explicit MVPropertyItem(QWidget* parent = nullptr) : QWidget(parent) {
        UTILITY_API->UpdateCloStyleForPlugIn(this);
    }
};
