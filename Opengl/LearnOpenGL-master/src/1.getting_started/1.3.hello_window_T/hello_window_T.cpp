#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
using namespace std;

// ��ά������ɫ��
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
	// ����glfw����
	glfwInit();
	// �����ڲ���
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

	//����opengl����ĺ���ָ��
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "fail load" << std::endl;
		return -1;
	}
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	// ������ɫ��
	unsigned int vertexShader;
	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);

	// �������Ҫ���б���
	glCompileShader(vertexShader);
	// ��֤��ɫ���Ƿ�ɹ�
	int success;
	char infoLog[512];
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		std::cout << "error:" << infoLog << std::endl;
	}

	//Ƭ����ɫ��
	unsigned int FragmentShader;
	FragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(FragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(FragmentShader);
	// ��֤��ɫ���Ƿ�ɹ�
	int fragmentsuccess;
	char fragmentinfoLog[512];
	glGetShaderiv(FragmentShader, GL_COMPILE_STATUS, &fragmentsuccess);
	if (!fragmentsuccess)
	{
		glGetShaderInfoLog(FragmentShader, 512, NULL, fragmentinfoLog);
		std::cout << "fragmenterror:" << fragmentinfoLog << std::endl;
	}

	// �����������������ɫ��
	unsigned int shaderProgram;
	shaderProgram = glCreateProgram();

	// ����������ɫ��
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, FragmentShader);
	glLinkProgram(shaderProgram);


	// attatch֮��Ϳ���ɾ����ɫ����
	glDeleteShader(vertexShader);
	glDeleteShader(FragmentShader);


	// ����VAO
	unsigned int VAO;
	unsigned int VBO;
	unsigned int EBO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &EBO);
	glGenBuffers(1, &VBO); //���ɴ洢����
	glBindVertexArray(VAO);
	//��������������
	//// �Ѷ������鸴�Ƶ������й�openglʹ�� 
	glBindBuffer(GL_ARRAY_BUFFER, VBO); // ���������
	glBufferData(GL_ARRAY_BUFFER, sizeof(rectvertices), rectvertices, GL_STATIC_DRAW);  // �û����ݸ�������������

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	// ��������
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

/*

	//// bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
	//glBindVertexArray(VAO);
	//glBindBuffer(GL_ARRAY_BUFFER, VBO); // ���������
	//glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);  // �û����ݸ�������������
	//// ���ö�������ָ��
	//// ��ô������������
	//glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	//glEnableVertexAttribArray(0);
*/


/*
	//EBO�ı���
*/
	//glUseProgram(shaderProgram);
	//glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNALED, 0);
	//��������
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
		glfwPollEvents(); //�����¼�����
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
