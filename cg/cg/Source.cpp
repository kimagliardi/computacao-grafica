#include <iostream>
#include <string>
#include <assert.h>
#include <GL\glew.h>
#include <GLFW\glfw3.h>
#include "Shader.h"
using namespace std;


// Function prototypes
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);
void drawCircle();
// Window dimensions
const GLuint WIDTH = 800, HEIGHT = 600;


GLuint VBO, VAO;
unsigned int VBOs[2], VAOs[2];
bool circ = false;
bool doubleT = false;
bool triang = false;


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

	Shader vShader("vertex.txt", "fragment.txt");


	// Game loop
	while (!glfwWindowShouldClose(window))
	{
		// Check if any events have been activiated (key pressed, mouse moved etc.) and call corresponding response functions
		glfwPollEvents();
		

		// Render
		// Clear the colorbuffer
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		if(triang == true){
			// Draw our first triangle
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

			
			// end of draw
			vShader.use();
			glBindVertexArray(VAO);
			glDrawArrays(GL_TRIANGLES, 0, 3);
			glBindVertexArray(0);
			glBindVertexArray(1);
			
		}
		if(circ == true) {
			glfwGetFramebufferSize(window, &width, &height);
			glViewport(0, 0, width, height);
			
			glMatrixMode(GL_PROJECTION);
			glLoadIdentity();
			glOrtho(0, 0, 12, 12,0,0);
			glMatrixMode(GL_MODELVIEW);
			glLoadIdentity();
			drawCircle();
		}
		if (doubleT == true) {
			vShader.use();

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

			glGenVertexArrays(2, VAOs); // we can also generate multiple VAOs or buffers at the same time
			glGenBuffers(2, VBOs);
			// first triangle setup
			// --------------------
			glBindVertexArray(VAOs[0]);
			glBindBuffer(GL_ARRAY_BUFFER, VBOs[0]);
			glBufferData(GL_ARRAY_BUFFER, sizeof(firstTriangle), firstTriangle, GL_STATIC_DRAW);
			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);	// Vertex attributes stay the same
			glEnableVertexAttribArray(0);
			// glBindVertexArray(0); // no need to unbind at all as we directly bind a different VAO the next few lines
			// second triangle setup
			// ---------------------
			glBindVertexArray(VAOs[1]);	// note that we bind to a different VAO now
			glBindBuffer(GL_ARRAY_BUFFER, VBOs[1]);	// and a different VBO
			glBufferData(GL_ARRAY_BUFFER, sizeof(secondTriangle), secondTriangle, GL_STATIC_DRAW);
			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0); // because the vertex data is tightly packed we can also specify 0 as the vertex attribute's stride to let OpenGL figure it out
			glEnableVertexAttribArray(0);
			// glBindVertexArray(0); // not really necessary as well, but beware of calls that could affect VAOs while this one is bound (like binding element buffer objects, or enabling/disabling vertex attributes)

			glBindVertexArray(VAOs[0]);
			glDrawArrays(GL_TRIANGLES, 0, 3);
			// then we draw the second triangle using the data from the second VAO
			glBindVertexArray(VAOs[1]);
			glDrawArrays(GL_TRIANGLES, 0, 3);
			glBindVertexArray(0);
			glBindVertexArray(1);

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
		triang = !triang;

	}
	if (key == GLFW_KEY_C && action == GLFW_PRESS) {
		circ = !circ;
	}
	
	if (key == GLFW_KEY_X && action == GLFW_PRESS) {
		doubleT = !doubleT;
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


