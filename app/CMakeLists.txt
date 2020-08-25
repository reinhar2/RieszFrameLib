# Global Header List only for sources for IDEs
file(GLOB HEADER_LIST LIST_DIRECTORIES false CONFIGURE_DEPENDS "${PROJECT_SOURCE_DIR}/include/*.hpp")

# add for testing purposes
add_executable(MyApp app1.cpp ${HEADER_LIST})
target_include_directories(MyApp PRIVATE ../include)
target_link_libraries(MyApp PRIVATE ${MATHLIB})