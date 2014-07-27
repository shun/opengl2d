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
		glfwSwapBuffers();
	}

	glfwTerminate();

	return EXIT_SUCCESS;
}
