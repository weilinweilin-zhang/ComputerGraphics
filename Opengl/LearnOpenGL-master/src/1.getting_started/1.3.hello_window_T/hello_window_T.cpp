#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
using namespace std;

// 二维顶点着色器
float vertices[] =
{
	-0.5f,-0.5f,0.0f,
	0.5f,-0.5f,0.0f,
	0.0f,0.5f,0.0f,
};

float rectvertices[] =
{
	0.5f,0.5f,0.0f,
	0.5f,-0.5f,0.0f,
	-0.5f,-0.5f,0.0f,
	-0.5f,0.5f,0.0f,
};

// EBO
unsigned int indices[] =
{
	0,1,2,
	1,2,3
};

const char *vertexShaderSource = "#version 330 core\n"
    "layout (location = 0) in vec3 aPos;\n"
    "void main()\n"
    "{\n"
    "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
    "}\0";
const char *fragmentShaderSource = "#version 330 core\n"
    "out vec4 FragColor;\n"
    "void main()\n"
    "{\n"
    "   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
    "}\n\0";

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(300, 300, width, height);
}
int main()
{
	// 加载glfw窗口
	glfwInit();
	// 给窗口参数
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(800, 800, "Train", NULL, NULL);
	if (!window)
	{
		std::cout << "fail" << std::endl;
		glfwTerminate();
	}
	glfwMakeContextCurrent(window);

	//加载opengl里面的函数指针
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "fail load" << std::endl;
		return -1;
	}
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	// 顶点着色器
	unsigned int vertexShader;
	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);

	// 设置完后要进行编译
	glCompileShader(vertexShader);
	// 验证着色器是否成功
	int success;
	char infoLog[512];
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		std::cout << "error:" << infoLog << std::endl;
	}

	//片段着色器
	unsigned int FragmentShader;
	FragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(FragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(FragmentShader);
	// 验证着色器是否成功
	int fragmentsuccess;
	char fragmentinfoLog[512];
	glGetShaderiv(FragmentShader, GL_COMPILE_STATUS, &fragmentsuccess);
	if (!fragmentsuccess)
	{
		glGetShaderInfoLog(FragmentShader, 512, NULL, fragmentinfoLog);
		std::cout << "fragmenterror:" << fragmentinfoLog << std::endl;
	}

	// 创建程序编译两个着色器
	unsigned int shaderProgram;
	shaderProgram = glCreateProgram();

	// 链接两个着色器
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, FragmentShader);
	glLinkProgram(shaderProgram);


	// attatch之后就可以删除着色器了
	glDeleteShader(vertexShader);
	glDeleteShader(FragmentShader);


	// 创建VAO
	unsigned int VAO;
	unsigned int VBO;
	unsigned int EBO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &EBO);
	glGenBuffers(1, &VBO); //生成存储区域
	glBindVertexArray(VAO);
	//三角形三个顶点
	//// 把顶点数组复制到缓冲中供opengl使用 
	glBindBuffer(GL_ARRAY_BUFFER, VBO); // 绑定这块区域
	glBufferData(GL_ARRAY_BUFFER, sizeof(rectvertices), rectvertices, GL_STATIC_DRAW);  // 用户数据复制在这块绑定区域，

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	// 复制数据
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

/*

	//// bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
	//glBindVertexArray(VAO);
	//glBindBuffer(GL_ARRAY_BUFFER, VBO); // 绑定这块区域
	//glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);  // 用户数据复制在这块绑定区域，
	//// 设置顶点属性指针
	//// 怎么解析顶点数据
	//glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	//glEnableVertexAttribArray(0);
*/


/*
	//EBO四边形
*/
	//glUseProgram(shaderProgram);
	//glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNALED, 0);
	//绘制物体
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	while (!glfwWindowShouldClose(window))
	{
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		glUseProgram(shaderProgram);
		glBindVertexArray(VAO);
		//glDrawArrays(GL_TRIANGLES, 0, 3);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		glfwSwapBuffers(window);
		glfwPollEvents(); //监听事件内容
	}
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);
	glDeleteProgram(shaderProgram);

	// glfw: terminate, clearing all previously allocated GLFW resources.
	// ------------------------------------------------------------------
	glfwTerminate();

	return 0;
}
