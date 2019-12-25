# - Find Zug

set(ZUG_LIBRARY ${PROJECT_SOURCE_DIR}/lib/zug/)
set(ZUG_INCLUDE_DIR ${PROJECT_SOURCE_DIR}/lib/zug/)
set(ZUG_FOUND TRUE)

add_library(zug INTERFACE)
target_include_directories(zug 
  INTERFACE
    ${ZUG_INCLUDE_DIR}
  )