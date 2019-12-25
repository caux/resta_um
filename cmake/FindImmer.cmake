# - Find Immer

set(IMMER_LIBRARY ${PROJECT_SOURCE_DIR}/lib/immer/)
set(IMMER_INCLUDE_DIR ${PROJECT_SOURCE_DIR}/lib/immer/)
set(IMMER_FOUND TRUE)

add_library(immer INTERFACE)
target_include_directories(immer 
  INTERFACE
    ${IMMER_INCLUDE_DIR}
  )