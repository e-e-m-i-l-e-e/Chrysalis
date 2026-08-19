#ifndef CHRYSALIS_TABLEINPUTACCORDION_H
#define CHRYSALIS_TABLEINPUTACCORDION_H

#include "BaseContainer.h"
#include "ClickableWidget.h"

namespace CLO3D::UI {
    QT_BEGIN_NAMESPACE
    namespace Ui {
        class TableInputAccordion;
    }
    QT_END_NAMESPACE

    class TableInputAccordion: public QWidget, public BaseContainer {
        Q_OBJECT
        Q_PROPERTY(QString title READ getTitle WRITE setTitle)
        Q_PROPERTY(QStringList columns READ getColumns WRITE setColumns)

    public:
        explicit TableInputAccordion(QWidget *parent = nullptr);

        ~TableInputAccordion() override;

        int count() const override;
        void insertWidget(int index, QWidget* widget) override;
        [[nodiscard]] QWidget* getWidget(int index) override;

        QString getTitle() const;
        void setTitle(const QString &title) const;

        QStringList getColumns() const;
        void setColumns(const QStringList &columns) const;

        ClickableWidget* getAccordionTitle() const;

    private:
        Ui::TableInputAccordion *ui;
        void updateTableHeight() const;
    };
} // UI

#endif //CHRYSALIS_TABLEINPUTACCORDION_H