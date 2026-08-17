#ifndef CHRYSALIS_BASECOMMANDARGUMENTSWIDGET_H
#define CHRYSALIS_BASECOMMANDARGUMENTSWIDGET_H

#include <QWidget>

#include "CLO3DExtensionExport.h"

#include "BaseCommandArguments.h"

namespace UI {
    class CLO3D_EXTENSION BaseCommandArgumentsWidget: public QWidget {
    public:
        explicit BaseCommandArgumentsWidget(BaseCommandArguments* arguments);

        virtual void load();
        virtual void save() const;
    protected:
        BaseCommandArguments* arguments_;
    };
}

#endif //CHRYSALIS_BASECOMMANDARGUMENTSWIDGET_H