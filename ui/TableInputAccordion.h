#ifndef CLOEXTENSIONS_TABLEINPUTACCORDION_H
#define CLOEXTENSIONS_TABLEINPUTACCORDION_H

#include <QWidget>

#include "Container.h"

namespace UI {
    QT_BEGIN_NAMESPACE

    namespace Ui {
        class TableInputAccordion;
    }

    QT_END_NAMESPACE

    class TableInputAccordion : public Container {
        Q_OBJECT
        Q_PROPERTY(QString title READ getTitle WRITE setTitle)
        Q_PROPERTY(QStringList columns READ getColumns WRITE setColumns)

    public:
        explicit TableInputAccordion(QWidget *parent = nullptr);

        ~TableInputAccordion() override;

        void insertWidget(int index, QWidget *widget) override;
        [[nodiscard]] QWidget * getWidget(int index) override;

        QString getTitle() const;
        void setTitle(const QString &title) const;

        QStringList getColumns() const;
        void setColumns(const QStringList &columns) const;

    protected:
        QBoxLayout* getLayout() override;

    private:
        Ui::TableInputAccordion *ui;
    };
} // UI

#endif //CLOEXTENSIONS_TABLEINPUTACCORDION_H