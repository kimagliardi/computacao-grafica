#include <iostream>
#include <string>
#include <assert.h>
using namespace std;

// GLEW
//#define GLEW_STATIC -- se habilitar, nao precisa da dll
#include <GL\glew.h>

// GLFW
#include <GLFW\glfw3.h>

// Function prototypes
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);
void drawCircle();
// Window dimensions
const GLuint WIDTH = 800, HEIGHT = 600;
GLuint VBO, VAO;
bool circ = false;
// Shaders | ############### Criar classes e passar para arquivos
const GLchar* vertexShaderSource = "#version 330 core\n"
"layout(location = 0) in vec3 aPos;\n"   // the position variable has attribute position 0
"layout(location = 1) in vec3 aColor;\n" // the color variable has attribute position 1

"out vec3 ourColor;\n" // output a color to the fragment shader

"void main()\n"
"{\n"
	"gl_Position = vec4(aPos, 1.0);\n"
	"ourColor = aColor;\n" // set ourColor to the input color we got from the vertex data
"}\n\0";
const GLchar* fragmentShaderSource = "#version 330\n"
"out vec4 FragColor;\n"
"in vec3 ourColor;"
"void main()\n"
"{\n"
"FragColor = vec4(ourColor, 1.0f);"
"}\n\0";


//"color = inputColor;\n"

// The MAIN function, from here we start the application and run the game loop
int main()
{
	// Init GLFW
	glfwInit();

	// Create a GLFWwindow object that we can use for GLFW's functions
	GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "LearnOpenGL", nullptr, nullptr);
	glfwMakeContextCurrent(window);

	// Set the required callback functions
	glfwSetKeyCallback(window, key_callback);

	// Set this to true so GLEW knows to use a modern approach to retrieving function pointers and extensions
	glewExperimental = GL_TRUE;
	// Initialize GLEW to setup the OpenGL Function pointers
	glewInit();

	/* get version info */
	const GLubyte* renderer = glGetString(GL_RENDERER); /* get renderer string */
	const GLubyte* version = glGetString(GL_VERSION); /* version as a string */
	cout << "Renderer: " << renderer << endl;
	cout << "OpenGL version supported " << version << endl;

	// Define the viewport dimensions
	int width, height;
	glfwGetFramebufferSize(window, &width, &height);
	glViewport(0, 0, width, height);


	// Build and compile our shader program
	// Vertex shader
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader);
	// Check for compile time errors
	GLint success;
	GLchar infoLog[512];
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
	}
	// Fragment shader
	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);
	// Check for compile time errors
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
	}
	// Link shaders
	GLuint shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);
	// Check for linking errors
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
	}
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);



	// Game loop
	while (!glfwWindowShouldClose(window))
	{
		// Check if any events have been activiated (key pressed, mouse moved etc.) and call corresponding response functions
		glfwPollEvents();
		

		// Render
		// Clear the colorbuffer
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		if(circ == false){
			// Draw our first triangle
			glUseProgram(shaderProgram);
			glBindVertexArray(VAO);
			glDrawArrays(GL_TRIANGLES, 0, 3);
			glBindVertexArray(0);
			glBindVertexArray(1);
		}
		else {
			glfwGetFramebufferSize(window, &width, &height);
			glViewport(0, 0, width, height);
			
			glMatrixMode(GL_PROJECTION);
			glLoadIdentity();
			glOrtho(0, 0, 12, 12,0,0);
			glMatrixMode(GL_MODELVIEW);
			glLoadIdentity();
			drawCircle();
		}
		// Swap the screen buffers
		glfwSwapBuffers(window);
	}
	// Properly de-allocate all resources once they've outlived their purpose
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	// Terminate GLFW, clearing any resources allocated by GLFW.
	glfwTerminate();
	return 0;
}

// Is called whenever a key is pressed/released via GLFW
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);

	//desenha triangulo..
	if (key == GLFW_KEY_T && action == GLFW_PRESS) {

		// desenhando triangulo
		GLfloat vertices[] = {
			0.0f,0.5f,0.0f,
			0.5f, -0.5f,0.0f,
			-0.5f, -0.5f,0.0f,
		};

		GLfloat colors[] = {
			1.0f, 0.5f, 0.0f,
			0.0f, 1.0f, 0.0f,
			0.0f, 0.0f, 1.0f
		};

		GLuint vVBO;
		glGenBuffers(1, &vVBO);
		glBindBuffer(GL_ARRAY_BUFFER, vVBO);
		glBufferData(GL_ARRAY_BUFFER, 9 * sizeof(GLfloat),
			vertices, GL_STATIC_DRAW);

		GLuint cVBO;
		glGenBuffers(1, &cVBO);
		glBindBuffer(GL_ARRAY_BUFFER, cVBO);
		glBufferData(GL_ARRAY_BUFFER, 9 * sizeof(GLfloat),
			colors, GL_STATIC_DRAW);

		glGenVertexArrays(1, &VAO);
		glBindVertexArray(VAO);

		//incluindo o buffer de vértices
		glBindBuffer(GL_ARRAY_BUFFER, vVBO);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);

		//incluindo o buffer de cores
		glBindBuffer(GL_ARRAY_BUFFER, cVBO);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)(3 * sizeof(float)));
		glEnableVertexAttribArray(1);
		glEnableVertexAttribArray(1);
		//fim do desenho

	}
	if (key == GLFW_KEY_C && action == GLFW_PRESS) {
		circ = !circ;
	}
}

	void drawCircle() {
		const float Pi = 3.14159;
		glPointSize(15);
		glLineWidth(1);
		glColor3f(0, 0, 0);

		GLfloat circle_points = 100;
		GLfloat angle;
			glBegin(GL_POLYGON);
		
		for (int i = 0; i < circle_points; i++) {
			angle = 2* Pi * i / circle_points;
			glVertex2d((cos(angle)), +((sin(angle))));
		}

		glEnd();
	}


