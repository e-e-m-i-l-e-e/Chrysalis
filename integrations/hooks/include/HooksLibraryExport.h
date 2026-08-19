#ifndef HOOKS_LIBRARY_EXPORT_H
#define HOOKS_LIBRARY_EXPORT_H

#ifdef _WIN32
    #ifdef HOOKS_LIBRARY_EXPORT
        #define HOOKS __declspec(dllexport)
    #else
        #define HOOKS __declspec(dllimport)
    #endif
#else
    #define HOOKS
#endif

#endif //HOOKS_LIBRARY_EXPORT_H
