set(QT_QML_OUTPUT_DIRECTORY  ${CMAKE_BINARY_DIR})
set(CMAKE_MODULE_PATH ${ECM_MODULE_PATH} ${CMAKE_CURRENT_SOURCE_DIR}/cmake)
set(CMAKE_AUTOMOC ON)

remove_definitions(-DQT_NO_CAST_FROM_BYTEARRAY)
remove_definitions(-DQT_NO_CAST_FROM_ASCII)
remove_definitions(-DQT_NO_CAST_TO_ASCII)

find_package(ECM REQUIRED NO_MODULE)
find_package(PkgConfig REQUIRED)
find_package(Qt6 6.4 COMPONENTS Quick Core Qml WaylandClient REQUIRED)

find_package(Doxygen)
if (DOXYGEN_FOUND)
    set(DOXYGEN_INPUT ${CMAKE_SOURCE_DIR}/doc/Doxyfile.in)
    set(DOXYGEN_OUTPUT_DIR ${CMAKE_BINARY_DIR}/doc)
    configure_file(${DOXYGEN_INPUT} ${CMAKE_BINARY_DIR}/Doxyfile @ONLY)
    add_custom_target(doc ${DOXYGEN_EXECUTABLE} ${CMAKE_BINARY_DIR}/Doxyfile
                      WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
                      COMMENT "Generating API documentation with Doxygen" VERBATIM)
# Finally, execute "make doc" or "cmake --build <build_dir> --target doc" in the compilation directory to generate Doxygen documentation.
endif ()

set(CLIENT_GENERATED_SRCS
    ${CMAKE_CURRENT_BINARY_DIR}/wayland-wlr-output-power-management-unstable-v1-client-protocol.h
)

set(WSMWAYLAND_SRCS
    wsmwaylandglobal.h
    wsmwaylandglobal.cpp
    outputpowermanagement.h outputpowermanagement.cpp
    abstractresource.h abstractresource.cpp
    abstractresource_p.h
    outputpowermanagement_p.h
)

add_library(wsmwayland
    SHARED
    ${WSMWAYLAND_SRCS}
)

set(control_QMLS
)

#add picture resource
set(image_RSRCS
#    image/switch/switch-handle.png
)

foreach(file IN LISTS control_QMLS image_RSRCS)
    get_filename_component(filename ${file} NAME)
    set_source_files_properties(${file} PROPERTIES QT_RESOURCE_ALIAS ${filename})
endforeach()

set_source_files_properties(${CLIENT_GENERATED_SRCS} PROPERTIES SKIP_AUTOMOC ON)

qt6_generate_wayland_protocol_client_sources(wsmwayland
    FILES
        ${CMAKE_CURRENT_SOURCE_DIR}/protocol/wlr-output-power-management-unstable-v1.xml
)

qt_add_qml_module(wsmwayland
    URI org.lychee.wsmwayland
    VERSION 1.0
    SOURCES ${WSMWAYLAND_SRCS}
    QML_FILES ${control_QMLS}
    RESOURCES ${image_RSRCS}
)

set_target_properties(wsmwayland PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

target_compile_definitions(wsmwayland
    PRIVATE $<$<OR:$<CONFIG:Debug>,$<CONFIG:RelWithDebInfo>>:QT_QML_DEBUG>)

target_link_libraries(wsmwayland PRIVATE
    Qt6::Core
    Qt6::Gui
    Qt6::GuiPrivate
    Qt6::Quick
    Qt6::QuickPrivate
    Qt6::WaylandClient
    Qt6::WaylandClientPrivate
)

target_include_directories(wsmwayland PUBLIC ${CMAKE_CURRENT_BINARY_DIR})

# Prevent EGL headers from including platform headers, in particular Xlib.h.
add_definitions(-DMESA_EGL_NO_X11_HEADERS)
add_definitions(-DEGL_NO_X11)
add_definitions(-DEGL_NO_PLATFORM_SPECIFIC_TYPES)

# get QML install dir
function(get_qml_install_dir target_var)
    get_target_property(QT6_QMAKE_EXECUTABLE Qt6::qmake IMPORTED_LOCATION)
    execute_process(
        COMMAND ${QT6_QMAKE_EXECUTABLE} -query QT_INSTALL_QML
        OUTPUT_VARIABLE QML_INSTALL_DIR
        OUTPUT_STRIP_TRAILING_WHITESPACE
    )
    set(${target_var} ${QML_INSTALL_DIR} PARENT_SCOPE)
endfunction()

get_qml_install_dir(QML_INSTALL_DIR)

install(TARGETS wsmwayland DESTINATION CMAKE_INSTALL_LIBDIR)
install(FILES 
    ${CMAKE_BINARY_DIR}/org/lychee/wsmwayland/qmldir
    ${CMAKE_BINARY_DIR}/org/lychee/wsmwayland/libwsmwaylandplugin.so 
    ${CMAKE_BINARY_DIR}/org/lychee/wsmwayland/wsmwayland.qmltypes 
    DESTINATION ${QML_INSTALL_DIR}/org/lychee/wsmwayland/
)
