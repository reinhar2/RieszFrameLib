# Global Header List only for sources for IDEs
file(GLOB HEADER_LIST LIST_DIRECTORIES false CONFIGURE_DEPENDS "${PROJECT_SOURCE_DIR}/include/*.hpp")

add_library(DataLib INTERFACE)
target_include_directories(DataLib INTERFACE ../include)
target_link_libraries(DataLib INTERFACE ${MATHLIB})