#define GLFW_DLL

#include <GL/glfw.h>
#include <cstdlib>

int main()
{
	if (!glfwInit())
		return EXIT_FAILURE;

	if (!glfwOpenWindow(0, 0, 0, 0, 0, 0, 0, 0, GLFW_WINDOW))
	{
		glfwTerminate();
		return EXIT_FAILURE;
	}

	glfwSwapInterval(1);

	while(glfwGetWindowParam(GLFW_OPENED))
	{
		glClearColor(0.0f,	// red:0.0-1.0
					 0.0f,	// green
					 0.0f,	// blue
					 0.0f);	// alpha
		glClear(GL_COLOR_BUFFER_BIT);

		static const GLfloat vtx[] = {-0.5f, -0.5f, 0.5, 0.5};
		glVertexPointer(2,
						GL_FLOAT,
						0,
						vtx);
		glLineWidth(1.0f);
		glColor4f(1.0f,
				  1.0f,
				  1.0f,
				  1.0f);

		glEnableClientState(GL_VERTEX_ARRAY);
		glDrawArrays(GL_LINES,
					 0,
					 2);
		glDisableClientState(GL_VERTEX_ARRAY);
				  
		glfwSwapBuffers();
	}

	glfwTerminate();

	return EXIT_SUCCESS;
}
