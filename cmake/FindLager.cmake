# - Find Lager

set(LAGER_LIBRARY ${PROJECT_SOURCE_DIR}/lib/lager/)
set(LAGER_INCLUDE_DIR ${PROJECT_SOURCE_DIR}/lib/lager/)
set(LAGER_FOUND TRUE)

configure_file(${LAGER_LIBRARY}lager/config.hpp.in
  "${LAGER_LIBRARY}lager/config.hpp")

add_library(lager INTERFACE)
target_include_directories(lager
  INTERFACE
    ${LAGER_INCLUDE_DIR}
  )