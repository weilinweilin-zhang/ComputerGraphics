#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;



float DoubleTranigleVertices[] =
{
    -1.0f,-0.5f,0.0f,
    -0.0f,-0.5f,0.0f,
    -0.5f,0.5f,0.0f,

    1.0f,-0.5f,0.0f,
    0.0f,-0.5f,0.0f,
    0.5f,0.5f,0.0f,
};

// ��ɫ��
const char* vertexShaderSource = "#version 330 core\n"
"layout (location=0) in vec3 aPos;\n"
"void main()\n"
"{\n"
"   gl_Position=vec4(aPos.x,aPos.y,aPos.z,1.0);\n"
"}\n";

const char* fragmentShaderSource = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
" FragColor = vec4(1.0f,0.5f,0.2f,1.0f);\n"
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

    // ������ɫ��
    // ���ɵ춨
    unsigned int vertexShader;
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);
    // �����Ƿ�ɹ�
    int success;
    char infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        std::cout << infoLog;
    }
    // ����Ƭ����ɫ��

    unsigned int fragmentShader;
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);

    int fragmentsuccess;
    char fragmentinfolog[512];
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &fragmentsuccess);
    if(!fragmentsuccess)
    {
		glGetShaderInfoLog(fragmentShader, 512, NULL,fragmentinfolog);
        std::cout << fragmentinfolog;
    }

    // ����������ɫ��
    unsigned int shaderprogram;
    shaderprogram = glCreateProgram();

    // ����������ɫ��
    glAttachShader(shaderprogram, vertexShader);
    glAttachShader(shaderprogram, fragmentShader);
    glLinkProgram(shaderprogram);

    // ���򴴽����������� ���ɸɵ���
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    // ֮����Ƕ�������
    unsigned int VAO, VBO;

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    // ��VAO
    glBindVertexArray(VAO);
    // �󶨻�������
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    // �����û�����
    glBufferData(GL_ARRAY_BUFFER, sizeof(DoubleTranigleVertices), DoubleTranigleVertices, GL_STATIC_DRAW);

    // ������˵��ô�������
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    // location ����;
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    




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