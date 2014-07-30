#define GLFW_DLL
#define GLEW_STATIC

#include <GL/glfw.h>
#include <cstdlib>

void drawpoint()
{
	static const GLfloat vtx[] = {0.0f, 0.0f};
	glVertexPointer(2, GL_FLOAT, 0, vtx);
	glPointSize(40.0f);
	glColor4f(1.0f, 1.0f, 1.0f, 10.f);

//	glEnable(GL_POINT_SMOOTH_);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glEnableClientState(GL_VERTEX_ARRAY);
	glDrawArrays(GL_POINTS, 0, 1);

	glDisableClientState(GL_VERTEX_ARRAY);

	glDisable(GL_POINT_SMOOTH);
	glDisable(GL_BLEND);
	
}

void drawline()
{
	static const GLfloat vtx[] = {
		-0.25f, -0.25f,
		0.25f, 0.25f};

	glVertexPointer(2, GL_FLOAT, 0, vtx);
	glLineWidth(20.0f);
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);

	glEnable(GL_LINE_SMOOTH);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA,
				GL_ONE_MINUS_SRC_ALPHA);

	glEnableClientState(GL_VERTEX_ARRAY);
	glDrawArrays(GL_LINES, 0, 2);
	glDisableClientState(GL_VERTEX_ARRAY);
	glDisable(GL_LINE_SMOOTH);
	glDisable(GL_BLEND);
	
}

void drawlinestipple()
{
	static const GLfloat vtx[] = {
		-0.5f, -0.0f,
		0.5f, 0.0f};

	glVertexPointer(2, GL_FLOAT, 0, vtx);
	glLineWidth(10.0f);
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	glEnable(GL_LINE_STIPPLE);
	glLineStipple(1, 0x1234);

	glEnableClientState(GL_VERTEX_ARRAY);
	glDrawArrays(GL_LINES, 0, 2);

	glDisableClientState(GL_VERTEX_ARRAY);
	glDisable(GL_LINE_STIPPLE);
	
}

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
		glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
		glClear(GL_COLOR_BUFFER_BIT);

//		drawpoint();
//		drawline();
		drawlinestipple();
		glfwSwapBuffers();
	}

	glfwTerminate();

	return EXIT_SUCCESS;
}
