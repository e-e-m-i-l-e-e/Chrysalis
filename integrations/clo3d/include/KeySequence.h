#ifndef CHRYSALIS_KEYSEQUENCE_H
#define CHRYSALIS_KEYSEQUENCE_H

#include <QKeySequenceEdit>

#include "CLO3DExtensionExport.h"

namespace CLO3D::UI {
    class CLO3D_EXTENSION KeySequence: public QKeySequenceEdit {
    public:
        explicit KeySequence(QWidget* parent = nullptr);
    protected:
        void focusInEvent(QFocusEvent *event) override;
        void focusOutEvent(QFocusEvent *event) override;
    };
}

#endif //CHRYSALIS_KEYSEQUENCE_H