#ifndef CLOEXTENSIONS_SEGMENT_H
#define CLOEXTENSIONS_SEGMENT_H

#include <QWidget>

namespace CloUICommon {
    class Segment : public QWidget
    {
        Q_OBJECT
    public:
        explicit Segment(QWidget* parent = nullptr) : QWidget(parent) {}
    };
}

#endif //CLOEXTENSIONS_SEGMENT_H