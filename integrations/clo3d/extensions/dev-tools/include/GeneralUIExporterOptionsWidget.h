#ifndef CHRYSALIS_GENERALUIEXPORTEROPTIONSWIDGET_H
#define CHRYSALIS_GENERALUIEXPORTEROPTIONSWIDGET_H

#include "BaseUIExporterOptionsWidget.h"
#include "GeneralUIExporterOptions.h"

namespace UI {
    QT_BEGIN_NAMESPACE

    namespace Ui {
        class GeneralUIExporterOptionsWidget;
    }

    QT_END_NAMESPACE

    class GeneralUIExporterOptionsWidget: public BaseUIExporterOptionsWidget {
        Q_OBJECT
    public:
        explicit GeneralUIExporterOptionsWidget(QWidget *parent = nullptr);
        ~GeneralUIExporterOptionsWidget() override;

        void read() override;
        void write() override;

        BaseUIExporterOptions* getOptions() override;
        void setOptions(BaseUIExporterOptions* options) override;
        BaseUIExporterSettingsBlockContainerWidget* getBaseUIExporterSettings() override;
    signals:
        void rootFolderChanged(const QString& rootFolder);
        void fileNameChanged(const QString& fileName);
        void objectNameChanged(const QString& objectName);
        void classNameChanged(const QString& className);
    private:
        Ui::GeneralUIExporterOptionsWidget *ui;
        GeneralUIExporterOptions* options_ = nullptr;
    };
} // UI

#endif //CHRYSALIS_GENERALUIEXPORTEROPTIONSWIDGET_H