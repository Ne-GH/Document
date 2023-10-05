/*******************************************************************************
 * Author : yongheng
 * Data   : 2023/10/05 22:12
*******************************************************************************/

#include "Shader.h"

Shader::Shader(const char *vertexPath, const char *fragmentPath) {
    std::string vertexCode,fragmentCode;
    std::ifstream vShaderFile,fShaderFile;
    vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    try {
        vShaderFile.open(vertexPath);
        fShaderFile.open(fragmentPath);
//        vShaderFile >> vertexCode;
//        fShaderFile >> fragmentCode;
//        vertexCode = std::string(std::istreambuf_iterator<char>{vShaderFile},std::istreambuf_iterator<char>{});
        std::stringstream vShaderStream,fShaderStream;
        vShaderStream << vShaderFile.rdbuf();
        fShaderStream << fShaderFile.rdbuf();
        vShaderFile.close();
        fShaderFile.close();
        vertexCode = vShaderStream.str();
        fragmentCode = fShaderStream.str();
    }
    catch (std::ifstream ::failure e) {
        std::cerr << "error::shader::file not succesfully read" << std::endl;
    }


    const char* vShaderCode = vertexCode.c_str();
    const char* fShaderCode = fragmentCode.c_str();
    unsigned int vertex,fragment;
    int success;
    char infoLog[512];
    vertex = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex,1,&vShaderCode,NULL);
    glCompileShader(vertex);
    glGetShaderiv(vertex,GL_COMPILE_STATUS,&success);
    if (!success) {
        glGetShaderInfoLog(vertex,512,NULL,infoLog);
        std::cout << "error::shader::vertex::compilation failed\n" << infoLog << std::endl;
    }

    fragment = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment,1,&fShaderCode,NULL);
    glCompileShader(fragment);
    glGetShaderiv(fragment,GL_COMPILE_STATUS,&success);
    if (!success) {
        glGetShaderInfoLog(fragment,512,NULL,infoLog);
        std::cout << "error::shader::vertex::compilation failed\n" << infoLog << std::endl;
    }

    // 着色器程序
    ID = glCreateProgram();
    glAttachShader(ID,vertex);
    glAttachShader(ID,fragment);
    glLinkProgram(ID);

    glGetProgramiv(ID,GL_LINK_STATUS,&success);
    if (!success) {
        glGetProgramInfoLog(ID,512,NULL,infoLog);
        std::cerr << "error::shader::program::linking failed\n" << infoLog << std::endl;
    }

    glDeleteShader(vertex);
    glDeleteShader(fragment);

}

void Shader::use() {
    glUseProgram(ID);
}

void Shader::SetBool(const std::string &name, bool value) const {
    glUniform1i(glGetUniformLocation(ID,name.c_str()),(int)value);
}

void Shader::SetInt(const std::string &name, int value) const {
    glUniform1i(glGetUniformLocation(ID,name.c_str()),value);
}

void Shader::SetFloat(const std::string &name, float value) const {
    glUniform1f(glGetUniformLocation(ID,name.c_str()),value);
}
