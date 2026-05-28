//
// Created by emily on 08/04/2026.
//

#ifndef CHRYSALIS_PARAMETERS_H
#define CHRYSALIS_PARAMETERS_H

#include <QWidget>

namespace UI::PatternBuilder {
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
} // UI::PatternBuilder

#endif //CHRYSALIS_PARAMETERS_H