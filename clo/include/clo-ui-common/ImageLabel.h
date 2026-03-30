#ifndef CLOEXTENSIONS_IMAGELABEL_H
#define CLOEXTENSIONS_IMAGELABEL_H

#include <QLabel>

namespace CloUICommon {
    class ImageLabel : public QLabel
    {
        Q_OBJECT
    public:
        explicit ImageLabel(QWidget* parent = nullptr) : QLabel(parent) {}
    };
}

#endif //CLOEXTENSIONS_IMAGELABEL_H