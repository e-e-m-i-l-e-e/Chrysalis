#ifndef FASHIONDESIGNAPPS_NAMEDWIDGET_H
#define FASHIONDESIGNAPPS_NAMEDWIDGET_H

#include <QWidget>

namespace UI {
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

#endif //FASHIONDESIGNAPPS_NAMEDWIDGET_H