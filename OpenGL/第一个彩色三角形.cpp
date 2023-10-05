
#include <glad/glad.h>  // 必须为首句
#include <GLFW/glfw3.h>
#include <iostream>
#include <chrono>
#include <thread>
#include <cmath>


void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

void processInput(GLFWwindow *window)
{
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

int main() {
    // 初始化FLFW
    glfwInit();
    // 使用OpenGL 3.3
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    // 使用的是核心模式(Core-profile)
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow *window = glfwCreateWindow(800,600,"LearnOpenGL",NULL,NULL);
    if (window == nullptr) {
        std::cerr << "创建GLFW窗口失败" << std::endl;
        glfwTerminate();
        return -1;
    }
      // 设置为当前线程的主上下文
    glfwMakeContextCurrent(window);

    // 使用GLAD管理OPENGL的函数指针
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    const char *vertexShaderSource =
            "#version 330 core\n"
            "layout (location = 0) in vec3 aPos;\n"
            "layout (location = 1) in vec3 aColor;\n"
            "out vec3 ourColor;\n"
            "void main()\n"
            "{\n"
            "   gl_Position = vec4(aPos, 1.0);\n"
            "   ourColor = aColor;\n"
            "}\0";


    unsigned int vertexShader;
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader,1,&vertexShaderSource,NULL);
    glCompileShader(vertexShader);
    int success;
    char infoLog[512];
    glGetShaderiv(vertexShader,GL_COMPILE_STATUS,&success);
    if (!success) {
        glGetShaderInfoLog(vertexShader,512,NULL,infoLog);
        std::cerr << "error::shader::vertex::compilation_failed" << '\n'
            << infoLog << std::endl;
    }

    unsigned int fragmentShader;
    const char *fragmentShaderSource =
            "#version 330 core\n"
            "out vec4 FragColor;\n"
            "in vec3 ourColor;\n"
            "void main()\n"
            "{\n"
            "   FragColor = vec4(ourColor, 1.0f);\n"
            "}\n\0";
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader,1,&fragmentShaderSource,NULL);
    glCompileShader(fragmentShader);


    unsigned int shaderProgram;
    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram,vertexShader);
    glAttachShader(shaderProgram,fragmentShader);
    glLinkProgram(shaderProgram);
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if(!success) {
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        std::cerr << "error::shader::program::linking_failer\n" << infoLog << std::endl;
    }
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);


    // 标准化设备坐标，屏幕中心为原点
    // 上为y轴正方向, 右为x轴正方
    float vertices[] = {
            // 位置              // 颜色
            0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f,  // bottom right
            -0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,  // bottom left
            0.0f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f   // top
    };
    // 定点缓冲对象,（其值是定点缓冲对象独一无二的ID）
    unsigned int VBO,VAO,EBO;
    glGenVertexArrays(1,&VAO);
    glGenBuffers(1,&VBO);
    glGenBuffers(1,&EBO);
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER,VBO);
    // 数据几乎不会改变
    glBufferData(GL_ARRAY_BUFFER,sizeof(vertices),vertices,GL_STATIC_DRAW);

//    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,EBO);
//    glBufferData(GL_ELEMENT_ARRAY_BUFFER,sizeof(indices),indices,GL_STATIC_DRAW);

    // 位置属性
    glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,6*sizeof(float ),(void*)0);
    glEnableVertexAttribArray(0);

    // 颜色属性
    glVertexAttribPointer(1,3,GL_FLOAT,GL_FALSE,6*sizeof(float ),(void*)(3*sizeof(float )));
    glEnableVertexAttribArray(1);



//    glBindBuffer(GL_ARRAY_BUFFER,0);
//    glBindVertexArray(0);


    // 视口
    // 前两个参数是左下角坐标，后面是宽高
    glViewport(0,0,800,600);
    // 注册事件，窗口大小调整的时候调用这个函数
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // 窗口是否要求退出
    while (!glfwWindowShouldClose(window)) {

        // 输入
        processInput(window);

        glClearColor(0.2f, 0.3f, 1.2f, 1.0f);// 设置清空缓冲（屏幕）所用的颜色
        glClear(GL_COLOR_BUFFER_BIT);// 清空颜色缓冲

        glUseProgram(shaderProgram);

        // update shader uniform
        double  timeValue = glfwGetTime();
        float greenValue = static_cast<float>(sin(timeValue) / 2.0 + 0.5);
        int vertexColorLocation = glGetUniformLocation(shaderProgram, "ourColor");
        glUniform4f(vertexColorLocation, 0.0f, greenValue, 0.0f, 1.0f);

        // render the triangle
        glDrawArrays(GL_TRIANGLES, 0, 3);

        // 触发事件
        glfwPollEvents();
        // 交换缓冲区颜色
        glfwSwapBuffers(window);
    }

    // 释放删除之前分配的资源
    glfwTerminate();


    return 0;
}
