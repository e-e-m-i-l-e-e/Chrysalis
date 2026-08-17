#ifndef CHRYSALIS_LOGGING_LIBRARY_EXPORT_H
#define CHRYSALIS_LOGGING_LIBRARY_EXPORT_H

#if defined(_WIN32) && defined(LOGGING_LIBRARY_SHARED)
    #ifdef LOGGING_LIBRARY_EXPORT
        #define LOGGING __declspec(dllexport)
    #else
        #define LOGGING __declspec(dllimport)
    #endif
#else
    #define LOGGING
#endif

#endif //CHRYSALIS_LOGGING_LIBRARY_EXPORT_H
