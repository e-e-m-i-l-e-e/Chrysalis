#ifndef FASHIONDESIGNAPPS_JSONUIEXPORTEROPTIONSWIDGET_H
#define FASHIONDESIGNAPPS_JSONUIEXPORTEROPTIONSWIDGET_H

#include "BaseUIExporterOptionsWidget.h"
#include "JsonUIExporterOptions.h"

namespace UI {
    QT_BEGIN_NAMESPACE

    namespace Ui {
        class JsonUIExporterOptionsWidget;
    }

    QT_END_NAMESPACE

    class JsonUIExporterOptionsWidget: public BaseUIExporterOptionsWidget {
        Q_OBJECT
    public:
        explicit JsonUIExporterOptionsWidget(QWidget *parent = nullptr);
        ~JsonUIExporterOptionsWidget() override;

        void read() override;
        BaseUIExporterOptions* getOptions() override;
        void setOptions(BaseUIExporterOptions* options) override;
        BaseUIExporterSettingsBlockContainerWidget* getBaseUIExporterSettings() override;
    public slots:
        void rootFolderChanged(const QString& rootFolder) const;
        void fileNameChanged(const QString& fileName) const;
        void objectNameChanged(const QString& objectName) const;
        void classNameChanged(const QString& className) const;
    private:
        Ui::JsonUIExporterOptionsWidget *ui;
        JsonUIExporterOptions* options_;
    };
} // UI

#endif //FASHIONDESIGNAPPS_JSONUIEXPORTEROPTIONSWIDGET_H