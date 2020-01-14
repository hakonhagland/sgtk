cmake_minimum_required(VERSION 3.9)
project(sgtk VERSION 0.5 DESCRIPTION "simple graphics library using gtk3")

# Use the package PkgConfig to detect GTK+ headers/library files
FIND_PACKAGE(PkgConfig REQUIRED)
# see /usr/lib/x86_64-linux-gnu/pkgconfig for valid names of the modules
PKG_CHECK_MODULES(GTK3 REQUIRED gtk+-3.0)

#configure_file(config.h.in config.h)
add_library(sgtk SHARED user.cpp sgtk.cpp)
#set_target_properties(sgtk PROPERTIES PUBLIC_HEADER sgtk.h)
target_include_directories(sgtk PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}
  ${GTK3_INCLUDE_DIRS})
target_link_libraries(sgtk PUBLIC ${GTK3_LIBRARY_DIRS})

install(TARGETS sgtk DESTINATION lib)
install(FILES sgtk.h DESTINATION include)

# specify the C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

