#define GLFW_DLL


#include <GL/glfw.h>
#include <cstdlib>
#include <fstream>
#include <vector>

int main()
{
	if (!glfwInit())
		return EXIT_FAILURE;

	if (!glfwOpenWindow(640, 480, 0, 0, 0, 0, 0, 0, GLFW_WINDOW))
	{
		glfwTerminate();
		return EXIT_FAILURE;
	}

	glfwSwapInterval(1);

	float posx = 0.0f;
	float posy = 0.0f;
	
	while(glfwGetWindowParam(GLFW_OPENED))
	{
		if (glfwGetKey(GLFW_KEY_ESC) == GLFW_PRESS)
			break;
		
		if (glfwGetKey('A') == GLFW_PRESS)
			posx -= 0.02f;
		if (glfwGetKey('D') == GLFW_PRESS)
			posx += 0.02;
		if (glfwGetKey('W') == GLFW_PRESS)
			posy += 0.02f;
		if (glfwGetKey('X') == GLFW_PRESS)
			posy -=0.02f;

		if (glfwGetMouseButton(GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
		{
			int mousex, mousey;
			glfwGetMousePos(&mousex, &mousey);

			posx = mousex * 2.0f / 640.0f - 1.0f;
			posy = -(mousey * 2.0f / 480.0f - 1.0f);
		}

		glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		const GLfloat vtx[] = {
			posx, posy};

		glVertexPointer(2, GL_FLOAT, 0, vtx);
		glPointSize(5.0f);
		glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
		glEnableClientState(GL_VERTEX_ARRAY);
		glDrawArrays(GL_POINTS, 0, 1);

		glDisableClientState(GL_VERTEX_ARRAY);
		glfwSwapBuffers();
				
	}

	glfwTerminate();

	return EXIT_SUCCESS;
}
