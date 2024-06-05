#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
using namespace std;
//创建窗口 

int main()
{

	// 加载glfw窗口
	glfwInit();
	// 给窗口参数
	glfwWindowHint(GLFW_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(800, 800, "Train", NULL, NULL);
	if (!window)
	{
		std::cout << "fail" << std::endl;
		glfwTerminate();
	}
	glfwMakeContextCurrent(window);
	return 0;
}
