#include <iostream>
#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

float vertices[] = {
	0.5f, 0.5f, 0.0f,   // 右上角
	0.5f, -0.5f, 0.0f,  // 右下角
	-0.5f, -0.5f, 0.0f, // 左下角
	-0.5f, 0.5f, 0.0f   // 左上角
};

unsigned int indices[] = { // 注意索引从0开始! 
	0, 1, 3, // 第一个三角形
	1, 2, 3  // 第二个三角形
};

const char *vertexShaderSource = 
"#version 330 core										\n"
"layout(location = 0) in vec3 aPos;						\n"
"void main()											\n"
"{														\n"
"	gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);	\n"
"}														\n";

const char *fragmentShaderSource =
"#version 330 core								\n"
"out vec4 FragColor;							\n"
"void main()									\n"
"{												\n"
"FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);		\n"
"}												\n";

void processInput(GLFWwindow *window);

int test() 
{
	//printf(fragmentShaderSource);
	//printf(vertexShaderSource);
	//system("pause");
	//return 0;

	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// Open GLEW Window
	GLFWwindow* window = glfwCreateWindow(800, 600, "CreateWin", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);

	// Init GLEW
	glewExperimental = true;
	if (glewInit() != GLEW_OK)
	{
		std::cout << "Init GLEW failed" << std::endl;
		glfwTerminate();
		return -1;
	}

	glViewport(0, 0, 800, 600);
	//glEnable(GL_CULL_FACE);
	//glCullFace(GL_BACK);
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	unsigned int VAO;
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);
	
	unsigned int VBO;
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	 
	unsigned int EBO;
	glGenBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);



	// 顶点着色器
	unsigned int vertexShader;
	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader);

	// 片段着色器
	unsigned int fragmentShader;
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);

	// 着色器程序
	unsigned int shaderProgram;
	shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);

	// 链接顶点
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	while (!glfwWindowShouldClose(window))
	{
		// input
		processInput(window);

		// rendering command
		glClearColor(0.0f, 0.6f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		glBindVertexArray(VAO);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		glUseProgram(shaderProgram);
		//glDrawArrays(GL_TRIANGLES, 0, 6);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

		// swap buffer
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	
	glfwTerminate();
	return 0;
}

void processInput(GLFWwindow *window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}



