#ifndef FASHIONDESIGNAPPS_BASEUIEXPORTEROPTIONSWIDGET_H
#define FASHIONDESIGNAPPS_BASEUIEXPORTEROPTIONSWIDGET_H

#include "BaseUIExporterOptions.h"
#include "BaseUIExporterSettingsBlockContainerWidget.h"

namespace UI {
    class BaseUIExporterOptionsWidget: public QWidget {
        Q_OBJECT
    protected:
        explicit BaseUIExporterOptionsWidget(QWidget* parent = nullptr): QWidget(parent) {}
    public:
        QString getTitle();
        virtual void read(QSettings* settings);
        virtual void write(QSettings* settings);
        virtual std::shared_ptr<BaseUIExporterOptions> getOptions() = 0;
        virtual void setOptions(std::shared_ptr<BaseUIExporterOptions> options) = 0;
        virtual BaseUIExporterSettingsBlockContainerWidget* getBaseUIExporterSettings() = 0;
    };
} // UI

#endif //FASHIONDESIGNAPPS_BASEUIEXPORTEROPTIONSWIDGET_H