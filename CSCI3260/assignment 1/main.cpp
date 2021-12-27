/*
Type your name and student ID here
	- Name: Liu Hoi Pan
	- Student ID: 1155127464
*/

#include "Dependencies/glew/glew.h"
#include "Dependencies/GLFW/glfw3.h"

#include "Dependencies/glm/glm.hpp"
#include "Dependencies/glm/gtc/matrix_transform.hpp"

#include <iostream>
#include <fstream>


GLint programID;
float s = 1.0f;// scaling
float theta = 0.0f;// rotation
float dx = 0.0f;// translation
float dy = 0.0f;
float dz = 0.0f;
float view = 0.0f;// viewPoint

GLuint vao[3];
GLuint vbo[3];

void get_OpenGL_info() {
	// OpenGL information
	const GLubyte* name = glGetString(GL_VENDOR);
	const GLubyte* renderer = glGetString(GL_RENDERER);
	const GLubyte* glversion = glGetString(GL_VERSION);
	std::cout << "OpenGL company: " << name << std::endl;
	std::cout << "Renderer name: " << renderer << std::endl;
	std::cout << "OpenGL version: " << glversion << std::endl;
}

bool checkStatus(
	GLuint objectID,
	PFNGLGETSHADERIVPROC objectPropertyGetterFunc,
	PFNGLGETSHADERINFOLOGPROC getInfoLogFunc,
	GLenum statusType)
{
	GLint status;
	objectPropertyGetterFunc(objectID, statusType, &status);
	if (status != GL_TRUE)
	{
		GLint infoLogLength;
		objectPropertyGetterFunc(objectID, GL_INFO_LOG_LENGTH, &infoLogLength);
		GLchar* buffer = new GLchar[infoLogLength];

		GLsizei bufferSize;
		getInfoLogFunc(objectID, infoLogLength, &bufferSize, buffer);
		std::cout << buffer << std::endl;

		delete[] buffer;
		return false;
	}
	return true;
}

bool checkShaderStatus(GLuint shaderID) {
	return checkStatus(shaderID, glGetShaderiv, glGetShaderInfoLog, GL_COMPILE_STATUS);
}

bool checkProgramStatus(GLuint programID) {
	return checkStatus(programID, glGetProgramiv, glGetProgramInfoLog, GL_LINK_STATUS);
}

std::string readShaderCode(const char* fileName) {
	std::ifstream meInput(fileName);
	if (!meInput.good()) {
		std::cout << "File failed to load ... " << fileName << std::endl;
		exit(1);
	}
	return std::string(
		std::istreambuf_iterator<char>(meInput),
		std::istreambuf_iterator<char>()
	);
}

void installShaders() {
	GLuint vertexShaderID = glCreateShader(GL_VERTEX_SHADER);
	GLuint fragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);

	const GLchar* adapter[1];
	//adapter[0] = vertexShaderCode;
	std::string temp = readShaderCode("VertexShaderCode.glsl");
	adapter[0] = temp.c_str();
	glShaderSource(vertexShaderID, 1, adapter, 0);
	//adapter[0] = fragmentShaderCode;
	temp = readShaderCode("FragmentShaderCode.glsl");
	adapter[0] = temp.c_str();
	glShaderSource(fragmentShaderID, 1, adapter, 0);

	glCompileShader(vertexShaderID);
	glCompileShader(fragmentShaderID);

	if (!checkShaderStatus(vertexShaderID) || !checkShaderStatus(fragmentShaderID))
		return;

	programID = glCreateProgram();
	glAttachShader(programID, vertexShaderID);
	glAttachShader(programID, fragmentShaderID);
	glLinkProgram(programID);

	if (!checkProgramStatus(programID))
		return;

	glDeleteShader(vertexShaderID);
	glDeleteShader(fragmentShaderID);

	glUseProgram(programID);
}

void sendDataToOpenGL() {
	// TODO:
	// create 2D objects and 3D objects and/or lines (points) here and bind to VAOs & VBOs
	// tutorial 4 problem 1 #1 
	// vao[0] refers to 2D island
	// without indexing
	const GLfloat island[] =
	{
		+0.5f,+0.5f,-0.4f,   // position 0
		+0.68f,+1.0f,+0.18f, // color
		+3.0f,+0.5f,-0.4f,   // position 1
		+0.68f,+1.0f,+0.18f, // color
		+0.5f,+3.0f,-0.4f,   // position 3
		+0.68f,+1.0f,+0.18f, // color

		+3.0f,+0.5f,-0.4f,   // position 1
		+0.68f,+1.0f,+0.18f, // color
		+3.0f,+3.0f,-0.4f,   // position 2
		+0.68f,+1.0f,+0.18f, // color
		+0.5f,+3.0f,-0.4f,   // position 3
		+0.68f,+1.0f,+0.18f, // color
	};

	glGenVertexArrays(1, &vao[0]);
	glBindVertexArray(vao[0]);
	glGenBuffers(1, &vbo[0]);
	glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(island), island, GL_STATIC_DRAW);
	// vertex position
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), 0);
	// vertex color
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (char*)(3 * sizeof(GLfloat)));
	
	// tutorial 4 problem 1 #3
	// vao[1] refers to fish
	// with indexing (tutorial 4 problem 2)

	const GLfloat fishvertex[] =
	{
		-0.4f, +0.0f, +0.0f, // position 0
		+0.1f, -0.4f, +0.2f, // position 1
		+0.1f, +0.4f, +0.2f, // position 2
		+0.1f, +0.4f, -0.2f, // position 3
		+0.1f, -0.4f, -0.2f, // position 4

	};
	const GLfloat fishcolor[] =
	{
		+0.0f, +1.0f, +0.0f,
		+0.0f, +1.0f, +0.0f,
		+0.0f, +0.0f, +1.0f,
		+0.0f, +0.0f, +1.0f,
		+1.0f, +0.0f, +0.0f,
		+1.0f, +0.0f, +0.0f,
	};
	GLushort fishindices[] = { 
		0,1,2,
		0,1,4,
		0,2,3,
		0,3,4,
		1,2,4,
		3,2,4,
	};
	glGenVertexArrays(1, &vao[1]);
	glBindVertexArray(vao[1]);
	glGenBuffers(1, &vbo[1]);
	glBindBuffer(GL_ARRAY_BUFFER, vbo[1]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(fishvertex) + sizeof(fishcolor),
				NULL, GL_STATIC_DRAW);
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(fishvertex), fishvertex);// SubData of Position
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(fishvertex), sizeof(fishcolor), fishcolor);// SubData of Color

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (char*)(sizeof(fishcolor)));

	//tutorial 4 problem 2 solution: use vbo_idx;
	GLuint vbo_idx;
	glGenBuffers(1, &vbo_idx);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vbo_idx);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(fishindices), fishindices, GL_STATIC_DRAW);

	// vao[2] refers to tree
	const GLfloat treevertex[] =
	{
		+1.5f, +1.5f, -0.4f,   // position 0
		+2.0f, +1.5f, -0.4f,   // position 1
		+2.0f, +2.0f, -0.4f,   // position 2
		+1.5f, +2.0f, -0.4f,   // position 3
		+1.5f, +1.5f, +1.0f,   // position 4
		+2.0f, +1.5f, +1.0f,   // position 5
		+2.0f, +2.0f, +1.0f,   // position 6
		+1.5f, +2.0f, +1.0f,   // position 7
		+1.0f, +1.75f, +0.9f,  // position 8
		+2.5f, +1.75f, +0.9f,  // position 9
		+1.75f, +1.75f, +1.5f, // position 10
	};
	const GLfloat treecolor[] =
	{
		+0.55f, +0.27f, +0.07f,
		+0.55f, +0.27f, +0.07f,
		+0.55f, +0.27f, +0.07f,
		+0.55f, +0.27f, +0.07f,
		+0.55f, +0.27f, +0.07f,
		+0.55f, +0.27f, +0.07f,
		+0.55f, +0.27f, +0.07f,
		+0.55f, +0.27f, +0.07f,
		+0.55f, +0.27f, +0.07f,
		+0.55f, +0.27f, +0.07f,
		+0.0f, +1.0f, +0.0f,
	};
	GLshort treeindices[]
	{
		0,1,3,
		1,2,3,
		0,4,3,
		3,4,7,
		0,1,4,
		1,5,4,
		0,2,5,
		2,5,6,
		3,2,7,
		2,6,7,
		8,9,10,
	};
	glGenVertexArrays(1, &vao[2]);
	glBindVertexArray(vao[2]);
	glGenBuffers(1, &vbo[2]);
	glBindBuffer(GL_ARRAY_BUFFER, vbo[2]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(treevertex) + sizeof(treecolor),
		NULL, GL_STATIC_DRAW);
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(treevertex), treevertex);// SubData of Position
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(treevertex), sizeof(treecolor), treecolor);// SubData of Color

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (char*)(sizeof(treecolor)));

	GLuint vbo_idx2;
	glGenBuffers(1, &vbo_idx2);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vbo_idx2);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(treeindices), treeindices, GL_STATIC_DRAW);
}

void paintGL(void) {
	// always run
	// TODO:
	glClearColor(0.0f, 0.8f, 1.0f, 1.0f);
	glEnable(GL_DEPTH_TEST);
	glClear(GL_COLOR_BUFFER_BIT
			|GL_DEPTH_BUFFER_BIT);

	GLint scaleMatrixUniformLocation =
		glGetUniformLocation(programID, "scaleMatrix");
	GLint rotationMatrixUniformLocation =
		glGetUniformLocation(programID, "rotationMatrix");
	GLint modelTransformMatrixUniformLocation =
		glGetUniformLocation(programID, "modelTransformMatrix");
	GLint viewMatrixUniformLocation =
		glGetUniformLocation(programID, "viewMatrix");
	GLint projectionMatrixUniformLocation =
		glGetUniformLocation(programID, "projectionMatrix");

	glBindVertexArray(vao[0]);

	// scaling for vao[0] (never scale)
	glm::mat4 scaleMatrixvao0 = glm::scale(glm::mat4(1.0f), glm::vec3(1, 1, 1));
	glUniformMatrix4fv(scaleMatrixUniformLocation, 1,
		GL_FALSE, &scaleMatrixvao0[0][0]);

	// rotation for vao[0] (never totate)
	glm::mat4 rotationMatrixvao0 = glm::rotate(glm::mat4(1.0f), 0.0f, glm::vec3(0,0,1));
	glUniformMatrix4fv(rotationMatrixUniformLocation, 1,
		GL_FALSE, &rotationMatrixvao0[0][0]);

	// translation for vao[0] (never translate)
	glm::mat4 modelTransformMatrixvao0  = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f));;
	glUniformMatrix4fv(modelTransformMatrixUniformLocation, 1,
		GL_FALSE, &modelTransformMatrixvao0[0][0]);

	// modelView for vao[0]
	glm::mat4 viewMatrixvao0 = glm::lookAt(glm::vec3(0.0f, 0.0f - view, 5.0f - view),
		glm::vec3(0.0f, 0.0f + view, 0.0f),
		glm::vec3(0.0f, 1.0f, 0.0f));
	glUniformMatrix4fv(viewMatrixUniformLocation, 1, GL_FALSE, &viewMatrixvao0[0][0]);
	
	// projection for vao[0]
	glm::mat4 projectionMatrixvao0 = glm::perspective(glm::radians(45.0f), +8.0f/+6.0f, 1.0f, 100.0f);
	glUniformMatrix4fv(projectionMatrixUniformLocation, 1,
		GL_FALSE, &projectionMatrixvao0[0][0]);

	glDrawArrays(GL_TRIANGLES, 0, 6);

	glBindVertexArray(vao[1]);

	// scaling for vao[1]
	glm::mat4 scaleMatrixvao1 = glm::scale(glm::mat4(1.0f), glm::vec3(s, s, s));
	glUniformMatrix4fv(scaleMatrixUniformLocation, 1,
		GL_FALSE, &scaleMatrixvao1[0][0]);

	// rotation for vao[1]
	glm::mat4 rotationMatrixvao1 = glm::rotate(glm::mat4(1.0f), glm::radians(theta), glm::vec3(0, 0, 1));
	glUniformMatrix4fv(rotationMatrixUniformLocation, 1,
		GL_FALSE, &rotationMatrixvao1[0][0]);

	// translation for vao[1]
	glm::mat4 modelTransformMatrixvao1 = glm::translate(glm::mat4(1.0f), glm::vec3(dx, dy, dz));;
	glUniformMatrix4fv(modelTransformMatrixUniformLocation, 1,
		GL_FALSE, &modelTransformMatrixvao1[0][0]);

	// ModelView for vao[1] (same as vao[0])
	
	glUniformMatrix4fv(viewMatrixUniformLocation, 1, GL_FALSE, &viewMatrixvao0[0][0]);

	// Projection for vao[1] (same as vao[0])

	glUniformMatrix4fv(projectionMatrixUniformLocation, 1,
		GL_FALSE, &projectionMatrixvao0[0][0]);

	glDrawElements(GL_TRIANGLES, 18, GL_UNSIGNED_SHORT, 0);

	glBindVertexArray(vao[2]);

	// scaling for vao[2] (same as vao[0])
	glUniformMatrix4fv(scaleMatrixUniformLocation, 1,
		GL_FALSE, &scaleMatrixvao0[0][0]);

	// rotation for vao[2] (same as vao[0])
	glUniformMatrix4fv(rotationMatrixUniformLocation, 1,
		GL_FALSE, &rotationMatrixvao0[0][0]);

	// translation for vao[2] (same as vao[0])
	glUniformMatrix4fv(modelTransformMatrixUniformLocation, 1,
		GL_FALSE, &modelTransformMatrixvao0[0][0]);

	// ModelView for vao[2] (same as vao[0])
	
	glUniformMatrix4fv(viewMatrixUniformLocation, 1, GL_FALSE, &viewMatrixvao0[0][0]);

	// Projection for vao[2] (same as vao[0])
	
	glUniformMatrix4fv(projectionMatrixUniformLocation, 1,
		GL_FALSE, &projectionMatrixvao0[0][0]);

	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_SHORT, 0);
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
	// TODO:
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
	
	if (key == GLFW_KEY_E && action == GLFW_PRESS)s += 0.1f;// scale
	if (key == GLFW_KEY_R && action == GLFW_PRESS)s -= 0.1f;

	if (key == GLFW_KEY_F && action == GLFW_PRESS)theta += 10.0f;// rotate
	if (key == GLFW_KEY_G && action == GLFW_PRESS)theta -= 10.0f;

	if (key == GLFW_KEY_A && action == GLFW_PRESS)dx -= 0.1f;// translate
	if (key == GLFW_KEY_D && action == GLFW_PRESS)dx += 0.1f;
	if (key == GLFW_KEY_S && action == GLFW_PRESS)dy -= 0.1f;
	if (key == GLFW_KEY_W && action == GLFW_PRESS)dy += 0.1f;
	if (key == GLFW_KEY_Z && action == GLFW_PRESS)dz += 0.1f;
	if (key == GLFW_KEY_X && action == GLFW_PRESS)dz -= 0.1f;

	if (key == GLFW_KEY_V && action == GLFW_PRESS)view += 0.1f;
	if (key == GLFW_KEY_B && action == GLFW_PRESS)view -= 0.1f;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);
}

void initializedGL(void) {
	// run only once
	// TODO:
	sendDataToOpenGL();
	installShaders();
}

int main(int argc, char* argv[]) {
	GLFWwindow* window;

	/* Initialize the glfw */
	if (!glfwInit()) {
		std::cout << "Failed to initialize GLFW" << std::endl;
		return -1;
	}
	/* glfw: configure; necessary for MAC */
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

	/* Create a windowed mode window and its OpenGL context */
	window = glfwCreateWindow(800, 600, "Assignment 1", NULL, NULL);
	if (!window) {
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}

	/* Make the window's context current */
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	glfwSetKeyCallback(window, key_callback);

	/* Initialize the glew */
	if (GLEW_OK != glewInit()) {
		std::cout << "Failed to initialize GLEW" << std::endl;
		return -1;
	}
	get_OpenGL_info();
	initializedGL();

	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(window)) {
		/* Render here */
		paintGL();

		/* Swap front and back buffers */
		glfwSwapBuffers(window);

		/* Poll for and process events */
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}