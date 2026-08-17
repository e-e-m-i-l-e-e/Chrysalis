#ifndef CHRYSALIS_CLO3DEXTENSIONEXPORT_H
#define CHRYSALIS_CLO3DEXTENSIONEXPORT_H

#if defined(_WIN32)
    #ifdef CLO3D_EXTENSION_EXPORT
        #define CLO3D_EXTENSION __declspec(dllexport)
    #else
        #define CLO3D_EXTENSION __declspec(dllimport)
    #endif
    #define CLO3D_EXTENSION_ENTRY __declspec(dllexport)
#else
    #define CLO3D_EXTENSION
    #define CLO3D_EXTENSION_ENTRY
#endif

#endif //CHRYSALIS_CLO3DEXTENSIONEXPORT_H
