#ifndef CLOEXTENSIONS_ACCORDION_H
#define CLOEXTENSIONS_ACCORDION_H

#include "Container.h"

namespace UI {
    QT_BEGIN_NAMESPACE
    namespace Ui { class AccordionContainer; }
    QT_END_NAMESPACE

    class AccordionContainer: public Container {
        Q_OBJECT

    public:
        explicit AccordionContainer(QWidget *parent = nullptr);
        ~AccordionContainer() override;

    protected:
        QBoxLayout* getLayout() override;

    private:
        Ui::AccordionContainer *ui;
    };
} // namespace UI

#endif //CLOEXTENSIONS_ACCORDION_H
