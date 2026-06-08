#ifndef CHRYSALIS_EXPORTPATTERNCOMMANDARGUMENTSWIDGET_H
#define CHRYSALIS_EXPORTPATTERNCOMMANDARGUMENTSWIDGET_H

#include "BaseCommandArgumentsWidget.h"
#include "ExportPatternCommandArguments.h"

namespace UI {
    QT_BEGIN_NAMESPACE
    namespace Ui {
        class ExportPatternCommandArgumentsWidget;
    }
    QT_END_NAMESPACE

    class ExportPatternCommandArgumentsWidget: public BaseCommandArgumentsWidget {
        Q_OBJECT
    public:
        explicit ExportPatternCommandArgumentsWidget(ExportPatternCommandArguments* arguments);
        ~ExportPatternCommandArgumentsWidget() override;

        void load() override;
        void save() const override;
    private:
        Ui::ExportPatternCommandArgumentsWidget* ui;
    };
} // UI

#endif //CHRYSALIS_EXPORTPATTERNCOMMANDARGUMENTSWIDGET_H