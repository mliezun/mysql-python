cmake_minimum_required(VERSION 3.9)
project(mysql-python VERSION 0.0.1 DESCRIPTION "mysql-python execute python code from mysql")
include(GNUInstallDirs)
add_library(mysql-python SHARED src/mysql-python.cpp)
add_subdirectory(pybind11)
set_target_properties(mysql-python PROPERTIES
    VERSION ${PROJECT_VERSION}
    SOVERSION 1
    PUBLIC_HEADER api/mysql-python.h)
configure_file(mysql-python.pc.in mysql-python.pc @ONLY)
target_include_directories(mysql-python PRIVATE .)
target_include_directories(mysql-python PRIVATE ./include)
target_link_libraries(mysql-python PRIVATE pybind11::embed)
install(TARGETS mysql-python
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})
install(FILES ${CMAKE_BINARY_DIR}/mysql-python.pc
    DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/pkgconfig)
