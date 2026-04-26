#ifndef FASHIONDESIGNAPPS_BASEUIEXPORTEROPTIONSWIDGET_H
#define FASHIONDESIGNAPPS_BASEUIEXPORTEROPTIONSWIDGET_H

#include <QWidget>

#include "BaseUIExporterOptions.h"

namespace UI {
    class BaseUIExporterOptionsWidget: public QWidget {
        Q_OBJECT
    protected:
        explicit BaseUIExporterOptionsWidget(QWidget* parent = nullptr): QWidget(parent) {}
    public:
        virtual void read() = 0;
        virtual void setOptions(BaseUIExporterOptions& options) = 0;
    };
} // UI

#endif //FASHIONDESIGNAPPS_BASEUIEXPORTEROPTIONSWIDGET_H