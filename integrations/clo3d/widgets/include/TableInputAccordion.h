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

        [[nodiscard]] int count() const override;
        void insertWidget(int index, QWidget* widget) override;
        [[nodiscard]] QWidget* getWidget(int index) override;

        [[nodiscard]] QString getTitle() const;
        void setTitle(const QString &title) const;

        [[nodiscard]] QStringList getColumns() const;
        void setColumns(const QStringList &columns) const;

        [[nodiscard]] ClickableWidget* getAccordionTitle() const;

    private:
        Ui::TableInputAccordion *ui;
        void updateTableHeight() const;
    };
} // UI

#endif //CHRYSALIS_TABLEINPUTACCORDION_H