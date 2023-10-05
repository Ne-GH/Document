/*******************************************************************************
 * Author : yongheng
 * Data   : 2023/10/05 22:12
*******************************************************************************/


#pragma once
#include <glad/glad.h>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

class Shader {
public:
    // 程序ID
    unsigned int ID;
    // 构造器读取并构建着色器
    Shader(const char* vertexPath,const char *fragmentPath);

    // 使用/激活程序
    void use();

    // uniform工具函数
    void SetBool(const std::string &name,bool value) const;
    void SetInt(const std::string &name,int value) const;
    void SetFloat(const std::string &name,float value) const;

};
