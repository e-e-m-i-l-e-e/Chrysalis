if(APP STREQUAL "CLO3D")
    # CLO3D extensions cannot be build in Debug mode. RelWithDebInfo is used instead.
    add_subdirectory(hooks)
    add_subdirectory(clo3d)
endif ()