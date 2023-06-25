add_library(te_shader te_shader.c)
target_include_directories(te_shader PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_link_libraries(te_shader PUBLIC collections glad)
