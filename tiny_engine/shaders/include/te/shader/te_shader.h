#pragma once

typedef unsigned int te_shader;

te_shader shader_new(const char* vertex_shader_path,
                     const char* fragment_shader_path,
                     bool* errors);

enum shader_type {
    SHADER_VERTEX,
    SHADER_FRAGMENT,
    SHADER_PROGRAM,
};
