#ifndef CHRYSALIS_KEYSEQUENCE_H
#define CHRYSALIS_KEYSEQUENCE_H

#include <QKeySequenceEdit>

namespace UI {
    class KeySequence: public QKeySequenceEdit {
    public:
        explicit KeySequence(QWidget* parent = nullptr);
    protected:
        void focusInEvent(QFocusEvent *event) override;
        void focusOutEvent(QFocusEvent *event) override;
    };
}

#endif //CHRYSALIS_KEYSEQUENCE_H