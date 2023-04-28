cmake_minimum_required(VERSION 3.26)
project(civetweb_qt)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_AUTOMOC ON)

find_package(Qt6 COMPONENTS
        Core
        Gui
        Widgets
        REQUIRED)

find_package(PkgConfig)
pkg_check_modules(CAIRO REQUIRED cairo)

find_package(OpenSSL REQUIRED)

set(CIVETWEB_SRC
        civetweb/include/civetweb.h
        civetweb/src/civetweb.c
        civetweb/src/md5.inl
        civetweb/src/sha1.inl
        civetweb/src/handle_form.inl
        civetweb/src/response.inl
        civetweb/src/sort.inl
        civetweb/src/match.inl
        civetweb/src/timer.inl
        civetweb/src/http2.inl
        )

add_executable(civetweb_qt main.cpp ${CIVETWEB_SRC}
        Server.cpp Server.h
        Dictionary.cpp Dictionary.h
        ImageGenerator.cpp ImageGenerator.h
        )

target_include_directories(civetweb_qt PUBLIC civetweb/include)

target_compile_definitions(civetweb_qt PUBLIC
        NO_SSL # no need, because local app cannot use it
        # DEBUG useful
        )

target_link_libraries(civetweb_qt
        Qt::Core
        Qt::Gui
        Qt::Widgets
        OpenSSL::SSL
        ${CAIRO_LIBRARIES}
        )

target_include_directories(civetweb_qt PUBLIC
        ${CAIRO_INCLUDE_DIRS})

