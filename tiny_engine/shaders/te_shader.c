#include <stdio.h>
#include <glad/glad.h>
#include <te/shader/te_shader.h>
#include <collections/d_string.h>




static bool shader_compile_errors(unsigned int shader, const char* path);
static bool shader_link_errors(unsigned int shader);



te_shader shader_new(const char* vertex_shader_path,
                     const char* fragment_shader_path,
                     bool* errors)
{
    *errors = false;
    const char* const vs_source = dstr_from_file(vertex_shader_path);
    GLuint vs;
    vs = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vs, 1, &vs_source, NULL);
    glCompileShader(vs);
    *errors |= shader_compile_errors(vs, vertex_shader_path);


    const char* const fs_source = dstr_from_file(fragment_shader_path);
    GLuint fs;
    fs = glCreateShader(GL_FRAGMENT_SHADER);

    glShaderSource(fs, 1, &fs_source, NULL);
    glCompileShader(fs);

    *errors |= shader_compile_errors(fs, fragment_shader_path);



    GLuint shader_program;
    shader_program = glCreateProgram();

    glAttachShader(shader_program, vs);
    glAttachShader(shader_program, fs);
    glLinkProgram(shader_program);
    *errors |= shader_link_errors(shader_program);

    glDeleteShader(vs);
    glDeleteShader(fs);

    return shader_program;
}

#define COLOR_BOLD_RED "\033[1;91m"
#define COLOR_BOLD     "\033[1m"
#define COLOR_NRM      "\x1B[0m"
static bool shader_compile_errors(unsigned int shader, const char* path)
{
    int  success;
    char infoLog[1024];

    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if(!success)
    {
        glGetShaderInfoLog(shader, 1024, NULL, infoLog);
        printf(COLOR_BOLD_RED "%s: " COLOR_NRM COLOR_BOLD "%s\n" COLOR_NRM, path, infoLog);
    }
    return !success;
}
static bool shader_link_errors(unsigned int shader)
{
    int  success;
    char infoLog[1024];

    glGetProgramiv(shader, GL_LINK_STATUS, &success);
    if(!success) {
        glGetProgramInfoLog(shader, 1024, NULL, infoLog);
        printf(COLOR_BOLD_RED "link error: " COLOR_NRM COLOR_BOLD "%s\n" COLOR_NRM, infoLog);
    }
    return !success;
}
