#ifndef FASHIONDESIGNAPPS_BASEUIEXPORTEROPTIONSWIDGET_H
#define FASHIONDESIGNAPPS_BASEUIEXPORTEROPTIONSWIDGET_H

#include "Settings.h"
#include "BaseUIExporterOptions.h"
#include "BaseUIExporterSettingsBlockContainerWidget.h"

namespace UI {
    class BaseUIExporterOptionsWidget: public QWidget {
        Q_OBJECT
    protected:
        explicit BaseUIExporterOptionsWidget(QWidget* parent = nullptr): QWidget(parent) {}
    public:
        QString getTitle();
        virtual void read(Settings& settings);
        virtual void write(Settings& settings);
        virtual BaseUIExporterOptions* getOptions() = 0;
        virtual void setOptions(BaseUIExporterOptions* options) = 0;
        virtual BaseUIExporterSettingsBlockContainerWidget* getBaseUIExporterSettings() = 0;
    };
} // UI

#endif //FASHIONDESIGNAPPS_BASEUIEXPORTEROPTIONSWIDGET_H