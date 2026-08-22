#ifndef CHRYSALIS_BASETASKEXCEPTION_H
#define CHRYSALIS_BASETASKEXCEPTION_H

#include <string>
#include <stdexcept>

#include <QString>

#include "CLO3DExtensionExport.h"

namespace CLO3D {
    class CLO3D_EXTENSION BaseTaskException: public std::exception {
    public:
        virtual ~BaseTaskException() = default;
        virtual const QString& name() const = 0;
    };
}

#endif // CHRYSALIS_BASETASKEXCEPTION_H
