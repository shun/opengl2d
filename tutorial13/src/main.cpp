#define GLFW_DLL
#define GLEW_STATIC

#include <GL/glfw.h>
#include <cstdlib>
#include <fstream>
#include <vector>
#include <cmath>
#if defined(__APPLE__)
#include <OpenGL/glext.h>
#endif	// __APPLE__

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

	GLint current_framebuffer;
	glGetIntegerv(GL_FRAMEBUFFER_BINDING, &current_framebuffer);

	GLuint fbo_texture_id;
	glGenTextures(1, &fbo_texture_id);

	glBindTexture(GL_TEXTURE_2D,
				  fbo_texture_id);

	glTexImage2D(GL_TEXTURE_2D,
				 0, GL_RGB, 256, 256,
				 0, GL_RGB,
				 GL_UNSIGNED_BYTE, 0);

	glTexParameteri(GL_TEXTURE_2D,
					GL_TEXTURE_MIN_FILTER,
					GL_LINEAR);
	
	glTexParameteri(GL_TEXTURE_2D,
					GL_TEXTURE_MAG_FILTER,
					GL_LINEAR);

	GLuint framebuffer_id;
	glGenFramebuffers(1, &framebuffer_id);

	glBindFramebuffer(GL_FRAMEBUFFER,
					  framebuffer_id);

	glFramebufferTexture2D(GL_FRAMEBUFFER,
						   GL_COLOR_ATTACHMENT0,
						   GL_TEXTURE_2D,
						   fbo_texture_id,
						   0);
	float angle = 0.0f;
	
	while(glfwGetWindowParam(GLFW_OPENED))
	{

		glBindFramebuffer(GL_FRAMEBUFFER, framebuffer_id);
		glViewport(0, 0, 256, 256);
		
		glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		angle += 0.02f;

		const float xofs = std::sin(angle) * 0.5f;

		const GLfloat vtx[] = {
			-0.5f + xofs, -0.5f,
			0.5f + xofs, -0.5f,
			0.5f + xofs, 0.5f,
			-0.5f + xofs, 0.5f};

		glVertexPointer(2, GL_FLOAT, 0, vtx);
		glColor4f(1.0f, 0.0f, 0.0f, 1.0f);

		glEnableClientState(GL_VERTEX_ARRAY);
		glDrawArrays(GL_QUADS, 0, 4);

		glDisableClientState(GL_VERTEX_ARRAY);

		glBindFramebuffer(GL_FRAMEBUFFER, current_framebuffer);

		glViewport(0, 0, 640, 480);
		glClearColor(0.5f, 0.5f, 0.5f, 0.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		for (int y = 0; y < 3; ++y)
		{
			for (int x = 0; x < 3; ++x)
			{

				float xofs = x * 0.55f - 0.8f;
				float yofs = y * 0.55f - 0.8f;

				const GLfloat vtx2[] = {
					0.0f + xofs, 0.0f + yofs,
					0.5f + xofs, 0.0f + yofs,
					0.5f + xofs, 0.5f + yofs,
					0.0f + xofs, 0.5f + yofs};
				glVertexPointer(2, GL_FLOAT, 0, vtx2);
				glColor4f(1.0f, 1.0f, 1.0f, 1.0f);

				static const GLfloat texture_uv[] = {
					0.0f, 0.0f,
					1.0f, 0.0f,
					1.0f, 1.0f,
					0.0f, 1.0f};

				glTexCoordPointer(2, GL_FLOAT, 0, texture_uv);
				glEnable(GL_TEXTURE_2D);
				glBindTexture(GL_TEXTURE_2D, fbo_texture_id);
				glEnableClientState(GL_VERTEX_ARRAY);
				glEnableClientState(GL_TEXTURE_COORD_ARRAY);
				glDrawArrays(GL_QUADS, 0, 4);
				glDisableClientState(GL_VERTEX_ARRAY);
				glDisableClientState(GL_TEXTURE_COORD_ARRAY);
				glDisable(GL_TEXTURE_2D);
			}
		}
		glfwSwapBuffers();
	}

	glDeleteTextures(1, &fbo_texture_id);
	glDeleteFramebuffers(1, &framebuffer_id);
	glfwTerminate();

	return EXIT_SUCCESS;
}
