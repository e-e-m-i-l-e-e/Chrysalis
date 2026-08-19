#ifndef CHRYSALIS_NAMEDWIDGET_H
#define CHRYSALIS_NAMEDWIDGET_H

#include <QWidget>

namespace CLO3D::UI {
    class NamedWidget: public QWidget {
        Q_OBJECT
        Q_PROPERTY(QString title READ getTitle WRITE setTitle)
    signals:
        void titleChanged(QString& title);
    public:
        explicit NamedWidget(QWidget* parent): QWidget(parent) {}
        ~NamedWidget() override = default;

        [[nodiscard]] QString getTitle() const {
            return title_;
        }
        virtual void setTitle(const QString& title) {
            title_ = title;
            emit titleChanged(title_);
        }
    private:
        QString title_;
    };
}

#endif //CHRYSALIS_NAMEDWIDGET_H