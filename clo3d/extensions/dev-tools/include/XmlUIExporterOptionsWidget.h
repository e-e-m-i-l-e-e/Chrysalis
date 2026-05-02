#ifndef FASHIONDESIGNAPPS_XMLUIEXPORTEROPTIONSWIDGET_H
#define FASHIONDESIGNAPPS_XMLUIEXPORTEROPTIONSWIDGET_H

#include "BaseUIExporterOptionsWidget.h"
#include "XmlUIExporterOptions.h"

namespace UI {
    QT_BEGIN_NAMESPACE

    namespace Ui {
        class XmlUIExporterOptionsWidget;
    }

    QT_END_NAMESPACE

    class XmlUIExporterOptionsWidget: public BaseUIExporterOptionsWidget {
        Q_OBJECT
    public:
        explicit XmlUIExporterOptionsWidget(QWidget *parent = nullptr);
        ~XmlUIExporterOptionsWidget() override;

        void read(QSettings* settings) override;
        std::shared_ptr<BaseUIExporterOptions> getOptions() override;
        void setOptions(std::shared_ptr<BaseUIExporterOptions> options) override;
        BaseUIExporterSettingsBlockContainerWidget* getBaseUIExporterSettings() override;
    public slots:
        void rootFolderChanged(const QString& rootFolder) const;
        void fileNameChanged(const QString& fileName) const;
        void objectNameChanged(const QString& objectName) const;
        void classNameChanged(const QString& className) const;
    private:
        Ui::XmlUIExporterOptionsWidget *ui;
        std::shared_ptr<XmlUIExporterOptions> options_;
    };
} // UI

#endif //FASHIONDESIGNAPPS_XMLUIEXPORTEROPTIONSWIDGET_H