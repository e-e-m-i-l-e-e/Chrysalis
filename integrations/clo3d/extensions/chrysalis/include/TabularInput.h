#ifndef CHRYSALIS_TABULARINPUT_H
#define CHRYSALIS_TABULARINPUT_H

#include <QWidget>

namespace CLO3D::UI {
    QT_BEGIN_NAMESPACE
    namespace Ui {
        class TabularInput;
    }
    QT_END_NAMESPACE

    class TabularInput : public QWidget {
        Q_OBJECT
        Q_PROPERTY(QString title READ getTitle WRITE setTitle)
    public:
        explicit TabularInput(QWidget *parent = nullptr);
        ~TabularInput() override;

        QString getTitle() const;
        void setTitle(const QString& title) const;
    private:
        Ui::TabularInput *ui;
    };
}

#endif //CHRYSALIS_TABULARINPUT_H