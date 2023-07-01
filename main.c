#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <stdio.h>
#include <time.h>
#include <sys/stat.h>
#include <sys/types.h>

#include <cglm/cglm.h>
#include <collections/vec.h> 
#include <collections/d_string.h>
#include <te/geo/triangle.h>
#include <te/geo/quad.h>
#include <te/shader/te_shader.h>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);

// settings
unsigned int SCR_WIDTH = 800;
unsigned int SCR_HEIGHT = 600;

int main(int argc, char** argv)
{
    GLFWwindow* window_configure()
    {
        // glfw: initialize and configure
        // ------------------------------
        glfwInit();
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif


        // glfw window creation
        // --------------------
        GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
        if (window == NULL)
        {
            printf("Failed to create GLFW window");
            glfwTerminate();
            abort();
        }
        glfwMakeContextCurrent(window);
        glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

        // glad: load all OpenGL function pointers
        // ---------------------------------------
        if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
        {
            printf("Failed to initialize GLAD");
            abort();
        }    

        return window;
    }
    GLFWwindow* window = window_configure();


    te_tri vertices;
    tri_new((vec3){-0.5f, -0.5f, 0.0f},
            (vec3){ 0.5f, -0.5f, 0.0f},
            (vec3){ 0.0f,  0.5f, 0.0f},
            &vertices);

    te_quad screen = rect_new((float[3]){0.0f, 0.0f, 0.0f}, 2.0f, 2.0f);
    GLuint VBO;
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);



    glVertexAttribPointer(0, 6, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);  

    // 0. copy our vertices array in a buffer for OpenGL to use
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(screen.verts), screen.verts, GL_STATIC_DRAW);
    // 1. then set the vertex attributes pointers
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);  
    // 2. use our shader program when we want to render an object

    unsigned int VAO;
    glGenVertexArrays(1, &VAO);
    // ..:: Initialization code (done once (unless your object frequently changes)) :: ..
    // 1. bind Vertex Array Object
    glBindVertexArray(VAO);
    // 2. copy our vertices array in a buffer for OpenGL to use
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(screen.verts), screen.verts, GL_STATIC_DRAW);
    // 3. then set our vertex attributes pointers
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    bool shader_errors = false;
    GLuint shaderProgram = shader_new("../shaders/hello.vs",
            "../shaders/hello.fs", 
            &shader_errors);
    // render loop
    // -----------
    //
    struct stat attr;
    stat("../shaders/hello.fs", &attr);
    time_t time_since_touched   = attr.st_mtime;
    time_t time_since_touched_2 = attr.st_mtime;
    double delta_time = 0.0;
    while (!glfwWindowShouldClose(window))
    {
        float iTime = glfwGetTime();
        int vertexColorLocation = glGetUniformLocation(shaderProgram, "iTime");
        glUniform1f(vertexColorLocation, iTime);

        int iResolution = glGetUniformLocation(shaderProgram, "iResolution");
        glUniform2ui(iResolution, SCR_WIDTH, SCR_HEIGHT);

        // get time
        stat("../shaders/hello.fs", &attr);
        time_since_touched_2 = attr.st_mtime;

        delta_time = difftime(time_since_touched_2, time_since_touched);
        // if the file was just written to
        if (delta_time > 0.1) {
            time_since_touched   = time_since_touched_2; // set the new touch time
            delta_time = 0.0;

            //delete the program
            glDeleteProgram(shaderProgram);

            //recompile
            shaderProgram = shader_new("../shaders/hello.vs",
                    "../shaders/hello.fs", 
                    &shader_errors);

            // while errors
            while (shader_errors) {
                // WAIT FOR FILE TOUCH
                //get time
                stat("../shaders/hello.fs", &attr);
                time_since_touched   = attr.st_mtime;
                time_since_touched_2 = time_since_touched;
                delta_time = 100; // delta is large

                // until the file has been touched
                do {
                    stat("../shaders/hello.fs", &attr); //get time
                    time_since_touched_2 = attr.st_mtime;
                    delta_time = difftime(time_since_touched_2, time_since_touched);
                    // printf("DTIME: %lf\n", delta_time);
                } while (delta_time < .1);


                glDeleteProgram(shaderProgram);
                shaderProgram = shader_new("../shaders/hello.vs",
                        "../shaders/hello.fs", 
                        &shader_errors);
            }
            glUseProgram(shaderProgram);
            printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
        }
        //printf("delta time %lf\n", delta_time);

        // input
        // -----
        processInput(window);

        // render
        // ------
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(shaderProgram);
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 6);


        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
        glfwSwapBuffers(window);
        glfwPollEvents();
        glDeleteProgram(shaderProgram);
    }

    // glfw: terminate, clearing all previously allocated GLFW resources.
    // ------------------------------------------------------------------
    glfwTerminate();
    return 0;
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow *window)
{
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and 
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
    SCR_HEIGHT = height;
    SCR_WIDTH = width;
}
