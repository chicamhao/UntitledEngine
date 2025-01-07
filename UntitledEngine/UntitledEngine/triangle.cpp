#include "triangle.h"

void handleCompileError(unsigned int shader);
void handleLinkError(unsigned int object);

void triangle::initialize(float vertices[], unsigned int indices[])
{
    // vertex
    unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexSource, nullptr);
    glCompileShader(vertexShader);
    handleCompileError(vertexShader);
    
    // fragment
    unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentSource, nullptr);
    glCompileShader(fragmentShader);
    handleCompileError(fragmentShader);
    
    // program
    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);
    handleLinkError(shaderProgram);
    
    // release shaders
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
    
    //--link vertex attribute--
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO); // store large number of vertices in GPU's memory
    glGenBuffers(1, &EBO); // avoid verices overlap by using indices

    // bind vertex array object VAO
    glBindVertexArray(VAO); // ~

    // copy vectices array in a buffer for OpenGL to use
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 12, vertices, GL_STATIC_DRAW);
    
    // copy index array in a element buffer
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * 6, indices, GL_STATIC_DRAW);
    
    // interpret the vertex data (per vertex attribute)
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    
    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
}

void triangle::render()
{
    // execute
    glUseProgram(shaderProgram);
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}

void triangle::release()
{
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteProgram(shaderProgram);
}

void handleCompileError(unsigned int object)
{
    int sucess;
    char infoLog[512];
    glGetShaderiv(object, GL_COMPILE_STATUS, &sucess);
    
    if (!sucess)
    {
        glGetShaderInfoLog(object, 512, nullptr, infoLog);
        std::cout << "ERROR::SHADER\n" << infoLog << std::endl;
    }
}

void handleLinkError(unsigned int object)
{
    int sucess;
    char infoLog[512];
    glGetProgramiv(object, GL_LINK_STATUS, &sucess);
    
    if (!sucess)
    {
        glGetProgramInfoLog(object, 512, nullptr, infoLog);
        std::cout << "ERROR::LINK\n" << infoLog << std::endl;
    }
}
