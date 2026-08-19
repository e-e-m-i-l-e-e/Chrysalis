#ifndef CHRYSALIS_BASEUIEXPORTERSETTINGSBLOCKCONTAINERWIDGET_H
#define CHRYSALIS_BASEUIEXPORTERSETTINGSBLOCKCONTAINERWIDGET_H

#include "NamedWidget.h"
#include "BaseContainer.h"

namespace CLO3D::UI {
    QT_BEGIN_NAMESPACE
    namespace Ui {
        class BaseUIExporterSettingsBlockContainerWidget;
    }
    QT_END_NAMESPACE

    class BaseUIExporterSettingsBlockContainerWidget: public NamedWidget, public BaseContainer {
        Q_OBJECT
        Q_PROPERTY(int labelWidth READ getLabelWidth WRITE setLabelWidth)
    public:
        explicit BaseUIExporterSettingsBlockContainerWidget(QWidget *parent = nullptr);
        ~BaseUIExporterSettingsBlockContainerWidget() override;

        [[nodiscard]] int count() const override;
        void insertWidget(int index, QWidget *widget) override;
        [[nodiscard]] QWidget * getWidget(int index) override;

        void setTitle(const QString &title) override;

        int getLabelWidth() const;
        void setLabelWidth(int labelWidth);

        void setRootFolderText(const QString &rootFolder) const;
        void setFileNameText(const QString &fileName) const;
        void setObjectNameText(const QString &objectName) const;
        void setClassNameText(const QString &className) const;

        QString getRootFolderText() const;
        QString getFileNameText() const;
        QString getObjectNameText() const;
        QString getClassNameText() const;
    signals:
        void rootFolderChanged(const QString& rootFolder);
        void fileNameChanged(const QString& fileName);
        void objectNameChanged(const QString& objectName);
        void classNameChanged(const QString& className);
    public slots:
        void chooseRootFolder();
        void enableContent(bool isEnabled) const;
    private:
        Ui::BaseUIExporterSettingsBlockContainerWidget *ui;
        int labelWidth_ = 20;
    };
} // UI

#endif //CHRYSALIS_BASEUIEXPORTERSETTINGSBLOCKCONTAINERWIDGET_H