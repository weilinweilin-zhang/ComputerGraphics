#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <learnopengl/shader_s.h>
#include <iostream>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;


// practice1
const char* vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"void main()\n"
"{\n"
"gl_Position = vec4(aPos,1.0);\n"
"}\n";

const char* fragmentShaderSource = "#version 330 core\n"
"out vec4 FragColor ;\n"
"uniform vec4 ourColor;\n"
"void main()\n"
"{\n"
" FragColor = ourColor;\n"
"}\n\0";

// practice2
const char* vertexShaderSource2 = "#version 330 core\n"
"layout (location =0) in vec3 aPos;\n"
"layout (location =1) in vec3 aColor;\n"
"out vec3 ourColor;\n"
"void main()\n"
"{\n"
" gl_Position = vec4(aPos,1.0);\n"
"ourColor =aColor;\n"
"}\0";


const char* fragmentShaderSource2 = "#version 330 core\n"
"out vec4 FragColor;\n"
"in vec3 ourColor;\n"
"void main()\n"
"{\n"
"FragColor=vec4(ourColor,1.0f);\n"
"}\n\0";







int main()
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
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // glad: load all OpenGL function pointers
    // ---------------------------------------
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    //unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    //glShaderSource(vertexShader, 1, &vertexShaderSource2, NULL);
    //glCompileShader(vertexShader);

    //int success;
    //char infoLog[512];
    //glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    //if (!success)
    //{
    //    glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
    //    std::cout << infoLog << "error log";
    //}

    //unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    //glShaderSource(fragmentShader, 1, &fragmentShaderSource2, NULL);
    //glCompileShader(fragmentShader);
    //glGetShaderiv(fragmentShader,GL_COMPILE_STATUS,&success);
    //if (!success)
    //{
    //    glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
    //    std::cout << infoLog << "error log";
    //}
    //unsigned int shaderProgram = glCreateProgram();
    //glAttachShader(shaderProgram, vertexShader);
    //glAttachShader(shaderProgram, fragmentShader);
    //glLinkProgram(shaderProgram);
    //glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    //if (!success)
    //{
    //    glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
    //    std::cout << infoLog;
    //}
    //glDeleteShader(vertexShader);
    //glDeleteShader(fragmentShader);

    // 练习1 顶点着色器上下颠倒
    Shader ourShader("3.3.shader.vs", "3.3.shader.fs");

    // 顶点数据
    float vertices[] = {
         0.5f, -0.5f, 0.0f,  // bottom right
        -0.5f, -0.5f, 0.0f,  // bottom left
         0.0f,  0.5f, 0.0f   // top 
    };

    // practice2
    float vertices2[] =
    {
         0.5f, -0.5f, 0.0f,1.0f,0.0f,0.0f,  // bottom right
        -0.5f, -0.5f, 0.0f,0.0f,1.0f,0.0f,  // bottom left
         0.0f,  0.5f, 0.0f,0.0f,0.0f,1.0f  // top 
    };
    unsigned int VAO, VBO;
    glGenVertexArrays(1, &VAO); 
    glGenBuffers(1, &VBO);

    // 先绑定VAO
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices2), vertices2, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*) 0);
    glEnableVertexAttribArray(0);

    // 第一个就是对应的layout位置
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3*sizeof(float)));
    glEnableVertexAttribArray(1);
    // 用对应的着色器进行干扰
    // render loop
    // -----------
    ourShader.use();
    float offset = 0.5f;
    ourShader.setFloat("xOffset", offset);
    while (!glfwWindowShouldClose(window))
    {
        // input
        // -----
        processInput(window);




        // render
        // ------
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        
        //practics 1
        //double timervalue = glfwGetTime();
        //float value = static_cast<float>(sin(timervalue) / 2.0 + 0.5);
        //// 传给着色器里面的uniform 对象


        // render the triangle
        //ourShader.use();
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // optional: de-allocate all resources once they've outlived their purpose:
    // ------------------------------------------------------------------------
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    // glfw: terminate, clearing all previously allocated GLFW resources.
    // ------------------------------------------------------------------
    glfwTerminate();
    return 0;
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow *window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and 
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}
