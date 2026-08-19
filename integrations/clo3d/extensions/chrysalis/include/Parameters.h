#ifndef CHRYSALIS_PARAMETERS_H
#define CHRYSALIS_PARAMETERS_H

#include <QWidget>

namespace CLO3D::UI {
    QT_BEGIN_NAMESPACE
    namespace Ui {
        class Parameters;
    }
    QT_END_NAMESPACE

    class Parameters : public QWidget {
        Q_OBJECT
    public:
        explicit Parameters(QWidget *parent = nullptr);
        ~Parameters() override;
    private:
        Ui::Parameters *ui;
    };
} // CLO3D::UI

#endif //CHRYSALIS_PARAMETERS_H