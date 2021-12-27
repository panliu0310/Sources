/*
Student ID: 1155127464
Student Name: Liu Hoi Pan
*/

#include "Dependencies/glew/glew.h"
#include "Dependencies/GLFW/glfw3.h"
#include "Dependencies/glm/glm.hpp"
#include "Dependencies/glm/gtc/matrix_transform.hpp"

#include "Shader.h"
#include "Texture.h"

#include <iostream>
#include <fstream>
#include <vector>
#include <map>

// struct for storing the obj file
struct Vertex {
	glm::vec3 position;
	glm::vec2 uv;
	glm::vec3 normal;
};

struct Model {
	std::vector<Vertex> vertices;
	std::vector<unsigned int> indices;
};

Shader shader;

Model dolphinObj;
Model seaObj;

Texture dolphinTexture[2];
Texture seaTexture[2];

//create GLuint dolphinVAO, dolphinEBO
GLuint dolphinVAO;
GLuint dolphinEBO;
GLuint seaVAO;
GLuint seaEBO;

struct keyboardcontroller
{
	int theme_dolphin = 0;
	int theme_sea = 0;
	float intensity = 1.0f;
	float dolphin_translate = 0.0f;
	float dolphin_rotate = 0.0f;
};
keyboardcontroller keyboardCtl;

struct MouseController {
	bool LEFT_BUTTON = false;
	float zoom = 45.0f;
};
MouseController mouseCtl;
const float radius = 15.0f;
float phi = 90.0f; float theta = 90.0f;
float lastX = 0; float lastY = 0;

// screen setting
const int SCR_WIDTH = 800;
const int SCR_HEIGHT = 600;

Model loadOBJ(const char* objPath)
{
	// function to load the obj file
	// Note: this simple function cannot load all obj files.

	struct V {
		// struct for identify if a vertex has showed up
		unsigned int index_position, index_uv, index_normal;
		bool operator == (const V& v) const {
			return index_position == v.index_position && index_uv == v.index_uv && index_normal == v.index_normal;
		}
		bool operator < (const V& v) const {
			return (index_position < v.index_position) ||
				(index_position == v.index_position && index_uv < v.index_uv) ||
				(index_position == v.index_position && index_uv == v.index_uv && index_normal < v.index_normal);
		}
	};

	std::vector<glm::vec3> temp_positions;
	std::vector<glm::vec2> temp_uvs;
	std::vector<glm::vec3> temp_normals;

	std::map<V, unsigned int> temp_vertices;

	Model model;
	unsigned int num_vertices = 0;

	std::cout << "\nLoading OBJ file " << objPath << "..." << std::endl;

	std::ifstream file;
	file.open(objPath);

	// Check for Error
	if (file.fail()) {
		std::cerr << "Impossible to open the file! Do you use the right path? See Tutorial 6 for details" << std::endl;
		exit(1);
	}

	while (!file.eof()) {
		// process the object file
		char lineHeader[128];
		file >> lineHeader;

		if (strcmp(lineHeader, "v") == 0) {
			// geometric vertices
			glm::vec3 position;
			file >> position.x >> position.y >> position.z;
			temp_positions.push_back(position);
		}
		else if (strcmp(lineHeader, "vt") == 0) {
			// texture coordinates
			glm::vec2 uv;
			file >> uv.x >> uv.y;
			temp_uvs.push_back(uv);
		}
		else if (strcmp(lineHeader, "vn") == 0) {
			// vertex normals
			glm::vec3 normal;
			file >> normal.x >> normal.y >> normal.z;
			temp_normals.push_back(normal);
		}
		else if (strcmp(lineHeader, "f") == 0) {
			// Face elements
			V vertices[3];
			for (int i = 0; i < 3; i++) {
				char ch;
				file >> vertices[i].index_position >> ch >> vertices[i].index_uv >> ch >> vertices[i].index_normal;
			}

			// Check if there are more than three vertices in one face.
			std::string redundency;
			std::getline(file, redundency);
			if (redundency.length() >= 5) {
				std::cerr << "There may exist some errors while load the obj file. Error content: [" << redundency << " ]" << std::endl;
				std::cerr << "Please note that we only support the faces drawing with triangles. There are more than three vertices in one face." << std::endl;
				std::cerr << "Your obj file can't be read properly by our simple parser :-( Try exporting with other options." << std::endl;
				exit(1);
			}

			for (int i = 0; i < 3; i++) {
				if (temp_vertices.find(vertices[i]) == temp_vertices.end()) {
					// the vertex never shows before
					Vertex vertex;
					vertex.position = temp_positions[vertices[i].index_position - 1];
					vertex.uv = temp_uvs[vertices[i].index_uv - 1];
					vertex.normal = temp_normals[vertices[i].index_normal - 1];

					model.vertices.push_back(vertex);
					model.indices.push_back(num_vertices);
					temp_vertices[vertices[i]] = num_vertices;
					num_vertices += 1;
				}
				else {
					// reuse the existing vertex
					unsigned int index = temp_vertices[vertices[i]];
					model.indices.push_back(index);
				}
			} // for
		} // else if
		else {
			// it's not a vertex, texture coordinate, normal or face
			char stupidBuffer[1024];
			file.getline(stupidBuffer, 1024);
		}
	}
	file.close();

	std::cout << "There are " << num_vertices << " vertices in the obj file.\n" << std::endl;
	return model;
}

void get_OpenGL_info()
{
	// OpenGL information
	const GLubyte* name = glGetString(GL_VENDOR);
	const GLubyte* renderer = glGetString(GL_RENDERER);
	const GLubyte* glversion = glGetString(GL_VERSION);
	std::cout << "OpenGL company: " << name << std::endl;
	std::cout << "Renderer name: " << renderer << std::endl;
	std::cout << "OpenGL version: " << glversion << std::endl;
}

void sendDataToOpenGL()
{
	//TODO
	//Load objects and bind to VAO and VBO
	dolphinObj = loadOBJ("resources/dolphin/dolphin.obj");
	seaObj = loadOBJ("resources/sea/sea.obj");

	//Load textures
	dolphinTexture[0].setupTexture("resources/dolphin/dolphin_01.jpg");
	dolphinTexture[1].setupTexture("resources/dolphin/dolphin_02.jpg");
	seaTexture[0].setupTexture("resources/sea/sea_01.jpg");
	seaTexture[1].setupTexture("resources/sea/sea_02.jpg");

	// dolphin

	// vertex array 
	glGenVertexArrays(1, &dolphinVAO);
	glBindVertexArray(dolphinVAO);

	// vertex buffer
	GLuint vboID;
	glGenBuffers(1, &vboID);
	glBindBuffer(GL_ARRAY_BUFFER, vboID);
	glBufferData(GL_ARRAY_BUFFER, dolphinObj.vertices.size() * sizeof(Vertex), &dolphinObj.vertices[0], GL_STATIC_DRAW);

	//vertex position
	glEnableVertexAttribArray(0); glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, position));
	//uv coordinates
	glEnableVertexAttribArray(1); glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, uv));
	//normal coordinates
	glEnableVertexAttribArray(2); glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, normal));
	glGenBuffers(1, &dolphinEBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, dolphinEBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, dolphinObj.indices.size() * sizeof(unsigned int), &dolphinObj.indices[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	// sea

	// vertex array 
	glGenVertexArrays(1, &seaVAO);
	glBindVertexArray(seaVAO);

	// vertex buffer
	GLuint vboID2;
	glGenBuffers(1, &vboID2);
	glBindBuffer(GL_ARRAY_BUFFER, vboID2);
	glBufferData(GL_ARRAY_BUFFER, seaObj.vertices.size() * sizeof(Vertex), &seaObj.vertices[0], GL_STATIC_DRAW);

	//vertex position
	glEnableVertexAttribArray(0); glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, position));
	//uv coordinates
	glEnableVertexAttribArray(1); glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, uv));
	//normal coordinates
	glEnableVertexAttribArray(2); glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, normal));
	glGenBuffers(1, &seaEBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, seaEBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, seaObj.indices.size() * sizeof(unsigned int), &seaObj.indices[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void initializedGL(void) //run only once
{
	if (glewInit() != GLEW_OK) {
		std::cout << "GLEW not OK." << std::endl;
	}

	get_OpenGL_info();
	sendDataToOpenGL();

	//TODO: set up the camera parameters	
	//TODO: set up the vertex shader and fragment shader
	shader.setupShader("VertexShaderCode.glsl", "FragmentShaderCode.glsl");
	shader.use();//Important! the shader is shader instance you create

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
}

void paintGL(void)  //always run
{
	glClearColor(1.0f, 1.0f, 1.0f, 0.5f); //specify the background color, this is just an example
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//TODO:
	//Set lighting information, such as position and color of lighting source
	//shader.setMat4 / setInt / setVec3...; //general setting of your shaders, like transformation matrixes

	// dolphin
	glm::vec3 eyePosition(0.0f, 0.0f, 0.0f);
	shader.setVec3("eyePositionWorld", eyePosition);
	glm::vec3 lightPosition(2.0f, 15.0f, 5.0f);
	shader.setVec3("dirlight.direction", lightPosition);
	shader.setFloat("dirlight.intensity", keyboardCtl.intensity);
	shader.setVec3("dirlight.ambient", glm::vec3(0.1f, 0.1f, 0.1f));
	shader.setVec3("dirlight.diffuse", glm::vec3(1.0f, 1.0f, 1.0f));
	shader.setVec3("dirlight.specular", glm::vec3(0.3f, 0.3f, 0.3f));
	shader.setVec3("pointlight.position", glm::vec3(5.0f, 10.0f, 2.0f));
	shader.setFloat("pointlight.constant", 1.0f);
	shader.setFloat("pointlight.linear", 0.5f);
	shader.setFloat("pointlight.quadratic", 0.5f);
	shader.setVec3("pointlight.ambient", glm::vec3(0.1f, 0.1f, 0.1f));
	shader.setVec3("pointlight.diffuse", glm::vec3(1.0f, 1.0f, 1.0f));
	shader.setVec3("pointlight.specular", glm::vec3(0.3f, 0.3f, 0.3f));
	shader.setFloat("material.shininess", 32.0f);

	//Set transformation matrix

	glm::mat4 scaleMatrix_dolphin = glm::scale(glm::mat4(1.0f), glm::vec3(0.01f, 0.01f, 0.01f));
	glm::mat4 rotationMatrix_dolphin = glm::rotate(glm::mat4(1.0f), keyboardCtl.dolphin_rotate, glm::vec3(0, 1, 0)) * glm::rotate(glm::mat4(1.0f), glm::radians(-90.0f), glm::vec3(1, 0, 0));
	glm::mat4 modelTransformMatrix_dolphin = glm::translate(glm::mat4(1.0f), glm::vec3(keyboardCtl.dolphin_translate * sin((keyboardCtl.dolphin_rotate)), 0.0f, keyboardCtl.dolphin_translate * cos(keyboardCtl.dolphin_rotate)));
	
	glm::vec3 cameraPos = glm::vec3(radius * cos(glm::radians(theta)) * sin(glm::radians(phi)), radius * cos(glm::radians(phi)), radius * sin(glm::radians(phi)) * sin(glm::radians(theta)));
	glm::vec3 cameraTarget = glm::vec3(0.0f, 1.0f, 0.0f);
	glm::vec3 cameraDirection = glm::normalize(cameraPos - cameraTarget);
	glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
	glm::mat4 viewMatrix = glm::lookAt(cameraPos, cameraTarget, cameraUp);
	
	glm::mat4 projectionMatrix = glm::perspective(glm::radians(mouseCtl.zoom), +8.0f / +6.0f, 1.0f, 100.0f);
	shader.setMat4("scaleMatrix", scaleMatrix_dolphin);
	shader.setMat4("rotationMatrix", rotationMatrix_dolphin);
	shader.setMat4("modelTransformMatrix", modelTransformMatrix_dolphin);
	shader.setMat4("viewMatrix", viewMatrix);
	shader.setMat4("projectionMatrix", projectionMatrix);

	//Bind different textures
	
	dolphinTexture[keyboardCtl.theme_dolphin].bind(0);  //index 0 for example
	glBindVertexArray(dolphinVAO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, dolphinEBO);
	glDrawElements(GL_TRIANGLES, dolphinObj.indices.size(), GL_UNSIGNED_INT, 0); //render primitives from array data

	// sea

	shader.setVec3("dirlight.direction", lightPosition);
	shader.setVec3("eyePositionWorld", eyePosition);
	shader.setFloat("dirlight.intensity", keyboardCtl.intensity);
	shader.setVec3("dirlight.ambient", glm::vec3(0.1f, 0.1f, 0.1f));
	shader.setVec3("dirlight.diffuse", glm::vec3(1.0f, 1.0f, 1.0f));
	shader.setVec3("dirlight.specular", glm::vec3(0.3f, 0.3f, 0.3f));
	shader.setVec3("pointlight.position", glm::vec3(5.0f, 5.0f, 5.0f));
	shader.setFloat("pointlight.constant", 1.0f);
	shader.setFloat("pointlight.linear", 0.5f);
	shader.setFloat("pointlight.quadratic", 0.5f);
	shader.setVec3("pointlight.ambient", glm::vec3(0.1f, 0.1f, 0.1f));
	shader.setVec3("pointlight.diffuse", glm::vec3(1.0f, 1.0f, 1.0f));
	shader.setVec3("pointlight.specular", glm::vec3(0.3f, 0.3f, 0.3f));
	shader.setFloat("material.shininess", 32.0f);

	glm::mat4 scaleMatrix_sea = glm::scale(glm::mat4(1.0f), glm::vec3(1.0f, 1.0f, 1.0f));
	glm::mat4 rotationMatrix_sea = glm::rotate(glm::mat4(1.0f), 0.0f, glm::vec3(0, 0, 1));
	glm::mat4 modelTransformMatrix_sea = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f));;
	shader.setMat4("scaleMatrix", scaleMatrix_sea);
	shader.setMat4("rotationMatrix", rotationMatrix_sea);
	shader.setMat4("modelTransformMatrix", modelTransformMatrix_sea);
	shader.setMat4("viewMatrix", viewMatrix);
	shader.setMat4("projectionMatrix", projectionMatrix);

	seaTexture[keyboardCtl.theme_sea].bind(0);
	glBindVertexArray(seaVAO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, seaEBO);
	glDrawElements(GL_TRIANGLES, seaObj.indices.size(), GL_UNSIGNED_INT, 0);

}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
	if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
	{
		mouseCtl.LEFT_BUTTON = true;
	}
	if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_RELEASE)
	{
		mouseCtl.LEFT_BUTTON = false;
	}
}

void cursor_position_callback(GLFWwindow* window, double x, double y)
{
	if (mouseCtl.LEFT_BUTTON)
	{
		float xoffset = float(x - lastX);
		float yoffset = float(lastY - y);
		const float sensitivity = 0.1f;
		xoffset *= sensitivity;
		yoffset *= sensitivity;

		theta += xoffset;
		phi += yoffset;

		if (phi > 180.0f)
			phi = 180.0f;
		if (phi < 0.0f)
			phi = 0.0f;
	}
	lastX = x;
	lastY = y;
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	if (mouseCtl.zoom >= 1.0f && mouseCtl.zoom <= 45.0f)
		mouseCtl.zoom -= yoffset;
	if (mouseCtl.zoom <= 1.0f)
		mouseCtl.zoom = 1.0f;
	if (mouseCtl.zoom >= 45.0f)
		mouseCtl.zoom = 45.0f;
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, true);
	}
	// Lighting control
	if (key == GLFW_KEY_W && action == GLFW_PRESS)
	{
		if (keyboardCtl.intensity < 2)
			keyboardCtl.intensity *= 1.1;
	}
	if (key == GLFW_KEY_S && action == GLFW_PRESS)
	{
		if (keyboardCtl.intensity > 0.5)
			keyboardCtl.intensity *= 0.9;
	}
	// Texture control
	if (key == GLFW_KEY_1 && action == GLFW_PRESS)
	{
		keyboardCtl.theme_dolphin = 0;
	}
	if (key == GLFW_KEY_2 && action == GLFW_PRESS)
	{
		keyboardCtl.theme_dolphin = 1;
	}
	if (key == GLFW_KEY_3 && action == GLFW_PRESS)
	{
		keyboardCtl.theme_sea = 0;
	}
	if (key == GLFW_KEY_4 && action == GLFW_PRESS)
	{
		keyboardCtl.theme_sea = 1;
	}
	// Object control
	if (key == GLFW_KEY_UP && action == GLFW_PRESS)
	{
		keyboardCtl.dolphin_translate += 0.1f;
	}
	if (key == GLFW_KEY_DOWN && action == GLFW_PRESS)
	{
		keyboardCtl.dolphin_translate -= 0.1f;
	}
	if (key == GLFW_KEY_LEFT && action == GLFW_PRESS)
	{
		keyboardCtl.dolphin_rotate += 0.1f;
	}
	if (key == GLFW_KEY_RIGHT && action == GLFW_PRESS)
	{
		keyboardCtl.dolphin_rotate -= 0.1f;
	}
}

int main(int argc, char* argv[])
{
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
	window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Assignment 2", NULL, NULL);
	if (!window) {
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}

	/* Make the window's context current */
	glfwMakeContextCurrent(window);

	/*register callback functions*/
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	glfwSetKeyCallback(window, key_callback);
	glfwSetScrollCallback(window, scroll_callback);
	glfwSetCursorPosCallback(window, cursor_position_callback);
	glfwSetMouseButtonCallback(window, mouse_button_callback);

	initializedGL();

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