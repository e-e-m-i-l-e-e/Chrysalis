#ifndef CHRYSALIS_BASEDIALOG_H
#define CHRYSALIS_BASEDIALOG_H

#include <QDialog>

namespace UI {
    class BaseDialog: public QDialog {
        Q_OBJECT
    public:
        explicit BaseDialog();
    };
}

#endif //CHRYSALIS_BASEDIALOG_H