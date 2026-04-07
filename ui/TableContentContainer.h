#ifndef CLOEXTENSIONS_TABLECONTENTCONTAINER_H
#define CLOEXTENSIONS_TABLECONTENTCONTAINER_H

#include "Container.h"

namespace UI {
    QT_BEGIN_NAMESPACE

    namespace Ui {
        class TableContentContainer;
    }

    QT_END_NAMESPACE

    class TableContentContainer : public Container {
        Q_OBJECT
        Q_PROPERTY(QStringList columns READ getColumns WRITE setColumns)

    public:
        explicit TableContentContainer(QWidget *parent = nullptr);

        ~TableContentContainer() override;

        [[nodiscard]] QStringList getColumns() const;
        void setColumns(const QStringList& columns) const;

    protected:
        QLayout * getLayout() override;
    private:
        Ui::TableContentContainer *ui;
    };
} // UI

#endif //CLOEXTENSIONS_TABLECONTENTCONTAINER_H