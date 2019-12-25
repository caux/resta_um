# - Find Lager

set(LAGER_LIBRARY ${PROJECT_SOURCE_DIR}/lib/lager/lager/)
set(LAGER_INCLUDE_DIR ${PROJECT_SOURCE_DIR}/lib/lager/lager/)
set(LAGER_FOUND TRUE)

configure_file(${LAGER_LIBRARY}config.hpp.in
  "${LAGER_LIBRARY}config.hpp")

add_library(lager INTERFACE)
target_include_directories(lager INTERFACE
  $<BUILD_INTERFACE:${lager_BINARY_DIR}/>
  $<BUILD_INTERFACE:${lager_SOURCE_DIR}/>
  $<INSTALL_INTERFACE:include>)