# =============================================================================
#  interfaces/CMakeLists.txt
#
#  INTERFACE targets for the project's header-only libraries.
#
#  Consumers link against a named target instead of spelling out every
#  dependency manually. Transitive propagation takes care of the rest:
#
#    target_link_libraries(MyTarget PRIVATE HooksManager)
#      → pulls in: polyhook2 only
#      → logging is DISABLED (HM_LOG_* macros are no-ops)
#
#    target_link_libraries(MyTarget PRIVATE HooksManager Logger)
#      → pulls in: polyhook2 + spdlog + LOGS_DIR definition
#      → logging is ENABLED (LOGS_DIR triggers Logger.h inclusion in HooksManager.h)
#
#    target_link_libraries(MyTarget PRIVATE Logger)
#      → pulls in: spdlog, LOGS_DIR
#
#  Qt is intentionally NOT listed here. Logger.h activates its Qt code only
#  when QT_CORE_LIB is defined (which Qt's own find_package sets), so each
#  consuming target opts in by linking Qt5::Core itself. HookManager.h has
#  no Qt dependency at all.
#
#  Prerequisites (must be found before add_subdirectory(interfaces) is called):
#    find_package(spdlog    REQUIRED)
#    find_package(polyhook2 REQUIRED)
# =============================================================================

# ── Logger ────────────────────────────────────────────────────────────────────
# Depends on: spdlog
# Propagates: include directory, spdlog, LOGS_DIR definition
find_package(spdlog REQUIRED)
add_library(Logger INTERFACE)
target_include_directories(Logger INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(Logger INTERFACE spdlog::spdlog)

# LOGS_DIR is set in the root CMakeLists.txt via a CACHE variable.
# Propagating it here avoids repeating the definition in every consumer.
target_compile_definitions(Logger INTERFACE LOGS_DIR="${LOGS_DIR}")

# ── HooksManager ──────────────────────────────────────────────────────────────
# Depends on: polyhook2 only
# Logger is intentionally NOT linked here. HooksManager.h detects Logger
# availability at compile time via the LOGS_DIR definition that Logger
# propagates. Logging is activated automatically when the consuming target
# also links Logger — no changes to HooksManager itself are needed.
find_package(polyhook2 REQUIRED)
add_library(HooksManager INTERFACE)
target_include_directories(HooksManager INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(HooksManager INTERFACE polyhook2::polyhook2)
