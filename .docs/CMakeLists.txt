set(DOCUMENTATION_DIR ${OUTPUT_DIR}/docs)
set(DIAGRAMS_DIR ${DOCUMENTATION_DIR}/diagrams/${APP})

# ----- Load tools -----------------------------------------------------------------------------------------------------

include(FetchContent)
FetchContent_Declare(
        doxygen-awesome-css
        URL https://github.com/jothepro/doxygen-awesome-css/archive/refs/heads/main.zip
)
FetchContent_MakeAvailable(doxygen-awesome-css)
FetchContent_GetProperties(doxygen-awesome-css SOURCE_DIR AWESOME_CSS_DIR)
if (LINUX)
    set(PLANTUML "plantuml")
    set(CLANG_UML "clang-uml")
else ()
    FetchContent_Declare(
            plantuml
            URL https://github.com/plantuml/plantuml/releases/download/v1.2026.6/plantuml.jar
            DOWNLOAD_NO_EXTRACT TRUE
    )
    FetchContent_MakeAvailable(plantuml)
    FetchContent_GetProperties(plantuml SOURCE_DIR PLANTUML_DIR)
    set(PLANTUML "java -jar ${PLANTUML_DIR}/plantuml.jar")

    find_program(CLANG_UML NAMES clang-uml.exe)
endif ()

# ----- Generate UML Diagrams ------------------------------------------------------------------------------------------

file(MAKE_DIRECTORY ${DIAGRAMS_DIR})
if(CLANG_UML)
    add_custom_target(GenerateUML
            COMMAND ${CLANG_UML} -c .docs/diagrams/${APP}/.clang-uml -o ${DOCUMENTATION_DIR}/diagrams/${APP} -d ${CMAKE_BINARY_DIR}
            WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
            COMMENT "Generating UML diagrams" USES_TERMINAL VERBATIM
    )
else()
    message(WARNING "clang-uml was not found.")
endif()

# ----- Doxygen + Coverage Reports -------------------------------------------------------------------------------------

find_package(Doxygen REQUIRED)

set(ALL_DOXYGEN_TARGETS "")
set(ALL_COVERAGE_TARGETS "")

set(MODULES_LIST "")
set(BREATHE_PROJECTS_LIST "")

function(document_module)
    cmake_parse_arguments(MODULE "" "NAME;CODE;SOURCE;OUTPUT" "" ${ARGN})
    string(REPLACE " " "_" MODULE_CODE "${MODULE_NAME}")

    set(DOXYGEN_FILE ${CMAKE_CURRENT_BINARY_DIR}/${MODULE_OUTPUT}/Doxyfile)
    set(DOXYGEN_HTML_OUTPUT doxygen/${MODULE_OUTPUT})
    set(DOXYGEN_XML_OUTPUT doxygen/${MODULE_OUTPUT}/xml)
    set(DOXYGEN_XML_DIR ${DOCUMENTATION_DIR}/${DOXYGEN_XML_OUTPUT})

    file(MAKE_DIRECTORY ${DOCUMENTATION_DIR}/${DOXYGEN_HTML_OUTPUT})

    configure_file(${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile.in ${DOXYGEN_FILE} @ONLY)
    add_custom_target(GenerateDoxygen_${MODULE_CODE}
            COMMAND ${DOXYGEN_EXECUTABLE} ${DOXYGEN_FILE}
            WORKING_DIRECTORY ${DOCUMENTATION_DIR}
            COMMENT "Generating Chrysalis Doxygen documentation for ${MODULE_NAME}" VERBATIM
    )
    set(ALL_DOXYGEN_TARGETS ${ALL_DOXYGEN_TARGETS} GenerateDoxygen_${MODULE_CODE} PARENT_SCOPE)
    set(BREATHE_PROJECTS_LIST "${BREATHE_PROJECTS_LIST}  \"${MODULE_NAME}\": \"${DOXYGEN_XML_DIR}\"," PARENT_SCOPE)
    set(MODULES_LIST "${MODULES_LIST}  {\"name\": \"${MODULE_NAME}\", \"path\": \"${MODULE_OUTPUT}\"}," PARENT_SCOPE)

    file(MAKE_DIRECTORY ${DOCUMENTATION_DIR}/coverage/${MODULE_OUTPUT})
    set(GCOVR_FILE ${CMAKE_CURRENT_BINARY_DIR}/${MODULE_OUTPUT}/.gcovr.cfg)
    configure_file(${CMAKE_CURRENT_SOURCE_DIR}/.gcovr.cfg.in ${GCOVR_FILE} @ONLY)
    add_custom_target(GenerateCoverageReport_${MODULE_CODE}
            COMMAND gcovr --config ${GCOVR_FILE}
            WORKING_DIRECTORY ${DOCUMENTATION_DIR}
            COMMENT "Generating coverage report for ${MODULE_NAME}" VERBATIM
    )
    set(ALL_COVERAGE_TARGETS ${ALL_COVERAGE_TARGETS} GenerateCoverageReport_${MODULE_CODE} PARENT_SCOPE)
endfunction()

document_module(NAME "Logging" SOURCE "logging" OUTPUT "logging")
document_module(NAME "Pattern" SOURCE "pattern" OUTPUT "pattern")
document_module(NAME "Renderer" SOURCE "renderer" OUTPUT "renderer")
document_module(NAME "Project Composer" SOURCE "pattern/composer" OUTPUT "composer")
if (APP STREQUAL "Chrysalis")
    document_module(NAME "Chrysalis Lab" SOURCE "lab" OUTPUT "lab")
else ()
    document_module(NAME "Hooks" SOURCE "integrations/hooks" OUTPUT "hooks")
    document_module(NAME "CLO3D Extensions" SOURCE "integrations/clo3d" OUTPUT "integrations/clo3d")
    document_module(NAME "CLO3D Chrysalis Extension" SOURCE "integrations/clo3d/extensions/chrysalis" OUTPUT "integrations/clo3d/extensions/chrysalis")
    document_module(NAME "CLO3D DevTools Extension" SOURCE "integrations/clo3d/extensions/dev-tools" OUTPUT "integrations/clo3d/extensions/dev-tools")
    document_module(NAME "CLO3D Authenticator Extension" SOURCE "integrations/clo3d/extensions/authenticator" OUTPUT "integrations/clo3d/extensions/authenticator")
    document_module(NAME "CLO3D Qt Designer plugin" SOURCE "integrations/clo3d/tools/qt-designer-plugin" OUTPUT "integrations/clo3d/qt-designer-plugin")
endif ()

add_custom_target(GenerateDoxygen DEPENDS ${ALL_DOXYGEN_TARGETS} COMMENT "Building all modules' documentation...")
add_custom_target(GenerateCoverageReport DEPENDS ${ALL_COVERAGE_TARGETS} COMMENT "Generating coverage reports...")

# ----- Sphynx Documentation -------------------------------------------------------------------------------------------

find_program(SPHINX_EXECUTABLE NAMES sphinx-build HINTS ${PYTHON_VENV_BIN} REQUIRED)

set(SPHINX_SOURCE ${CMAKE_CURRENT_SOURCE_DIR}/sphinx/source)
set(SPHINX_BUILD ${DOCUMENTATION_DIR})

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/sphinx/source/conf.py.in ${CMAKE_CURRENT_BINARY_DIR}/conf.py @ONLY)

add_custom_target(GenerateDocumentation
        COMMAND ${SPHINX_EXECUTABLE} -c ${CMAKE_CURRENT_BINARY_DIR} -b html ${SPHINX_SOURCE} ${SPHINX_BUILD}
        WORKING_DIRECTORY ${DOCUMENTATION_DIR}
        COMMENT "Generating Chrysalis documentation" VERBATIM
)