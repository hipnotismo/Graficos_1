#include "BaseGame.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>

#define ASSERT(x)  if(!(x)) __debugbreak();
#define GLCall(x) GLClearError();\
    x;\
    ASSERT (GLLogCall(#x, __FILE__, __LINE__));

static void GLClearError()
{
    while (glGetError() != GL_NO_ERROR);
}

static bool GLLogCall(const char* function, const char* file, int line)
{
    while (GLenum error = glGetError())
    {
        std::cout << "[OpenGL ERROR] ( " << error << " ):" << function << " : " << file << std::endl;
        return false;
    }
    return true;
}

static unsigned int CompileShader(unsigned int type, const std::string & source)
{
    unsigned int id = glCreateShader(type);
    const char* src = source.c_str();

    GLCall(glShaderSource(id, 1, &src, nullptr));
    GLCall(glCompileShader(id));

    int result;
    GLCall(glGetShaderiv(id, GL_COMPILE_STATUS, &result));

    if (result == GL_FALSE)
    {
        int lenght;
        GLCall(glGetShaderiv(id, GL_INFO_LOG_LENGTH, &lenght));
        char* message = (char*)alloca(lenght * sizeof(char));
        GLCall(glGetShaderInfoLog(id, lenght, &lenght, message));
        std::cout << "failed to compile " << (type == GL_VERTEX_SHADER ? " vertex" : " fragment");

        std::cout << message << std::endl;
        GLCall(glDeleteShader(id));
        return 0;
    }

    return id;
}
// ^
// "Writing a shader in openGL" - cherno (vid)
static unsigned int CreateShader(const std::string & vertexShader, const std::string & fragmentShader)
{
    unsigned int program = glCreateProgram();
    unsigned int vs = CompileShader(GL_VERTEX_SHADER, vertexShader);
    unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, fragmentShader);

    GLCall(glAttachShader(program, vs));
    GLCall(glAttachShader(program, fs));
    GLCall(glLinkProgram(program));
    GLCall(glValidateProgram(program));

    GLCall(glDetachShader(program, vs));
    GLCall(glDeleteShader(vs));
    GLCall(glDetachShader(program, fs));
    GLCall(glDeleteShader(fs));

    return program;
}

std::string vertexShader =
"#version 330 core\n"
"\n"
"layout(location = 0) in vec4 position;\n"
"void main()\n"
"{\n"
"gl_Position = position;"
"}\n";

std::string fragmentShader =
"#version 330 core\n"
"\n"
"layout(location = 0) out vec4 color;"
"void main()\n"
"{\n"
"color = vec4 (1.0, 0.0, 0.0, 1.0);\n"
"}\n";


int main(void)
{
    GLFWwindow* window;

    // Init lib
    if (!glfwInit())
        return -1;

    // Create a windowed mode window and its OpenGL context 
    window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    // Make the window's context current 
    glfwMakeContextCurrent(window);

    // Glew Init.
    if (glewInit() != GLEW_OK)
        std::cout << "ERROR!" << std::endl;
    std::cout << glGetString(GL_VERSION) << std::endl;

    // triangle load
    float positions[] =
    {
        -0.5f, -0.5f,
         0.5f, -0.5f,
         0.5f,  0.5f,
        -0.5f,  0.5f,
    };

    unsigned int indices[] = {
        0, 1, 2,
        2, 3, 0
    };

    unsigned int buffer;
    glGenBuffers(1, &buffer);   
    glBindBuffer(GL_ARRAY_BUFFER, buffer);
    glBufferData(GL_ARRAY_BUFFER, 6 * 2 * sizeof(float), positions, GL_STATIC_DRAW);

    //Attrib - Layouts
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, 0);

    unsigned int ibo; //Index Buffer Object = ibo
    glGenBuffers(1, &ibo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, 6 * sizeof(unsigned int), indices, GL_STATIC_DRAW);

    unsigned int shader = CreateShader(vertexShader, fragmentShader);
    glUseProgram(shader);

    glBindBuffer(GL_ARRAY_BUFFER, 0);

    // Main Loop
    while (!glfwWindowShouldClose(window))
    {
        // Render here 
        GLCall(glClear(GL_COLOR_BUFFER_BIT));


        // Draw Binded buffer
        GLCall(glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr));

        // Swap front and back buffers 
        GLCall(glfwSwapBuffers(window));

        // Poll for and process events 
        GLCall(glfwPollEvents());
    }

    glDeleteProgram(shader);

    glfwTerminate();
    return 0;
}


