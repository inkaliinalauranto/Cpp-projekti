cmake_minimum_required(VERSION 3.5)

project(Cpp-projekti LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(Cpp-projekti main.cpp
    skis.h skis.cpp
    skiboots.h skiboots.cpp
    poles.h poles.cpp
    others.h others.cpp
    menu.h menu.cpp
    items.h items.cpp
    item.h item.cpp)

include(GNUInstallDirs)
install(TARGETS Cpp-projekti
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
