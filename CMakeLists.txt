cmake_minimum_required(VERSION 3.8)
set(CMAKE_CXX_STANDARD 17)
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

# Main project
project(resta_um)

# ccache
find_program(CCACHE ccache)
if (CCACHE)
  message(STATUS "Using ccache: ${CCACHE}")
  set_property(GLOBAL PROPERTY RULE_LAUNCH_COMPILE ${CCACHE})
  set_property(GLOBAL PROPERTY RULE_LAUNCH_LINK ${CCACHE})
else()
  message(STATUS "Could not find ccache")
endif()

find_package(Boost 1.56 COMPONENTS system REQUIRED)
find_package(Immer REQUIRED)
find_package(Zug REQUIRED)
find_package(Lager REQUIRED)

# sources
add_subdirectory(src)