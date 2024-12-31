#include "triangle.h"

void handle_log(unsigned int vertexShader, GLenum status);

void triangle::setup(float vertices[])
{
    // vertex
    unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexSource, nullptr);
    glCompileShader(vertexShader);
    handle_log(vertexShader, GL_COMPILE_STATUS);
    
    // fragment
    unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentSource, nullptr);
    glCompileShader(fragmentShader);
    handle_log(fragmentShader, GL_COMPILE_STATUS);
    
    // program
    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);
    handle_log(shaderProgram, GL_LINK_STATUS);
    
    // release shaders
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
    
    // link vertex attribute
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
}

void triangle::render()
{
    // execute
    glUseProgram(shaderProgram);
    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, 3);
}

void triangle::release()
{
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteProgram(shaderProgram);
}

void handle_log(unsigned int shader, GLenum status)
{
    int sucess;
    char infoLog[512];
    glGetShaderiv(shader, status, &sucess);
    if (!sucess)
    {
        glGetShaderInfoLog(shader, 512, nullptr, infoLog);
        std::cout << "ERROR::\n" << infoLog << std::endl;
    }
}
