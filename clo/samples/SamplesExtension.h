#ifndef CLOEXTENSIONS_SAMPLESEXTENSION_H
#define CLOEXTENSIONS_SAMPLESEXTENSION_H

#include "Extension.h"

class SamplesExtension: public Extension {
public:
    void configureMenu(QMenu* extensionMenu) override;
};

#endif //CLOEXTENSIONS_SAMPLESEXTENSION_H