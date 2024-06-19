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

// 着色器
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

const char* fragmentShaderSource2 = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
" FragColor = vec4(0.2f,0.5f,0.2f,1.0f);\n"
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

    // 编译着色器
    // 生成奠定
    unsigned int vertexShader;
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);
    // 编译是否成功
    int success;
    char infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        std::cout << infoLog;
    }
    // 编译片段着色器

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

    unsigned int fragmentShader2;
    fragmentShader2 = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader2, 1, &fragmentShaderSource2,NULL);
    glCompileShader(fragmentShader2);

    int fragmantsuccess1;
    char fragmentinfo2[512];
    glGetShaderiv(fragmentShader2, GL_COMPILE_STATUS, &fragmantsuccess1);
    if(!fragmantsuccess1)
    {
		glGetShaderInfoLog(fragmentShader2, 512, NULL,fragmentinfo2);
        std::cout << fragmentinfo2;
    }

    // 编译链接着色器
    unsigned int shaderprogram;
    shaderprogram = glCreateProgram();

    // 链接两个着色器
    glAttachShader(shaderprogram, vertexShader);
    glAttachShader(shaderprogram, fragmentShader);
    // 链接着色器 ，什么时候切换下来
    glLinkProgram(shaderprogram);

    unsigned int shaderprogram2;
    shaderprogram2 = glCreateProgram();
    // 链接两个着色器
    glAttachShader(shaderprogram2, vertexShader);
    glAttachShader(shaderprogram2, fragmentShader2);
    // 链接着色器 ，什么时候切换下来
    glLinkProgram(shaderprogram2);
    // 程序创建创建玩链接 即可干掉了
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
    glDeleteShader(fragmentShader2);
    // 1
    if (0)
    {

		// 之后就是顶点数据
		unsigned int VAO, VBO;

		glGenVertexArrays(1, &VAO);
		glGenBuffers(1, &VBO);
		// 绑定VAO
		glBindVertexArray(VAO);
		// 绑定缓存数据
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		// 复制用户数据
		glBufferData(GL_ARRAY_BUFFER, sizeof(DoubleTranigleVertices), DoubleTranigleVertices, GL_STATIC_DRAW);

		// 给程序说怎么理解数据
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);
		// location 启动;
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);
		
		// 绘制两个三角形
		while (!glfwWindowShouldClose(window))
		{
			processInput(window);
			glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT);
			// draw out  first triangle
			glUseProgram(shaderprogram);
			glBindVertexArray(VAO); //标记着
			glDrawArrays(GL_TRIANGLES, 0, 6);
			glfwSwapBuffers(window);
			glfwPollEvents();
		}
		glDeleteVertexArrays(1, &VAO);
		glDeleteBuffers(1, &VBO);
		glDeleteProgram(shaderprogram);
		glfwTerminate();
		return 0;
    }

    // 2
    // 使用两个VBO VAO
    if (0)
    {
        float firstTriangle[] = {
			-0.9f, -0.5f, 0.0f,  // left 
			-0.0f, -0.5f, 0.0f,  // right
			-0.45f, 0.5f, 0.0f,  // top 
        };
        float secondTriangle[] = {
            0.0f, -0.5f, 0.0f,  // left
            0.9f, -0.5f, 0.0f,  // right
            0.45f, 0.5f, 0.0f   // top 
        };
        // 一个VAO绑定就是一个顶点数据
        unsigned int VBOs[2], VAOs[2];
        glGenVertexArrays(2, VAOs);
        glGenBuffers(2,VBOs);

        // 然后每次绑定信息 先绑定顶点数据，在绑定附加的数据
        glBindVertexArray(VAOs[0]);
        glBindBuffer(GL_ARRAY_BUFFER, VBOs[0]);
        // 塞入用户指定的数据
        glBufferData(GL_ARRAY_BUFFER, sizeof(firstTriangle), firstTriangle, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);	// Vertex attributes stay the same
        glEnableVertexAttribArray(0);


        glBindVertexArray(VAOs[1]);
        glBindBuffer(GL_ARRAY_BUFFER, VBOs[1]);
        // 塞入用户指定的数据
        glBufferData(GL_ARRAY_BUFFER, sizeof(secondTriangle), secondTriangle, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0); // because the vertex data is tightly packed we can also specify 0 as the vertex attribute's stride to let OpenGL figure it out
        glEnableVertexAttribArray(0);


        // 绘制
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);


		while (!glfwWindowShouldClose(window))
		{
			processInput(window);
			glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT);
			// draw out  first triangle
			glUseProgram(shaderprogram);
			glBindVertexArray(VAOs[0]); //标记着
			glDrawArrays(GL_TRIANGLES, 0, 3);   
            // 绑定完之后就可以那这个顶点进行绘制
			glBindVertexArray(VAOs[1]); //标记着
			glDrawArrays(GL_TRIANGLES, 0, 3);   
			glfwSwapBuffers(window);
			glfwPollEvents();
		}
		glDeleteVertexArrays(2, VAOs);
		glDeleteBuffers(2, VBOs);
		glDeleteProgram(shaderprogram);
		glfwTerminate();
		return 0;
    }

    //3
    if (1)
    {
        float firstTriangle[] = {
            -0.9f, -0.5f, 0.0f,  // left 
            -0.0f, -0.5f, 0.0f,  // right
            -0.45f, 0.5f, 0.0f,  // top 
        };
        float secondTriangle[] = {
            0.0f, -0.5f, 0.0f,  // left
            0.9f, -0.5f, 0.0f,  // right
            0.45f, 0.5f, 0.0f   // top 
        };
        // 一个VAO绑定就是一个顶点数据
        unsigned int VBOs[2], VAOs[2];
        glGenVertexArrays(2, VAOs);
        glGenBuffers(2, VBOs);

        // 然后每次绑定信息 先绑定顶点数据，在绑定附加的数据
        glBindVertexArray(VAOs[0]);
        glBindBuffer(GL_ARRAY_BUFFER, VBOs[0]);
        // 塞入用户指定的数据
        glBufferData(GL_ARRAY_BUFFER, sizeof(firstTriangle), firstTriangle, GL_STATIC_DRAW);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);	// Vertex attributes stay the same
        glEnableVertexAttribArray(0);


        glBindVertexArray(VAOs[1]);
        glBindBuffer(GL_ARRAY_BUFFER, VBOs[1]);
        // 塞入用户指定的数据
        glBufferData(GL_ARRAY_BUFFER, sizeof(secondTriangle), secondTriangle, GL_STATIC_DRAW);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0); // because the vertex data is tightly packed we can also specify 0 as the vertex attribute's stride to let OpenGL figure it out
        glEnableVertexAttribArray(0);


        // 绘制
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);


        while (!glfwWindowShouldClose(window))
        {
            processInput(window);
            glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT);
            // draw out  first triangle
            glUseProgram(shaderprogram);
            glBindVertexArray(VAOs[0]); //标记着
            glDrawArrays(GL_TRIANGLES, 0, 3);
            // 绑定完之后就可以那这个顶点进行绘制
            glUseProgram(shaderprogram2);
            glBindVertexArray(VAOs[1]); //标记着
            glDrawArrays(GL_TRIANGLES, 0, 3);
            glfwSwapBuffers(window);
            glfwPollEvents();
        }
        glDeleteVertexArrays(2, VAOs);
        glDeleteBuffers(2, VBOs);
        glDeleteProgram(shaderprogram);
        glDeleteProgram(shaderprogram2);
        glfwTerminate();
        return 0;
    }



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