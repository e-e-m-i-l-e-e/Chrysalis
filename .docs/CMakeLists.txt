# ----- Load tools -----------------------------------------------------------------------------------------------------

set(DOCUMENTS_DIR ${CMAKE_BINARY_DIR}/docs)

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
    set(PLANTUML "${PLANTUML_DIR}/plantuml.jar")

    find_program(CLANG_UML NAMES clang-uml.exe)
endif ()

# ----- Generate UML Diagrams ------------------------------------------------------------------------------------------

if(CLANG_UML)
    add_custom_target(GenerateUML
            COMMAND ${CLANG_UML} -c .docs/diagrams/chrysalis/.clang-uml -o ${DOCUMENTS_DIR}/diagrams/chrysalis
            COMMAND ${CLANG_UML} -c .docs/diagrams/clo3d/.clang-uml -o ${DOCUMENTS_DIR}/diagrams/clo3d
            WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
            COMMENT "Generating Chrysalis UML diagrams" USES_TERMINAL VERBATIM
    )
else()
    message(WARNING "clang-uml was not found.")
endif()

# ----- Doxygen --------------------------------------------------------------------------------------------------------

find_package(Doxygen REQUIRED)

set(DOXYGEN_FILE ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile)

set(DOXYGEN_HTML_OUTPUT doxygen)
set(DOXYGEN_XML_OUTPUT doxygen/xml)
set(DOXYGEN_XML_DIR ${DOCUMENTS_DIR}/${DOXYGEN_XML_OUTPUT})

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile.in ${DOXYGEN_FILE} @ONLY)
add_custom_target(GenerateDoxygen
        COMMAND ${DOXYGEN_EXECUTABLE} ${DOXYGEN_FILE}
        WORKING_DIRECTORY ${DOCUMENTS_DIR}
        COMMENT "Generating Chrysalis Doxygen documentation" VERBATIM
)

# ----- Sphynx Documentation -------------------------------------------------------------------------------------------

find_program(SPHINX_EXECUTABLE NAMES sphinx-build REQUIRED)

set(SPHINX_SOURCE ${CMAKE_CURRENT_SOURCE_DIR}/sphinx/source)
set(SPHINX_BUILD ${CMAKE_BINARY_DIR}/docs)

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/sphinx/source/conf.py.in ${CMAKE_CURRENT_BINARY_DIR}/conf.py @ONLY )

add_custom_target(Documentation
        COMMAND ${SPHINX_EXECUTABLE} -c ${CMAKE_CURRENT_BINARY_DIR} -b html ${SPHINX_SOURCE} ${SPHINX_BUILD}
        WORKING_DIRECTORY ${DOCUMENTS_DIR}
        COMMENT "Generating Chrysalis documentation" VERBATIM
)