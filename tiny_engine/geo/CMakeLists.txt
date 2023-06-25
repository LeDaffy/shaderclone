add_library(geo triangle.c quad.c)
target_include_directories(geo PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
