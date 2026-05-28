#ifndef FASHIONDESIGNAPPS_KEYSEQUENCE_H
#define FASHIONDESIGNAPPS_KEYSEQUENCE_H

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

#endif //FASHIONDESIGNAPPS_KEYSEQUENCE_H