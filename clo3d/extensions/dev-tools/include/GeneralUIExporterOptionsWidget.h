#ifndef FASHIONDESIGNAPPS_GENERALUIEXPORTEROPTIONSWIDGET_H
#define FASHIONDESIGNAPPS_GENERALUIEXPORTEROPTIONSWIDGET_H

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

        void read(QSettings* settings) override;
        std::shared_ptr<BaseUIExporterOptions> getOptions() override;
        void setOptions(std::shared_ptr<BaseUIExporterOptions> options) override;
        BaseUIExporterSettingsBlockContainerWidget* getBaseUIExporterSettings() override;
    signals:
        void rootFolderChanged(const QString& rootFolder);
        void fileNameChanged(const QString& fileName);
        void objectNameChanged(const QString& objectName);
        void classNameChanged(const QString& className);
    private:
        Ui::GeneralUIExporterOptionsWidget *ui;
        std::shared_ptr<GeneralUIExporterOptions> options_;
    };
} // UI

#endif //FASHIONDESIGNAPPS_GENERALUIEXPORTEROPTIONSWIDGET_H